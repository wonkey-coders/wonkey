/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <math.h>

#include "Manager.h"
#include "AudioInterface.h"

#include "DataSource.h"
#include "Exception.h"
#include "FrameQueue.h"
#include "Mutex.h"
#include "Thread.h"
#include "Timer.h"
#include "Utility.h"
#include "VideoClip.h"
#include "VideoFrame.h"

namespace theoraplayer
{
	VideoClip::VideoClip(DataSource* dataSource, OutputMode outputMode, int precachedFramesCount, bool usePotStride) :
		frameQueue(NULL), audioInterface(NULL), stream(NULL), timer(NULL), assignedWorkerThread(NULL), audioMutex(NULL),
		threadAccessMutex(NULL), threadAccessCount(0), useAlpha(false), useStride(false), precachedFramesCount(4), audioGain(1.0f),
		autoRestart(false), outputMode(FORMAT_UNDEFINED), priority(1.0f), duration(-1.0f), frameDuration(0.0f), width(0), height(0),
		stride(0), framesCount(-1), fps(1), endOfFile(false), waitingForCache(false), subFrameX(0), subFrameY(0), subFrameWidth(0),
		subFrameHeight(0), seekFrame(-1), requestedOutputMode(FORMAT_UNDEFINED), firstFrameDisplayed(false), restarted(false), iteration(0),
		playbackIteration(0), droppedFramesCount(0), displayedFramesCount(0)
	{
		this->name = dataSource->toString();
		this->requestedOutputMode = outputMode;
		this->precachedFramesCount = precachedFramesCount;
		this->useStride = usePotStride;
		this->threadAccessMutex = new Mutex();
		this->timer = this->defaultTimer = new Timer();
		this->setOutputMode(outputMode);
	}

	VideoClip::~VideoClip()
	{
		// wait untill a worker thread is done decoding the frame
		Mutex::ScopeLock lock(this->threadAccessMutex);
		delete this->defaultTimer;
		if (this->stream != NULL)
		{
			delete this->stream;
		}
		if (this->frameQueue != NULL)
		{
			delete this->frameQueue;
		}
		if (this->audioInterface != NULL)
		{
			Mutex::ScopeLock audioMutexLock(this->audioMutex); // ensure a thread isn't using this mutex
			delete this->audioInterface; // notify audio interface it's time to call it a day
			audioMutexLock.release();
			delete this->audioMutex;
		}
		lock.release();
		delete this->threadAccessMutex;
	}

	void VideoClip::setAudioInterface(AudioInterface* audioInterface)
	{
		this->audioInterface = audioInterface;
		if (this->audioInterface != NULL && this->audioMutex == NULL)
		{
			this->audioMutex = new Mutex();
		}
		if (this->audioInterface == NULL && this->audioMutex != NULL)
		{
			delete this->audioMutex;
			this->audioMutex = NULL;
		}
	}

	void VideoClip::setTimer(Timer* timer)
	{
		this->timer = (timer == NULL ? this->defaultTimer : timer);
	}

	int VideoClip::getWidth() const
	{
		return (this->useAlpha ? this->width / 2 : this->width);
	}

	int VideoClip::getSubFrameX() const
	{
		return (this->useAlpha ? 0 : this->subFrameX);
	}

	int VideoClip::getSubFrameY() const
	{
		return (this->useAlpha ? 0 : this->subFrameY);
	}

	int VideoClip::getSubFrameWidth() const
	{
		return this->useAlpha ? this->width / 2 : this->subFrameWidth;
	}

	int VideoClip::getSubFrameHeight() const
	{
		return this->useAlpha ? this->height : this->subFrameHeight;
	}

	float VideoClip::getTimePosition() const
	{
		return this->timer->getTime();
	}

	void VideoClip::setAudioGain(float gain)
	{
		if (gain >= 1.0f)
		{
			this->audioGain = 1.0f;
		}
		else if (gain <= 0.0f)
		{
			this->audioGain = 0.0f;
		}
		else
		{
			this->audioGain = gain;
		}
	}

	float VideoClip::getPlaybackSpeed() const
	{
		return this->timer->getSpeed();
	}

	void VideoClip::setPlaybackSpeed(float speed)
	{
		this->timer->setSpeed(speed);
	}

