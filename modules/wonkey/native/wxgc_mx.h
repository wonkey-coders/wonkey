
#ifndef WX_GC_H
#define WX_GC_H

#ifndef WX_THREADS
#error "Wrong gc header"
#endif

#include "wxtypes.h"
#include "wxfunction.h"

struct wxGCNode;
struct wxGCThread;
struct wxGCFiber;
struct wxGCFrame;
struct wxGCRoot;
struct wxGCTmp;
	
namespace wxGC{

	extern wxGCThread *threads;
	extern thread_local wxGCThread *currentThread;
	extern thread_local wxGCFiber *currentFiber;
	
	extern std::atomic_char markedBit;
	extern std::atomic_char unmarkedBit;
	extern std::atomic<wxGCNode*> markQueue;
}

struct wxGCNode{
	
	wxGCNode *succ;
	wxGCNode *pred;
	wxGCNode *qsucc;
	std::atomic_char state;
	char flags;		//1=finalize
	char pad[2];

	wxGCNode(){}
	virtual ~wxGCNode(){}
	
	void gcNeedsFinalize();
	
	virtual void gcFinalize();
	virtual void gcMark();
	virtual void dbEmit();
	virtual const char *typeName()const;
};

struct wxGCThread{
	
	wxGCThread *succ,*pred;
	wxGCFiber *fibers;
	void *handle;

	wxFunction<void()> entry;
	
	wxGCThread();
	~wxGCThread();
	
	void link();
	void unlink();
};

struct wxGCFiber{

	wxGCFiber *succ;
	wxGCFiber *pred;
	wxGCFrame *frames;
	wxGCTmp *tmps;
	wxGCTmp *freeTmps;
	wxGCNode *ctoring;
	
	wxFunction<void()> entry;
	
	wxGCFiber();
	
	void link();
	void unlink();
};

struct wxGCFrame{
	
	wxGCFrame *succ;
	
	wxGCFrame():succ( wxGC::currentFiber->frames ){
		wxGC::currentFiber->frames=this;
	}
	
	~wxGCFrame(){
		wxGC::currentFiber->frames=succ;
	}
	
	virtual void gcMark();
};

struct wxGCRoot{
	
	wxGCRoot *succ;
	
	wxGCRoot();
	
	virtual void gcMark();
};

struct wxGCTmp{
	wxGCTmp *succ;
	wxGCNode *node;
};

namespace wxGC{

	void init();
	void setTrigger( size_t trigger );
	void suspend();
	void resume();
	void retain( wxGCNode *p );
	void release( wxGCNode *p );
	void setDebug( bool debug );
	void *malloc( size_t size );
	size_t mallocSize( void *p );
	void free( void *p );
	void collect();
	
	inline void pushTmp( wxGCNode *p ){
		wxGCTmp *tmp=currentFiber->freeTmps;
		if( tmp ) currentFiber->freeTmps=tmp->succ; else tmp=new wxGCTmp;
		tmp->succ=currentFiber->tmps;
		tmp->node=p;
		currentFiber->tmps=tmp;
	}
	
	inline void popTmps( int n ){
		while( n-- ){
			wxGCTmp *tmp=currentFiber->tmps;
			currentFiber->tmps=tmp->succ;
			tmp->succ=currentFiber->freeTmps;
			currentFiber->freeTmps=tmp;
		}
	}

	template<class T, int D> wxArray<T, D> tmp(const wxArray<T, D> &arr) {
		pushTmp(arr._rep);
		return arr;
	}

	template<class T> T *tmp( T *p ){
		pushTmp( p );
		return p;
	}
	
#ifdef NDEBUG
	__forceinline void enqueue( wxGCNode *p ){
		if( !p || p->state.load()!=unmarkedBit ) return;
		if( p->state.exchange( 4 )==4 ) return;
		p->qsucc=markQueue;
		while( !markQueue.compare_exchange_weak( p->qsucc,p ) ){}
	}

	inline void beginCtor( wxGCNode *p ){
		p->state=4;
		p->flags=0;
		p->qsucc=currentFiber->ctoring;
		currentFiber->ctoring=p;
	}
	
	inline void endCtor( wxGCNode *p ){
		currentFiber->ctoring=p->qsucc;
		p->succ=p->pred=p;
		p->qsucc=markQueue;
		while( !markQueue.compare_exchange_weak( p->qsucc,p ) ){}
	}
#else
	void enqueue( wxGCNode *p );
	void beginCtor( wxGCNode *p );
	void endCtor( wxGCNode *p );
#endif

}

template<class T> void wxGCMark( T const& ){
}

#endif
