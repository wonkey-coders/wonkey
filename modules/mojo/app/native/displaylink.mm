
#include "displaylink.h"

#include <CoreVideo/CoreVideo.h>

#include <SDL.h>

namespace{

CVDisplayLinkRef displayLink;

CVReturn displayLinkOutputCallback(
        CVDisplayLinkRef displayLink,
        const CVTimeStamp *inNow,
        const CVTimeStamp *inOutputTime,
        CVOptionFlags flagsIn,
        CVOptionFlags *flagsOut,
        void *displayLinkContext)
{
	SDL_UserEvent uevent{};
	uevent.type=SDL_USEREVENT;
	uevent.code=2;
				
	if( SDL_PeepEvents( (SDL_Event*)&uevent,1,SDL_ADDEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT )!=1 ){
	}
	
    return kCVReturnSuccess;
}

}

namespace wxDisplayLink{

void init(){
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, displayLinkOutputCallback, 0);
}

void enable(bool on){
	if( on ){
	    CVDisplayLinkStart(displayLink);
	}else{
		CVDisplayLinkStop(displayLink);
	}
}

}