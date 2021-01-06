
#ifndef WX_TYPES_H
#define WX_TYPES_H

#include "wxstd.h"

typedef bool wxBool;
typedef signed char wxByte;
typedef unsigned char wxUByte;
typedef signed short wxShort;
typedef unsigned short wxUShort;
typedef signed int wxInt;
typedef unsigned int wxUInt;
typedef signed long long wxLong;
typedef unsigned long long wxULong;
typedef float wxFloat;
typedef double wxDouble;

typedef unsigned short wxChar;

class wxString;

template<class T> class wxFunction;

template<class T,int D=1> class wxArray;

template<class T> struct wxGCVar;

struct wxVariant;
struct wxTypeInfo;
struct wxDeclInfo;

namespace detail{

	template<int...I> struct seq { };
	
    template<int N, int...I> struct gen_seq : gen_seq<N-1,N-1,I...> { };
	
    template<int...I> struct gen_seq<0,I...> : seq<I...> { };
    
	template<typename T> struct remove_pointer { typedef T type; };

	template<typename T> struct remove_pointer<T*> { typedef typename remove_pointer<T>::type type; };
}

wxString wxTypeName( const char *type );

template<class T> bool operator<( const T &x,const T &y ){
	return memcmp( &x,&y,sizeof(T) );
}

template<class X,class Y> int wxCompare( const X &x,const Y &y ){
	if( x<y ) return -1;
	return y<x;
}

#ifdef NDEBUG

#define WX_CLASS(X) struct X; \
wxTypeInfo *wxGetType(X*const&);

#define WX_STRUCT(X) struct X; \
wxTypeInfo *wxGetType(X const&); 

#define WX_ENUM(X) enum class X; \
wxTypeInfo *wxGetType(X const&);

#else
 
#define WX_CLASS(X) struct X; \
wxTypeInfo *wxGetType(X*const&); \
wxString wxDBType(X**); \
wxString wxDBValue(X**);

#define WX_STRUCT(X) struct X; \
wxTypeInfo *wxGetType(X const&); \
wxString wxDBType(X*); \
wxString wxDBValue(X*);

#define WX_ENUM(X) enum class X; \
wxTypeInfo *wxGetType(X const&); \
wxString wxDBType(X*); \
wxString wxDBValue(X*);

#endif

#endif
