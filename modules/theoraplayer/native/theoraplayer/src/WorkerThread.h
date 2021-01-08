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
/// Defines a worker thread.

#ifndef THEORAPLAYER_WORKER_THREAD_H
#define THEORAPLAYER_WORKER_THREAD_H

#include "Mutex.h"
#include "Thread.h"

namespace theoraplayer
{
	class VideoClip;

	/**
		This is the worker thread, requests work from VideoManager
		and decodes assigned VideoClip objects
	*/
	class WorkerThread : public Thread
	{
	public:
		WorkerThread();
		~WorkerThread();

		inline VideoClip* getAssignedClip() const { return this->clip; }

	protected:
		VideoClip* clip;

		static void _work(Thread* thread);

	};

}
#endif