	void VideoClip::setOutputMode(OutputMode value)
	{
		if (value == FORMAT_UNDEFINED)
		{
			throw TheoraplayerException("Invalid output mode: FORMAT_UNDEFINED for video: " + this->name);
		}
		if (this->outputMode == value)
		{
			return;
		}
		this->requestedOutputMode = value;
		this->useAlpha = (value == FORMAT_RGBA || value == FORMAT_ARGB || value == FORMAT_BGRA || value == FORMAT_ABGR ||
			value == FORMAT_GREY3A || value == FORMAT_AGREY3 || value == FORMAT_YUVA || value == FORMAT_AYUV);
		if (this->assignedWorkerThread != NULL)
		{
			Mutex::ScopeLock lock(this->threadAccessMutex);
			// discard current frames and recreate them
			this->frameQueue->setSize(this->frameQueue->getSize());
		}
		this->outputMode = this->requestedOutputMode;
	}

	void VideoClip::setAutoRestart(bool value)
	{
		this->autoRestart = value;
		if (this->autoRestart)
		{
			this->endOfFile = false;
		}
	}

	float VideoClip::getPriorityIndex() const
	{
		float priority = (float)getReadyFramesCount();
		if (this->timer->isPaused())
		{
			priority += this->getPrecachedFramesCount() / 2;
		}
		return priority;
	}

	int VideoClip::getPrecachedFramesCount() const
	{
		return this->frameQueue->getSize();
	}

	void VideoClip::setPrecachedFramesCount(int count)
	{
		if (this->frameQueue->getSize() != count)
		{
			this->frameQueue->setSize(count);
		}
	}

	int VideoClip::getReadyFramesCount() const
	{
		if (this->seekFrame != -1)
		{
			return 0; // clip is about to seek, consider frame queue empty (even though it will be actually emptied upon seek)
		}
		return this->frameQueue->getReadyCount();
	}

	bool VideoClip::isDone() const
	{
		if (this->endOfFile)
		{
			VideoFrame* frame = this->frameQueue->getFirstAvailableFrame();
			if (frame == NULL || frame->timeToDisplay >= this->duration) // in some cases, there could be a diference between the reported video duration and timestamp on the last frame(s)
			{
				return true;
			}
		}
		return false;
	}

	bool VideoClip::isPaused() const
	{
		return this->timer->isPaused();
	}

	bool VideoClip::_isBusy() const
	{
		return (this->assignedWorkerThread != NULL || this->outputMode != this->requestedOutputMode);
	}

	float VideoClip::_getAbsPlaybackTime() const
	{
		return (this->timer->getTime() + this->playbackIteration * this->duration);
	}

	float VideoClip::updateTimerToNextFrame()
	{
		VideoFrame* f = this->frameQueue->getFirstAvailableFrame();
		if (f == NULL)
		{
			return 0.0f;
		}
		float time = f->timeToDisplay - this->timer->getTime();
		if (time <= 0.0f)
		{
			return 0.0f;
		}
		this->_update(time);
		return time;
	}

	VideoFrame* VideoClip::fetchNextFrame()
	{
		VideoFrame* frame = NULL;
		// if we are about to seek, then the current frame queue is invalidated
		// (will be cleared when a worker thread does the actual seek)
		if (this->seekFrame != -1)
		{
			return NULL;
		}
		Mutex::ScopeLock lock(this->frameQueue->getMutex());
		float time = this->_getAbsPlaybackTime();
		this->_discardOutdatedFrames(time);
		frame = this->frameQueue->_getFirstAvailableFrame();
		if (frame != NULL && frame->timeToDisplay + frame->iteration * this->duration > time && this->firstFrameDisplayed)
		{
			frame = NULL; // frame is ready but it's not yet time to display it, except when we haven't displayed any frames yet
		}
		return frame;
	}

	void VideoClip::popFrame()
	{
		++this->displayedFramesCount;
		// after transfering frame data to the texture, free the frame
		// so it can be used again
		if (!this->firstFrameDisplayed)
		{
			Mutex::ScopeLock lock(this->frameQueue->getMutex());
			this->frameQueue->_pop(1);
			this->firstFrameDisplayed = true;
		}
		else
		{
			this->frameQueue->pop();
		}
	}

	void VideoClip::play()
	{
		this->timer->play();
	}

	void VideoClip::pause()
	{
		this->timer->pause();
	}

	void VideoClip::stop()
	{
		this->pause();
		this->_resetFrameQueue();
		this->firstFrameDisplayed = false;
		this->seek(0);
	}

	void VideoClip::restart()
	{
		this->endOfFile = true; // temp, to prevent threads to decode while restarting
		Mutex::ScopeLock lock(this->threadAccessMutex);
		this->_executeRestart();
		this->timer->seek(0);
		this->firstFrameDisplayed = false;
		this->_resetFrameQueue();
		this->endOfFile = false;
		this->restarted = false;
		this->seekFrame = -1;
	}

