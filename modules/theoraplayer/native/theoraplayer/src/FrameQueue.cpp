/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include "Manager.h"

#include "FrameQueue.h"
#include "Mutex.h"
#include "theoraplayer.h"
#include "Thread.h"
#include "Utility.h"
#include "VideoFrame.h"

namespace theoraplayer
{
	FrameQueue::FrameQueue(VideoClip* parent) : mutex(new Mutex())
	{
		this->parent = parent;
	}

	FrameQueue::~FrameQueue()
	{
		// TODOth - is this safe to delete without a mutex lock?
		foreach_l (VideoFrame*, it, this->queue)
		{
			delete (*it);
		}
		this->queue.clear();
		delete this->mutex;
	}

	VideoFrame* FrameQueue::_createFrameInstance(VideoClip* clip)
	{
		VideoFrame* frame = new VideoFrame(clip);
		if (frame->getBuffer() == NULL) // This can happen if you run out of memory
		{
			delete frame;
			return NULL;
		}
		return frame;
	}

	int FrameQueue::getUsedCount() const
	{
		Mutex::ScopeLock lock(this->mutex);
		int result = 0;
		foreachc_l (VideoFrame*, it, this->queue)
		{
			if ((*it)->inUse)
			{
				++result;
			}
		}
		return result;
	}

	VideoFrame* FrameQueue::getFirstAvailableFrame()
	{
		Mutex::ScopeLock lock(this->mutex);
		return this->_getFirstAvailableFrame();
	}

	VideoFrame* FrameQueue::_getFirstAvailableFrame() const
	{
		VideoFrame* frame = this->queue.front();
		return (frame->ready ? frame : NULL);
	}

	int FrameQueue::getReadyCount()
	{
		Mutex::ScopeLock lock(this->mutex);
		return this->_getReadyCount();
	}

	int FrameQueue::_getReadyCount() const
	{
		int result = 0;
		foreachc_l(VideoFrame*, it, this->queue)
		{
			if ((*it)->ready)
			{
				++result;
			}
		}
		return result;
	}

	int FrameQueue::getSize() const
	{
		return (int)this->queue.size();
	}

	void FrameQueue::setSize(int n)
	{
		Mutex::ScopeLock lock(this->mutex);
		if (this->queue.size() > 0)
		{
			foreach_l (VideoFrame*, it, this->queue)
			{
				delete (*it);
			}
			this->queue.clear();
		}
		VideoFrame* frame = NULL;
		for (int i = 0; i < n; ++i)
		{
			frame = this->_createFrameInstance(this->parent);
			if (frame == NULL)
			{
				log("FrameQueue: unable to create " + str(n) + " frames, out of memory. Created " + str((int) this->queue.size()) + " frames.");
				break;
			}
			this->queue.push_back(frame);
		}
	}

	bool FrameQueue::isFull()
	{
		return (this->getReadyCount() == (int)this->queue.size());
	}

	std::list<VideoFrame*>& FrameQueue::_getFrameQueue()
	{
		return this->queue;
	}

	void FrameQueue::clear()
	{
		Mutex::ScopeLock lock(this->mutex);
		foreach_l (VideoFrame*, it, this->queue)
		{
			(*it)->clear();
		}
	}

	void FrameQueue::pop(int n)
	{
		Mutex::ScopeLock lock(this->mutex);
		this->_pop(n);
	}

	void FrameQueue::_pop(int n)
	{
		VideoFrame* first = NULL;
		for (int i = 0; i < n; ++i)
		{
			first = this->queue.front();
			first->clear();
			this->queue.pop_front();
			this->queue.push_back(first);
		}
	}

	VideoFrame* FrameQueue::requestEmptyFrame()
	{
		Mutex::ScopeLock lock(this->mutex);
		foreach_l (VideoFrame*, it, this->queue)
		{
			if (!(*it)->inUse)
			{
				(*it)->inUse = 1;
				(*it)->ready = 0;
				return (*it);
			}
		}
		return NULL;
	}

}
