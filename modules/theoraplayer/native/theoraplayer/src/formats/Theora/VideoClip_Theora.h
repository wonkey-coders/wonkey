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
/// Implements an interface to be able to process the Theora codec.

//***** Mark was here *****
#define _USE_THEORA 1

#ifdef _USE_THEORA
#ifndef THEORAPLAYER_VIDEO_CLIP_THEORA_H
#define THEORAPLAYER_VIDEO_CLIP_THEORA_H

#include <ogg/ogg.h>
#include <theora/theoradec.h>
#include <vorbis/vorbisfile.h>

#include "AudioPacketQueue.h"
#include "DataSource.h"
#include "Utility.h"
#include "VideoClip.h"

namespace theoraplayer
{
	struct TheoraInfoStruct
	{
		// ogg/vorbis/theora variables
		ogg_sync_state   OggSyncState;
		ogg_page         OggPage;
		ogg_stream_state VorbisStreamState;
		ogg_stream_state TheoraStreamState;
		//Theora State
		th_info        TheoraInfo;
		th_comment     TheoraComment;
		th_setup_info* TheoraSetup;
		th_dec_ctx*    TheoraDecoder;
		//Vorbis State
		vorbis_info      VorbisInfo;
		vorbis_dsp_state VorbisDSPState;
		vorbis_block     VorbisBlock;
		vorbis_comment   VorbisComment;
	};

	class VideoClip_Theora : public VideoClip, public AudioPacketQueue
	{
	public:
		VideoClip_Theora(DataSource* dataSource, OutputMode outputMode, int precachedFramesCount, bool usePotStride);
		~VideoClip_Theora();

		std::string getDecoderName() const { return THEORA_DECODER_NAME; }

		static VideoClip* create(DataSource* dataSource, OutputMode outputMode, int precachedFramesCount, bool usePotStride);

	protected:
		TheoraInfoStruct info;
		int theoraStreams;
		/// @brief Keeps track of Theora and Vorbis Streams.
		int vorbisStreams;
		unsigned int readAudioSamples;
		unsigned long lastDecodedFrameNumber;

		void _load(DataSource* source);
		bool _readData();
		bool _decodeNextFrame();
		float _decodeAudio();
		void _decodedAudioCheck();
		void _executeSeek();
		void _executeRestart();

		long _seekPage(long targetFrame, bool returnKeyFrame);
		void _readTheoraVorbisHeaders();

	};

}
#endif
#endif
