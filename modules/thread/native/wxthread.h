
#ifndef WX_THREAD_H
#define WX_THREAD_H

#include "wxwonkey.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

struct wxThread{

	static std::atomic_int next_id;
	
	static thread_local int current_id;
	
	std::thread thread;
	
	bool running=false;
	
	int  start( wxFunction<void()> entry );
	
	void detach();
	
	void join();
};

struct wxMutex : public std::mutex{
};

struct wxCondvar : public std::condition_variable_any{
};

#endif
