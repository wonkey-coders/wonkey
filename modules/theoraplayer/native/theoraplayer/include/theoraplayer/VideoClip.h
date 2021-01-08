/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Defines a video clip.

#ifndef THEORAPLAYER_VIDEO_CLIP_H
#define THEORAPLAYER_VIDEO_CLIP_H

#include <string>

#include "theoraplayerExport.h"

namespace theoraplayer
{
	// forward class declarations
	class DataSource;
	class FrameQueue;
	class Manager;
	class Mutex;
	class WorkerThread;
	class Timer;
	class VideoFrame;
	class AudioInterface;

	/// @brief Format of the VideoFrame pixels. Affects decoding time.
	enum OutputMode
	{
		// A = full alpha (255), order of letters represents the byte order for a pixel
		// A means the image is treated as if it contains an alpha channel, while X formats
		// just mean that RGB frame is transformed to a 4 byte format
		FORMAT_UNDEFINED = 0,
		FORMAT_RGB,
		FORMAT_RGBA,
		FORMAT_RGBX,
		FORMAT_ARGB,
		FORMAT_XRGB,
		FORMAT_BGR,
		FORMAT_BGRA,
		FORMAT_BGRX,
		FORMAT_ABGR,
		FORMAT_XBGR,
		FORMAT_GREY,
		FORMAT_GREY3,
		FORMAT_GREY3A,
		FORMAT_GREY3X,
		FORMAT_AGREY3,
		FORMAT_XGREY3,
		FORMAT_YUV,
		FORMAT_YUVA,
		FORMAT_YUVX,
		FORMAT_AYUV,
		FORMAT_XYUV
	};

	/// @brief This object contains all data related to video playback, eg. the open source file, the frame queue etc.
	class theoraplayerExport VideoClip
	{
	public:
		struct Format
		{
			std::string name;
			std::string extension;
			VideoClip* (*createFunction)(DataSource*, OutputMode, int, bool);

		};

		friend class Manager;
		friend class VideoFrame;
		friend class WorkerThread;

		std::string getName() const { return this->name; }
		/// @return The string name of the decoder backend (eg. Theora, AVFoundation)
		virtual std::string getDecoderName() const = 0;

		inline FrameQueue* getFrameQueue() const { return this->frameQueue; }
		inline AudioInterface* getAudioInterface() const { return this->audioInterface; }
		void setAudioInterface(AudioInterface* audioInterface);
		/// @return Timer object associated with this clip.
		inline Timer* getTimer() const { return this->timer; }
		/// @brief Replaces the current Timer object with a new one.
		void setTimer(Timer* timer);

		/// @return Width in pixels of the clip.
		int getWidth() const;
		/// @return Height in pixels of the clip.
		inline int getHeight() const { return this->height; }
		/// @return Whether the clip has an alpha channel.
		inline bool hasAlphaChannel() const { return this->useAlpha; }
		/// @brief X Offset of the actual picture inside a video frame (depending on implementation, this may be 0 or within a codec block size (usually 16))
		int getSubFrameX() const;
		/// @brief Y Offset of the actual picture inside a video frame (depending on implementation, this may be 0 or differ within a codec block size (usually 16))
		int getSubFrameY() const;
		/// @brief Width of the actual picture inside a video frame (depending on implementation, this may be equal to mWidth or differ within a codec block size (usually 16))
		int getSubFrameWidth() const;
		/// @brief Height of the actual picture inside a video frame (depending on implementation, this may be equal to mHeight or differ within a codec block size (usually 16))
		int getSubFrameHeight() const;
		/// @brief Gets the stride in pixels count.
		/// If usePower2Stride is used, when creating the VideoClip object, this value will be the next power of two size compared to width, eg: w=376, stride=512.
		/// Otherwise, stride will be equal to width
		inline int getStride() const { return this->stride; }
		/// @return Current time index from the timer object.
		float getTimePosition() const;
		/// @return Duration of the clip in seconds.
		inline float getDuration() const { return this->duration; }
		/// @return The clip's frame rate.
		float getFps() const { return this->fps; }
		/// @return Number of frames in this clip.
		inline int getFramesCount() const { return this->framesCount; }
		inline float getAudioGain() const { return this->audioGain; }
		/// @brief Changes the audio gane in a range between 0 and 1 inclusively.
		void setAudioGain(float gain);
		float getPlaybackSpeed() const;
		void setPlaybackSpeed(float speed);
		/// @return Current output mode for this video object.
		OutputMode getOutputMode() const { return this->outputMode; }
		/// @brief Set a new output mode.
		/// @note This discards the frame queue and ready frames will be lost.
		void setOutputMode(OutputMode mode);
		inline bool isAutoRestart() const { return this->autoRestart; }
		/// @brief Whether the clip should automatically and smoothly restart when the last frame was reached.
		void setAutoRestart(bool value);
		inline float getPriority() const { return this->priority; }
		void setPriority(float priority) { this->priority = priority; }
		/// @brief Used by Manager to schedule work.
		float getPriorityIndex() const;
		/// @return Size of the frame queue.
		int getPrecachedFramesCount() const;
		/// @brief Resizes the frame queue.
		/// @note This call discards ready frames in the frame queue.
		void setPrecachedFramesCount(int count);
		/// @return Number of ready frames in the frame queue.
		int getReadyFramesCount() const;
		/// @brief Used for benchmarking.
		inline int getDisplayedFramesCount() const { return this->displayedFramesCount; }
		/// @brief Used for benchmarking.
		inline int getDroppedFramesCount() const { return this->droppedFramesCount; }

