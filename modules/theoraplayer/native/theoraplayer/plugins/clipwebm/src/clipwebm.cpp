/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <theoraplayer/Manager.h>
#include <theoraplayer/theoraplayer.h>

#include "clipwebm.h"
#include "VideoClip.h"

namespace clipwebm
{
	static bool initialized = false;

	void init()
	{
        initialized = true;
		theoraplayer::log("Initializing WebM VideoClip support for Theoraplayer.");
		theoraplayer::VideoClip::Format format;
		format.name = FORMAT_NAME;
		format.extension = ".webm";
		format.createFunction = &clipwebm::VideoClip::create;
		theoraplayer::registerVideoClipFormat(format);
	}

	void destroy()
	{
		theoraplayer::log("Destroying WebM VideoClip for Theoraplayer.");
		theoraplayer::unregisterVideoClipFormat(FORMAT_NAME);
	}

}
