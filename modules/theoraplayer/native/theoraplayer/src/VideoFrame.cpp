/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <memory.h>

#include "Manager.h"
#include "PixelTransform.h"
#include "VideoClip.h"
#include "VideoFrame.h"

//#define YUV_TEST // uncomment this if you want to benchmark YUV decoding functions

extern "C"
{
	void decodeRGB  (struct Theoraplayer_PixelTransform* t);
	void decodeRGBA (struct Theoraplayer_PixelTransform* t);
	void decodeRGBX (struct Theoraplayer_PixelTransform* t);
	void decodeARGB (struct Theoraplayer_PixelTransform* t);
	void decodeXRGB (struct Theoraplayer_PixelTransform* t);
	void decodeBGR  (struct Theoraplayer_PixelTransform* t);
	void decodeBGRA (struct Theoraplayer_PixelTransform* t);
	void decodeBGRX (struct Theoraplayer_PixelTransform* t);
	void decodeABGR (struct Theoraplayer_PixelTransform* t);
	void decodeXBGR (struct Theoraplayer_PixelTransform* t);
	void decodeGrey (struct Theoraplayer_PixelTransform* t);
	void decodeGrey3(struct Theoraplayer_PixelTransform* t);
	void decodeGreyA(struct Theoraplayer_PixelTransform* t);
	void decodeGreyX(struct Theoraplayer_PixelTransform* t);
	void decodeAGrey(struct Theoraplayer_PixelTransform* t);
	void decodeXGrey(struct Theoraplayer_PixelTransform* t);
	void decodeYUV  (struct Theoraplayer_PixelTransform* t);
	void decodeYUVA (struct Theoraplayer_PixelTransform* t);
	void decodeYUVX (struct Theoraplayer_PixelTransform* t);
	void decodeAYUV (struct Theoraplayer_PixelTransform* t);
	void decodeXYUV (struct Theoraplayer_PixelTransform* t);
}

namespace theoraplayer
{
	static void(*conversion_functions[])(struct Theoraplayer_PixelTransform*) =
	{
		0,
		decodeRGB,
		decodeRGBA,
		decodeRGBX,
		decodeARGB,
		decodeXRGB,
		decodeBGR,
		decodeBGRA,
		decodeBGRX,
		decodeABGR,
		decodeXBGR,
		decodeGrey,
		decodeGrey3,
		decodeGreyA,
		decodeGreyX,
		decodeAGrey,
		decodeXGrey,
		decodeYUV,
		decodeYUVA,
		decodeYUVX,
		decodeAYUV,
		decodeXYUV
	};

	VideoFrame::VideoFrame(VideoClip* clip) : timeToDisplay(0.0f), ready(false), inUse(false), iteration(0), bpp(0), clip(NULL), buffer(NULL), frameNumber(0)
	{
		this->clip = clip;
		// number of bytes based on output mode
		int bytemap[] = { 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 1, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4 };
		this->bpp = bytemap[this->clip->getOutputMode()];
		unsigned int size = this->clip->getStride() * this->clip->height * this->bpp;
		try
		{
			this->buffer = new unsigned char[size];
		}
		catch (std::bad_alloc)
		{
			this->buffer = NULL;
			return;
		}
		memset(this->buffer, 255, size);
	}

	VideoFrame::~VideoFrame()
	{
		if (this->buffer)
		{
			delete[] this->buffer;
		}
	}

	int VideoFrame::getWidth() const
	{
		return this->clip->getWidth();
	}

	int VideoFrame::getStride() const
	{
		return this->clip->stride;
	}

	int VideoFrame::getHeight() const
	{
		return this->clip->getHeight();
	}
	
	void VideoFrame::_init(float timeToDisplay, int iteration, unsigned long frameNumber)
	{
		this->timeToDisplay = timeToDisplay;
		this->iteration = iteration;
		this->frameNumber = frameNumber;
	}

	void VideoFrame::decode(struct Theoraplayer_PixelTransform* t)
	{
		if (t->raw != NULL)
		{
			unsigned int bufferStride = this->clip->getWidth() * this->bpp;
			if (bufferStride == t->rawStride)
			{
				memcpy(this->buffer, t->raw, t->rawStride * this->clip->getHeight());
			}
			else
			{
				unsigned char* buff = this->buffer;
				unsigned char* src = t->raw;
				int i;
				int h = this->clip->getHeight();
				for (i = 0; i < h; ++i, buff += bufferStride, src += t->rawStride)
				{
					memcpy(buff, src, bufferStride);
				}
			}
		}
		else
		{
			t->out = this->buffer;
			t->w = this->clip->getWidth();
			t->h = this->clip->getHeight();
#ifdef YUV_TEST // when benchmarking yuv conversion functions during development, do a timed average
#define N 1000
			clock_t time = clock();
			for (int i = 0; i < N; ++i)
			{
				conversion_functions[mParent->getOutputMode()](t);
			}
			float diff = (clock() - time) * 1000.0f / CLOCKS_PER_SEC;
			char s[128] = { '\0' };
			sprintf(s, "%.2f", diff / N);
			Manager::getSingleton().logMessage("YUV Decoding time: " + std::string(s) + " ms\n");
#else
			conversion_functions[this->clip->getOutputMode()](t);
#endif
		}
		this->ready = true;
	}

	void VideoFrame::clear()
	{
		this->inUse = false;
		this->ready = false;
	}

}
