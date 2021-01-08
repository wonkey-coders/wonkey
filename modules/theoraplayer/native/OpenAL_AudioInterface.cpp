/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <stdio.h>
#include <string.h>

#include "OpenAL_AudioInterface.h"

ALCdevice* gDevice = 0;
ALCcontext* gContext = 0;

short float2short(float f)
{
	if (f > 1.0f)
	{
		f = 1.0f;
	}
	else if (f < -1.0f)
	{
		f = -1.0f;
	}
	return (short)(f * 32767);
}

OpenAL_AudioInterface::OpenAL_AudioInterface(theoraplayer::VideoClip* clip, int channelsCount, int frequency) :
	theoraplayer::AudioInterface(clip, channelsCount, frequency), theoraplayer::Timer()
{
	this->sourceNumChannels = this->channelsCount;
	if (this->channelsCount > 2)
	{
		// ignore audio with more than 2 channels, use only the stereo channels
		this->channelsCount = 2;
	}
	this->maxBuffSize = frequency * this->channelsCount * 2;
	this->buffSize = 0;
	this->numProcessedSamples = 0;
	this->currentTimer = 0;
	this->tempBuffer = new short[this->maxBuffSize];
	alGenSources(1, &this->source);
	clip->setTimer(this);
	this->numPlayedSamples = 0;
}

OpenAL_AudioInterface::~OpenAL_AudioInterface()
{
	if (this->tempBuffer != NULL)
	{
		delete[] this->tempBuffer;
	}
	if (this->source != 0)
	{
		alSourcei(this->source, AL_BUFFER, 0);
		alDeleteSources(1, &this->source);
	}
	while (this->bufferQueue.size() > 0)
	{
		alDeleteBuffers(1, &this->bufferQueue.front().id);
		this->bufferQueue.pop();
	}
}

float OpenAL_AudioInterface::getQueuedAudioSize()
{
	return ((float)(this->numProcessedSamples - this->numPlayedSamples)) / this->frequency;
}

void OpenAL_AudioInterface::insertData(float* data, int samplesCount)
{
	float* tempData = NULL;
	if (this->sourceNumChannels > 2)
	{
		tempData = new float[samplesCount * 2 / this->sourceNumChannels + 16]; // 16 padding just in case
		int i = 0;
		int n = 0;
		for (n = 0, i = 0; i < samplesCount; i += this->sourceNumChannels, n += 2)
		{
			tempData[n] = data[i];
			tempData[n + 1] = data[i + 1];
		}
		data = tempData;
		samplesCount = n;
	}
	//printf("got %d bytes, %d buffers queued\n",samplesCount,(int)this->bufferQueue.size());
	int state = 0;
	OpenAL_Buffer buff;
	ALuint format;
	for (int i = 0; i < samplesCount; ++i)
	{
		if (this->buffSize < this->maxBuffSize)
		{
			this->tempBuffer[this->buffSize] = float2short(data[i]);
			++this->buffSize;
		}
		if (this->buffSize == this->frequency * this->channelsCount / 10)
		{
			memset(&buff, 0, sizeof(OpenAL_Buffer));
			alGenBuffers(1, &buff.id);
			format = (this->channelsCount == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
			alBufferData(buff.id, format, this->tempBuffer, this->buffSize * 2, this->frequency);
			alSourceQueueBuffers(this->source, 1, &buff.id);
			buff.samplesCount = this->buffSize / this->channelsCount;
			this->numProcessedSamples += this->buffSize / this->channelsCount;
			this->bufferQueue.push(buff);
			this->buffSize = 0;
			state = 0;
			alGetSourcei(this->source, AL_SOURCE_STATE, &state);
			if (state != AL_PLAYING)
			{
				//alSourcef(this->source,AL_PITCH,0.5); // debug
				//alSourcef(this->source,AL_SAMPLE_OFFSET,(float) this->numProcessedSamples-mFreq/4);
				alSourcePlay(this->source);
			}
		}
	}
	if (tempData != NULL)
	{
		delete[] tempData;
	}
}

void OpenAL_AudioInterface::update(float timeDelta)
{
	int i = 0;
	int nProcessed = 0;
	OpenAL_Buffer buff;
	// process played buffers
	alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &nProcessed);
	for (i = 0; i < nProcessed; ++i)
	{
		buff = this->bufferQueue.front();
		this->bufferQueue.pop();
		this->numPlayedSamples += buff.samplesCount;
		alSourceUnqueueBuffers(this->source, 1, &buff.id);
		alDeleteBuffers(1, &buff.id);
	}
	if (nProcessed != 0)
	{
		// update offset
		alGetSourcef(this->source, AL_SEC_OFFSET, &this->currentTimer);
	}
	// control playback and return time position
	//alGetSourcei(this->source,AL_SOURCE_STATE,&state);
	//if (state == AL_PLAYING)
	this->currentTimer += timeDelta;
	this->time = this->currentTimer + (float) this->numPlayedSamples / this->frequency;
	float duration = this->clip->getDuration();
	if (this->time > duration)
	{
		this->time = duration;
	}
}

void OpenAL_AudioInterface::pause()
{
	alSourcePause(this->source);
	Timer::pause();
}

void OpenAL_AudioInterface::play()
{
	alSourcePlay(this->source);
	Timer::play();
}

void OpenAL_AudioInterface::seek(float time)
{
	OpenAL_Buffer buff;
	alSourceStop(this->source);
	while (!this->bufferQueue.empty())
	{
		buff = this->bufferQueue.front();
		this->bufferQueue.pop();
		alSourceUnqueueBuffers(this->source, 1, &buff.id);
		alDeleteBuffers(1, &buff.id);
	}
	//		int nProcessed;
	//		alGetSourcei(this->source,AL_BUFFERS_PROCESSED,&nProcessed);
	//		if (nProcessed != 0)
	//			nProcessed=nProcessed;
	this->buffSize = 0;
	this->currentTimer = 0;
	this->numPlayedSamples = this->numProcessedSamples = (int)(time * this->frequency);
	this->time = time;
}

OpenAL_AudioInterfaceFactory::OpenAL_AudioInterfaceFactory()
{
	return;
	
	// openal init is here used only to simplify samples for this plugin
	// if you want to use this interface in your own program, you'll
	// probably want to remove the openal init/destory lines
	gDevice = alcOpenDevice(NULL);
	if (alcGetError(gDevice) != ALC_NO_ERROR)
	{
		return;
	}
	gContext = alcCreateContext(gDevice, NULL);
	if (alcGetError(gDevice) != ALC_NO_ERROR)
	{
		alcCloseDevice(gDevice);
		gDevice = NULL;
		return;
	}
	alcMakeContextCurrent(gContext);
	if (alcGetError(gDevice) != ALC_NO_ERROR)
	{
		alcDestroyContext(gContext);
		gContext = NULL;
		alcCloseDevice(gDevice);
		gDevice = NULL;
	}
}

OpenAL_AudioInterfaceFactory::~OpenAL_AudioInterfaceFactory()
{
	return;
	
	if (gDevice != NULL)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(gContext);
		alcCloseDevice(gDevice);
	}
}

OpenAL_AudioInterface* OpenAL_AudioInterfaceFactory::createInstance(theoraplayer::VideoClip* clip, int channelsCount, int frequency)
{
	return new OpenAL_AudioInterface(clip, channelsCount, frequency);
}
