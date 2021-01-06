
#include "process.h"
#include "procutil.h"

#include "../../../libc/native/libc.h"
#include "../../../std/async/native/async.h"


struct wxProcess::Rep{

	struct FinishedEvent : public wxAsync::Event{
		Rep *rep;
		wxFunction<void()> func;
		void dispatch(){
			func();
			rep->release();
		}
	};

	struct StdoutEvent : public wxAsync::Event{
		Rep *rep;
		int avail;
		wxFunction<void()> func;
		void dispatch(){
			int n=avail;
			rep->stdoutAvail=n;
			func();
			if( !n ) rep->release();
		}
	};

	int refs;
	wxAsync::Semaphore stdoutSema;
	char stdoutBuf[4096];
	char *stdoutGet;
	int stdoutAvail=0;
	bool exited=false;
	int exit=-1;
	
	FinishedEvent finishedEvent;
	StdoutEvent stdoutEvent;

#if _WIN32

	HANDLE proc;
	HANDLE in;
	HANDLE out;
	HANDLE err;
	HANDLE breakEvent;
	
	Rep( HANDLE proc,HANDLE in,HANDLE out,HANDLE err,HANDLE breakEvent ):proc( proc ),in( in ),out( out ),err( err ),breakEvent( breakEvent ),exit( -1 ),refs( 1 ){
	}
	
	void close(){
		CloseHandle( proc );
		CloseHandle( in );
		CloseHandle( out );
		CloseHandle( err );
		CloseHandle( breakEvent );
	}

#else

	int proc;
	int in;
	int out;
	int err;

	Rep( int proc,int in,int out,int err ):proc( proc ),in( in ),out( out ),err( err ),exit( -1 ),refs( 1 ){
	}
	
	void close(){
		::close( in );
		::close( out );
		::close( err );
	}

#endif
	
	void retain(){
		++refs;
	}
	
	void release(){
		if( --refs ) return;
		
		close();
		
		delete this;
	}
};

wxProcess::wxProcess():_rep( nullptr ){
}

wxProcess::~wxProcess(){

	if( !_rep ) return;
	
//	printf( "Destroying wxProcess refs=%i\n",_rep->refs );fflush( stdout );
	
	_rep->finishedEvent.func={};
	_rep->stdoutEvent.func={};
	_rep->release();
}

wxBool wxProcess::start( wxString cmd ){

	if( _rep ) return false;
	
#if _WIN32

	HANDLE in[2],out[2],err[2];
	SECURITY_ATTRIBUTES sa={sizeof(sa),0,1};
	CreatePipe( &in[0],&in[1],&sa,0 );
	CreatePipe( &out[0],&out[1],&sa,0 );
	CreatePipe( &err[0],&err[1],&sa,0 );
	HANDLE breakEvent=CreateEvent( &sa,0,0,"MX2_BREAK_EVENT" );

	STARTUPINFOW si={sizeof(si)};
	si.dwFlags=STARTF_USESTDHANDLES;
	si.hStdInput=in[0];
	si.hStdOutput=out[1];
	si.hStdError=err[1];

	PROCESS_INFORMATION pi={0};
    
	DWORD flags=CREATE_NEW_PROCESS_GROUP|CREATE_NO_WINDOW;
	
	wchar_t *wstr=_wcsdup( widen_utf8( wxCString( cmd ) ) );
	
	int res=CreateProcessW( 0,wstr,0,0,TRUE,flags,0,0,&si,&pi );
	
	free( wstr );

	CloseHandle( in[0] );
	CloseHandle( out[1] );
	CloseHandle( err[1] );

	if( !res ){
		CloseHandle( in[1] );
		CloseHandle( out[0] );
		CloseHandle( err[0] );
		return false;
	}

	CloseHandle( pi.hThread );
	
	Rep *rep=new Rep( pi.hProcess,in[1],out[0],err[0],breakEvent );
    
#else
  
	int in[2],out[2],err[2];

	pipe( in );
	pipe( out );
	pipe( err );

	char **argv=wxProcUtil::makeargv( wxCString( cmd ) );
	
	bool failed=false;

	int proc=vfork();

	if( !proc ){

#if __linux
		setsid();
#else
		setpgid(0,0);
#endif

		dup2( in[0],0 );
		dup2( out[1],1 );
		dup2( err[1],2 );

		execvp( argv[0],argv );
		
		failed=true;

		_exit( 127 );
	}
	
	if( failed ) proc=-1;

	close( in[0] );
	close( out[1] );
	close( err[1] );

	if( proc==-1 ){
		close( in[1] );
		close( out[0] );
		close( err[0] );
		return false;
	}
  
	Rep *rep=new Rep( proc,in[1],out[0],err[0] );
	
#endif

	//Create finished thread    
    rep->retain();
    rep->finishedEvent.rep=rep;
    rep->finishedEvent.func=finished;
    
    std::thread( [=](){
    
		#if _WIN32
		
	    	WaitForSingleObject( rep->proc,INFINITE );
	    	
	    	GetExitCodeProcess( rep->proc,(DWORD*)&rep->exit );
	    	
//	    	CloseHandle( rep->breakEvent );
	    		
//	    	CloseHandle( rep->proc );
	    	
		#else
		
			int status;
			waitpid( rep->proc,&status,0 );
			
			if( WIFEXITED( status ) ){
				rep->exit=WEXITSTATUS( status );
			}else{
				rep->exit=-1;
			}
			
		#endif
		
			rep->exited=true;
		
			rep->finishedEvent.post();

	} ).detach();
	

	// Create stdoutReady thread
	//
	rep->retain();
	rep->stdoutEvent.rep=rep;
	rep->stdoutEvent.avail=-1;
	rep->stdoutEvent.func=stdoutReady;
	
	std::thread( [=](){
	
		for(;;){
		
#if _WIN32		
			DWORD n=0;
			if( !ReadFile( rep->out,rep->stdoutBuf,4096,&n,0 ) ) break;
			if( n<=0 ) break;
#else
			int n=read( rep->out,rep->stdoutBuf,4096 );
			if( n<=0 ) break;
#endif
			rep->stdoutGet=rep->stdoutBuf;
			
			rep->stdoutEvent.avail=n;
			
			rep->stdoutEvent.post();

			rep->stdoutSema.wait();
			
			if( rep->stdoutAvail ) break;
		}
		
		rep->stdoutEvent.avail=0;
		
		rep->stdoutEvent.post();

	} ).detach();
	
	_rep=rep;
    
    return true;
}

