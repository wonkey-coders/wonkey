/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <string>

#include <theoraplayer/PixelTransform.h>
#include <theoraplayer/FrameQueue.h>
#include <theoraplayer/Timer.h>
#include <theoraplayer/VideoClip.h>
#include <theoraplayer/VideoFrame.h>

#include "Utility.h"
#include "VideoClip.h"

#define READ_BUFFER_SIZE 4096

#ifdef __cplusplus
	#define __STDC_CONSTANT_MACROS
	#ifdef _STDINT_H
		#undef _STDINT_H
	#endif
	#include <stdint.h>
#endif

#define _FFMPEG_DEBUG

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "libavutil/avassert.h"
}

namespace clipffmpeg
{
	static bool ffmpegInitialised = false;

	// utility functions

	static int _readFunction(void* data, uint8_t* buf, int buf_size)
	{
#ifdef _FFMPEG_DEBUG
		theoraplayer::log("reading " + str(buf_size) + " bytes");
#endif
		theoraplayer::DataSource* src = (theoraplayer::DataSource*)data;
		return src->read(buf, buf_size);
	}

	static int64_t _seekFunction(void* data, int64_t offset, int whence)
	{
#ifdef _FFMPEG_DEBUG
		theoraplayer::log("seeking: offset = " + str((long)offset) + ", whence = " + str(whence));
#endif
		theoraplayer::DataSource* src = (theoraplayer::DataSource*)data;
		if (whence == AVSEEK_SIZE)
		{
			return src->getSize();
		}
		if (whence == SEEK_SET)
		{
			src->seek((long)offset);
		}
		else if (whence == SEEK_END)
		{
			src->seek(src->getSize() - (long)offset);
		}
		return src->getPosition();
	}

	static void avlog_theoraplayer(void* p, int level, const char* fmt, va_list vargs)
	{
		theoraplayer::log(fmt);
		static char logstr[65536] = { 0 };
		vsprintf(logstr, fmt, vargs);
		theoraplayer::log("ffmpeg: " + std::string(logstr));
	}

	std::string text;

	static void _log(const char* s)
	{
		text += s;
	}

	static void _log(const char c)
	{
		char s[2] = { c, 0 };
		_log(s);
	}

	static const AVCodec *_nextCodecForId(enum AVCodecID id, const AVCodec *prev, int encoder)
	{
		while ((prev = av_codec_next(prev)))
		{
			if (prev->id == id && (encoder ? av_codec_is_encoder(prev) : av_codec_is_decoder(prev)))
			{
				return prev;
			}
		}
		return NULL;
	}

	static int _compareCodecDesc(const void *a, const void *b)
	{
		const AVCodecDescriptor** da = (const AVCodecDescriptor**)a;
		const AVCodecDescriptor** db = (const AVCodecDescriptor**)b;
		return (*da)->type != (*db)->type ? (*da)->type - (*db)->type : strcmp((*da)->name, (*db)->name);
	}

	static unsigned _getCodecsSorted(const AVCodecDescriptor*** rcodecs)
	{
		const AVCodecDescriptor* desc = NULL;
		const AVCodecDescriptor** codecs;
		unsigned nb_codecs = 0;
		unsigned i = 0;
		while ((desc = avcodec_descriptor_next(desc)))
		{
			++nb_codecs;
		}
		if (!(codecs = (const AVCodecDescriptor**)av_calloc(nb_codecs, sizeof(*codecs))))
		{
			av_log(NULL, AV_LOG_ERROR, "Out of memory\n");
			exit(1);
		}
		desc = NULL;
		while ((desc = avcodec_descriptor_next(desc)))
		{
			codecs[i] = desc;
			++i;
		}
		av_assert0(i == nb_codecs);
		qsort(codecs, nb_codecs, sizeof(*codecs), _compareCodecDesc);
		*rcodecs = codecs;
		return nb_codecs;
	}

	static char _getMediaTypeChar(enum AVMediaType type)
	{
		switch (type)
		{
		case AVMEDIA_TYPE_VIDEO:		return 'V';
		case AVMEDIA_TYPE_AUDIO:		return 'A';
		case AVMEDIA_TYPE_DATA:			return 'D';
		case AVMEDIA_TYPE_SUBTITLE:		return 'S';
		case AVMEDIA_TYPE_ATTACHMENT:	return 'T';
		default:						return '?';
		}
	}

