
#ifdef WX_THREADS

#include "wxwonkey.h"
//#include "wxgc_mx.h"
#include "wxweakref.h"

#include <mutex>
#include <condition_variable>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#endif

namespace wxDB{

	void stop();
	
	void stopped();
	
	void error( wxString err );
}

namespace{

	typedef std::chrono::duration<double> Duration;
	typedef std::chrono::high_resolution_clock Clock;
	
	double now(){
	
		static Clock::time_point start=Clock::now();
		
		auto elapsed=(Clock::now()-start).count();
	
		return elapsed * ((double)Clock::period::num/(double)Clock::period::den);
	}
}

namespace wxGC{

	const char *state="IDLE";

	size_t trigger=4*1024*1024;
	int suspended=1;
	
	size_t memused;
	size_t malloced;

	wxGCThread *threads;
	thread_local wxGCThread *currentThread;
	thread_local wxGCFiber *currentFiber;

	std::atomic_char markedBit;
	std::atomic_char unmarkedBit;
	std::atomic<wxGCNode*> markQueue;
	
	std::mutex collectorMutex;
	
	wxGCRoot *roots;
	wxGCTmp *retained;
	wxGCNode *markedList;
	wxGCNode *unmarkedList;
	wxGCNode markLists[2];
	wxGCNode freeList;
	
	size_t markedBytes;
	size_t unmarkedBytes;
	size_t allocedBytes;
	
	void *pools[32];
	unsigned char *poolBuf;
	size_t poolBufSize;
	std::mutex poolsMutex;
	
	void suspendSigHandler( int sig );
	
	bool inited;
	
	void finit(){
	
		suspended=0x7fffffff;
		
		inited=false;
	}
	
	void init(){

		if( inited ) return;
		inited=true;
		
//		wx_printf( "Initializing threaded GC\n" );
		
		markedBit=1;
		markedList=&markLists[0];
		markedList->succ=markedList->pred=markedList;
		
		unmarkedBit=2;
		unmarkedList=&markLists[1];
		unmarkedList->succ=unmarkedList->pred=unmarkedList;
		
		freeList.succ=freeList.pred=&freeList;
		
		threads=new wxGCThread;
		
		currentThread=threads;
		
		currentFiber=currentThread->fibers;
		
#ifndef _WIN32
		struct sigaction action;
		memset( &action,0,sizeof(action) );
		action.sa_handler=suspendSigHandler;
		action.sa_flags=SA_RESTART;
			
		if( sigaction( SIGUSR2,&action,0 )<0 ) exit(-1);
#endif
		suspended=0;
		
		atexit( finit );
	}
	
	void setTrigger( size_t size ){
	
		trigger=size;
	}
	
	void suspend(){
	
		++suspended;
	}
	
	void resume(){
	
		--suspended;
	}
	
	__forceinline void insert( wxGCNode *p,wxGCNode *succ ){
		p->succ=succ;
		p->pred=succ->pred;
		p->pred->succ=p;
		succ->pred=p;
	}

	__forceinline void remove( wxGCNode *p ){	
		p->pred->succ=p->succ;
		p->succ->pred=p->pred;
	}
	
	void lockCollector(){
	
//		printf( "lockCollector\n" );fflush( stdout );
	
		if( inited ) collectorMutex.lock();
	}
	
	void unlockCollector(){
	
//		printf( "unlockCollector\n" );fflush( stdout );
	
		if( inited ) collectorMutex.unlock();
	}
	

#ifdef _WIN32

	//collectorMutex locked.
	//
	void suspendThreads(){
	
		for( wxGCThread *thread=currentThread->succ;thread!=currentThread;thread=thread->succ ){

			int n=(int)SuspendThread( thread->handle );
						
			if( n<0 ){ printf( "SuspendThread failed! n=%i\n",n );fflush( stdout );exit( -1 ); }
		}

		for( wxGCThread *thread=currentThread->succ;thread!=currentThread;thread=thread->succ ){

			CONTEXT context={0};//CONTEXT_CONTROL};
						
			if( !GetThreadContext( thread->handle,&context ) ){ printf( "GetThreadContext failed\n" );fflush( stdout );exit( -1 ); }
		}
	}
	
