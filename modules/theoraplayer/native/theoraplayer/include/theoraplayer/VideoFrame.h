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
/// Defines a video frame.

#ifndef THEORAPLAYER_VIDEO_FRAME_H
#define THEORAPLAYER_VIDEO_FRAME_H

#include "theoraplayerExport.h"
#include "VideoClip.h"
#include "VideoFrame.h"

struct Theoraplayer_PixelTransform;

namespace theoraplayer
{
	class FrameQueue;
	class VideoClip;

	class theoraplayerExport VideoFrame
	{
	public:
		friend class FrameQueue;
		friend class VideoClip;

		VideoFrame(VideoClip* clip);
		virtual ~VideoFrame();

		inline unsigned char* getBuffer() const { return this->buffer; }
		inline unsigned long getFrameNumber() const { return this->frameNumber; }
		int getWidth() const;
		int getStride() const;
		int getHeight() const;

		void clear();

		//! Called by VideoClip to decode a source buffer onto itself
		virtual void decode(struct Theoraplayer_PixelTransform* t);
		
		void clearInUseFlag() { this->inUse = false; }
		bool isReady() const { return this->ready; }
		float getTimeToDisplay() const { return this->timeToDisplay; }
		void _init(float timeToDisplay, int iteration, unsigned long frameNumber);

	protected:
		/// @brief Global time in seconds this frame should be displayed on.
		float timeToDisplay;
		/// @brief Whether the frame is ready for display or not.
		bool ready;
		/// @brief Indicates the frame is being used by TheoraWorkerThread instance.
		bool inUse;
		/// @brief Used to keep track of linear time in looping videos.
		int iteration;
		/// @brief Bytes per pixel.
		int bpp;
		/// @brief The VideoClip.
		VideoClip* clip;
		/// @brief Current buffer.
		unsigned char* buffer;
		/// @brief Current frame number.
		unsigned long frameNumber;

	};

}
#endif
