
#include "fiber.h"
#include "fcontext.h"

#include "../../time/native/time.h"
#include "../../async/native/async.h"

namespace wxFiber{

	const int MAX_FIBERS=1024;
	
	const size_t STACK_SIZE=65536;	//woho

	const size_t STACK_BUF_SIZE=65536;
	
	struct Fiber{
	
		Fiber *succ;
		int id;
				
		unsigned char *stack;
		wxDBContext *dbContext;
		wxGCFiber *gcFiber;
		
		fcontext_t fcontext;
		fcontext_t fcontext2;
	};
	
	Fiber *fibers;
	Fiber *freeFibers;
	Fiber *mainFiber;
	Fiber *currFiber;
	
	unsigned char *stackBuf,*stackEnd;
	
	unsigned char *allocStack(){
		
		if( stackBuf==stackEnd ){
			stackBuf=alloc_fcontext_stack( STACK_BUF_SIZE,false );
			stackEnd=stackBuf+STACK_BUF_SIZE;
		}
		
		unsigned char *p=stackBuf;
		stackBuf+=STACK_SIZE;
		
		return p;
	}
	
	void init(){
	
		if( fibers ) return;
		
		fibers=new Fiber[MAX_FIBERS];
		wxGCFiber *gcFibers=new wxGCFiber[MAX_FIBERS];
		wxDBContext *dbContexts=new wxDBContext[MAX_FIBERS];
	
		for( int i=0;i<MAX_FIBERS;++i ){
			fibers[i].id=i;
			fibers[i].succ=&fibers[i+1];
			fibers[i].stack=nullptr;
			fibers[i].gcFiber=&gcFibers[i];
			fibers[i].dbContext=&dbContexts[i];
			fibers[i].fcontext=nullptr;
			fibers[i].fcontext2=nullptr;
		}
		fibers[MAX_FIBERS-1].succ=nullptr;
		freeFibers=&fibers[1];
		
		mainFiber=&fibers[0];
		mainFiber->gcFiber=wxGC::currentFiber;
		mainFiber->dbContext=wxDB::currentContext;
		
		currFiber=mainFiber;
	}
	
	Fiber *getFiber( int id ){
	
		if( !fibers ) return nullptr;
		
		Fiber *fiber=&fibers[id & (MAX_FIBERS-1)];
		
		if( fiber->id==id ) return fiber;
		
		return nullptr;
	}
	
	Fiber *allocFiber(){
	
		if( !fibers ) init();
	
		Fiber *fiber=freeFibers;
		if( !fiber ) return nullptr;
		
		if( !fiber->stack ) fiber->stack=allocStack();
		
		freeFibers=fiber->succ;
		
		fiber->id+=MAX_FIBERS;
		
		return fiber;
	}
	
	fcontext_t freeFiber( Fiber *fiber ){
	
		fcontext_t fcontext=fiber->fcontext2;
		
		fiber->id+=MAX_FIBERS;
		
		fiber->succ=freeFibers;
		freeFibers=fiber;
		
		return fcontext;
	}
	
	void setCurrFiber( Fiber *fiber ){

		wxGC::currentFiber=fiber->gcFiber;
		wxDB::currentContext=fiber->dbContext;
		currFiber=fiber;
	}
	
	void fiberEntry( transfer_t t ){
	
		Fiber *fiber=(Fiber*)t.data;
		
		fiber->fcontext2=t.fcontext;
		fiber->dbContext->init();
		fiber->gcFiber->link();
		
		setCurrFiber( fiber );
		
		fiber->gcFiber->entry();
		
		fiber->gcFiber->unlink();
		
		jump_fcontext( freeFiber( fiber ),nullptr );
	}
	
	// ***** API *****

	// Currently unsafe!
	//
	// gcFiber->entry will not be gc_marked until fiber is running...
	//
	int createFiber( Entry entry ){
	
		Fiber *fiber=allocFiber();
		if( !fiber ) return 0;
		
		fiber->gcFiber->entry=entry;
		fiber->fcontext=make_fcontext( fiber->stack+STACK_SIZE,STACK_SIZE,fiberEntry );
		
		return fiber->id;
	}
	
	// Safe!
	//
	int startFiber( Entry entry ){

		Fiber *fiber=allocFiber();
		if( !fiber ) return 0;

		int id=fiber->id;
		
		fiber->gcFiber->entry=entry;
		fiber->fcontext=make_fcontext( fiber->stack+STACK_SIZE,STACK_SIZE,fiberEntry );
		
		Fiber *curr=currFiber;

		fiber->fcontext=jump_fcontext( fiber->fcontext,fiber ).fcontext;

		setCurrFiber( curr );
		
		return id;
	}
	
	void resumeFiber( int id ){
	
		Fiber *fiber=getFiber( id );
		if( !fiber ){
			//
			// could signal a semaphore...?
			//
			wxDB::error( "Invalid fiber id" );
			return;
		}
		
		Fiber *curr=currFiber;
		
		fiber->fcontext=jump_fcontext( fiber->fcontext,fiber ).fcontext;
		
		setCurrFiber( curr );
	}
	
	void suspendCurrentFiber(){
	
		if( currFiber==mainFiber ){
			//
			// could wait on a semaphore...?
			//
			wxDB::error( "Can't suspend main fiber" );
			return;
		}
	
		Fiber *fiber=currFiber;
		
		fiber->fcontext2=jump_fcontext( fiber->fcontext2,nullptr ).fcontext;
		
		setCurrFiber( fiber );
	}
	
	void currentFiberSleep( double seconds ){
	
		struct ResumeEvent : public wxAsync::Event{
		
			int fiber;
			
			ResumeEvent():fiber( getCurrentFiber() ){}
			
			void dispatch(){
			
				resumeFiber( fiber );
			}
		};
		
		ResumeEvent event;
		
		event.post( seconds );
		
		suspendCurrentFiber();
	}
	
	void terminateFiber( int id ){

	}
	
	int getCurrentFiber(){
	
		if( fibers ) return currFiber->id;
		
		return 0;
	}
}
