/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include "Exception.h"
#include "theoraplayer.h"
#include "Utility.h"

namespace theoraplayer
{
	_Exception::_Exception(const std::string& message, const char* sourceFile, int lineNumber)
	{
		this->_setInternalMessage(message, sourceFile, lineNumber);
	}

	_Exception::~_Exception()
	{
	}

	void _Exception::_setInternalMessage(const std::string& message, const char* sourceFile, int lineNumber)
	{
		this->message = "[" + std::string(sourceFile) + ":" + str(lineNumber) + "] " + message;
		// because Visual Studio on WinRT cannot properly display exceptions and stack traces for some reason even though it should
		// because Android doesn't display register data properly if an exception is thrown
		log("FATAL: " + this->message);
	}

}