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
/// Implements an interface to be able to process the WebM codec.

#ifndef CLIPWEBM_VIDEO_CLIP_H
#define CLIPWEBM_VIDEO_CLIP_H

#include <theoraplayer/AudioPacketQueue.h>
#include <theoraplayer/DataSource.h>
#include <theoraplayer/VideoClip.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

#include "webmdec.h"

#define FORMAT_NAME "WebM"

namespace clipwebm
{
	struct VpxDecInputContext
	{
		struct VpxInputContext* vpxInputContext;
		struct WebmInputContext* webmContext;
	};

	class VideoClip : public theoraplayer::VideoClip, public theoraplayer::AudioPacketQueue
	{
	public:
		VideoClip(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride);
		~VideoClip();

		bool _readData();
		bool _decodeNextFrame();
		void _executeRestart();
		float _decodeAudio();
		void _decodedAudioCheck();
		std::string getDecoderName() const { return FORMAT_NAME; }

		static theoraplayer::VideoClip* create(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride);

	protected:
		vpx_codec_ctx_t decoder;
		vpx_codec_dec_cfg_t cfg;
		VpxDecInputContext input;
		VpxInputContext vpxInputContext;
		WebmInputContext webmContext;
		VpxInterface* fourccInterface;
		vpx_image* frame;
		int frameNumber;
		unsigned long lastDecodedFrameNumber;

		void _load(theoraplayer::DataSource* source);
		void _executeSeek();

	};

}
#endif
