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
/// Provides an interface for a video data source from memory.

#ifndef THEORAPLAYER_MEMORY_DATA_SOURCE_H
#define THEORAPLAYER_MEMORY_DATA_SOURCE_H

#include "DataSource.h"
#include "theoraplayerExport.h"

namespace theoraplayer
{
	/// @brief Pre-loads the entire file and streams from memory. Very useful if you're continuously displaying a video
	/// and want to avoid disk reads. Not very practical for large files.
	class theoraplayerExport MemoryDataSource : public DataSource
	{
	public:
		MemoryDataSource(unsigned char* data, long size, const std::string& formatName, const std::string& filename = "memory");
		MemoryDataSource(const std::string& filename);
		~MemoryDataSource();

		inline std::string getFormatName() const { return this->formatName; }
		inline std::string getFilename() const { return this->filename; }
		inline int64_t getSize() { return this->size; }
		inline int64_t getPosition() { return this->position; }

		int read(void* output, int count);
		void seek(int64_t byteIndex);

		inline std::string toString() const { return "MEM:" + this->filename + " (format: " + this->formatName + ")"; }

	private:
		std::string filename;
		std::string fullFilename;
		std::string formatName;
		int64_t size;
		int64_t position;
		unsigned char* data;

		void _loadFile();

	};

}
#endif
