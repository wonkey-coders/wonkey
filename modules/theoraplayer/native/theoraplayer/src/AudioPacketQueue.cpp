/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <stdlib.h>

//***** Mark was HERE *****
#include <string.h>

#include "AudioInterface.h"
#include "AudioPacketQueue.h"
#include "Mutex.h"

namespace theoraplayer
{
	AudioPacketQueue::AudioPacketQueue() : audioFrequency(0), audioChannelsCount(0), audioPacketQueue(NULL)
	{
	}

	AudioPacketQueue::~AudioPacketQueue()
	{
		this->destroyAllAudioPackets();
	}

	float AudioPacketQueue::getAudioPacketQueueLength() const
	{
		int count = 0;
		for (AudioPacket* packet = this->audioPacketQueue; packet != NULL; packet = packet->next)
		{
			count += packet->samplesCount;
		}
		return (float)count / (this->audioFrequency * this->audioChannelsCount);
	}

	void AudioPacketQueue::_addAudioPacket(float* data, int samplesCount)
	{
		AudioPacket* packet = new AudioPacket;
		packet->pcmData = data;
		packet->samplesCount = samplesCount;
		packet->next = NULL;
		if (this->audioPacketQueue == NULL)
		{
			this->audioPacketQueue = packet;
		}
		else
		{
			AudioPacket* last = this->audioPacketQueue;
			for (AudioPacket* current = last; current != NULL; current = current->next)
			{
				last = current;
			}
			last->next = packet;
		}
	}

	void AudioPacketQueue::addAudioPacket(float** buffer, int samplesCount, float gain)
	{
		int size = samplesCount * this->audioChannelsCount;
		float* data = new float[size];
		memset(data, 0, size * sizeof(float));
		float* dataptr = data;
		int i = 0;
		unsigned int j = 0;
		if (gain < 1.0f)
		{
			// apply gain, let's attenuate the samples
			for (i = 0; i < samplesCount; ++i)
			{
				for (j = 0; j < this->audioChannelsCount; ++j, ++dataptr)
				{
					*dataptr = buffer[j][i] * gain;
				}
			}
		}
		else if (gain > 0.0f)
		{
			// do a simple copy, faster then the above method, when gain is 1.0f
			for (i = 0; i < samplesCount; ++i)
			{
				for (j = 0; j < this->audioChannelsCount; ++j, ++dataptr)
				{
					*dataptr = buffer[j][i];
				}
			}
		}
		this->_addAudioPacket(data, samplesCount * this->audioChannelsCount);
	}

	void AudioPacketQueue::addAudioPacket(float* buffer, int samplesCount, float gain)
	{
		int size = samplesCount * this->audioChannelsCount;
		float* data = new float[size];
		memset(data, 0, size * sizeof(float));
		float* dataptr = data;
		int i = 0;
		int floatCount = samplesCount * this->audioChannelsCount;
		if (gain < 1.0f)
		{
			// apply gain, let's attenuate the samples
			for (i = 0; i < floatCount; ++i, ++dataptr)
			{
				*dataptr = buffer[i] * gain;
			}
		}
		else if (gain > 0.0f)
		{
			// do a simple copy, faster then the above method, when gain is 1.0f
			for (i = 0; i < floatCount; ++i, ++dataptr)
			{
				*dataptr = buffer[i];
			}
		}
		this->_addAudioPacket(data, floatCount);
	}

	AudioPacketQueue::AudioPacket* AudioPacketQueue::popAudioPacket()
	{
		AudioPacket* result = this->audioPacketQueue;
		if (result != NULL)
		{
			this->audioPacketQueue = result->next;
		}
		return result;
	}

	void AudioPacketQueue::destroyAudioPacket(AudioPacket* packet)
	{
		if (packet != NULL)
		{
			delete[] packet->pcmData;
			delete packet;
		}
	}

	void AudioPacketQueue::destroyAllAudioPackets()
	{
		for (AudioPacket* packet = this->popAudioPacket(); packet != NULL; packet = this->popAudioPacket())
		{
			this->destroyAudioPacket(packet);
		}
	}

	void AudioPacketQueue::flushAudioPackets(AudioInterface* audioInterface)
	{
		for (AudioPacket* packet = this->popAudioPacket(); packet != NULL; packet = this->popAudioPacket())
		{
			audioInterface->insertData(packet->pcmData, packet->samplesCount);
			this->destroyAudioPacket(packet);
		}
	}

	void AudioPacketQueue::_flushSynchronizedAudioPackets(AudioInterface* audioInterface, Mutex* mutex)
	{
		Mutex::ScopeLock lock(mutex);
		this->flushAudioPackets(audioInterface);
	}

}
