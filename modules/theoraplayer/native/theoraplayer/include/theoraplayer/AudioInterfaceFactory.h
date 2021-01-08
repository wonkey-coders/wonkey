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
/// Provides an interface for connecting videos with audio.

#ifndef THEORAPLAYER_AUDIO_INTERFACE_FACTORY_H
#define THEORAPLAYER_AUDIO_INTERFACE_FACTORY_H

#include "theoraplayerExport.h"

namespace theoraplayer
{
	class VideoClip;
	class AudioInterface;

	class theoraplayerExport AudioInterfaceFactory
	{
	public:
		AudioInterfaceFactory();
		virtual ~AudioInterfaceFactory();

		/// @brief VideoManager calls this when creating a new VideoClip object
		virtual AudioInterface* createInstance(theoraplayer::VideoClip* clip, int channelsCount, int frequency) = 0;

	};

}
#endif