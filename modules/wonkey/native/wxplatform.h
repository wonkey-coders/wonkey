
#ifndef WX_PLATFORM_H
#define WX_PLATFORM_H

#ifdef _WIN32

	#define WX_WINDOWS 1

   #ifdef _WIN64
   
   #endif
   
#elif __APPLE__

    #include "TargetConditionals.h"
    
    #if TARGET_IPHONE_SIMULATOR
    
    	#define WX_IOS 1
    
    #elif TARGET_OS_IPHONE
    
    	#define WX_IOS 1
    	
    #elif TARGET_OS_MAC
    
        #define WX_MACOS 1
        
    #else
    
    	#error "Unknown Apple platform"
    
    #endif
    
#elif __EMSCRIPTEN__

	#define WX_EMSCRIPTEN 1
	    
#elif __ANDROID__

	#define WX_ANDROID 1
	
#elif __linux__

	#define WX_LINUX 1

/*	
#elif __unix__ // all unices not caught above

    // Unix
    
#elif defined(_POSIX_VERSION)

    // POSIX
*/
    
#else

	#error "Unknown compiler"

#endif

#endif
