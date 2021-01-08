
#include "wxthread.h"

std::atomic_int wxThread::next_id{1};

thread_local int wxThread::current_id{1};

int wxThread::start( wxFunction<void()> entry ){

	int id=++next_id;
	
	running=true;
	
	thread=std::thread( [=](){
	
		wxGCThread gcThread;
		gcThread.link();
		
		wxDBContext dbContext;
		dbContext.init();
		
		wxDB::currentContext=&dbContext;
		
		current_id=id;
		
		entry();
		
		running=false;
		
		wxDB::currentContext=nullptr;
		
		gcThread.unlink();
	} );
	
	return id;
}

void wxThread::detach(){

	thread.detach();
}

void wxThread::join(){

	thread.join();
}
