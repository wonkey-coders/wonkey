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

#ifndef THEORAPLAYER_AUDIO_INTERFACE_H
#define THEORAPLAYER_AUDIO_INTERFACE_H

#include "theoraplayerExport.h"

namespace theoraplayer
{
	class AudioInterfaceFactory;
	class VideoClip;

	/// @brief This is the class that serves as an interface between the library's audio output and the audio playback library of your choice.
	///        The class gets mono or stereo PCM data in floating point data
	class theoraplayerExport AudioInterface
	{
	public:
		friend class AudioInterfaceFactory;

		virtual ~AudioInterface();

		inline theoraplayer::VideoClip* getClip() const { return this->clip; }
		inline int getChannelsCount() const { return this->channelsCount; }
		inline int getFrequency() const { return this->frequency; }

		/// @brief A function that the VideoClip object calls once more audio packets are decoded
		/// @param[in] data contains one or two channels of float PCM data in the range [-1,1]
		/// @param[in] samplesCount contains the number of samples that the data parameter contains in each channel
		virtual void insertData(float* data, int samplesCount) = 0;

	protected:
		/// @brief Pointer to the parent VideoClip object
		theoraplayer::VideoClip* clip;
		/// @brief 1 for mono or 2 for stereo.
		int channelsCount;
		/// @brief PCM frequency in Hz (usually 44100).
		int frequency;

		AudioInterface(theoraplayer::VideoClip* owner, int channelsCount, int frequency);

	};

}
#endif

