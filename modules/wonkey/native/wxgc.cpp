
#ifndef WX_THREADS

#include "wxgc.h"
#include "wxweakref.h"

namespace wxDB{

	void stop();
	
	void stopped();
	
	void error( wxString err );
}

namespace wxGC{

	int memused;
	
	int malloced;

	size_t trigger=4*1024*1024;

	int suspended=1;
	
	int markedBit;
	int unmarkedBit;

	wxGCNode *markQueue;
	wxGCNode *markedList;
	wxGCNode *unmarkedList;
	
	wxGCRoot *roots;
	
	wxGCFiber *fibers;
	wxGCFiber *currentFiber;
	
	wxGCTmp *freeTmps;
	
	wxGCTmp *retained;

	wxGCNode markLists[2];
	wxGCNode freeList;
	
	size_t markedBytes;
	size_t unmarkedBytes;
	
	size_t allocedBytes;
	
	void *pools[32];
	
	unsigned char *poolBuf;
	size_t poolBufSize;
	
	bool inited;
	
	void init(){

		if( inited ) return;
		inited=true;

		markedBit=1;
		markedList=&markLists[0];
		markedList->succ=markedList->pred=markedList;
		
		unmarkedBit=2;
		unmarkedList=&markLists[1];
		unmarkedList->succ=unmarkedList->pred=unmarkedList;
		
		freeList.succ=freeList.pred=&freeList;
		
		fibers=new wxGCFiber;
		
		currentFiber=fibers;
		
		suspended=0;
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
	
	void reclaim( size_t size=0x7fffffff ){
	
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
				
				p->state=unmarkedBit;
				
				p->gcFinalize();
				
				if( p->state==markedBit ) wxRuntimeError( "Object resurrected in finalizer" );
					
				--suspended;
			}
			
			p->~wxGCNode();
			
			wxGC::free( p );
		}
	}
	
	void markQueued( size_t tomark=0x7fffffff ){
	
		while( markQueue && markedBytes<tomark ){

			wxGCNode *p=markQueue;
			markQueue=p->succ;
			
			insert( p,markedList );
			
			markedBytes+=mallocSize( p );
			
			p->gcMark();
		}
	}

	void markRoots(){
	
		for( wxGCRoot *root=roots;root;root=root->succ ){
		
			root->gcMark();
		}
	}
	
	void markRetained(){
	
		for( wxGCTmp *tmp=retained;tmp;tmp=tmp->succ ){
		
			enqueue( tmp->node );
		}
	}
	
	void markFibers(){
	
		wxGCFiber *fiber=fibers;
		
		for(;;){
		
			wxGCMark( fiber->entry );

			for( wxGCFrame *frame=fiber->frames;frame;frame=frame->succ ){
			
				frame->gcMark();
			}
			
			for( wxGCNode *node=fiber->ctoring;node;node=node->succ ){
			
				node->gcMark();
			}
			
			for( wxGCTmp *tmp=fiber->tmps;tmp;tmp=tmp->succ ){
			
				enqueue( tmp->node );
			}
			
			fiber=fiber->succ;
			
			if( fiber==fibers ) break; 
		}
	}
	
	void sweep(){
	
		markRetained();
		
		markFibers();
	
		markQueued();
		
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
		auto tmp2=markedBit;markedBit=unmarkedBit;unmarkedBit=tmp2;
		unmarkedBytes=markedBytes;
		markedBytes=0;

		//start new sweep phase
		allocedBytes=0;

		markRoots();
	}
	
	void retain( wxGCNode *node ){
		WXGC_VALIDATE( node );

		if( !node ) return;
		
		wxGCTmp *tmp=freeTmps;
		if( tmp ) freeTmps=tmp->succ; else tmp=new wxGCTmp;
			
		tmp->node=node;
		tmp->succ=retained;
		retained=tmp;
	}
	
	void release( wxGCNode *node ){
		if( !node ) return;
		
		wxGCTmp **p=&retained;
		while( wxGCTmp *tmp=*p ){
			if( tmp->node==node ){
				*p=tmp->succ;
				tmp->succ=freeTmps;
				freeTmps=tmp;
				return;
			}
			p=&tmp->succ;
		}
		printf( "Warning! wxGC::release() - node not found!\n" );
	}
	
	void *malloc( size_t size ){
	
		size=(size+8+7) & ~7;
		
		memused+=size;
		
		
		if( !suspended ){

			if( allocedBytes+size>=trigger ){
				
				sweep();
				
			}else{
			
				markQueued( double( allocedBytes+size ) / double( trigger ) * double( unmarkedBytes + trigger ) );
			}
			
			reclaim( size );
		}
		
		void *p;
		
		if( size<256 ){
			
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
		}else{
			p=::malloc( size );
			malloced+=size;
		}
		
		allocedBytes+=size;
		size_t *q=(size_t*)p;
		if( sizeof(size_t)==4 ) ++q;
		*q++=size;

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
			*(void**)q=pools[size>>3];
			pools[size>>3]=q;
		}else{
			malloced-=size;
			::free( q );
		}
	}
/*
	wxGCNode *alloc( size_t size ){

		wxGCNode *p=(wxGCNode*)wxGC::malloc( size );
		
		*((void**)p)=(void*)0xcafebabe;
		
		p->state=0;
		p->flags=0;
		
		return p;
	}
*/	
	void collect(){
	
		if( !inited ) return;
		
		static size_t maxused;
	
		sweep();
		
		reclaim();
		
		if( memused>maxused ) maxused=memused;
		
//		printf( "Collect complete: memused=%i max memused=%i\n",memused,maxused );fflush( stdout );
	}
}

#endif
