
#include "procutil.h"

#include <stdio.h>

namespace wxProcUtil{

#if _WIN32

	void terminateChildren( DWORD procid,HANDLE snapshot,int exitCode ){
	
		PROCESSENTRY32 procinfo;
			
		procinfo.dwSize=sizeof( procinfo );
		
		int gotinfo=Process32First( snapshot,&procinfo );

		while( gotinfo ){
		
			if( procinfo.th32ParentProcessID==procid ){
			
				terminateChildren( procinfo.th32ProcessID,snapshot,exitCode );
				 
				HANDLE child=OpenProcess( PROCESS_ALL_ACCESS,0,procinfo.th32ProcessID );
				
				if( child ){
					int res=TerminateProcess( child,exitCode );
					
					CloseHandle( child );
				}
			}
			
			gotinfo=Process32Next( snapshot,&procinfo );
		}	
	}
	
	int TerminateProcessGroup( HANDLE prochandle,int exitCode ){

		HANDLE snapshot;
		
		int procid=GetProcessId( prochandle );

		//undocumented at msdn! GetProcessId returns 0 if process finished?
		if( !procid ) return 1;
		
		snapshot=CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS,0 );
		
		if( snapshot!=INVALID_HANDLE_VALUE ){
			
			terminateChildren( GetProcessId( prochandle ),snapshot,exitCode );

			CloseHandle( snapshot );
		}
			
		int res=TerminateProcess( prochandle,exitCode );
		
		return res;
	}

#else

	char **makeargv( const char *cmd ){
	    int n,c;
	    char *p;
	    static char *args,**argv;
	
	    if( args ) free( args );
	    if( argv ) free( argv );
	    args=(char*)malloc( strlen(cmd)+1 );
	    strcpy( args,cmd );
	
	    n=0;
	    p=args;
	    while( (c=*p++) ){
	        if( c==' ' ){
	            continue;
	        }else if( c=='\"' ){
	            while( *p && *p!='\"' ) ++p;
	        }else{
	            while( *p && *p!=' ' ) ++p;
	        }
	        if( *p ) ++p;
	        ++n;
	    }
	    argv=(char**)malloc( (n+1)*sizeof(char*) );
	    n=0;
	    p=args;
	    while( (c=*p++) ){
	        if( c==' ' ){
	            continue;
	        }else if( c=='\"' ){
	            argv[n]=p;
	            while( *p && *p!='\"' ) ++p;
	        }else{
	            argv[n]=p-1;
	            while( *p && *p!=' ' ) ++p;
	        }
	        if( *p ) *p++=0;
	        ++n;
	    }
	    argv[n]=0;
	    return argv;
	}
	
#endif

}
