
//Libc fudge, mainly for windows.

#ifndef WX_LIB_C_H
#define WX_LIB_C_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#if _WIN32

#include <windows.h>
#include <wchar.h>

#define PATH_MAX 260

#if _MSC_VER
typedef int mode_t;
#endif

struct dirent{
	char *d_name;
};
	
struct DIR;

typedef struct tm tm_t;

typedef struct _stat stat_t;

const wchar_t *widen_utf8( const char *p );
const char *narrow_utf8( const wchar_t *w );

FILE *fopen_utf8( const char *path,char const *mode );
FILE *popen_utf8( const char *path,char const *mode );
int fputs_utf8( const char *str,FILE *stream );
char *fgets_utf8( const char *str,int size,FILE *stream );
int remove_utf8( const char *path );
int rename_utf8( const char *oldpath,const char *newpath );
int puts_utf8( const char *str );
int setenv_utf8( const char *name,const char *value,int overwrite );
char *getenv_utf8( const char *name );
int system_utf8( const char *cmd );
char *realpath_utf8( const char *path,char *resolved_path );
int mkdir_utf8( const char *path,int mode );
int gettimeofday_utf8( timeval *tv );
char *getcwd_utf8( char *buf,int size );
int chdir_utf8( const char *path );
int rmdir_utf8( const char *path );
int stat_utf8( const char *path,stat_t *buf );
DIR *opendir_utf8( const char *path );
dirent *readdir_utf8( DIR *dir );
void closedir_utf8( DIR *dir );

#else

#include <unistd.h>
#include <dirent.h>
#include <sys/time.h>

typedef struct tm tm_t;

typedef struct stat stat_t;

#define fopen_utf8 fopen
#define popen_utf8 popen
#define fputs_utf8 fputs
#define fgets_utf8 fgets
#define remove_utf8 remove
#define rename_utf8 rename
#define puts_utf8 puts
#define setenv_utf8 setenv
#define getenv_utf8 getenv
#define system_utf8 system
#define realpath_utf8 realpath
#define mkdir_utf8 mkdir
#define gettimeofday_utf8 gettimeofday
#define getcwd_utf8 getcwd
#define chdir_utf8 chdir
#define rmdir_utf8 rmdir
#define stat_utf8 stat
#define opendir_utf8 opendir
#define readdir_utf8 readdir
#define closedir_utf8 closedir

#endif

#endif

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>

#if _MSC_VER
#include <direct.h>
#include <winsock2.h>	//for struct timeval?!?
#include "dirent_msvc.h"
typedef int mode_t;
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/time.h>
#endif

#if _WIN32
#define PATH_MAX 260
#define realpath(X,Y) _fullpath( (Y),(X),PATH_MAX )
#else
#include <limits.h>
#endif

typedef struct tm tm_t;

typedef struct stat stat_t;

int system_( const char *command );
void setenv_( const char *name,const char *value,int overwrite );
int mkdir_( const char *path,int mode );
int gettimeofday_( timeval *tv );

#endif

*/

