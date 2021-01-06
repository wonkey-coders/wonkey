
#include "wxwonkey.h"

#include "wxplatform.h"

#include <stdarg.h>

int wx_argc;
char **wx_argv;

void wxMain();

#if WX_ANDROID

#include <android/log.h>

void wx_print( wxString str ){
	__android_log_write( ANDROID_LOG_INFO,"WX",str.c_str() );
}

void wx_printf( const char *fmt,... ){
	va_list args;
	va_start( args,fmt );
	__android_log_vprint( ANDROID_LOG_INFO,"WX",fmt,args );
	va_end( args );
}

#elif !WX_IOS

void wx_print( wxString str ){
	puts( str.c_str() );fflush( stdout );
}

void wx_printf( const char *fmt,... ){
	va_list args;
	va_start( args,fmt );
	vprintf( fmt,args );
	va_end( args );
	fflush( stdout );
}

#endif

#if WX_ANDROID || WX_IOS

extern "C" int SDL_main( int argc,char *argv[] ){

#else

int main( int argc,char **argv ){

#endif

	wxGC::init();
	wxDB::init();

	wx_argc=argc;
	wx_argv=argv;
	
	try{
	
		wxMain();
	
	}catch( wxThrowable *t ){
	
		printf( "\n***** Uncaught Wonkey Throwable *****\n\n" );

	}catch(...){
	
		printf( "***** Uncaught Native Exception *****\n" );fflush( stdout );
		throw;
	}
	
	return 0;
}
