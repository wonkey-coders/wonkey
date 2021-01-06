
#include "time.h"

#include <chrono>
#include <thread>

namespace wxTime{

	typedef std::chrono::duration<double> Duration;
	typedef std::chrono::high_resolution_clock Clock;
	
	double now(){
	
		static Clock::time_point start=Clock::now();
		
		auto elapsed=(Clock::now()-start).count();
	
		return elapsed * ((double)Clock::period::num/(double)Clock::period::den);
	}
	
	void sleep( double seconds ){
	
		std::this_thread::sleep_for( Duration( seconds ) );
	}
}