	static void _printCodecsForId(enum AVCodecID id, int encoder)
	{
		const AVCodec *codec = NULL;
		_log(encoder ? "encoders" : "decoders");
		while ((codec = _nextCodecForId(id, codec, encoder)))
		{
			_log(codec->name);
		}
		_log(")");
	}

	static int _showCodecs(void *optctx, const char *opt, const char *arg)
	{
		const AVCodecDescriptor** codecs;
		unsigned i;
		unsigned nb_codecs = _getCodecsSorted(&codecs);
		char tmp[1024] = { 0 };
		theoraplayer::log("Codecs:\n"
			" D..... = Decoding supported\n"
			" .E.... = Encoding supported\n"
			" ..V... = Video codec\n"
			" ..A... = Audio codec\n"
			" ..S... = Subtitle codec\n"
			" ...I.. = Intra frame-only codec\n"
			" ....L. = Lossy compression\n"
			" .....S = Lossless compression\n"
			" -------\n");
		const AVCodecDescriptor* desc = NULL;
		const AVCodec* codec = NULL;
		for (i = 0; i < nb_codecs; ++i)
		{
			desc = codecs[i];
			codec = NULL;
			_log(" ");
			_log(avcodec_find_decoder(desc->id) ? "D" : ".");
			_log(avcodec_find_encoder(desc->id) ? "E" : ".");
			_log(_getMediaTypeChar(desc->type));
			_log((desc->props & AV_CODEC_PROP_INTRA_ONLY) ? "I" : ".");
			_log((desc->props & AV_CODEC_PROP_LOSSY) ? "L" : ".");
			_log((desc->props & AV_CODEC_PROP_LOSSLESS) ? "S" : ".");
			sprintf(tmp, " %-20s %s", desc->name, desc->long_name ? desc->long_name : "");
			_log(tmp);
			/* print decoders/encoders when there's more than one or their
			* names are different from codec name */
			while ((codec = _nextCodecForId(desc->id, codec, 0)))
			{
				if (strcmp(codec->name, desc->name))
				{
					_printCodecsForId(desc->id, 0);
					break;
				}
			}
			codec = NULL;
			while ((codec = _nextCodecForId(desc->id, codec, 1)))
			{
				if (strcmp(codec->name, desc->name))
				{
					_printCodecsForId(desc->id, 1);
					break;
				}
			}
			_log("\n");
		}
		av_free(codecs);
		av_log(0, 0, "%s", text.c_str());
		return 0;
	}

	// actual class

	VideoClip::VideoClip(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride) :
		theoraplayer::VideoClip(dataSource, outputMode, precachedFramesCount, usePotStride),
		AudioPacketQueue()
	{
		this->formatContext = NULL;
		this->codecContext = NULL;
		this->codec = NULL;
		this->frame = NULL;
		this->videoStreamIndex = -1;
	}

	theoraplayer::VideoClip* VideoClip::create(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride)
	{
		return new VideoClip(dataSource, outputMode, precachedFramesCount, usePotStride);
	}

	VideoClip::~VideoClip()
	{
		this->_unload();
	}

	void VideoClip::_load(theoraplayer::DataSource* source)
	{
		this->videoStreamIndex = -1;
		this->frameNumber = 0;
		AVDictionary* optionsDict = NULL;
		if (!ffmpegInitialised)
		{
#ifdef _FFMPEG_DEBUG
			theoraplayer::log("Initializing ffmpeg");
#endif
			theoraplayer::log("avcodec version: " + str(avcodec_version()));
			av_register_all();
			av_log_set_level(AV_LOG_DEBUG);
			av_log_set_callback(avlog_theoraplayer);
			ffmpegInitialised = 1;
			//_showCodecs(0, 0, 0);
		}
		this->inputBuffer = (unsigned char*)av_malloc(READ_BUFFER_SIZE);
		this->avioContext = avio_alloc_context(this->inputBuffer, READ_BUFFER_SIZE, 0, source, &_readFunction, NULL, &_seekFunction);
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": avio context created");
#endif
		this->formatContext = avformat_alloc_context();
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": avformat context created");
#endif
		this->formatContext->pb = this->avioContext;
		int err = 0;
		if ((err = avformat_open_input(&this->formatContext, "", NULL, NULL)) != 0)
		{
			theoraplayer::log(this->name + ": avformat input opening failed!");
			theoraplayer::log(this->name + ": error_code: " + str(err));
			return;
		}
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": avformat input opened");
#endif
		// Retrieve stream information
		if (avformat_find_stream_info(this->formatContext, NULL) < 0)
		{
			return; // Couldn't find stream information
		}
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": got stream info");
#endif

		// Dump information about file onto standard error
		//av_dump_format(mFormatContext, 0, "", 0);
		// Find the first video stream
		for (unsigned int i = 0; i < this->formatContext->nb_streams; ++i)
		{
			if (this->formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				this->videoStreamIndex = i;
				break;
			}
		}
		if (this->videoStreamIndex == -1)
		{
			return; // Didn't find a video stream
		}
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": Found video stream at index " + str(this->videoStreamIndex));
#endif
		// Get a pointer to the codec context for the video stream
		this->codecContext = this->formatContext->streams[this->videoStreamIndex]->codec;
		// Find the decoder for the video stream
		this->codec = avcodec_find_decoder(this->codecContext->codec_id);
		if (this->codec == NULL)
		{
			theoraplayer::log("Unsupported codec!");
			return; // Codec not found
		}
		// Open codec
		if (avcodec_open2(this->codecContext, this->codec, &optionsDict) < 0)
		{
			return; // Could not open codec
		}
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": Codec opened");
#endif
		this->frame = av_frame_alloc();
