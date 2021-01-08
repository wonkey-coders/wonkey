/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#ifdef __APPLE__
#define AVFOUNDATION_CLASSES_DEFINED
#import <AVFoundation/AVFoundation.h>

#include <theoraplayer/Exception.h>
#include <theoraplayer/FrameQueue.h>
#include <theoraplayer/Manager.h>
#include <theoraplayer/PixelTransform.h>
#include <theoraplayer/Timer.h>
#include <theoraplayer/VideoClip.h>
#include <theoraplayer/VideoFrame.h>
#include <theoraplayer/FileDataSource.h>
#include <theoraplayer/MemoryDataSource.h>
#include <theoraplayer/AudioInterfaceFactory.h>
#include <Mutex.h>

#include "Utility.h"
#include "VideoClip.h"

using namespace theoraplayer;

namespace clipavfoundation
{
#ifdef _AVFOUNDATION_BGRX
	// a fast function developed to use kernel byte swapping calls to optimize alpha decoding.
	// In AVFoundation, BGRX mode conversion is prefered to YUV conversion because apple's YUV
	// conversion on iOS seems to run faster than libtheoraplayer's implementation
	// This may change in the future with more optimizations to libtheoraplayers's YUV conversion
	// code, making this function obsolete.
	static void bgrx2rgba(unsigned char* dest, int w, int h, struct PixelTransform* t)
	{
		unsigned register int a;
		unsigned int* dst = (unsigned int*)dest;
		unsigned int* dstEnd = NULL;
		unsigned char* src = t->raw;
		int y = 0;
		int x = 0;
		int ax = 0;
		for (y = 0; y < h; ++y, src += t->rawStride)
		{
			for (x = 0, ax = w * 4, dstEnd = dst + w; dst != dstEnd; x += 4, ax += 4, ++dst)
			{
				// use the full alpha range here because the Y channel has already been converted
				// to RGB and that's in [0, 255] range.
				a = src[ax];
				*dst = (OSReadSwapInt32(src, x) >> 8) | (a << 24);
			}
		}
	}
#endif

	static CVPlanarPixelBufferInfo_YCbCrPlanar getYUVStruct(void* src)
	{
		CVPlanarPixelBufferInfo_YCbCrPlanar* bigEndianYuv = (CVPlanarPixelBufferInfo_YCbCrPlanar*) src;
		CVPlanarPixelBufferInfo_YCbCrPlanar yuv;
		yuv.componentInfoY.offset = OSSwapInt32(bigEndianYuv->componentInfoY.offset);
		yuv.componentInfoY.rowBytes = OSSwapInt32(bigEndianYuv->componentInfoY.rowBytes);
		yuv.componentInfoCb.offset = OSSwapInt32(bigEndianYuv->componentInfoCb.offset);
		yuv.componentInfoCb.rowBytes = OSSwapInt32(bigEndianYuv->componentInfoCb.rowBytes);
		yuv.componentInfoCr.offset = OSSwapInt32(bigEndianYuv->componentInfoCr.offset);
		yuv.componentInfoCr.rowBytes = OSSwapInt32(bigEndianYuv->componentInfoCr.rowBytes);
		return yuv;
	}
	
