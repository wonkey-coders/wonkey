/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <theoraplayer/Manager.h>
#include <theoraplayer/theoraplayer.h>

#include "clipffmpeg.h"
#include "VideoClip.h"

namespace clipffmpeg
{
	static bool initialized = false;

	void init()
	{
		theoraplayer::log("Initializing mp4 VideoClip support for Theoraplayer.");
		theoraplayer::VideoClip::Format format;
		format.name = FORMAT_NAME;
		format.extension = ".mp4";
		format.createFunction = &clipffmpeg::VideoClip::create;
		theoraplayer::registerVideoClipFormat(format);
	}

	void destroy()
	{
		theoraplayer::log("Destroying mp4 VideoClip for Theoraplayer.");
		theoraplayer::unregisterVideoClipFormat(FORMAT_NAME);
	}

}
