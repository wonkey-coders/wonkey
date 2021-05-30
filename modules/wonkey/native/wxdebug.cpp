
#include "wxdebug.h"
#include "wxarray.h"
#include <wxwonkey.h>

#if _WIN32
#include <windows.h>
#include <thread>
#endif

#include <signal.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef void(*dbEmit_t)(void*);

#if WX_THREADS
namespace wxGC{
	extern const char *state;
	void suspendThreads();
	void resumeThreads();
}
#endif

namespace wxDB{

#if WX_THREADS	
	std::atomic_int nextSeq;
	thread_local wxDBContext *currentContext;
#else
	int nextSeq;
	wxDBContext *currentContext;
#endif

	wxDBContext mainContext;
	
#if !_WIN32
	void breakHandler( int sig ){
	
		currentContext->stopped=1;
	}
#endif

	//Note: doesn't work on non-mainthread on at least windows.
	//
	void sighandler( int sig  ){
	
		const char *err="SIGNAL: Unknown signal";
		
		switch( sig ){
		case SIGSEGV:err="SIGNAL: Memory access violation";break;
		case SIGILL:err= "SIGNAL: Illegal instruction";break;
		case SIGFPE:err= "SIGNAL: Floating point exception";break;
#if !_WIN32
		case SIGBUS:err= "SIGNAL: Bus error";break;
#endif	
		}
		
		char buf[160];
#ifdef WX_THREADS		
		sprintf( buf,"Wonkey Runtime Error: %s\nGC state=%s\n",err,wxGC::state );
#else
		sprintf( buf,"Wonkey Runtime Error: %s\n",err );
#endif
		wx_printf( buf );

#ifdef NDEBUG
#ifdef _WIN32
 		MessageBoxA( 0,buf,"Wonkey Runtime Error",MB_OK );
#endif
		exit( -1 );
#endif
		stopped();
	}
	
	void init(){
	
		mainContext.init();
		
		currentContext=&mainContext;
	
		signal( SIGSEGV,sighandler );
		signal( SIGILL,sighandler );
		signal( SIGFPE,sighandler );
#if !_WIN32
		signal( SIGBUS,sighandler );
#endif		

#ifndef NDEBUG
		
#if _WIN32
		if( HANDLE breakEvent=OpenEvent( EVENT_ALL_ACCESS,false,"WX_BREAK_EVENT" ) ){
//			wx_printf( "Found BREAK_EVENT!\n" );fflush( stdout );
		    std::thread( [=](){
		    	for( ;; ){
		    		WaitForSingleObject( breakEvent,INFINITE );
//	    			wx_printf( "received Break event!\n" );fflush( stdout );
					currentContext->stopped=1;
		    	}
		    } ).detach();
		}
#else		
		signal( SIGTSTP,breakHandler );
#endif
#endif
	}
	
	void emit( const char *e ){
	
		if( const char *p=strchr( e,':' ) ){
			dbEmit_t dbEmit=(dbEmit_t)( strtol( p+1,0,16 ) );
			dbEmit( (void*)strtol( e,0,16 ) );
		}else{
			wxGCNode *node=(wxGCNode*)strtoll( e,0,16 );
			node->dbEmit();
		}
		
		puts( "" );
		fflush( stdout );
	}
	
	void emitVar( wxDBVar *v ){
		wxString id=v->name;
		wxString type=v->type->type();
		wxString value=v->type->value( v->var );
		wxString t=id+":"+type+"="+value+"\n";
		wx_printf( "%s",t.c_str() );
	}
	
	void emitStack(){
	    if(!currentContext) return;
		wxDBVar *ev=currentContext->locals;
		
		for( wxDBFrame *f=currentContext->frames;f;f=f->succ ){

			wx_printf( ">%s;%s;%i;%i\n",f->decl,f->srcFile,f->srcPos>>12,f->seq );
			
			for( wxDBVar *v=f->locals;v!=ev;++v ){
				emitVar( v );
			}

			ev=f->locals;
		}
	}
	
	void error( wxString msg ){
#if _WIN32
		MessageBoxW( 0,wxWString( msg ),L"Wonkey Runtime Error",MB_OK );
#else
		wx_print( msg );
#endif
		stopped();
	}
	
	void stopped(){
	
#ifdef NDEBUG
		exit( -1 );
#endif

#ifdef WX_THREADS
		wxGC::suspendThreads();
#endif

#ifdef __EMSCRIPTEN__
		emscripten_pause_main_loop();
#endif

		wx_printf( "{{*** DEBUG ***}}\n" );
		emitStack();
		wx_printf( "\n" );
		
		fflush( stdout );
		
		for(;;){
		
			char buf[256];
			char *e=fgets( buf,256,stdin );
			if( !e ) exit( -1 );
			
#ifdef WX_THREADS
			wxGC::resumeThreads();
#endif

#ifdef __EMSCRIPTEN__
			emscripten_resume_main_loop();
#endif
			if(currentContext) {
                switch( e[0] ){
                case 'r':currentContext->stopped=0;currentContext->stepMode=0;break;
                case 'e':currentContext->stopped=1;currentContext->stepMode=0;break;
                case 's':currentContext->stopped=1;currentContext->stepMode='s';break;
                case 'l':currentContext->stopped=0;currentContext->stepMode='l';break;
                case '@':emit( e+1 );continue;
                case 'q':exit( 0 );break;
                default:
                    wx_printf( "Unrecognized debug cmd: %s\n",buf );fflush( stdout );
                    exit( -1 );
                }
			}
			return;
		}
	}
	
	wxArray<wxString> stack(){
	
		int n=0;
		if(currentContext) {
            for (wxDBFrame *frame = currentContext->frames; frame; frame = frame->succ) ++n;
        }
		
		//TODO: Fix GC issues! Can't have a free local like this in case wxString ctors cause gc sweep!!!!
		wxArray<wxString> st=wxArray<wxString>( n );
		
		int i=0;
        if(currentContext) {
            for (wxDBFrame *frame = currentContext->frames; frame; frame = frame->succ) {
                st[i++] = WX_T(frame->srcFile) + " [" + wxString(frame->srcPos >> 12) + "] " + frame->decl;
            }
        }
		
		return st;
	}
	
	void stop(){
	
		//currentContext->stopped=1;	//stop on *next* stmt.
		
		stopped();						//stop on DebugStop() stmt.
	}
	
}

void wxDBContext::init(){
	if( !localsBuf ) localsBuf=new wxDBVar[16384];
	locals=localsBuf;
	frames=nullptr;
	stepMode=0;
	stopped=0;
}

wxDBContext::~wxDBContext(){
	delete[] localsBuf;
}

wxString wxDBValue( wxString *p ){
	wxString t=*p,dd="";
	if( t.length()>100 ){
		t=t.slice( 0,100 );
		dd="...";
	}
	t=t.replace( "\"","~q" );
	t=t.replace( "\n","~n" );
	t=t.replace( "\r","~r" );
	t=t.replace( "\t","~t" );
	return WX_T("\"")+t+"\""+dd;
}
