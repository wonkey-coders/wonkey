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
/// Defines an audio interface for OpenAL.

#ifndef THEORAPLAYER_DEMOS_OPENAL_AUDIO_INTERFACE_H
#define THEORAPLAYER_DEMOS_OPENAL_AUDIO_INTERFACE_H

#ifndef __APPLE__
#include <AL/al.h>
#include <AL/alc.h>
#else
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
#include <queue>

#include <theoraplayer/AudioInterface.h>
#include <theoraplayer/AudioInterfaceFactory.h>
#include <theoraplayer/Timer.h>
#include <theoraplayer/VideoClip.h>

class OpenAL_AudioInterface : public theoraplayer::AudioInterface, theoraplayer::Timer
{	
public:
	OpenAL_AudioInterface(theoraplayer::VideoClip* clip, int channelsCount, int frequency);
	~OpenAL_AudioInterface();

	//! queued audio buffers, expressed in seconds
	float getQueuedAudioSize();

	void insertData(float* data, int samplesCount);	

	void update(float timeDelta);

	void pause();
	void play();
	void seek(float time);

private:
	int sourceNumChannels;
	int maxBuffSize;
	int buffSize;
	short* tempBuffer;
	float currentTimer;

	struct OpenAL_Buffer
	{
		ALuint id;
		int samplesCount;
	};
	std::queue<OpenAL_Buffer> bufferQueue;

	ALuint source;
	int numProcessedSamples;
	int numPlayedSamples;

};

class OpenAL_AudioInterfaceFactory : public theoraplayer::AudioInterfaceFactory
{
public:
	OpenAL_AudioInterfaceFactory();
	~OpenAL_AudioInterfaceFactory();

	OpenAL_AudioInterface* createInstance(theoraplayer::VideoClip* clip, int channelsCount, int frequency);

};

#endif