#ifdef _FFMPEG_DEBUG
		theoraplayer::log(this->name + ": Frame allocated");
#endif
		//AVRational rational = mCodecContext->time_base;
		this->fps = 25; // TODOth - implement this!
		this->width = this->stride = this->codecContext->width;
		this->height = this->codecContext->height;
		this->frameDuration = 1.0f / this->fps;
		this->duration = (float)(this->formatContext->duration / AV_TIME_BASE);
		if (this->frameQueue == NULL) // TODOth - maybe this should be moved to theoraplayer::VideoClip
		{
			this->frameQueue = new theoraplayer::FrameQueue(this);
			this->frameQueue->setSize(this->precachedFramesCount);
		}
	}
	
	bool VideoClip::_readData()
	{
		return true;
	}

	bool VideoClip::_decodeNextFrame()
	{
		theoraplayer::VideoFrame* frame = this->frameQueue->requestEmptyFrame();
		if (frame == NULL)
		{
			return false;
		}
		AVPacket packet;
		int frameFinished = 0;
		while (av_read_frame(this->formatContext, &packet) >= 0)
		{
			if (packet.stream_index == this->videoStreamIndex)
			{
				avcodec_decode_video2(this->codecContext, this->frame, &frameFinished, &packet);
				if (frameFinished != 0)
				{
					Theoraplayer_PixelTransform pixelTransform;
					memset(&pixelTransform, 0, sizeof(Theoraplayer_PixelTransform));
					pixelTransform.y = this->frame->data[0];	pixelTransform.yStride = this->frame->linesize[0];
					pixelTransform.u = this->frame->data[1];	pixelTransform.uStride = this->frame->linesize[1];
					pixelTransform.v = this->frame->data[2];	pixelTransform.vStride = this->frame->linesize[2];
					frame->decode(&pixelTransform);
					this->_setVideoFrameTimeToDisplay(frame, this->frameNumber / this->fps);
					this->_setVideoFrameIteration(frame, this->iteration);
					this->_setVideoFrameFrameNumber(frame, this->frameNumber);
					++this->frameNumber;
					av_packet_unref(&packet);
					break;
				}
			}
			av_packet_unref(&packet);
		}
		return true;
	}

	float VideoClip::_decodeAudio()
	{
		return -1.0f;
	}

	void VideoClip::_decodedAudioCheck()
	{
		if (this->audioInterface != NULL && !this->timer->isPaused())
		{
			this->_flushSynchronizedAudioPackets(this->audioInterface, this->audioMutex);
		}
	}

	void VideoClip::_executeSeek()
	{
	}

	void VideoClip::_executeRestart()
	{
	}

	void VideoClip::_unload()
	{
		if (this->inputBuffer != NULL)
		{
			//		av_free(this->inputBuffer);
			this->inputBuffer = NULL;
		}
		if (this->avioContext != NULL)
		{
			av_free(this->avioContext);
			this->avioContext = NULL;
		}
		if (this->frame != NULL)
		{
			av_free(this->frame);
			this->frame = NULL;
		}
		if (this->codecContext)
		{
			avcodec_close(this->codecContext);
			this->codecContext = NULL;
		}
		if (this->formatContext != NULL)
		{
			avformat_close_input(&this->formatContext);
			this->formatContext = NULL;
		}
	}

}
