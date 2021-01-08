/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#ifndef _WIN32
#include <unistd.h>
#include <pthread.h>
#endif

#include "Manager.h"
#include "Mutex.h"
#include "WorkerThread.h"
#include "VideoClip.h"

namespace theoraplayer
{
#ifdef _THREAD_NAMING
	static int threadCounter = 1;
	static theoraplayer::Mutex counterMutex;
#endif

	WorkerThread::WorkerThread() : Thread(&WorkerThread::_work)
	{
		this->clip = NULL;
	}

	WorkerThread::~WorkerThread()
	{
	}

	void WorkerThread::_work(Thread* thread)
	{
		WorkerThread* self = (WorkerThread*)thread;
		Mutex::ScopeLock lock;
#ifdef _THREAD_NAMING
		{
			lock.acquire(&counterMutex);
			char name[64] = { 0 };
			sprintf(name, "WorkerThread %d", threadCounter++);
			pthread_setname_np(name);
			lock.release();
		}
#endif
		bool decoded = false;
		while (self->executing && self->isRunning())
		{
			self->clip = theoraplayer::manager->_requestWork(self);
			if (self->clip == NULL)
			{
				if (!self->executing || !self->isRunning()) // don't pause if a destruction was given
				{
					break;
				}
				Thread::sleep(100.0f);
				continue;
			}
			lock.acquire(self->clip->threadAccessMutex);
			// if user requested seeking, do that then.
			if (self->clip->seekFrame >= 0)
			{
				self->clip->_executeSeek();
			}
			decoded = self->clip->_decodeNextFrame();
			// TODOth - this is a potential hazard as assignedWorkerThread is set under a VideoManager::workMutex lock, but accessed here under a VideoClip::threadAccessMutex lock
			if (self->clip->assignedWorkerThread == self)
			{
				self->clip->assignedWorkerThread = NULL;
				self->clip = NULL;
			}
			lock.release();
			if (!decoded)
			{
				Thread::sleep(1.0f); // this happens when the video frame queue is full.
			}
		}
	}

}