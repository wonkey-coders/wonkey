/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include "Timer.h"

namespace theoraplayer
{
	Timer::Timer()
	{
		this->time = 0.0f;
		this->speed = 1.0f;
		this->paused = false;
	}

	Timer::~Timer()
	{
	}

	void Timer::update(float timeDelta)
	{
		if (!this->isPaused())
		{
			this->time += timeDelta * this->speed;
		}
	}

	void Timer::play()
	{
		this->paused = false;
	}

	void Timer::pause()
	{
		this->paused = true;
	}

	void Timer::stop()
	{
	}

	void Timer::seek(float time)
	{
		this->time = time;
	}

}
