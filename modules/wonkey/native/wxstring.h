
#ifndef WX_STRING_H
#define WX_STRING_H

#include "wxtypes.h"
#include "wxassert.h"

namespace wxGC{
	void *malloc( size_t size );
	void free( void *p );
}

class wxCString;

class wxString{

	struct Rep{
#ifdef WX_THREADS
		std::atomic_int refs;
#else
		int refs;
#endif
		int length;
		wxChar data[0];
		
		static Rep *alloc( int length );
		
		template<class C> static Rep *create( const C *p,int length ){
			Rep *rep=alloc( length );
			for( int i=0;i<length;++i ) rep->data[i]=p[i];
			return rep;
		}
		
		template<class C> static Rep *create( const C *p ){
			const C *e=p;
			while( *e ) ++e;
			return create( p,e-p );
		}
	};

	static Rep _nullRep;
	
#ifdef WX_THREADS

	std::atomic<Rep*> _rep;

	void retain()const{
		++_rep.load()->refs;
	}
	
	void release(){
		Rep *rep=_rep.load();
		if( !--rep->refs && rep!=&_nullRep ) wxGC::free( rep );
	}
	
#else

	Rep *_rep;
	
	void retain()const{
		++_rep->refs;
	}
	
	void release(){
		if( !--_rep->refs && _rep!=&_nullRep ) wxGC::free( _rep );
	}
	
#endif

	wxString( Rep *rep ):_rep(rep){
	}
	
	public:
	
	const char *c_str()const;
	
	wxString():_rep( &_nullRep ){
	}
	
#if WX_THREADS
	wxString( const wxString &s ):_rep( s._rep.load() ){
		retain();
	}
#else
	wxString( const wxString &s ):_rep( s._rep ){
		retain();
	}
#endif
	
	wxString( const void *data );
	
	wxString( const void *data,int length );
	
	wxString( const wxChar *data );
	
	wxString( const wxChar *data,int length );

	wxString( const wchar_t *data );
	
	wxString( const wchar_t *data,int length );
	
#if __OBJC__
	wxString( const NSString *str );
#endif

	explicit wxString( bool b );

	explicit wxString( int n );
	
	explicit wxString( unsigned int n );
	
	explicit wxString( long n );
	
	explicit wxString( unsigned long n );

	explicit wxString( long long n );
	
	explicit wxString( unsigned long long n );
	
	explicit wxString( float n );
	
	explicit wxString( double n );
	
	~wxString(){
		release();
	}
	
#if WX_THREADS
	const wxChar *data()const{
		return _rep.load()->data;
	}
	
	int length()const{
		return _rep.load()->length;
	}
#else
	const wxChar *data()const{
		return _rep->data;
	}
	
	int length()const{
		return _rep->length;
	}
#endif

	wxChar operator[]( int index )const{
		wxDebugAssert( index>=0 && index<length(),"String character index out of range" );
		return data()[index];
	}
	
	wxString operator+()const{
		return *this;
	}
	
	wxString operator-()const;
	
	wxString operator+( const wxString &str )const;
	
	wxString operator+( const char *str )const{
		return operator+( wxString( str ) );
	}
	
	wxString operator*( int n )const;
	
#ifdef WX_THREADS	
	wxString &operator=( const wxString &str ){
		Rep *oldrep=_rep,*newrep=str._rep;
		if( _rep.compare_exchange_strong( oldrep,newrep ) ){
			++newrep->refs;
			if( !--oldrep->refs && oldrep!=&_nullRep ) wxGC::free( oldrep );
		}
		return *this;
	}
#else
	wxString &operator=( const wxString &str ){
		str.retain();
		release();
		_rep=str._rep;
		return *this;
	}
#endif
	
	template<class C> wxString &operator=( const C *data ){
		release();
		_rep=Rep::create( data );
		return *this;
	}
	
	wxString &operator+=( const wxString &str ){
		*this=*this+str;
		return *this;
	}
	
	wxString &operator+=( const char *str ){
		return operator+=( wxString( str ) );
	}
	
	int find( wxString str,int from=0 )const;
	
	int findLast( const wxString &str,int from=0 )const;
	
	bool contains( const wxString &str )const{
		return find( str )!=-1;
	}
	
