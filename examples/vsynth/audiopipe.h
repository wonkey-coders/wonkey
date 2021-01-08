#pragma once
#include <deque>
#include <mutex>
#include <algorithm>

typedef double Sample;

class AudioPipe{

	std::mutex mutex;
	std::deque<Sample> buffer;

public:
	int readPointer=0;
	int writePointer=0;
		
	void WriteSamples(Sample *samples,int count){	
		mutex.lock();
		for(int i=0;i<count;i++){
			buffer.push_back(samples[i]);
		}
		writePointer+=count;
		mutex.unlock();
	}
	
	void readSamples(short *dest, int sampleCount){
		mutex.lock();	
		int available=buffer.size();
		if (available>=sampleCount){
			for(int i=0;i<sampleCount;i++){
				Sample s=buffer.front();
				buffer.pop_front();			
				dest[i]=32767*std::max(-1.0, std::min(s, 1.0));
			}
			readPointer+=sampleCount;
		}
		mutex.unlock();
	}

	static void Callback(void *a, unsigned char *b, int c){
		memset(b,0,c);
		auto pipe=(AudioPipe*)a;		
		int sampleCount=c/2;
		short *dest=(short *)b;
		pipe->readSamples(dest,sampleCount);
	}
	
	void *Handle(){
		return (void *)this;
	}

	static AudioPipe *Create(){
		return new AudioPipe();
	}
};