	void VideoClip::seek(float time)
	{
		this->seekToFrame((int)(time * this->getFps()));
	}

	void VideoClip::seekToFrame(int frame)
	{
		if (frame < 0)
		{
			this->seekFrame = 0;
		}
		else if (frame > this->framesCount)
		{
			this->seekFrame = this->framesCount;
		}
		else
		{
			this->seekFrame = frame;
		}
		this->firstFrameDisplayed = false;
		this->endOfFile = false;
	}

	float VideoClip::waitForCache(float desiredCacheRatio, float maxWaitTime)
	{
		this->waitingForCache = true;
		bool paused = this->timer->isPaused();
		if (!paused)
		{
			this->timer->pause();
		}
		int elapsed = 0;
		int readyCount = 0;
		int frameQueueSize = this->getPrecachedFramesCount();
		if (this->framesCount < frameQueueSize)
		{
			frameQueueSize = this->framesCount;
		}
		int desiredPrecachedFramesCount = (int)ceil(desiredCacheRatio * frameQueueSize);
		do
		{
			readyCount = this->getReadyFramesCount();
			if (readyCount >= desiredPrecachedFramesCount)
			{
				break;
			}
			Thread::sleep(10.0f);
			elapsed += 10;
		} while (elapsed >= maxWaitTime * 1000);
		if (!paused)
		{
			this->timer->play();
		}
		this->waitingForCache = false;
		return ((float)readyCount / frameQueueSize);
	}

	void VideoClip::_update(float timeDelta)
	{
		if (this->timer->isPaused())
		{
			this->timer->update(0); // update timer in case there is some code that needs to execute each frame
			return;
		}
		float time = this->timer->getTime(), speed = this->timer->getSpeed();
		if (time + timeDelta * speed >= this->duration)
		{
			if (this->autoRestart && this->restarted)
			{
				float seekTime = time + timeDelta * speed;
				while (seekTime >= this->duration)
				{
					seekTime -= this->duration;
					++this->playbackIteration;
				}
				this->timer->seek(seekTime);
			}
			else if (time != this->duration)
			{
				this->timer->update((this->duration - time) / speed);
			}
		}
		else
		{
			this->timer->update(timeDelta);
		}
	}

	void VideoClip::_resetFrameQueue()
	{
		this->frameQueue->clear();
		this->playbackIteration = 0;
		this->iteration = 0;
	}

	int VideoClip::_discardOutdatedFrames(float absTime)
	{
		int readyCount = this->frameQueue->_getReadyCount();
		// only drop frames if you have more frames to show. otherwise even the late frame will do..
		if (readyCount == 1)
		{
			return 0;
		}
		float time = absTime;
		int popCount = 0;
		VideoFrame* frame = NULL;
		float timeToDisplay = 0.0f;
		std::list<VideoFrame*>& queue = this->frameQueue->_getFrameQueue();
		foreach_l(VideoFrame*, it, queue)
		{
			frame = *it;
			if (!frame->ready)
			{
				break;
			}
			timeToDisplay = frame->timeToDisplay + frame->iteration * this->duration;
			if (time <= timeToDisplay + this->frameDuration)
			{
				break;
			}
			++popCount;
			if (readyCount - popCount == 1)
			{
				break; // always leave at least one in the queue
			}
		}
		if (popCount > 0)
		{
#ifdef _DEBUG_FRAMEDROP
			std::string message = this->getName() + ": dropped frame ";
			int i = popCount;
			foreach_l (VideoFrame*, it, queue)
			{
				message += str((int)(*it)->getFrameNumber());
				if (i <= 1)
				{
					break;
				}
				message += ", ";
				--i;
			}
			log(message);
#endif
			this->droppedFramesCount += popCount;
			this->frameQueue->_pop(popCount);
		}
		return popCount;
	}

	void VideoClip::_lockAudioMutex()
	{
		this->audioMutex->lock();
	}

	void VideoClip::_unlockAudioMutex()
	{
		this->audioMutex->unlock();
	}

	void VideoClip::_setVideoFrameTimeToDisplay(VideoFrame* frame, float value)
	{
		frame->timeToDisplay = value;
	}

	void VideoClip::_setVideoFrameReady(VideoFrame* frame, bool value)
	{
		frame->ready = value;
	}

	void VideoClip::_setVideoFrameInUse(VideoFrame* frame, bool value)
	{
		frame->inUse = value;
	}

	void VideoClip::_setVideoFrameIteration(VideoFrame* frame, int value)
	{
		frame->iteration = value;
	}

	void VideoClip::_setVideoFrameFrameNumber(VideoFrame* frame, int value)
	{
		frame->frameNumber = value;
	}

}
