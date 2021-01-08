/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

//***** Mark was here *****
#define _USE_THEORA 1

#include <string>
#include <vector>

#include "Manager.h"
#include "theoraplayer.h"
#include "Utility.h"
#ifdef _USE_THEORA
#include "Theora/VideoClip_Theora.h"
#endif

namespace theoraplayer
{
	static void _log(const std::string& output)
	{
		printf("%s\n", output.c_str());
	}
	static void (*logFunction)(const std::string&) = _log;

	std::vector<VideoClip::Format> videoClipFormats;

	void init(int workerThreadCount)
	{
		theoraplayer::manager = new Manager();
#ifdef _USE_THEORA
		VideoClip::Format theora;
		theora.name = THEORA_DECODER_NAME;
		theora.extension = ".ogv";
		theora.createFunction = &VideoClip_Theora::create;
		registerVideoClipFormat(theora);
#endif
		theoraplayer::manager->setWorkerThreadCount(workerThreadCount);
	}

	void destroy()
	{
		delete theoraplayer::manager;
		theoraplayer::manager = NULL;
		videoClipFormats.clear();
	}

	void setLogFunction(void (*function)(const std::string&))
	{
		logFunction = function;
		if (logFunction == NULL)
		{
			logFunction = _log;
		}
	}

	void log(const std::string& message)
	{
		(*logFunction)(message);
	}

	void registerVideoClipFormat(VideoClip::Format format)
	{
		videoClipFormats.push_back(format);
	}

	void unregisterVideoClipFormat(const std::string& name)
	{
		foreach (VideoClip::Format, it, videoClipFormats)
		{
			if ((*it).name == name)
			{
				videoClipFormats.erase(it);
				break;
			}
		}
	}

	std::vector<VideoClip::Format> getVideoClipFormats()
	{
		return videoClipFormats;
	}

}