	wxString slice( int from )const;
	
	wxString slice( int from,int term )const;

	wxString left( int count )const{
		return slice( 0,count );
	}
	
	wxString right( int count )const{
		return slice( -count );
	}
	
	wxString mid( int from,int count )const{
		return slice( from,from+count );
	}
	
	bool startsWith( const wxString &str )const;
	
	bool endsWith( const wxString &str )const;
	
	wxString toUpper()const;
	
	wxString toLower()const;
	
	wxString capitalize()const;
	
	wxString trim()const;
	
	wxString trimStart()const;
	
	wxString trimEnd()const;
	
	wxString dup( int n )const;

	wxString padLeft( int w )const;

	wxString padLeft( int w, const wxString ch )const;

	wxString padRight( int w )const;

	wxString padRight( int w, const wxString ch )const;
	
	wxString replace( const wxString &str,const wxString &repl )const;
	
	wxString fmt( wxArray<wxString> args )const;
	wxString fmt( wxString arg00 )const;
	wxString fmt( wxString arg00, wxString arg01 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13, wxString arg14 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13, wxString arg14, wxString arg15 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13, wxString arg14, wxString arg15, wxString arg16 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13, wxString arg14, wxString arg15, wxString arg16, wxString arg17 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13, wxString arg14, wxString arg15, wxString arg16, wxString arg17, wxString arg18 )const;
	wxString fmt( wxString arg00, wxString arg01, wxString arg02, wxString arg03, wxString arg04, wxString arg05, wxString arg06, wxString arg07, wxString arg08, wxString arg09, wxString arg10, wxString arg11, wxString arg12, wxString arg13, wxString arg14, wxString arg15, wxString arg16, wxString arg17, wxString arg18, wxString arg19 )const;
	
	wxArray<wxString> split( wxString sep )const;
	
	wxString join( wxArray<wxString> bits )const;
	
	int compare( const wxString &t )const;
	
	bool operator<( const wxString &t )const{
		return compare( t )<0;
	}
	
	bool operator>( const wxString &t )const{
		return compare( t )>0;
	}
	
	bool operator<=( const wxString &t )const{
		return compare( t )<=0;
	}
	
	bool operator>=( const wxString &t )const{
		return compare( t )>=0;
	}
	
	bool operator==( const wxString &t )const{
		return compare( t )==0;
	}
	
	bool operator!=( const wxString &t )const{
		return compare( t )!=0;
	}
	
	operator wxBool()const{
		return length()!=0;
	}
	
	operator wxInt()const;
	
	operator wxByte()const;
	
	operator wxUByte()const;
	
	operator wxShort()const;
	
	operator wxUShort()const;
	
	operator wxUInt()const;
	
	operator wxLong()const;
	
	operator wxULong()const;
	
	operator float()const;
	
	operator double()const;
	
	int utf8Length()const;
	
	void toCString( void *buf,int size )const;

	void toWString( void *buf,int size )const;
	
#if __OBJC__	
	NSString *ToNSString()const;
#endif
	
	static wxString fromChar( int chr );
	
	static wxString fromChars( wxArray<int> chrs );
	
	static wxString fromCString( const void *data ){ return wxString( data ); }
	
	static wxString fromCString( const void *data,int size ){ return wxString( data,size ); }
	
	static wxString fromWString( const void *data ){ return wxString( (const wchar_t*)data ); }
	
	static wxString fromWString( const void *data,int size ){ return wxString( (const wchar_t*)data,size ); }
};

class wxCString{
	
	char *_data;
	
	public:

	wxCString():_data(0){}
	
	wxCString( const wxString &str );
	
	~wxCString();
	
	operator char*()const;
	
	operator signed char*()const;
	
	operator unsigned char*()const;
};

class wxWString{
	wchar_t *_data;
	
	public:
	
	wxWString():_data(0){}
	
	wxWString( const wxString &str );
	
	~wxWString();
	
	operator wchar_t*()const;
};

template<class C> wxString operator+( const C *str,const wxString &str2 ){
	return wxString::fromCString( str )+str2;
}

inline wxString WX_T( const char *p ){
	return wxString::fromCString( p );
}

#endif

