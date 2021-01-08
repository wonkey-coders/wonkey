
#ifndef WX_THEORAPLAYER_GLUE_H
#define WX_THEORAPLAYER_GLUE_H

#include <wxwonkey.h>

namespace theoraplayer{
	class Manager;
	class VideoClip;
	class MemoryDataSource;
}

theoraplayer::Manager *wx_theoraplayer_getManager();

theoraplayer::VideoClip *wx_theoraplayer_createVideoClip( theoraplayer::Manager *self,const char *filename );

theoraplayer::VideoClip *wx_theoraplayer_createVideoClip( theoraplayer::Manager *self,const void *data,int length );

theoraplayer::MemoryDataSource *wx_theoraplayer_createMemoryDataSource( const void *data,int length,const char *formatName );

#endif
