/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

//***** Mark was here *****
#define _USE_THEORA 1

#ifdef _USE_THEORA

#include <theora/theoradec.h>
#include <vorbis/vorbisfile.h>
#endif

#include "AudioInterface.h"
#include "FileDataSource.h"
#include "Exception.h"
#include "FrameQueue.h"
#include "Manager.h"
#include "theoraplayer.h"
#include "Utility.h"
#include "VideoClip.h"
#include "WorkerThread.h"

#ifdef _ANDROID //libtheoraplayer addition for cpu feature detection
	#include "cpu-features.h"
#endif

// declaring function prototype here so I don't have to put it in a header file
// it only needs to be used by this plugin and called once
extern "C"
{
	void initYUVConversionModule();
}

//#define _DECODING_BENCHMARK //uncomment to test average decoding time on a given device

namespace theoraplayer
{
#ifdef _SCHEDULING_DEBUG
	static float threadDiagnosticTimer = 0.0f;
#endif
#ifdef _DECODING_BENCHMARK
	void benchmark(VideoClip* clip)
	{
		int precachedFramesCount = 256;
		int count = precachedFramesCount;
		char message[1024] = {0};
		clock_t t = clock();
		while (count > 0)
		{
			clip->waitForCache(1.0f, 1000000);
			count -= 32;
			clip->getFrameQueue()->clear();
		}
		float diff = ((float)(clock() - t) * 1000.0f) / CLOCKS_PER_SEC;
		sprintf(message, "BENCHMARK: %s: Decoding %d frames took %.1fms (%.2fms average per frame)\n", clip->getName().c_str(), precachedFramesCount, diff, diff / precachedFramesCount);
		log(message);
		clip->seek(0);
	}
#endif

	struct WorkCandidate
	{
		VideoClip* clip;
		float priority;
		float queuedTime;
		float workTime;
		float entitledTime;
	};

	Manager* manager = NULL;

	Manager::Manager() : defaultPrecachedFramesCount(8), workMutex(new Mutex()), audioInterfaceFactory(NULL)
	{
		std::string message = "Initializing Theoraplayer Video Playback Library (" + this->getVersionString() + ")\n";
#ifdef _USE_THEORA
		message += "  - libtheora version: " + std::string(th_version_string()) + "\n" +
			"  - libvorbis version: " + std::string(vorbis_version_string()) + "\n";
#endif
#ifdef _ANDROID
		uint64_t features = libtheoraplayer_android_getCpuFeaturesExt();
		char s[128] = { 0 };
		sprintf(s, "  - Android: CPU Features: %u\n", (unsigned int)features);
		message += s;
		if ((features & ANDROID_CPU_ARM_FEATURE_NEON) == 0)
		{
			message += "  - Android: NEON features NOT SUPPORTED by CPU\n";
		}
		else
		{
			message += "  - Android: Detected NEON CPU features\n";
		}
#endif
		log(message + "------------------------------------");
		// for CPU based yuv2rgb decoding
		initYUVConversionModule();
	}

	Manager::~Manager()
	{
		this->_destroyWorkerThreads();
		Mutex::ScopeLock lock(this->workMutex);
		foreach (VideoClip*, it, this->clips)
		{
			delete (*it);
		}
		this->clips.clear();
		lock.release();
		delete this->workMutex;
	}

	int Manager::getWorkerThreadCount() const
	{
		return (int)this->workerThreads.size();
	}

	void Manager::setWorkerThreadCount(int value)
	{
		if (value < 1)
		{
			value = 1;
		}
		int currentWorkerThreads = this->getWorkerThreadCount();
		if (value != currentWorkerThreads)
		{
			log("Changing number of worker threads to: " + str(value));
			if (value > currentWorkerThreads)
			{
				this->_createWorkerThreads(value - currentWorkerThreads);
			}
			else
			{
				this->_destroyWorkerThreads(currentWorkerThreads - value);
			}
		}
	}

	std::vector<std::string> Manager::getSupportedFormats() const
	{
		std::vector<std::string> result;
		foreachc (VideoClip::Format, it, videoClipFormats)
		{
			result.push_back((*it).name);
		}
		return result;
	}

