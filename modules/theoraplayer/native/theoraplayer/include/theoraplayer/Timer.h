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
/// Provides a a timer interface.

#ifndef THEORAPLAYER_TIMER_H
#define THEORAPLAYER_TIMER_H

#include "theoraplayerExport.h"

namespace theoraplayer
{
	/// @brief This is a Timer object, it is used to control the playback of a VideoClip.
	/// You can inherit this class and make a timer that eg. plays twice as fast,
	/// or playbacks an audio track and uses it's time offset for syncronizing Video etc.
	class theoraplayerExport Timer
	{
	public:
		Timer();
		virtual ~Timer();

		virtual inline float getTime() const { return this->time; }
		/// @return The update speed 1.0 is the default.
		virtual inline float getSpeed() const { return this->speed; }
		/// @brief Sets playback speed.
		/// 1.0 is the default. The speed factor multiplies time advance, thus setting the value higher will increase playback speed etc.
		/// @note depending on Timer implementation, it may not support setting the speed.
		virtual inline void setSpeed(float value) { this->speed = value; }
		virtual inline bool isPaused() const { return this->paused; }
		/// @brief Advances the time.
		/// If you're using another synronization system, eg. an audio track, then you can ignore this call or use it to perform other updates.
		/// @note This is usually called by Manager from the main thread
		virtual void update(float timeDelta);

		virtual void play();
		virtual void pause();
		virtual void stop();
		/// @brief Change the current time position.
		/// If you're using another syncronization mechanism, make sure to adjust the time offset there.
		virtual void seek(float time);

	protected:
		/// @brief Current time in seconds.
		float time;
		float speed;
		/// @brief Is the timer paused or not.
		bool paused;

	};

}
#endif
