
#include "async_cb.h"

#if __ANDROID__
#include <jni.h>
#endif

namespace wxAsync{

	struct AsyncCallback;

	AsyncCallback *cb_first,*cb_free;
	std::mutex cb_mutex;
	int cb_nextid;
	
	struct AsyncCallback : public Event{
	
		AsyncCallback *succ;
		wxFunction<void()> func;
		std::atomic<int> posted;
		bool oneshot;
		int id;
		
		void dispatch(){
		
			int n=posted.exchange( 0 );

			for( int i=0;i<n;++i ) func();
			
			if( !oneshot ) return;

			std::lock_guard<std::mutex> lock( cb_mutex );
			
			succ=cb_free;
			cb_free=this;
			id=0;
		}
	};
	
	int createAsyncCallback( wxFunction<void()> func,bool oneshot ){
	
		std::lock_guard<std::mutex> lock( cb_mutex );
	
		AsyncCallback *cb=cb_free;
		
		if( cb ){
			cb_free=cb->succ;
		}else{
			cb=new AsyncCallback;
		}
		cb->func=func;
		cb->posted=0;
		cb->oneshot=oneshot;
		cb->id=++cb_nextid;
		cb->succ=cb_first;
		cb_first=cb;
		
		return cb->id;
	}
	
	void destroyAsyncCallback( int callback ){
	
		std::lock_guard<std::mutex> lock( cb_mutex );
	
		AsyncCallback **prev=&cb_first;
		
		while( AsyncCallback *cb=*prev ){
			if( cb->id!=callback ){
				prev=&cb->succ;
				continue;
			}
			if( cb->posted ) return;	//OOPS, can't destroy posted callback.
			*prev=cb->succ;
			cb->succ=cb_free;
			cb_free=cb;
			return;
		}
	}

	void invokeAsyncCallback( int callback ){

		std::lock_guard<std::mutex> lock( cb_mutex );
	
		AsyncCallback **prev=&cb_first;
		
		while( AsyncCallback *cb=*prev ){
			if( cb->id!=callback ){
				prev=&cb->succ;
				continue;
			}
			if( cb->oneshot ) *prev=cb->succ;
			if( ++cb->posted==1 ) cb->post();
			break;
		}
	}

	#if __ANDROID__
	
	extern "C"{
	
	JNIEXPORT void JNICALL Java_com_wonkey_lib_WonkeyAsync_invokeAsyncCallback( JNIEnv *env,jclass clazz,jint callback ){
	
		invokeAsyncCallback( callback );
	}
	
	}
	
	#endif
}
