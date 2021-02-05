
#include "libc.h"

/*
#if _WIN32
#include <windows.h>
#include <bbstring.h>
#if _MSC_VER
#include <stdint.h>
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#endif
*/

#if _WIN32

struct DIR{
	WIN32_FIND_DATAW ffd;
	HANDLE hfind;
	dirent entry;
};

static void *tmps[32];
static int tmpsi;

static const WCHAR *widen( const char *p ){

	int n=MultiByteToWideChar( CP_UTF8,0,p,-1,0,0 );

	WCHAR *w=(WCHAR*)malloc( n*2 );
	
	MultiByteToWideChar( CP_UTF8,0,p,-1,w,n );
	
	free(tmps[tmpsi&31]);
	tmps[(tmpsi++)&31]=w;
	
	return w;
}

static const char *narrow( const WCHAR *w ){

	int n=WideCharToMultiByte( CP_UTF8,0,w,-1,0,0,0,0 );
	
	char *p=(char*)malloc( n );
	
	WideCharToMultiByte( CP_UTF8,0,w,-1,p,n,0,0 );
	
	free(tmps[tmpsi&31]);
	tmps[(tmpsi++)&31]=p;
	
	return p;	
}

const wchar_t *widen_utf8( const char *p ){

	return widen( p );
}

const char *narrow_utf8( const wchar_t *w ){

	return narrow( w );
}

FILE *fopen_utf8( const char *filename,const char *mode ){

	return _wfopen( widen( filename ),widen( mode ) );
}

FILE *fopen_utf8( const char *command,const char *mode ){

	return _wpopen( widen( command ),widen( mode ) );
}

int fputs_utf8( const char *str,FILE *stream ){
	
	return fputws( widen( str ),stream );
}

char *fgets_utf8( const char *str,int size, FILE *stream ){
	
	return fgetws( widen( str ), size,stream );
}

int remove_utf8( const char *path ){

	return _wremove( widen( path ) );
}

int rename_utf8( const char *oldpath,const char *newpath ){

	return _wrename( widen( oldpath ),widen( newpath ) );
}

int puts_utf8( const char *str ){

	return _putws( widen( str ) );
}

int setenv_utf8( const char *name,const char *value,int overwrite ){

	const WCHAR *wname=widen( name );

	if( !overwrite && _wgetenv( wname ) ) return -1;
	
	WCHAR *wbuf=(WCHAR*)malloc( (strlen(name)+strlen(value)+2)*2 );
	
	wcscpy( wbuf,wname );
	wcscat( wbuf,L"=" );
	wcscat( wbuf,widen( value ) );
	
	int n=_wputenv( wbuf );
	
	return n;
}

char *getenv_utf8( const char *name ){

	static char *p;

	const WCHAR *wname=widen( name );
	
	WCHAR *w=_wgetenv( wname );
	if( !w ) return 0;
	
	free( p );
	p=strdup( narrow( w ) );
	
	return p;
}

int system_utf8( const char *cmd ){

	bool inherit=false;
	DWORD flags=CREATE_NO_WINDOW;
	STARTUPINFOW si={sizeof(si)};
	PROCESS_INFORMATION pi={0};
	
	if( GetStdHandle( STD_OUTPUT_HANDLE ) ){
	
		inherit=true;
		si.dwFlags=STARTF_USESTDHANDLES;
		si.hStdInput=GetStdHandle( STD_INPUT_HANDLE );
		si.hStdOutput=GetStdHandle( STD_OUTPUT_HANDLE );
		si.hStdError=GetStdHandle( STD_ERROR_HANDLE );
	}
	
	if( GetConsoleWindow() ){

		flags=0;
	}

//	bbString tmp=BB_T( "cmd /S /C\"" )+BB_T( cmd )+BB_T( "\"" );
	
	const WCHAR *wopts=L"cmd /S /C\"";
	const WCHAR *wcmd=widen( cmd );
	
	WCHAR *wtmp=(WCHAR*)malloc( (wcslen( wopts )+wcslen( wcmd )+2)*2 );
	
	wcscpy( wtmp,wopts );
	wcscat( wtmp,wcmd );
	wcscat( wtmp,L"\"" );
	
	if( !CreateProcessW( 0,wtmp,0,0,inherit,flags,0,0,&si,&pi ) ) return -1;

	WaitForSingleObject( pi.hProcess,INFINITE );
	
	int res=GetExitCodeProcess( pi.hProcess,(DWORD*)&res ) ? res : -1;
	
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return res;
}

char *realpath_utf8( const char *path,char *rpath ){

	if( !rpath ){
		rpath=(char*)malloc( PATH_MAX );
		if( realpath_utf8( path,rpath ) ) return rpath;
		free( rpath );
		return 0;
	}
	
	WCHAR wbuf[PATH_MAX];
	
	if( !GetFullPathNameW( widen( path ),PATH_MAX,wbuf,0 ) ) return 0;
	
	WideCharToMultiByte( CP_UTF8,0,wbuf,-1,rpath,PATH_MAX,0,0 );
		
	return rpath;
}

int mkdir_utf8( const char *path,int mode ){

	return _wmkdir( widen( path ) );
}

char *getcwd_utf8( char *buf,int size ){

	WCHAR wbuf[PATH_MAX];
	
	if( !GetCurrentDirectoryW( size,wbuf ) ) return 0;
	
	WideCharToMultiByte( CP_UTF8,0,wbuf,-1,buf,size,0,0 );
	
	return buf;
}

int chdir_utf8( const char *path ){

	return SetCurrentDirectoryW( widen( path ) ) ? 0 : -1;
}

int rmdir_utf8( const char *path ){

	return _wrmdir( widen( path ) );
}

int stat_utf8( const char *path,stat_t *buf ){

	return _wstat( widen( path ),buf );
}

DIR *opendir_utf8( const char *path ){

	const WCHAR *wpath=widen( path );

	WCHAR *wbuf=(WCHAR*)malloc( (wcslen(wpath)+3)*2 );
	
	wcscpy( wbuf,wpath );
	wcscat( wbuf,L"\\*" );
	
	DIR *dir=(DIR*)malloc( sizeof( DIR ) );
	memset( dir,0,sizeof(DIR) );
	
	dir->hfind=FindFirstFileW( wbuf,&dir->ffd );

	if( !dir->hfind ){
		free( dir );
		dir=0;
	}
	
	free( wbuf );
	
	return dir;
}

dirent *readdir_utf8( DIR *dir ){

	if( !dir->hfind ) return 0;

	const char *p=narrow( dir->ffd.cFileName );
	free( dir->entry.d_name );
	dir->entry.d_name=strdup( p );
	
	if( !FindNextFileW( dir->hfind,&dir->ffd ) ){
		FindClose( dir->hfind );
		dir->hfind=0;
	}
	
	return &dir->entry;
}

void closedir_utf8( DIR *dir ){

	if( dir->hfind ) FindClose( dir->hfind );

	free( dir->entry.d_name );
	free( dir );
}

#endif

