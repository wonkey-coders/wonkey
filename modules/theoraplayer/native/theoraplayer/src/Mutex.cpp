/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "Exception.h"
#include "Mutex.h"
#include "theoraplayer.h"
#include "Thread.h"

namespace theoraplayer
{
	Mutex::ScopeLock::ScopeLock(Mutex* mutex, bool logUnhandledUnlocks) : mutex(NULL)
	{
		this->logUnhandledUnlocks = logUnhandledUnlocks;
		this->acquire(mutex);
	}

	Mutex::ScopeLock::~ScopeLock()
	{
		Mutex* mutex = this->mutex;
		if (this->release() && this->logUnhandledUnlocks && mutex != NULL)
		{
			char message[1024] = { '\0' };
#ifdef _WIN32
			sprintf(message, "WARNING: '<0x%p>' has been scope-unlocked automatically!", this);
#else
			sprintf(message, "WARNING: '<%p>' has been scope-unlocked automatically!", this);
#endif
			log(message);
		}
	}

	bool Mutex::ScopeLock::acquire(Mutex* mutex)
	{
		if (this->mutex == NULL && mutex != NULL)
		{
			this->mutex = mutex;
			this->mutex->lock();
			return true;
		}
		return false;
	}

	bool Mutex::ScopeLock::release()
	{
		if (this->mutex != NULL)
		{
			this->mutex->unlock();
			this->mutex = NULL;
			return true;
		}
		return false;
	}

	Mutex::Mutex() : handle(NULL), locked(false)
	{
#ifdef _WIN32
		this->handle = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
#ifndef _WINRT // WinXP does not have InitializeCriticalSectionEx()
		InitializeCriticalSection((CRITICAL_SECTION*)this->handle);
#elif !defined(_DEBUG)
		InitializeCriticalSectionEx((CRITICAL_SECTION*)this->handle, 0, 0);
#else
		InitializeCriticalSectionEx((CRITICAL_SECTION*)this->handle, 0, CRITICAL_SECTION_NO_DEBUG_INFO);
#endif
#else
		this->handle = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((pthread_mutex_t*)this->handle, 0);
#endif
	}

	Mutex::~Mutex()
	{
#ifdef _WIN32
		DeleteCriticalSection((CRITICAL_SECTION*)this->handle);
		free((CRITICAL_SECTION*)this->handle);
#else
		pthread_mutex_destroy((pthread_mutex_t*)this->handle);
		free((pthread_mutex_t*)this->handle);
#endif
	}

	void Mutex::lock()
	{
#ifdef _WIN32
		EnterCriticalSection((CRITICAL_SECTION*)this->handle);
		if (this->locked)
		{
			char message[1024] = { '\0' };
#ifdef _WIN32
			sprintf(message, "WARNING: '<0x%p>' is deadlocked!", this);
#else
			sprintf(message, "WARNING: '<%p>'  is deadlocked!", this);
#endif
			log(message);
			while (true) // simulating a deadlock
			{
				Thread::sleep(1.0f);
			}
		}
		this->locked = true;
#else
		pthread_mutex_lock((pthread_mutex_t*)this->handle);
#endif
	}

	void Mutex::unlock()
	{
#ifdef _WIN32
		this->locked = false;
		LeaveCriticalSection((CRITICAL_SECTION*)this->handle);
#else
		pthread_mutex_unlock((pthread_mutex_t*)this->handle);
#endif
	}
	
	Mutex::Mutex(const Mutex& other)
	{
		throw TheoraplayerException("Cannot copy theoraplayer::Mutex object!");
	}

	Mutex& Mutex::operator=(Mutex& other)
	{
		throw TheoraplayerException("Cannot assign theoraplayer::Mutex object!");
		return (*this);
	}

}
