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
/// Defines a frame queue.

#ifndef THEORAPLAYER_FRAME_QUEUE_H
#define THEORAPLAYER_FRAME_QUEUE_H

#include <list>

#include "theoraplayerExport.h"

namespace theoraplayer
{
	class Mutex;
	class VideoClip;
	class VideoFrame;

	/// @brief This class handles the frame queue. contains frames and handles their alloctation/deallocation it is designed to be thread-safe.
	class theoraplayerExport FrameQueue
	{
	public:
		FrameQueue(VideoClip* clip);
		~FrameQueue();

		Mutex* getMutex() const { return this->mutex; }
		/// @return The number of used (but not ready) frames.
		int getUsedCount() const;

		/// @brief Returns the first available frame in the queue or NULL if no frames are available.
		/// @note This function DOES NOT remove the frame from the queue, you have to do it manually
		/// when you want to mark the frame as used by calling the pop() function.
		VideoFrame* getFirstAvailableFrame();
		/// @brief This is a non-mutexed thread-unsafe version.
		/// @see getFirstAvailableFrame
		VideoFrame* _getFirstAvailableFrame() const;

		/// @return The number of ready frames.
		int getReadyCount();
		/// @brief This is a non-mutexed thread-unsafe version.
		/// @see getReadyCount
		int _getReadyCount() const;

		/// @return The size of the queue.
		int getSize() const;
		/// @brief set's the size of the frame queue.
		/// @note Currently stored ready frames will be lost upon this call if the new size is less than the current one.
		void setSize(int size);

		/// @return Whether all frames in the queue are ready for display.
		bool isFull();

		/// @return returns the internal frame queue. Warning: Always lock / unlock queue's mutex before accessing frames directly!
		std::list<VideoFrame*>& _getFrameQueue();

		/// @brief Called by WorkerThreads when they need to unload frame data, do not call directly!
		VideoFrame* requestEmptyFrame();

		/// @brief Removes the first N available frame from the queue. Use this every time you display a frameso you can get the next
		/// one when the time comes. This function marks the frame on the front of the queue as unused and it's memory, then gets used
		/// again in the decoding process. If you don't call this, the frame queue will fill up with precached frames up to the
		/// specified amount in the Manager class and you won't be able to advance the video.
		void pop(int count = 1);
		/// @brief This is a non-mutexed thread-unsafe version.
		/// @see pop
		void _pop(int count);

		/// @brief Frees all decoded frames for reuse.
		/// @note This does not free the memory, it just marks the frames as "freed".
		void clear();

	protected:
		std::list<VideoFrame*> queue;
		VideoClip* parent;
		Mutex* mutex;

		/// @brief The implementation that returns a VideoFrame instance.
		VideoFrame* _createFrameInstance(VideoClip* clip);

	};

}
#endif
