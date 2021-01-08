/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#define DEFAULT_THREAD_NAME "Theoraplayer Worker Thread"

#include "Exception.h"
#include "Mutex.h"
#include "theoraplayer.h"
#include "Thread.h"

#ifdef _WINRT
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
#endif

namespace theoraplayer
{
#if defined(_WIN32) && defined(_MSC_VER)
#pragma pack(push, 8)
	typedef struct _THREADNAME_INFO
	{
		DWORD dwType;
		LPCSTR szName;
		DWORD dwThreadID;
		DWORD dwFlags;
	} THREADNAME_INFO;
#pragma pack(pop)

	static void SetThreadName(DWORD id)
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = DEFAULT_THREAD_NAME;
		info.dwThreadID = id;
		info.dwFlags = 0;
		__try
		{
			RaiseException(0x406D1388, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
		}
		__except (EXCEPTION_CONTINUE_EXECUTION)
		{
		}
	}
#endif

#ifdef _WIN32
	static unsigned long WINAPI _asyncCall(void* param)
	{
		Thread::ThreadRunner* t = (Thread::ThreadRunner*)param;
#ifdef _MSC_VER
		SetThreadName(GetCurrentThreadId());
#endif
		t->execute();
		return 0;
	}
#else
	static void* _asyncCall(void* param)
	{
		Thread::ThreadRunner* t = (Thread::ThreadRunner*)param;
#ifdef __APPLE__
		pthread_setname_np(DEFAULT_THREAD_NAME);
#endif
		t->execute();
		pthread_exit(NULL);
		return NULL;
	}
#endif

#ifdef _WINRT
	struct AsyncActionWrapper
	{
	public:
		IAsyncAction^ asyncAction;
		AsyncActionWrapper(IAsyncAction^ asyncAction)
		{
			this->asyncAction = asyncAction;
		}
	};
#endif

	Thread::ThreadRunner::ThreadRunner(Thread* thread)
	{
		this->thread = thread;
	}

	Thread::ThreadRunner::~ThreadRunner()
	{
	}

	void Thread::ThreadRunner::execute()
	{
		this->thread->_execute();
	}

	Thread::Thread(void (*function)(Thread*)) : executing(false), runner(this), id(0), running(false)
	{
		this->function = function;
	}

	Thread::~Thread()
	{
		if (this->running)
		{
			log("Thread still executing in destructor! Attempting 'stop', but this may be unsafe. The thread should be joined before deleting it.");
			this->stop();
		}
		this->_clear();
	}

	void Thread::start()
	{
		if (this->running)
		{
			char message[1024] = { '\0' };
#ifdef _WIN32
			sprintf(message, "WARNING: Thread '%s' '<0x%p>' already running, cannot start!", DEFAULT_THREAD_NAME, this);
#else
			sprintf(message, "WARNING: Thread '%s' '<%p>' already running, cannot start!", DEFAULT_THREAD_NAME, this);
#endif
			log(message);
			return;
		}
		this->running = true;
		this->_clear(); // if thread exited on its own, but the data is still allocated
		this->_platformStart();
	}

	void Thread::join()
	{
		this->running = false;
		this->_platformJoin();
		this->_clear();
		// aborted execution can leave this variable in any state, reset it
		this->executing = false;
	}

	void Thread::resume()
	{
		this->_platformResume();
	}

	void Thread::pause()
	{
		this->_platformPause();
	}

	void Thread::stop()
	{
		if (this->running)
		{
			this->running = false;
			this->_platformStop();
			this->_clear();
			// aborted execution can leave this variable in any state, reset it
			this->executing = false;
		}
		else
		{
			this->_clear();
		}
	}

	void Thread::_execute()
	{
		if (this->running && this->function != NULL)
		{
			this->executing = true;
			try
			{
				(*this->function)(this);
			}
			catch (_Exception& e)
			{
				char message[1024] = { '\0' };
#ifdef _WIN32
				sprintf(message, "FATAL: Thread '%s' '<0x%p>':", DEFAULT_THREAD_NAME, this);
#else
				sprintf(message, "FATAL: Thread '%s' '<%p>':", DEFAULT_THREAD_NAME, this);
#endif
				log(message + e.getMessage());
				throw e;
			}
		}
		this->executing = false;
		this->running = false;
	}

