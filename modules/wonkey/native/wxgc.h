
#ifndef WX_GC_H
#define WX_GC_H

#ifdef WX_THREADS
#error "Wrong gc header"
#endif

#include "wxtypes.h"
#include "wxfunction.h"

#ifndef NDEBUG
#define WXGC_VALIDATE( P ) \
if( (P) && ((P)->state!=0 && (P)->state!=1 && (P)->state!=2) ){ \
	printf( "WXGC_VALIDATE failed: %p %s %i\n",(P),(P)->typeName(),(P)->state ); \
	fflush( stdout ); \
	abort(); \
}
#else
#define WXGC_VALIDATE( P )
#endif

struct wxGCNode;
struct wxGCFiber;
struct wxGCFrame;
struct wxGCRoot;
struct wxGCTmp;

namespace wxGC{

	extern int markedBit;
	extern int unmarkedBit;
	
	extern wxGCRoot *roots;
	
	extern wxGCTmp *freeTmps;

	extern wxGCNode *markQueue;
	extern wxGCNode *unmarkedList;
	
	extern wxGCFiber *fibers;
	extern wxGCFiber *currentFiber;

	void init();
	
	void suspend();
	
	void resume();
	
	void retain( wxGCNode *p );
	
	void release( wxGCNode *p );
	
	void setDebug( bool debug );

	void setTrigger( size_t trigger );

	void *malloc( size_t size );
	
	size_t mallocSize( void *p );

	void free( void *p );

	void collect();

//	wxGCNode *alloc( size_t size );
}

struct wxGCNode{
	wxGCNode *succ;
	wxGCNode *pred;
	char pad[2];
	char state;		//0=lonely, 1/2=marked/unmarked; 3=destroyed
	char flags;		//1=finalize

	wxGCNode(){
	}
	
	void gcNeedsFinalize(){
		flags|=1;
	}
	
	virtual ~wxGCNode(){
	}
	
	virtual void gcFinalize(){
	}

	virtual void gcMark(){
	}
	
	virtual void dbEmit(){
	}
	
	virtual const char *typeName()const{
		return "wxGCNode";
	}
};

struct wxGCFiber{

	wxGCFiber *succ;
	wxGCFiber *pred;
	wxGCFrame *frames;
	wxGCNode *ctoring;
	wxGCTmp *tmps;
	wxFunction<void()> entry;
	
	wxGCFiber():succ( this ),pred( this ),frames( nullptr ),ctoring( nullptr ),tmps( nullptr ){
	}
	
	void link(){
		succ=wxGC::fibers;
		pred=wxGC::fibers->pred;
		wxGC::fibers->pred=this;
		pred->succ=this;
	}
	
	void unlink(){
		pred->succ=succ;
		succ->pred=pred;
	}
};

struct wxGCFrame{
	wxGCFrame *succ;
	
	wxGCFrame():succ( wxGC::currentFiber->frames ){
		wxGC::currentFiber->frames=this;
	}
	
	~wxGCFrame(){
		wxGC::currentFiber->frames=succ;
	}

	virtual void gcMark(){
	}
};

struct wxGCRoot{
	wxGCRoot *succ;
	
	wxGCRoot():succ( wxGC::roots ){
		wxGC::roots=this;
	}
	
	virtual void gcMark(){
	}
};

struct wxGCTmp{
	wxGCTmp *succ;
	wxGCNode *node;
};

namespace wxGC{

	inline void insert( wxGCNode *p,wxGCNode *succ ){
		p->succ=succ;
		p->pred=succ->pred;
		p->pred->succ=p;
		succ->pred=p;
	}

	inline void remove( wxGCNode *p ){	
		p->pred->succ=p->succ;
		p->succ->pred=p->pred;
	}

	inline void enqueue( wxGCNode *p ){
		WXGC_VALIDATE( p )

		if( !p || p->state!=unmarkedBit ) return;
		
		remove( p );
		p->succ=markQueue;
		markQueue=p;
		
		p->state=markedBit;
	}
	
	inline void pushTmp( wxGCNode *p ){
		WXGC_VALIDATE( p );
		
		wxGCTmp *tmp=freeTmps;
		if( tmp ) freeTmps=tmp->succ; else tmp=new wxGCTmp;
		tmp->succ=currentFiber->tmps;
		currentFiber->tmps=tmp;
		tmp->node=p;
	}
	
	inline void popTmps( int n ){
		while( n-- ){
			wxGCTmp *tmp=currentFiber->tmps;
			currentFiber->tmps=tmp->succ;
			tmp->succ=freeTmps;
			freeTmps=tmp;
		}
	}
	
	template<class T> T *tmp( T *p ){
		pushTmp( p );
		return p;
	}
	
	inline void beginCtor( wxGCNode *p ){
		p->succ=currentFiber->ctoring;
		currentFiber->ctoring=p;
		p->state=0;
		p->flags=0;
	}
	
	inline void endCtor( wxGCNode *p ){
		currentFiber->ctoring=p->succ;
		p->succ=markQueue;
		markQueue=p;
		p->state=markedBit;
	}
}

template<class T> void wxGCMark( T const& ){
}

#endif
