
#include "wxwonkey_c.h"

#if __ANDROID__

#include <android/log.h>

void wx_printf( const char *fmt,... ){
	va_list args;
	va_start( args,fmt );
	__android_log_vprint( ANDROID_LOG_INFO,"WX",fmt,args );
	va_end( args );
}

#else

#include <stdio.h>
#include <stdarg.h>

void wx_printf( const char *fmt,... ){
	va_list args;
	va_start( args,fmt );
	vprintf( fmt,args );
	va_end( args );
	fflush( stdout );
}

#endif