		bool isDone() const;
		bool isPaused() const;

		/// @brief Update timer to the display time of the next frame. This is useful if you want to grab frames instead of regular display.
		/// @return The time advanced. 0 if no frames are ready.
		/// @note On an abstract level, this works similar to seek, but on a practical level it's different.
		float updateTimerToNextFrame();
		/// @return The first available frame in the queue or NULL if no frames are available.
		/// @see FrameQueue::getFirstAvailableFrame()
		VideoFrame* fetchNextFrame();
		/// @brief Pops the frame from the front of the frame queue.
		/// @see FrameQueue::pop()
		void popFrame();

		void play();
		void pause();
		void stop();
		void restart();

		/// @brief Seeks to a given time position.
		void seek(float time);
		/// @brief Seeks to a given frame number
		void seekToFrame(int frame);
		/// @brief Waits for the clip to cache a given ratio of frames.
		/// @param[in] desiredCacheRatio The ratio of precached frames to wait for.
		/// @param[in] maxWaitTime in range [0,1]. Returns actual precache factor
		/// @param[in] factor in range [0,1]. Returns actual precache factor
		float waitForCache(float desiredCacheFactor = 0.5f, float maxWaitTime = 1.0f);

	protected:
		std::string name;
		FrameQueue* frameQueue;
		AudioInterface* audioInterface;
		DataSource* stream;
		Timer* timer;
		Timer* defaultTimer;
		WorkerThread* assignedWorkerThread;
		/// @brief Syncs audio decoding and extraction.
		Mutex* audioMutex;
		Mutex* threadAccessMutex;
		/// @brief Counter used by Manager to schedule workload
		int threadAccessCount;

		bool useAlpha;
		bool useStride;
		int precachedFramesCount;
		/// @brief Multiplier for audio samples in range between 0 and 1 inclusively.
		float audioGain;
		bool autoRestart;
		OutputMode outputMode;
		/// @brief User assigned priority.
		/// @note Default value is 1.
		float priority;

		float duration;
		float frameDuration;
		int width;
		int height;
		int stride;
		int framesCount;
		float fps;
		bool endOfFile;
		bool waitingForCache;

		int subFrameX;
		int subFrameY;
		int subFrameWidth;
		int subFrameHeight;

		/// @brief Contains desired seek position as a frame number. next worker thread will do the seeking and reset this var to -1
		int seekFrame;
		OutputMode requestedOutputMode;
		bool firstFrameDisplayed;
		bool restarted;
		int iteration;
		/// @brief Used to ensure smooth playback of looping clips.
		int playbackIteration;

		// benchmark vars
		int droppedFramesCount;
		int displayedFramesCount;

		VideoClip(DataSource* dataSource, OutputMode outputMode, int precachedFramesCount, bool usePotStride);
		virtual ~VideoClip();

		bool _isBusy() const;
		float _getAbsPlaybackTime() const;

		/// @bried Advance times. Manager calls this.
		void _update(float timeDelta);

		virtual void _load(DataSource* source) = 0;
		virtual bool _readData() = 0;
		/// @brief Used by WorkerThread, do not call directly
		virtual bool _decodeNextFrame() = 0;
		/// @brief Decodes audio from the vorbis stream and stores it in audio packets. This is an internal function of VideoClip, called
		/// regularly if playing an audio enabled video clip.
		/// @return Last decoded timestamp (if found in decoded packet's granule position).
		virtual float _decodeAudio() = 0;
		/// @brief Check if there is enough audio data decoded to submit to the audio interface. WorkerThread calls this.
		virtual void _decodedAudioCheck() = 0;
		/// @brief Called by WorkerThread to seek to seekFrame.
		virtual void _executeSeek() = 0;
		/// @brief Resets the decoder and stream but leaves the frame queue intact.
		virtual void _executeRestart() = 0;

		void _resetFrameQueue();
		int _discardOutdatedFrames(float absTime);

		void _lockAudioMutex();
		void _unlockAudioMutex();

		void _setVideoFrameTimeToDisplay(VideoFrame* frame, float value);
		void _setVideoFrameReady(VideoFrame* frame, bool value);
		void _setVideoFrameInUse(VideoFrame* frame, bool value);
		void _setVideoFrameIteration(VideoFrame* frame, int value);
		void _setVideoFrameFrameNumber(VideoFrame* frame, int value);

	};

}
#endif
