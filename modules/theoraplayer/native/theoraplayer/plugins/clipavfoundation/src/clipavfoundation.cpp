/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <theoraplayer/Manager.h>
#include <theoraplayer/theoraplayer.h>

#include "clipavfoundation.h"
#include "VideoClip.h"

namespace clipavfoundation
{
//	static bool initialized = false;

	void init()
	{
#ifdef __APPLE__
		theoraplayer::log("Initializing AVFoundation VideoClip support for Theoraplayer.");
		theoraplayer::VideoClip::Format format;
		format.name = FORMAT_NAME;
		format.extension = ".mp4";
		format.createFunction = &clipavfoundation::VideoClip::create;
		theoraplayer::registerVideoClipFormat(format);
#else
		theoraplayer::log("AVFoundation VideoClip is not support on non-Apple OSes.");
#endif
	}

	void destroy()
	{
#ifdef __APPLE__
		theoraplayer::log("Destroying AVFoundation VideoClip for Theoraplayer.");
		theoraplayer::unregisterVideoClipFormat(FORMAT_NAME);
#endif
	}

}
