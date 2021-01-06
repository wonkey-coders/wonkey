
#include "app.h"

#include "../../../std/async/native/async.h"

#include <SDL.h>

namespace wxApp{

	void postEventFilter( wxAsync::Event *event ){

		SDL_UserEvent uevent;
		uevent.type=SDL_USEREVENT;
		uevent.code=0;
		uevent.data1=event;
		uevent.data2=0;
	
		if( SDL_PeepEvents( (SDL_Event*)&uevent,1,SDL_ADDEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT )!=1 ){
			//TODO: Cleanup shutdown!
			//printf( "SDL_PeepEvents error: %s\n",SDL_GetError() );fflush( stdout );
		}
	}

	void init(){

		wxAsync::setPostEventFilter( postEventFilter );
	}
}