	//collectorMutex locked.
	//
	void resumeThreads(){
	
		for( wxGCThread *thread=currentThread->succ;thread!=currentThread;thread=thread->succ ){

			ResumeThread( thread->handle );
		}
	}

#else
	
	std::mutex suspendMutex;
	std::condition_variable_any suspendCondvar;
	std::atomic_int threadsSuspending{0};
	
	std::mutex resumeMutex;
	std::condition_variable_any resumeCondvar;
	std::atomic_int resumeCount{0};
	
	void suspendSigHandler( int sig ){
	
		int resume=resumeCount+1;
	
		//signal suspended
		suspendMutex.lock();
		threadsSuspending-=1;
		suspendMutex.unlock();
		suspendCondvar.notify_one();
		
		//wait for resume
		resumeMutex.lock();
		while( resumeCount!=resume ) resumeCondvar.wait( resumeMutex );
		resumeMutex.unlock();
	}
	
	//collectorMutex locked.
	//
	void suspendThreads(){
	
		threadsSuspending=0;
	
		for( wxGCThread *thread=currentThread->succ;thread!=currentThread;thread=thread->succ ){
		
			++threadsSuspending;
		}
		
		for( wxGCThread *thread=currentThread->succ;thread!=currentThread;thread=thread->succ ){
		
			pthread_kill( (pthread_t)thread->handle,SIGUSR2 );
		}
		
		suspendMutex.lock();
		while( threadsSuspending ) suspendCondvar.wait( suspendMutex );
		suspendMutex.unlock();
	}
	
	//collectorMutex locked.
	//
	void resumeThreads(){
	
		//signal resume
		resumeMutex.lock();
		resumeCount+=1;
		resumeMutex.unlock();
		resumeCondvar.notify_all();
	}

#endif
	
	//collectorMutex locked.
	//
	void reclaim( size_t size ){
	
		size_t freed=0;
	
		while( freeList.succ!=&freeList && freed<size ){
		
			wxGCNode *p=freeList.succ;
			
			freed+=mallocSize( p );
			
			remove( p );
			
			if( p->flags & 2 ){

				//printf( "deleting weak refs for: %s %p\n",p->typeName(),p );fflush( stdout );
				
				wxGCWeakRef **pred=&wxGC::weakRefs,*curr;
				
				while( curr=*pred ){
					if( curr->target==p ){
						curr->target=0;
						*pred=curr->succ;
					}else{
						pred=&curr->succ;
					}
				}
			}
			
			if( p->flags & 1 ){
				
				//printf( "finalizing: %s %p\n",p->typeName(),p );fflush( stdout );
				
				++suspended;
				
				p->state=char(unmarkedBit);
				
				p->gcFinalize();
				
				if( p->state==markedBit ) wxRuntimeError( "Object resurrected in finalizer" );
					
				--suspended;
			}
			
			p->~wxGCNode();
			
			wxGC::free( p );
		}
	}
	
	//collectorMutex locked.
	//
	void markRoots(){
	
		for( wxGCRoot *root=roots;root;root=root->succ ){
		
			root->gcMark();
		}
	}
	
	//collectorMutex locked + threads suspended.
	//
	void markRetained(){
	
		for( wxGCTmp *tmp=retained;tmp;tmp=tmp->succ ){
		
			enqueue( tmp->node );
		}
	}
	
	//collectorMutex locked + threads suspended.
	//
	void markFibers(){
	
		wxGCThread *thread=threads;
		
		for(;;){
		
			wxGCMark( thread->entry );
		
			wxGCFiber *fiber=thread->fibers;
		
			for(;;){
			
				wxGCMark( fiber->entry );
	
				for( wxGCFrame *frame=fiber->frames;frame;frame=frame->succ ){
				
					frame->gcMark();
				}
				
				for( wxGCNode *node=fiber->ctoring;node;node=node->qsucc ){
				
					node->gcMark();
				}
				
				for( wxGCTmp *tmp=fiber->tmps;tmp;tmp=tmp->succ ){
				
					enqueue( tmp->node );
				}
				
				fiber=fiber->succ;
				
				if( fiber==thread->fibers ) break; 
			}
			
			thread=thread->succ;
			
			if( thread==threads ) break;
		}
	}
	
