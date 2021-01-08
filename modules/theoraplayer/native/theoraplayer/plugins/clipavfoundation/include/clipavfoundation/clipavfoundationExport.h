/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Defines macros for DLL exports/imports.

#ifndef CLIPAVFOUNDATION_EXPORT_H
#define CLIPAVFOUNDATION_EXPORT_H

	#ifdef _LIB
		#define clipavfoundationExport
		#define clipavfoundationFnExport
	#else
		#ifdef _WIN32
			#ifdef CLIPAVFOUNDATION_EXPORTS
				#define clipavfoundationExport __declspec(dllexport)
				#define clipavfoundationFnExport __declspec(dllexport)
			#else
				#define clipavfoundationExport __declspec(dllimport)
				#define clipavfoundationFnExport __declspec(dllimport)
			#endif
		#else
			#define clipavfoundationExport __attribute__ ((visibility("default")))
			#define clipavfoundationFnExport __attribute__ ((visibility("default")))
		#endif
	#endif
	#ifndef DEPRECATED_ATTRIBUTE
		#ifdef _MSC_VER
			#define DEPRECATED_ATTRIBUTE __declspec(deprecated("function is deprecated"))
		#else
			#define DEPRECATED_ATTRIBUTE __attribute__((deprecated))
		#endif
	#endif

#endif

