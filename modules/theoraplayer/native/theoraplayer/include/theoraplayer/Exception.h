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
/// Defines exceptions.

#ifndef THEORAPLAYER_EXCEPTION_H
#define THEORAPLAYER_EXCEPTION_H

#include <string>

#include "theoraplayerExport.h"

namespace theoraplayer
{
	/// @brief Provides functionality of a basic exception.
	class theoraplayerExport _Exception
	{
	public:
		/// @brief Basic constructor.
		/// @param[in] message Exception message.
		/// @param[in] sourceFile Name of the source file.
		/// @param[in] lineNumber Number of the line.
		_Exception(const std::string& message, const char* sourceFile, int lineNumber);
		/// @brief Destructor.
		virtual ~_Exception();

		/// @brief Gets the exception type.
		/// @return The exception type.
		virtual inline std::string getType() const { return "TheoraplayerException"; }
		/// @brief Gets the exception message.
		/// @return The exception message.
		virtual inline std::string getMessage() const { return this->message; }

	protected:
		/// @brief Exception message.
		std::string message;
		/// @brief Sets internal message.
		/// @param[in] message Exception message.
		/// @param[in] sourceFile Name of the source file.
		/// @param[in] lineNumber Number of the line.
		/// @note Should be used only when setting the error message from within the class.
		void _setInternalMessage(const std::string& message, const char* sourceFile, int lineNumber);

	};
	/// @brief Alias for simpler code.
	#define TheoraplayerException(message) theoraplayer::_Exception(message, __FILE__, __LINE__)

}
#endif