	//collectorMutex locked.
	//
	void markQueued( size_t tomark ){
	
		while( markQueue && markedBytes<tomark ){
			
			wxGCNode *p=markQueue;
			while( !markQueue.compare_exchange_weak( p,p->qsucc ) ){}
				
			remove( p );
			
			p->gcMark();
			
			insert( p,markedList );
			
			p->state=char(markedBit);

			markedBytes+=mallocSize( p );
		}
	}

	//collectorMutex locked.
	//
	void sweep(){
	
		double start=now();
		
//		printf( "GC info: sweeping...\n" );fflush( stdout );
		
		suspendThreads();
		
		markRetained();
		
		markFibers();
	
		markQueued( SIZE_MAX );
		
		if( unmarkedList->succ!=unmarkedList ){
			
			//append unmarked to end of free queue
			unmarkedList->succ->pred=freeList.pred;
			unmarkedList->pred->succ=&freeList;
			freeList.pred->succ=unmarkedList->succ;
			freeList.pred=unmarkedList->pred;
			
			//clear unmarked
			unmarkedList->succ=unmarkedList->pred=unmarkedList;
		}

		//swap mark/unmarked lists
		
		auto tmp1=markedList;markedList=unmarkedList;unmarkedList=tmp1;
		auto tmp2=char(markedBit);markedBit=char(unmarkedBit);unmarkedBit=tmp2;
		unmarkedBytes=markedBytes;
		markedBytes=0;

		//start new sweep phase
		allocedBytes=0;

		resumeThreads();
		
		markRoots();
		
		double elapsed=now()-start;
		
//		wx_printf( "sweep=%g (%ims)\n",elapsed,int(elapsed*1000+0.5) );fflush( stdout );
		
//		printf( "end sweep\n" );fflush( stdout );
	}
	
	void retain( wxGCNode *node ){
		
		if( !node ) return;
		
		wxGCTmp *tmp=currentFiber->freeTmps;
		if( tmp ) currentFiber->freeTmps=tmp->succ; else tmp=new wxGCTmp;
		tmp->node=node;
		
		lockCollector();
		
		tmp->succ=retained;
		retained=tmp;
		
		unlockCollector();
	}
	
	void release( wxGCNode *node ){
		if( !node ) return;
		
		lockCollector();
		
		wxGCTmp **p=&retained;
		while( wxGCTmp *tmp=*p ){
			if( tmp->node!=node ){
				p=&tmp->succ;
				continue;
			}
			*p=tmp->succ;
			tmp->succ=currentFiber->freeTmps;
			currentFiber->freeTmps=tmp;
			break;
		}
		
		unlockCollector();
	}
	
	void *malloc( size_t size ){
	
//		printf( "malloc %u\n",size );fflush( stdout );
	
		size=(size+8+7) & ~7;
		
		memused+=size;
		
		if( !suspended ){
			
			lockCollector();

			if( allocedBytes+size>=trigger ){
				
				state="SWEEPING";
				
				sweep();
				
			}else{
			
				state="MARKING";
			
				markQueued( double( allocedBytes+size ) / double( trigger ) * double( unmarkedBytes + trigger ) );
			}
			
			state="RECLAIMING";			
			
			reclaim( size );
			
			state="IDLE";
			
			unlockCollector();
		}
		
		void *p;
		
		if( size<256 ){
			
			if( inited ) poolsMutex.lock();
			
			if( pools[size>>3] ){
				
				p=pools[size>>3];
				pools[size>>3]=*(void**)p;
				
			}else{
			
				if( size>poolBufSize ){
					if( poolBufSize ){
						*(void**)poolBuf=pools[poolBufSize>>3];
						pools[poolBufSize>>3]=poolBuf;
					}
					poolBufSize=65536;
					poolBuf=(unsigned char*)::malloc( poolBufSize );
					malloced+=poolBufSize;
				}
				p=poolBuf;
				poolBuf+=size;
				poolBufSize-=size;
			}
			
			if( inited ) poolsMutex.unlock();
			
		}else{
			p=::malloc( size );
			malloced+=size;
		}
		
		allocedBytes+=size;
		size_t *q=(size_t*)p;
		if( sizeof(size_t)==4 ) ++q;
		*q++=size;

//		printf( "end malloc %u\n",size );fflush( stdout );
	
		return q;
	}
	
	size_t mallocSize( void *p ){
	
		if( p ) return *((size_t*)p-1);
		
		return 0;
	}
	