	std::string Manager::getVersionString() const
	{
		int major = 0;
		int minor = 0;
		int revision = 0;
		this->getVersion(&major, &minor, &revision);
		std::string result = str(major) + "." + str(minor);
		if (revision != 0)
		{
			result += (revision < 0 ? " RC" + str(-revision) : "." + str(revision));
		}
		return result;
	}

	void Manager::getVersion(int* major, int* minor, int* revision) const
	{
		*major = 2;
		*minor = 0;
		*revision = 0;
	}

	VideoClip* Manager::findVideoClipByName(const std::string& name)
	{
		Mutex::ScopeLock lock(this->workMutex);
		foreach (VideoClip*, it, this->clips)
		{
			if ((*it)->getName() == name)
			{
				return (*it);
			}
		}
		return NULL;
	}

	VideoClip* Manager::createVideoClip(const std::string& filename, OutputMode outputMode, int precachedFramesCountOverride, bool usePotStride)
	{
		return this->createVideoClip(new FileDataSource(filename), outputMode, precachedFramesCountOverride, usePotStride);
	}

	VideoClip* Manager::createVideoClip(DataSource* dataSource, OutputMode outputMode, int precachedFramesCountOverride, bool usePotStride)
	{
		Mutex::ScopeLock lock(this->workMutex);
		VideoClip* clip = NULL;
		int precachedFramesCount = (precachedFramesCountOverride > 0 ? precachedFramesCountOverride : this->defaultPrecachedFramesCount);
		log("Creating video from data source: " + dataSource->toString() + " [" + str(precachedFramesCount) + " precached frames].");
		std::string formatName = dataSource->getFormatName();
		if (formatName != "")
		{
			foreach (VideoClip::Format, it, videoClipFormats)
			{
				if (formatName == (*it).name)
				{
					clip = (*(*it).createFunction)(dataSource, outputMode, precachedFramesCount, usePotStride);
					break;
				}
			}
		}
		if (clip != NULL)
		{
			try
			{
				clip->_load(dataSource);
			}
			catch (_Exception& e)
			{
				delete clip;
				// don't delete dataSource, it should be deleted by the calling function
				throw e;
			}
			clip->_decodeNextFrame(); // ensure the first frame is always preloaded and have the main thread do it to prevent potential thread starvation
			this->clips.push_back(clip);
		}
		else
		{
			log("ERROR: Failed creating video clip: " + dataSource->toString());
		}
		lock.release();
#ifdef _DECODING_BENCHMARK
		benchmark(clip);
#endif
		return clip;
	}

	void Manager::destroyVideoClip(VideoClip* clip)
	{
		if (clip == NULL)
		{
			return;
		}
		log("Destroying video clip: " + clip->getName());
		Mutex::ScopeLock lock(this->workMutex);
		bool reported = false;
		while (clip->assignedWorkerThread != NULL)
		{
			if (!reported)
			{
				log(" - Waiting for WorkerThread to finish decoding in order to destroy");
				reported = true;
			}
			Thread::sleep(1.0f);
		}
		if (reported)
		{
			log(" - WorkerThread done, destroying clip now...");
		}
		foreach (VideoClip*, it, this->clips)
		{
			if ((*it) == clip)
			{
				this->clips.erase(it);
				break;
			}
		}
		// remove all it's references from the work log
		this->workLog.remove(clip);
		// delete the actual clip
		delete clip;
#ifdef _DEBUG
		log("Destroyed video clip.");
#endif
	}

	void Manager::update(float timeDelta)
	{
		Mutex::ScopeLock lock(this->workMutex);
		foreach (VideoClip*, it, this->clips)
		{
			(*it)->_update(timeDelta);
			(*it)->_decodedAudioCheck();
		}
		lock.release();
#ifdef _SCHEDULING_DEBUG
		threadDiagnosticTimer += timeDelta;
#endif
	}

	void Manager::_createWorkerThreads(int count)
	{
		WorkerThread* t = NULL;
		for (int i = 0; i < count; ++i)
		{
			t = new WorkerThread();
			this->workerThreads.push_back(t);
			t->start();
		}
	}

	void Manager::_destroyWorkerThreads()
	{
		foreach (WorkerThread*, it, this->workerThreads)
		{
			(*it)->join();
			delete (*it);
		}
		this->workerThreads.clear();
	}