wxInt wxProcess::stdoutAvail(){

	if( !_rep ) return 0;

	return _rep->stdoutAvail;
}

wxString wxProcess::readStdout(){

	if( !_rep || !_rep->stdoutAvail ) return "";

	wxString str=wxString::fromCString( _rep->stdoutGet,_rep->stdoutAvail );
	
	_rep->stdoutAvail=0;
	
	_rep->stdoutSema.signal();
	
	return str;
}

wxInt wxProcess::readStdout( void *buf,int count ){

	if( !_rep || count<=0 || !_rep->stdoutAvail ) return 0;

	if( count>_rep->stdoutAvail ) count=_rep->stdoutAvail;
	
	memcpy( buf,_rep->stdoutGet,count );
	
	_rep->stdoutGet+=count;

	_rep->stdoutAvail-=count;
	
	if( !_rep->stdoutAvail ) _rep->stdoutSema.signal();
	
	return count;
}

int wxProcess::writeStdin( wxString str ){

	if( !_rep ) return 0;

#if _WIN32	
	int n=WriteFile( _rep->in,str.c_str(),str.length(),0,0 );
#else
	int n=write( _rep->in,str.c_str(),str.length() );
#endif

	return n>=0 ? n : 0;
}

int wxProcess::writeStdin( void *buf,int count ){

	if( !_rep ) return 0;
	
#if _WIN32
	int n=WriteFile( _rep->in,buf,count,0,0 );
#else
	int n=write( _rep->in,buf,count );
#endif	

	return n>=0 ? n : 0;
}

void wxProcess::terminate(){

	if( !_rep || _rep->exited ) return;

#if _WIN32
	wxProcUtil::TerminateProcessGroup( _rep->proc,-1 );
	CancelIoEx( _rep->out,0 );
#else
	killpg( _rep->proc,SIGTERM );
#endif
}

void wxProcess::sendBreak(){

	if( !_rep || _rep->exited ) return;
	
#if _WIN32
	SetEvent( _rep->breakEvent );
#else
	killpg( _rep->proc,SIGTSTP );
#endif
}

int wxProcess::exitCode(){

	if( !_rep || !_rep->exited ) return -1;

	return _rep->exit;
}

void wxProcess::gcMark(){

	wxGCMark( finished );
	wxGCMark( stdoutReady );
	
	if( _rep ){
		wxGCMark( _rep->finishedEvent.func );
		wxGCMark( _rep->stdoutEvent.func );
	}
}
