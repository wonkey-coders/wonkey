/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Implements an interface to be able to process the MP4 codec through AVFoundation.

#ifndef CLIPAVFOUNDATION_VIDEO_CLIP_H
#define CLIPAVFOUNDATION_VIDEO_CLIP_H

#include <theoraplayer/AudioPacketQueue.h>
#include <theoraplayer/DataSource.h>
#include <theoraplayer/VideoClip.h>

#ifndef AVFOUNDATION_CLASSES_DEFINED
class AVAssetReader;
class AVAssetReaderTrackOutput;
#endif

#define FORMAT_NAME "AVFoundation"

namespace clipavfoundation
{
	class VideoClip : public theoraplayer::VideoClip, public theoraplayer::AudioPacketQueue
	{
	public:
		VideoClip(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride);
		~VideoClip();

		std::string getDecoderName() const { return FORMAT_NAME; }

		static theoraplayer::VideoClip* create(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride);

	protected:
		bool loaded;
		int frameNumber;
		AVAssetReader* reader;
		AVAssetReaderTrackOutput* output;
		AVAssetReaderTrackOutput* audioOutput;
		unsigned int readAudioSamples;
		unsigned long lastDecodedFrameNumber;

		void _load(theoraplayer::DataSource* source);
		bool _readData();
		bool _decodeNextFrame();
		float _decodeAudio();
		void _decodedAudioCheck();
		void _executeSeek();
		void _executeRestart();
		void _unload();
		
	};

}
#endif