	VideoClip::VideoClip(theoraplayer::DataSource* dataSource, theoraplayer::OutputMode outputMode, int precachedFramesCount, bool usePotStride) :
		theoraplayer::VideoClip(dataSource, outputMode, precachedFramesCount, usePotStride),
		AudioPacketQueue()
	{
		this->loaded = false;
		this->reader = NULL;
		this->output = NULL;
		this->audioOutput = NULL;
		this->readAudioSamples = 0;
		this->audioFrequency = 0;
		this->audioChannelsCount = 0;
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
		this->stream = source;
		this->frameNumber = 0;
		this->endOfFile = false;
		theoraplayer::FileDataSource* fileDataSource = dynamic_cast<theoraplayer::FileDataSource*>(source);
		std::string filename;
		if (fileDataSource != NULL)
		{
			filename = fileDataSource->getFilename();
		}
		else
		{
			theoraplayer::MemoryDataSource* memoryDataSource = dynamic_cast<theoraplayer::MemoryDataSource*>(source);
			if (memoryDataSource != NULL)
			{
				filename = memoryDataSource->getFilename();
			}
			else
			{
				throw TheoraplayerException("Unable to load MP4 file");
			}
		}
		NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
		NSString* path = [NSString stringWithUTF8String:filename.c_str()];
		NSError* err = NULL;
		NSURL* url = [NSURL fileURLWithPath:path];
		AVAsset* asset = [[AVURLAsset alloc] initWithURL:url options:nil];
		this->reader = [[AVAssetReader alloc] initWithAsset:asset error:&err];
		NSArray* tracks = [asset tracksWithMediaType:AVMediaTypeVideo];
		if ([tracks count] == 0)
		{
			throw TheoraplayerException("Unable to open video file: " + filename);
		}
		AVAssetTrack* videoTrack = [tracks objectAtIndex:0];
		NSArray* audioTracks = [asset tracksWithMediaType:AVMediaTypeAudio];
		AVAssetTrack* audioTrack = (audioTracks.count > 0 ? [audioTracks objectAtIndex:0] : NULL);
#ifdef _AVFOUNDATION_BGRX
		bool yuvOutput = (this->outputMode != theoraplayer::FORMAT_BGRX && this->outputMode != theoraplayer::FORMAT_RGBA);
#else
		bool yuvOutput = true;
#endif
		
		NSDictionary* videoOptions = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:(yuvOutput) ? kCVPixelFormatType_420YpCbCr8Planar : kCVPixelFormatType_32BGRA], kCVPixelBufferPixelFormatTypeKey, nil];
		this->output = [[AVAssetReaderTrackOutput alloc] initWithTrack:videoTrack outputSettings:videoOptions];
		[this->reader addOutput:this->output];
		if ([this->output respondsToSelector:@selector(setAlwaysCopiesSampleData:)]) // Not supported on iOS versions older than 5.0
		{
			this->output.alwaysCopiesSampleData = NO;
		}
		this->fps = videoTrack.nominalFrameRate;
		this->width = this->subFrameWidth = this->stride = videoTrack.naturalSize.width;
		this->height = this->subFrameHeight = videoTrack.naturalSize.height;
		frameDuration = 1.0f / this->fps;
		this->duration = (float)CMTimeGetSeconds(asset.duration);
		this->framesCount = this->duration * this->fps;
		if (this->frameQueue == NULL)
		{
			this->frameQueue = new FrameQueue(this);
			this->frameQueue->setSize(this->precachedFramesCount);
		}
		if (this->seekFrame != -1)
		{
			this->frameNumber = this->seekFrame;
			[this->reader setTimeRange: CMTimeRangeMake(CMTimeMakeWithSeconds(this->seekFrame / this->fps, 1), kCMTimePositiveInfinity)];
		}
		if (audioTrack != NULL)
		{
			AudioInterfaceFactory* audioInterfaceFactory = theoraplayer::manager->getAudioInterfaceFactory();
			if (audioInterfaceFactory)
			{
				NSDictionary *audioOptions = [NSDictionary dictionaryWithObjectsAndKeys:
											  [NSNumber numberWithInt:kAudioFormatLinearPCM], AVFormatIDKey,
											  [NSNumber numberWithBool:NO], AVLinearPCMIsNonInterleaved,
											  [NSNumber numberWithBool:NO], AVLinearPCMIsBigEndianKey,
											  [NSNumber numberWithBool:YES], AVLinearPCMIsFloatKey,
											  [NSNumber numberWithInt:32], AVLinearPCMBitDepthKey,
											  nil];
				this->audioOutput = [[AVAssetReaderTrackOutput alloc] initWithTrack:audioTrack outputSettings:audioOptions];
				[this->reader addOutput:this->audioOutput];
				if ([this->audioOutput respondsToSelector:@selector(setAlwaysCopiesSampleData:)]) // Not supported on iOS versions older than 5.0
				{
					this->audioOutput.alwaysCopiesSampleData = NO;
				}
				NSArray* desclst = audioTrack.formatDescriptions;
				CMAudioFormatDescriptionRef desc = (CMAudioFormatDescriptionRef) [desclst objectAtIndex:0];
				const AudioStreamBasicDescription* audioDesc = CMAudioFormatDescriptionGetStreamBasicDescription(desc);
				this->audioFrequency = (unsigned int)audioDesc->mSampleRate;
				this->audioChannelsCount = audioDesc->mChannelsPerFrame;
				if (this->seekFrame != -1)
				{
					this->readAudioSamples = this->frameNumber * (this->audioFrequency * this->audioChannelsCount) / this->fps;
				}
				else
				{
					this->readAudioSamples = 0;
				}
				if (this->audioInterface == NULL)
				{
					this->setAudioInterface(audioInterfaceFactory->createInstance(this, this->audioChannelsCount, this->audioFrequency));
				}
			}
		}
