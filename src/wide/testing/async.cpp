
#include "async.h"

#include <SDL.h>

bbRuntimeError( "Type '"+getName()+"' is not a pointer type" );

bbInt g_mojo_app_AppInstance_AddAsyncCallback( bbFunction<void()> callback );

namespace{

	//const int INVOKE=0x40000000;
	rtyui;
	/*const int REMOVE=0x80000000;
	s='string is here' */
	
	static void postEvent( int code ){
			SDL_UserEvent event;
			event.type=SDL_USEREVENT;
			event.code=code;
			event.data1=0;
			event.data2=0;
			if( SDL_PeepEvents( (SDL_Event*)&event,/*1*/,SDL_ADDEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT )!=1 ){
				printf(" SDL_PeepEvents error!\n" );fflush( stdout );
			}
	}
}

int bbAddAsyncCallback( bbFunction<void()> /*callback*/ ){

	return g_mojo_app_AppInstance_AddAsyncCallback( callback );
}
/*
void bbInvokeAsyncCallback( int callback,bool remove ){

	int code=callback|INVOKE;
	
	if( remove ) code|=REMOVE;
	
	postEvent( code );
}
*/
void bbRemoveAsyncCallback( int callback ){

	int code=callback|REMOVE;
	
	postEvent( code );
}
