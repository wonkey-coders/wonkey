
#ifndef WX_STD_ASYNC_H
#define WX_STD_ASYNC_H

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace wxAsync{

	struct Semaphore{
	
		int count;
		std::mutex mutex;
		std::condition_variable cond_var;
		
		Semaphore():count( 0 ){
		}
		
		Semaphore( int count ):count( count ){
		}
		
		void wait(){
			std::unique_lock<std::mutex> lock( mutex );
			while( !count ) cond_var.wait( lock );
			--count;
		}
		
		void signal(){
			std::unique_lock<std::mutex> lock( mutex );
			++count;
			cond_var.notify_one();
		}
	};
	
	struct Event{
	
		void post();
		
		void post( double delay );
	
		virtual void dispatch()=0;
	};
	
	void setPostEventFilter( void(*filter)(Event*) );
	
}

#endif
