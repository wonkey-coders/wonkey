/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <memory.h>
#include <stdio.h>
#include <sys/stat.h>

#include "MemoryDataSource.h"
#include "Exception.h"
#include "Manager.h"
#include "theoraplayer.h"
#include "Utility.h"

namespace theoraplayer
{
    MemoryDataSource::MemoryDataSource(unsigned char* data, long size, const std::string& formatName, const std::string& filename)
	{
		this->filename = filename;
		this->data = data;
		this->size = size;
		this->position = 0;
        this->formatName = formatName;
	}

	MemoryDataSource::MemoryDataSource(const std::string& filename)
	{
		this->filename = filename;
		this->data = NULL;
		this->size = 0;
		this->position = 0;
        VideoClip::Format format;
        // used for determining the file format, does not throw an exception inside the ctor
        FILE* file = openSupportedFormatFile(this->filename, format, this->fullFilename);
        if (file != NULL)
        {
            fclose(file);
        }
        this->formatName = format.name;
	}

	MemoryDataSource::~MemoryDataSource()
	{
		if (this->data != NULL)
		{
			delete[] this->data;
		}
	}

	// must not be called in the ctor, can throw exceptions
	void MemoryDataSource::_loadFile()
	{
		if (this->data == NULL)
		{
			VideoClip::Format format;
			FILE* file = openSupportedFormatFile(filename, format, this->fullFilename);
			if (file == NULL)
			{
				std::string message = "Can't open or find video file: " + filename;
				log(message);
				throw TheoraplayerException(message);
			}
			this->formatName = format.name;
			
//***** Mark was here! *****
#ifdef _MSC_VER	//_WIN32

			struct _stat64 s;
			_fstati64(_fileno(file), &s);
#else
			struct stat s;
			fstat(fileno(file), &s);
#endif
			this->size = (int64_t)s.st_size;
			if (this->size > 0xFFFFFFFF)
			{
				fclose(file);
				throw TheoraplayerException("MemoryDataSource doesn't support files larger than 4GB!");
			}
			if (1)	//this->size < UINT_MAX)
			{
				this->data = new unsigned char[(unsigned int)this->size];
				fread(this->data, 1, (size_t)this->size, file);
			}
			else
			{
				fclose(file);
				throw TheoraplayerException("Unable to preload file to memory, file is too large.");
			}
			fclose(file);
		}
	}

	int MemoryDataSource::read(void* output, int count)
	{
		if (this->size == 0)
		{
			this->_loadFile();
		}
		int result = (int)((this->position + count <= this->size) ? count : this->size - this->position);
		if (result > 0)
		{
			memcpy(output, this->data + this->position, result);
			this->position += result;
		}
		return result;
	}

	void MemoryDataSource::seek(int64_t byteIndex)
	{
		this->position = byteIndex;
	}

}
