/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include "AudioInterface.h"

namespace theoraplayer
{
	AudioInterface::AudioInterface(theoraplayer::VideoClip* clip, int channelsCount, int frequency)
	{
		this->clip = clip;
		this->channelsCount = channelsCount;
		this->frequency = frequency;
	}

	AudioInterface::~AudioInterface()
	{
	}

}
