
#include "wxmusic.h"

#if __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include "../../../std/async/native/async.h"
#include "../../../std/async/native/async_cb.h"
#include "../../../stb-vorbis/native/stb-vorbis.h"

#include <std/filesystem/native/filesystem.h>

#include <atomic>

namespace{

	struct Counter;

	Counter *counters;
	
	//little atomic counter class...
	//
	struct Counter{
		
		Counter *succ;
		int source;
		std::atomic<int> count{};
		
		Counter( int source ):source( source ){
			succ=counters;
			counters=this;
		}
		
		~Counter(){
			Counter **pred=&counters;
			
			while( Counter *c=*pred ){
				if( c==this ){
					*pred=succ;
				}
				pred=&c->succ;
			}
		}
	};
	
	Counter *getCounter( int source ){
		for( Counter *c=counters;c;c=c->succ ){
			if( c->source==source ) return c;
		}
		return 0;
	}
}

namespace wxMusic{

	int playMusic( FILE *file,int callback,int alsource ){
	
		const int buffer_ms=100;
			
		int error=0;
		stb_vorbis *vorbis=stb_vorbis_open_file( file,0,&error,0 );
		if( !vorbis ) return false;

		stb_vorbis_info info=stb_vorbis_get_info( vorbis );
		
		Counter *buffersProcessed=new Counter( alsource );
		
		std::thread thread( [=](){
		
			ALuint source=alsource;
	
//			int length=stb_vorbis_stream_length_in_samples( vorbis );
//			float duration=stb_vorbis_stream_length_in_seconds( vorbis );
//			wx_printf( "vorbis length=%i, duration=%f, info.sample_rate=%i, info.channels=%i\n",length,duration,info.sample_rate,info.channels );

			ALenum format=(info.channels==2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16);

			int nsamples=buffer_ms*info.sample_rate/1000;
			int buffer_size=nsamples * (info.channels==2 ? 4 : 2);
			
//			wx_printf( "Samples per buffer=%i\n",nsamples );
			
			//polling for paused occasionally fails with only 2 buffers
			
			const int numbufs=3;
			
			ALuint buffers[numbufs];
			alGenBuffers( numbufs,buffers );
			
			short *vorbis_data=new short[buffer_size/2];
			
			int n=buffer_size;
			
			for( int i=0;i<numbufs;++i ){
			
				if( n ) n=stb_vorbis_get_samples_short_interleaved( vorbis,info.channels,vorbis_data,buffer_size/2 );
				
				alBufferData( buffers[i],format,vorbis_data,buffer_size,info.sample_rate );
			}

			alSourceQueueBuffers( source,numbufs,buffers );
			
			alSourcePlay( source );
			
//			wx_printf( "Playing music...\n" );

			for(;;){

				//decode more...				
				if( n ) n=stb_vorbis_get_samples_short_interleaved( vorbis,info.channels,vorbis_data,buffer_size/2 );
					
				ALenum state;
				
				for(;;){
				
					alGetSourcei( source,AL_SOURCE_STATE,&state );
					
					if( state==AL_STOPPED ) break;
						
					if( state==AL_PLAYING ){

						ALint processed;
						alGetSourcei( source,AL_BUFFERS_PROCESSED,&processed );
						
//						if( processed>1 )  wx_printf( "processed=%i\n",processed );
							
						if( processed ) break;
					}

					std::this_thread::sleep_for( std::chrono::milliseconds( buffer_ms/2 ) );
				}
				
				if( state==AL_STOPPED ){
//					wx_printf( "AL_STOPPED\n" );
					break;
				}
				
				buffersProcessed->count+=1;
					
				ALuint buffer;
				alSourceUnqueueBuffers( source,1,&buffer );
				
				if( !n ) continue;
				
				alBufferData( buffer,format,vorbis_data,buffer_size,info.sample_rate );
					
				alSourceQueueBuffers( source,1,&buffer );
			}

//			wx_printf( "Music done.\n" );
			
			alSourceStop( source );
			
			alDeleteBuffers( numbufs,buffers );
			
			delete[] vorbis_data;
			
			stb_vorbis_close( vorbis );
			
			fclose( file );
			
			wxAsync::invokeAsyncCallback( callback );
		} );
		
		thread.detach();
		
		return info.sample_rate;
	}
	
	int getBuffersProcessed( int source ){
		Counter *c=getCounter( source );
		if( c ) return c->count;
		return 0;
	}
	
	void endMusic( int source ){
		Counter *c=getCounter( source );
		delete c;
	}
}

