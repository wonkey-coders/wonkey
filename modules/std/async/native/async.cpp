
#include "async.h"

#if __ANDROID__
#include <jni.h>
#endif

namespace wxAsync{

	typedef std::chrono::duration<double> Duration;
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::time_point<Clock,Duration> TimePoint;

	struct DelayedEvent{
		DelayedEvent *succ;
		Event *event;
		TimePoint time;
	};

	DelayedEvent *que;
	DelayedEvent *free_que;
	std::mutex que_mutex;
	std::condition_variable que_condvar;
	
	void initQue(){
	
		static bool inited;
		if( inited ) return;
		inited=true;
	
		std::thread( [](){
		
			std::unique_lock<std::mutex> lock( que_mutex );
			
			for(;;){
			
				if( que ){
					que_condvar.wait_until( lock,que->time );
				}else{
					que_condvar.wait( lock );
				}

				while( que && que->time<=Clock::now() ){
					
					DelayedEvent *devent=que;
	
					que=devent->succ;
					
					devent->event->post();
					
					devent->succ=free_que;
					
					free_que=devent;
				}
			}
	
		} ).detach();
	}

	void (*postEventFilter)( Event* );
	
	void setPostEventFilter( void(*filter)(Event*) ){

		postEventFilter=filter;
	}

	void Event::post(){

		postEventFilter( this );
	}
	
	void Event::post( double delay ){
	
		TimePoint time=Clock::now()+Duration( delay );
		
		initQue();
		
		{
			std::lock_guard<std::mutex> lock( que_mutex );
			
			DelayedEvent *devent=free_que;
			
			if( devent ){
				free_que=devent->succ;
			}else{
				devent=new DelayedEvent;
			}
			
			devent->event=this;
			devent->time=time;
	
			DelayedEvent *succ,**pred=&que;
			
			while( succ=*pred ){
				if( devent->time<succ->time ) break;
				pred=&succ->succ;
			}
			
			devent->succ=succ;

			*pred=devent;
		}
		
		que_condvar.notify_one();
	}
	
}
