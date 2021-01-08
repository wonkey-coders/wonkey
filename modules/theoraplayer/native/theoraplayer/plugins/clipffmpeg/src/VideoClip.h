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
/// Implements an interface to be able to process the FFmpeg codec.

#ifndef CLIPFFMPEG_VIDEO_CLIP_H
#define CLIPFFMPEG_VIDEO_CLIP_H

#include <theoraplayer/AudioPacketQueue.h>
#include <theoraplayer/DataSource.h>
#include <theoraplayer/VideoClip.h>

struct AVFormatContext;
struct AVCodecContext;
struct AVCodec;
struct AVFrame;
struct AVIOContext;

#define FORMAT_NAME "FFmpeg"

// taken from vpxdec.c
struct VpxDecInputContext
{
	struct VpxInputContext* vpx_input_ctx;
	struct WebmInputContext* webm_ctx;
};

namespace clipffmpeg
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
		AVFormatContext* formatContext;
		AVCodecContext* codecContext;
		AVIOContext* avioContext;
		AVCodec* codec;
		AVFrame* frame;
		unsigned char* inputBuffer;
		int videoStreamIndex;
		int frameNumber;

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