	void Thread::_clear()
	{
		if (this->id != NULL)
		{
#ifdef _WIN32
#ifndef _WINRT
			CloseHandle(this->id);
#else
			delete this->id;
#endif
#else
			free((pthread_t*)this->id);
#endif
			this->id = NULL;
		}
	}

	void Thread::_platformStart()
	{
#ifdef _WIN32
#ifndef _WINRT
		this->id = CreateThread(0, 0, &_asyncCall, &this->runner, 0, 0);
#else
		this->id = new AsyncActionWrapper(ThreadPool::RunAsync(ref new WorkItemHandler([&](IAsyncAction^ workItem)
		{
			SetThreadName(GetCurrentThreadId());
			this->_execute();
		}), WorkItemPriority::Normal, WorkItemOptions::TimeSliced));
#endif
#else
		pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t));
		this->id = thread;
		pthread_create(thread, NULL, &_asyncCall, &this->runner);
#ifndef __APPLE__
		pthread_setname_np(*thread, DEFAULT_THREAD_NAME);
#endif
#endif
	}

	void Thread::_platformJoin()
	{
		if (this->id == NULL)
		{
			return;
		}
#ifdef _WIN32
#ifndef _WINRT
		WaitForSingleObject(this->id, INFINITE);
#else
		IAsyncAction^ action = ((AsyncActionWrapper*)this->id)->asyncAction;
		int i = 0;
		while (action->Status != AsyncStatus::Completed &&
			action->Status != AsyncStatus::Canceled &&
			action->Status != AsyncStatus::Error &&
			i < 100)
		{
			Thread::sleep(50);
			++i;
		}
		if (i >= 100)
		{
			i = 0;
			action->Cancel();
			while (action->Status != AsyncStatus::Completed &&
				action->Status != AsyncStatus::Canceled &&
				action->Status != AsyncStatus::Error &&
				i < 100)
			{
				Thread::sleep(50);
				++i;
			}
		}
#endif
#else
		pthread_join(*((pthread_t*)this->id), 0);
#endif
	}

	void Thread::_platformResume()
	{
#ifdef _WIN32
#ifndef _WINRT
		ResumeThread(this->id);
#else
		// not available in WinRT
		log("WARNING: Thread::resume() is not available on WinRT.");
#endif
#endif
	}

	void Thread::_platformPause()
	{
#ifdef _WIN32
#ifndef _WINRT
		SuspendThread(this->id);
#else
		// not available in WinRT
		log("WARNING: Thread::pause() is not available on WinRT.");
#endif
#endif
	}

	void Thread::_platformStop()
	{
		if (this->id == NULL)
		{
			return;
		}
#ifdef _WIN32
#ifndef _WINRT
		TerminateThread(this->id, 0);
#else
		((AsyncActionWrapper*)this->id)->asyncAction->Cancel();
#endif
#elif defined(__ANDROID__)
		pthread_kill(*((pthread_t*)this->id), 0);
#else
		pthread_cancel(*((pthread_t*)this->id));
#endif
	}

	void Thread::sleep(float milliseconds)
	{
#ifdef _WIN32
#ifndef _WINRT
		Sleep((int)milliseconds);
#else
		WaitForSingleObjectEx(GetCurrentThread(), (int)milliseconds, 0);
#endif
#else
		usleep(milliseconds * 1000);
#endif
	}

	Thread::Thread(const Thread& other) : runner(this)
	{
		throw TheoraplayerException("Cannot copy theoraplayer::Thread object!");
	}

	Thread& Thread::operator=(Thread& other)
	{
		throw TheoraplayerException("Cannot assign theoraplayer::Thread object!");
		return (*this);
	}

}