#ifdef _DEBUG
		else if (!this->loaded)
		{
			theoraplayer::log("-----\nwidth: " + str(this->width) + ", height: " + str(this->height) + ", fps: " + str((int) getFPS()));
			theoraplayer::log("duration: " + strf(this->duration) + " seconds\n-----");
		}
#endif
		[this->reader startReading];
		[pool release];
		this->loaded = true;
	}
	
	bool VideoClip::_readData()
	{
		return true;
	}

	bool VideoClip::_decodeNextFrame()
	{
		if (this->reader == NULL || this->endOfFile)
		{
			return false;
		}
		AVAssetReaderStatus status = [this->reader status];
		if (status == AVAssetReaderStatusFailed)
		{
			// This can happen on iOS when you suspend the app... Only happens on the device, iOS simulator seems to work fine.
			theoraplayer::log("AVAssetReader reading failed, restarting...");
			this->seekFrame = this->timer->getTime() * this->fps;
			// just in case
			if (this->seekFrame < 0)
			{
				this->seekFrame = 0;
			}
			if (this->seekFrame > this->duration * this->fps - 1)
			{
				this->seekFrame = this->duration * this->fps - 1;
			}
			this->_executeRestart();
			status = [this->reader status];
			if (status == AVAssetReaderStatusFailed)
			{
				theoraplayer::log("AVAssetReader restart failed!");
				return false;
			}
			theoraplayer::log("AVAssetReader restart succeeded!");
		}
		theoraplayer::VideoFrame* frame = this->frameQueue->requestEmptyFrame();
		if (frame == NULL)
		{
			return false;
		}
		CMSampleBufferRef sampleBuffer = NULL;
		NSAutoreleasePool* pool = NULL;
		CMTime presentationTime;
		if (this->audioInterface != NULL)
		{
			this->_decodeAudio();
		}
		if (status == AVAssetReaderStatusReading)
		{
			pool = [[NSAutoreleasePool alloc] init];
			while ((sampleBuffer = [this->output copyNextSampleBuffer]))
			{
				presentationTime = CMSampleBufferGetOutputPresentationTimeStamp(sampleBuffer);
				float timeToDisplay = (float) CMTimeGetSeconds(presentationTime);
				frame->_init(timeToDisplay, iteration, this->frameNumber);
				++this->frameNumber;
				if (timeToDisplay < this->timer->getTime() && !this->restarted && this->frameNumber % 16 != 0)
				{
					// %16 operation is here to prevent a playback halt during video playback if the decoder can't keep up with demand.
#ifdef _DEBUG_FRAMEDROP
					theoraplayer::log(this->name + ": pre-dropped frame " + str(this->frameNumber - 1));
#endif
					++this->displayedFramesCount;
					++this->droppedFramesCount;
					CMSampleBufferInvalidate(sampleBuffer);
					CFRelease(sampleBuffer);
					sampleBuffer = NULL;
					continue; // drop frame
				}
				CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
				CVPixelBufferLockBaseAddress(imageBuffer, 0);
				void* baseAddress = CVPixelBufferGetBaseAddress(imageBuffer);
				this->stride = (int)CVPixelBufferGetBytesPerRow(imageBuffer);
//				size_t width = CVPixelBufferGetWidth(imageBuffer);
//				size_t height = CVPixelBufferGetHeight(imageBuffer);
				Theoraplayer_PixelTransform t;
				memset(&t, 0, sizeof(Theoraplayer_PixelTransform));
#ifdef _AVFOUNDATION_BGRX
				if (this->outputMode == FORMAT_BGRX || this->outputMode == FORMAT_RGBA)
				{
					t.raw = (unsigned char*)baseAddress;
					t.rawStride = mStride;
				}
				else
#endif
				{
					CVPlanarPixelBufferInfo_YCbCrPlanar yuv = getYUVStruct(baseAddress);
					t.y = (unsigned char*)baseAddress + yuv.componentInfoY.offset;  t.yStride = yuv.componentInfoY.rowBytes;
					t.u = (unsigned char*)baseAddress + yuv.componentInfoCb.offset; t.uStride = yuv.componentInfoCb.rowBytes;
					t.v = (unsigned char*)baseAddress + yuv.componentInfoCr.offset; t.vStride = yuv.componentInfoCr.rowBytes;
				}
#ifdef _AVFOUNDATION_BGRX
				if (this->outputMode == FORMAT_RGBA)
				{
					unsigned char* buffer = frame->getBuffer();
					for (int i = 0; i < 1000; ++i)
					{
						bgrx2rgba(buffer, this->width / 2, this->height, &t);
					}
					frame->ready = true;
				}
				else
#endif
				{
					frame->decode(&t);
				}
				CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
				CMSampleBufferInvalidate(sampleBuffer);
				CFRelease(sampleBuffer);
				break; // TODO - should this really be a while loop instead of an if block?
			}
		}
		if (pool != NULL)
		{
			[pool release];
		}
		if (!frame->isReady()) // in case the frame wasn't used
		{
			frame->clearInUseFlag();
		}
		if (sampleBuffer == NULL && this->reader.status == AVAssetReaderStatusCompleted) // other cases could be app suspended
		{
			if (this->autoRestart)
			{
				++iteration;
				this->_executeRestart();
			}
			else
			{
				this->_unload();
				this->endOfFile = true;
				theoraplayer::log(this->name + " finished playing.");
			}
			return false;
		}
		return true;
	}

	float VideoClip::_decodeAudio()
	{
		if (this->restarted)
		{
			return -1.0f;
		}
		if (this->reader == NULL || this->endOfFile)
		{
			return 0.0f;
		}
		AVAssetReaderStatus status = [this->reader status];
		if (this->audioOutput != NULL)
		{
			CMSampleBufferRef sampleBuffer = NULL;
			NSAutoreleasePool* pool = NULL;
			bool mutexLocked = false;
			// TODOth - this needs to be refactored without using a scope lock since it's local in theoraplayer, maybe use this->_lockAudioMutex() and a try-catch block
			Mutex::ScopeLock audioMutexLock;
			float factor = 1.0f / (this->audioFrequency * this->audioChannelsCount);
			float videoTime = (float) this->frameNumber / this->fps;
			float min = this->frameQueue->getSize() / this->fps + 1.0f;
			if (status == AVAssetReaderStatusReading)
			{
				pool = [[NSAutoreleasePool alloc] init];
				// always buffer up of audio ahead of the frames
				while (this->readAudioSamples * factor - videoTime < min)
				{
					if ((sampleBuffer = [this->audioOutput copyNextSampleBuffer]))
					{
						AudioBufferList audioBufferList;
						CMBlockBufferRef blockBuffer = NULL;
						CMSampleBufferGetAudioBufferListWithRetainedBlockBuffer(sampleBuffer, NULL, &audioBufferList, sizeof(audioBufferList), NULL, NULL, 0, &blockBuffer);
						for (int y = 0; y < audioBufferList.mNumberBuffers; ++y)
						{
							AudioBuffer audioBuffer = audioBufferList.mBuffers[y];
							float *frame = (float*)audioBuffer.mData;
							if (!mutexLocked)
							{
								audioMutexLock.acquire(this->audioMutex);
								mutexLocked = true;
							}
							this->addAudioPacket(frame, audioBuffer.mDataByteSize / (this->audioChannelsCount * sizeof(float)), this->audioGain);
							this->readAudioSamples += audioBuffer.mDataByteSize / (sizeof(float));
						}
						CFRelease(blockBuffer);
						CMSampleBufferInvalidate(sampleBuffer);
						CFRelease(sampleBuffer);
					}
					else
					{
						[this->audioOutput release];
						this->audioOutput = nil;
						break;
					}
				}
				[pool release];
			}
		}
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
		float time = this->seekFrame / getFps();
		this->timer->seek(time);
		bool paused = this->timer->isPaused();
		if (!paused)
		{
			this->timer->pause();
		}
		this->_resetFrameQueue();
#ifdef _DEBUG
		theoraplayer::log("Seek frame: " + str(this->seekFrame));
#endif
		this->lastDecodedFrameNumber = this->seekFrame;
		if (!paused)
		{
			this->timer->play();
		}
		this->seekFrame = -1;
	}

	void VideoClip::_executeRestart()
	{
		this->endOfFile = false;
		this->_unload();
		this->_load(this->stream);
		this->restarted = true;
	}

	void VideoClip::_unload()
	{
		if (this->output != NULL || this->audioOutput != NULL || this->reader != NULL)
		{
			NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
			if (this->output != NULL)
			{
				[this->output release];
				this->output = NULL;
			}
			if (this->audioOutput != NULL)
			{
				[this->audioOutput release];
				this->audioOutput = NULL;
			}
			if (this->reader != NULL)
			{
				[this->reader release];
				this->reader = NULL;
			}
			[pool release];
		}
	}

}
#endif
