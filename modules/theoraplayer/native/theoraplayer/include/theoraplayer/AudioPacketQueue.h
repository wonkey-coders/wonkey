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
/// Defines an audio packet queue.

#ifndef THEORAPLAYER_AUDIO_PACKET_QUEUE_H
#define THEORAPLAYER_AUDIO_PACKET_QUEUE_H

#include "theoraplayerExport.h"
#include "theoraplayer.h"

namespace theoraplayer
{
	class AudioInterface;

	/// @brief This is a Mutex object, used in thread syncronization.
	class theoraplayerExport AudioPacketQueue
	{
	public:
		/// @brief This is an internal structure which VideoClip uses to store audio packets
		struct AudioPacket
		{
			float* pcmData;
			/// @brief Size in number of float samples.
			/// @note Stereo has twice the number of samples.
			int samplesCount;
			/// @brief The next AudioPacket* instance.
			AudioPacket* next;
		};

		AudioPacketQueue();
		~AudioPacketQueue();

		float getAudioPacketQueueLength() const;

		void addAudioPacket(float** buffer, int samplesCount, float gain = 1.0f);
		void addAudioPacket(float* buffer, int samplesCount, float gain = 1.0f);

		AudioPacket* popAudioPacket();

		void destroyAudioPacket(AudioPacket* packet);
		void destroyAllAudioPackets();

		void flushAudioPackets(AudioInterface* audioInterface);

	protected:
		unsigned int audioFrequency;
		unsigned int audioChannelsCount;
		AudioPacket* audioPacketQueue;

		void _addAudioPacket(float* data, int samplesCount);
		void _flushSynchronizedAudioPackets(AudioInterface* audioInterface, Mutex* mutex);

	};
}

#endif
