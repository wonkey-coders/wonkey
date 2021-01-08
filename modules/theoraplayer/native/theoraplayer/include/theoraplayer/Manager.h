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
/// Defines a video manager.

#ifndef THEORAPLAYER_VIDEO_MANAGER_H
#define THEORAPLAYER_VIDEO_MANAGER_H

#include <vector>
#include <list>
#include <string>

#include "theoraplayerExport.h"
#include "VideoClip.h"

namespace theoraplayer
{
	class AudioInterfaceFactory;
	class DataSource;
	class Mutex;
	class WorkerThread;

	/// @brief This is the main singleton class that handles all playback/sync operations.
	class theoraplayerExport Manager
	{
	public:
		friend class WorkerThread;

		Manager();
		virtual ~Manager();

		int getWorkerThreadCount() const;
		void setWorkerThreadCount(int value);
		inline int getDefaultPrecachedFramesCount() const { return this->defaultPrecachedFramesCount; }
		inline void setDefaultPrecachedFramesCount(int value) { this->defaultPrecachedFramesCount = value; }
		/// @return The supported decoders (eg. Theora, AVFoundation...)
		std::vector<std::string> getSupportedFormats() const;
		/// @return Nicely formated version string.
		std::string getVersionString() const;
		/// @return Version numbers.
		void getVersion(int* major, int* minor, int* revision) const;

		inline AudioInterfaceFactory* getAudioInterfaceFactory() { return this->audioInterfaceFactory; }
		inline void setAudioInterfaceFactory(AudioInterfaceFactory* value) { this->audioInterfaceFactory = value; }

		/// @brief Searches registered clips by name
		VideoClip* findVideoClipByName(const std::string& name);

		VideoClip* createVideoClip(const std::string& filename, OutputMode outputMode = FORMAT_RGB, int precachedFramesCountOverride = 0, bool usePotStride = false);
		VideoClip* createVideoClip(DataSource* dataSource, OutputMode outputMode = FORMAT_RGB, int precachedFramesCountOverride = 0, bool usePotStride = false);
		void destroyVideoClip(VideoClip* clip);

		void update(float timeDelta);

	protected:
		typedef std::vector<VideoClip*> ClipList;
		typedef std::vector<WorkerThread*> ThreadList;

		/// @brief Stores pointers to worker threads which are decoding video and audio
		ThreadList workerThreads;
		/// @brief Stores pointers to created video clips
		ClipList clips;
		/// @brief Stores pointer to clips that were docoded in the past in order to achieve fair scheduling
		std::list<VideoClip*> workLog;
		int defaultPrecachedFramesCount;
		Mutex* workMutex;
		AudioInterfaceFactory* audioInterfaceFactory;

		void _createWorkerThreads(int count);
		void _destroyWorkerThreads();
		void _destroyWorkerThreads(int count);
		/// @brief Called by WorkerThread to request a VideoClip instance to work on decoding
		VideoClip* _requestWork(WorkerThread* caller);

	};

	theoraplayerExport extern Manager* manager;

}
#endif