	void free( void *p ){
	
		if( !p ) return;
		
		size_t *q=(size_t*)p;
		size_t size=*--q;
		if( sizeof(size_t)==4 ) --q;
		
#ifndef NDEBUG
		memset( q,0xa5,size );
#endif
		
		memused-=size;
		
		if( size<256 ){

			if( inited ) poolsMutex.lock();
			
			*(void**)q=pools[size>>3];
			pools[size>>3]=q;

			if( inited ) poolsMutex.unlock();
			
		}else{
			malloced-=size;
			::free( q );
		}
	}
	
	void collect(){
	
		if( !inited ) return;
		
		static size_t maxused;
		
		lockCollector();
	
		sweep();
		
		reclaim( SIZE_MAX );

		unlockCollector();
		
		if( memused>maxused ) maxused=memused;
		
//		printf( "Collect complete: memused=%i max memused=%i\n",memused,maxused );fflush( stdout );
	}

#ifndef NDEBUG	
	void qinsert( wxGCNode *p ){

		static int max_n;
		
		int n=0;
		
		p->qsucc=markQueue;
		while( !markQueue.compare_exchange_weak( p->qsucc,p ) ){ ++n; }
			
		if( n>max_n ){ max_n=n;printf( "GC info: max spins=%i\n",max_n );fflush( stdout ); }			
	}
	
	void enqueue( wxGCNode *p ){
		
		if( !p || p->state.load()!=unmarkedBit ) return;
		
		char oldstate=p->state.exchange( 4 );
		
		if( oldstate==4 ) return;
		
		if( oldstate!=unmarkedBit ){ printf( "GC info: redundant enqueue\n" );fflush( stdout ); }
		
		qinsert( p );
	}
	
	void beginCtor( wxGCNode *p ){
		p->state=4;
		p->flags=0;
		p->qsucc=currentFiber->ctoring;
		currentFiber->ctoring=p;
	}
	
	void endCtor( wxGCNode *p ){
		currentFiber->ctoring=p->qsucc;
		p->succ=p->pred=p;
		qinsert( p );
	}
#endif
}

// ***** wxGCNode *****

void wxGCNode::gcNeedsFinalize(){
	flags|=1;
}

void wxGCNode::gcFinalize(){
}

void wxGCNode::gcMark(){
}

void wxGCNode::dbEmit(){
}

const char *wxGCNode::typeName()const{

	return "wxGCNode";
}

// ***** wxGCThread *****

wxGCThread::wxGCThread():succ( this ),pred( this ),fibers( new wxGCFiber ){

#if _WIN32
	handle=OpenThread( THREAD_ALL_ACCESS,FALSE,GetCurrentThreadId() );
#else
	handle=(void*)pthread_self();
#endif

}

wxGCThread::~wxGCThread(){

#ifdef _WIN32
	CloseHandle( handle );
#endif
}

void wxGCThread::link(){

	wxGC::lockCollector();
	
	succ=wxGC::threads;
	pred=wxGC::threads->pred;
	wxGC::threads->pred=this;
	pred->succ=this;
	
	wxGC::currentThread=this;
	wxGC::currentFiber=fibers;
	
	wxGC::unlockCollector();
}

void wxGCThread::unlink(){

	wxGC::lockCollector();
	
	pred->succ=succ;
	succ->pred=pred;
	
	wxGC::currentThread=0;
	wxGC::currentFiber=0;
	
	wxGC::unlockCollector();
}

// ***** wxGCFiber *****

wxGCFiber::wxGCFiber():succ( this ),pred( this ),frames( nullptr ),tmps( nullptr ),freeTmps( nullptr ),ctoring( nullptr ){
}
	
void wxGCFiber::link(){

	succ=wxGC::currentThread->fibers;
	pred=wxGC::currentThread->fibers->pred;
	wxGC::currentThread->fibers->pred=this;
	pred->succ=this;
}

void wxGCFiber::unlink(){

	pred->succ=succ;
	succ->pred=pred;
}

// ***** wxGCFrame *****

void wxGCFrame::gcMark(){
}

// ***** wxGCRoot *****

wxGCRoot::wxGCRoot(){

	wxGC::lockCollector();
	
	succ=wxGC::roots;
	wxGC::roots=this;
	
	wxGC::unlockCollector();
}

void wxGCRoot::gcMark(){
}

#endif