	void Manager::_destroyWorkerThreads(int count)
	{
		WorkerThread* thread = NULL;
		while (count > 0)
		{
			thread = this->workerThreads.back();
			thread->join();
			delete thread;
			this->workerThreads.pop_back();
			--count;
		}
	}

	VideoClip* Manager::_requestWork(WorkerThread* caller)
	{
		Mutex::ScopeLock lock(this->workMutex);
		float maxQueuedTime = 0;
		int totalAccessCount = 0;
		int readyFramesCount = 0;
		std::vector<WorkCandidate> candidates;
		WorkCandidate candidate;
		// first pass is for playing videos, but if no such videos are available for decoding
		// paused videos are selected in the second pass.
		// Note that paused videos that are waiting for cache are considered equal to playing
		// videos in the scheduling context
		for (int i = 0; i < 2 && candidates.size() == 0; ++i)
		{
			foreach (VideoClip*, it, this->clips)
			{
				if (!(*it)->_isBusy() && (i > 0 || (*it)->isPaused() || !(*it)->waitingForCache))
				{
					readyFramesCount = (*it)->getReadyFramesCount();
					if (readyFramesCount != (*it)->getFrameQueue()->getSize())
					{
						candidate.clip = (*it);
						candidate.priority = (*it)->getPriority();
						candidate.queuedTime = (float)readyFramesCount / ((*it)->getFps() * (*it)->getPlaybackSpeed());
						candidate.workTime = (float)(*it)->threadAccessCount;
						totalAccessCount += (*it)->threadAccessCount;
						if (maxQueuedTime < candidate.queuedTime)
						{
							maxQueuedTime = candidate.queuedTime;
						}
						candidates.push_back(candidate);
					}
				}
			}
		}
		// prevent division by zero
		if (totalAccessCount == 0)
		{
			totalAccessCount = 1;
		}
		if (maxQueuedTime == 0)
		{
			maxQueuedTime = 1;
		}
		// normalize candidate values
		float prioritySum = 0.0f;
		foreach (WorkCandidate, it, candidates)
		{
			it->workTime /= totalAccessCount;
			// adjust user priorities to favor clips that have fewer frames queued
			it->priority *= 1.0f - (it->queuedTime / maxQueuedTime) * 0.5f;
			prioritySum += it->priority;
		}
		foreach (WorkCandidate, it, candidates)
		{
			it->entitledTime = it->priority / prioritySum;
		}
		// now, based on how much access time has been given to each clip in the work log
		// and how much time should be given to each clip based on calculated priorities,
		// we choose a best suited clip for this worker thread to decode next
		float maxDiff = -1.0f;
		float diff = 0.0f;
		VideoClip* selectedClip = NULL;
		foreach (WorkCandidate, it, candidates)
		{
			diff = it->entitledTime - it->workTime;
			if (maxDiff < diff)
			{
				maxDiff = diff;
				selectedClip = it->clip;
			}
		}
		if (selectedClip != NULL)
		{
			selectedClip->assignedWorkerThread = caller;
			int clipsCount = (int)this->clips.size();
			unsigned int maxWorkLogSize = (clipsCount - 1) * 50;
			if (clipsCount > 1)
			{
				this->workLog.push_front(selectedClip);
				++selectedClip->threadAccessCount;
			}
			VideoClip* clip = NULL;
			while (this->workLog.size() > maxWorkLogSize)
			{
				clip = this->workLog.back();
				this->workLog.pop_back();
				--clip->threadAccessCount;
			}
#ifdef _SCHEDULING_DEBUG
			if (this->clips.size() > 1)
			{
				int accessCount = (int)this->workLog.size();
				if (threadDiagnosticTimer > 2.0f)
				{
					threadDiagnosticTimer = 0.0f;
					std::string message = "-----\nTheoraplayer Video Playback Library debug CPU time analysis (" + str(accessCount) + "):\n";
					int percent;
					foreach (VideoClip*, it, this->clips)
					{
						percent = ((float)(*it)->threadAccessCount / (int)this->workLog.size()) * 100.0f;
						message += (*it)->getName() + " (" + str((*it)->getPriority()) + "): " + str((*it)->threadAccessCount) + ", " + str(percent) + "%\n";
					}
					message += "-----";
					log(message);
				}
			}
#endif
		}
		return selectedClip;
	}

}
