
#include "wxstring.h"
#include "wxarray.h"
#include "wxplatform.h"
#include "wxwonkey.h"

#include <cwctype>
#include <clocale>

#ifdef WX_THREADS
#include <mutex>
#endif

wxString::Rep wxString::_nullRep;

#if WX_ANDROID

#include <jni.h>

//FIXME: SDL2 dependancy!
extern "C" void *SDL_AndroidGetJNIEnv();

#endif

namespace{

#if WX_ANDROID
	jclass jclass_lang;
	
	jmethodID jmethod_toUpper;
	jmethodID jmethod_toLower;
	jmethodID jmethod_capitalize;

	wxString JStringToString( JNIEnv *env,jstring jstr ){
		if( !jstr ) return "";
		const char *cstr=env->GetStringUTFChars( jstr,0 );
		wxString str=wxString::fromCString( cstr );
		env->ReleaseStringUTFChars( jstr,cstr );
		return str;
	}
	
	jstring StringToJString( JNIEnv *env,wxString str ){
		int n=str.utf8Length()+1;
		char *buf=new char[n];
		str.toCString( buf,n );
		jstring jstr=env->NewStringUTF( buf );
		return jstr;
	}
	
	wxString invokeStaticStringMethod( jmethodID jmethod,wxString arg ){
		JNIEnv *env=(JNIEnv*)SDL_AndroidGetJNIEnv();
		jstring jarg=StringToJString( env,arg );
		jstring jres=(jstring)env->CallStaticObjectMethod( jclass_lang,jmethod,jarg );
		wxString res=JStringToString( env,jres );
		env->DeleteLocalRef( jres );
		env->DeleteLocalRef( jarg );
		return res;
	}
#endif
	
	void initLocale(){
	
#if WX_THREADS
		static std::atomic_bool inited;
		if( inited.exchange( true ) ) return;
#else
		static bool inited;
		if( inited ) return;
		inited=true;
#endif
		
#if WX_ANDROID
		JNIEnv *env=(JNIEnv*)SDL_AndroidGetJNIEnv();
		jclass_lang=env->FindClass( "com/wonkey/lib/WonkeyLang" );
		jmethod_toUpper=env->GetStaticMethodID( jclass_lang,"toUpper","(Ljava/lang/String;)Ljava/lang/String;" );
		jmethod_toLower=env->GetStaticMethodID( jclass_lang,"toLower","(Ljava/lang/String;)Ljava/lang/String;" );
		jmethod_capitalize=env->GetStaticMethodID( jclass_lang,"capitalize","(Ljava/lang/String;)Ljava/lang/String;" );
		wx_printf( "initLocale: env=%p\n",env );
#elif WX_WINDOWS
		std::setlocale( LC_ALL,"English" );
//		std::setlocale( LC_CTYPE,"English" );
#else
		std::setlocale( LC_CTYPE,"en_US.UTF-8" );
#endif
	}
	
	template<class C> int t_memcmp( const C *p1,const C *p2,int count ){
		return memcmp( p1,p2,count*sizeof(C) );
	}

	//returns END of dst!	
	template<class C> C *t_memcpy( C *dst,const C *src,int count ){
		return (C*)memcpy( dst,src,count*sizeof(C) )+count;
	}

	int countUtf8Chars( const char *p,int sz ){
	
		const char *e=p+sz;
	
		int n=0;
	
		while( p!=e ){
			int c=*p++;
			
			if( c & 0x80 ){
				if( (c & 0xe0)==0xc0 ){
					if( p==e || (p[0] & 0xc0)!=0x80 ) return -1;
					p+=1;
				}else if( (c & 0xf0)==0xe0 ){
					if( p==e || p+1==e || (p[0] & 0xc0)!=0x80 || (p[1] & 0xc0)!=0x80 ) return -1;
					p+=2;
				}else{
					return -1;
				}
			}
			n+=1;
		}
		return n;
	}
	
	int countNullTerminatedUtf8Chars( const char *p,int sz ){
	
		const char *e=p+sz;
	
		int n=0;
	
		while( p!=e && *p ){
			int c=*p++;
			
			if( c & 0x80 ){
				if( (c & 0xe0)==0xc0 ){
					if( p==e || (p[0] & 0xc0)!=0x80 ) return -1;
					p+=1;
				}else if( (c & 0xf0)==0xe0 ){
					if( p==e || p+1==e || (p[0] & 0xc0)!=0x80 || (p[1] & 0xc0)!=0x80 ) return -1;
					p+=2;
				}else{
					return -1;
				}
			}
			n+=1;
		}
		return n;
	}
	
	void charsToUtf8( const wxChar *p,int n,char *dst,int size ){
	
		char *end=dst+size;
		
		const wxChar *e=p+n;
		
		while( p<e && dst<end ){
			wxChar c=*p++;
			if( c<0x80 ){
				*dst++=c;
			}else if( c<0x800 ){
				if( dst+2>end ) break;
				*dst++=0xc0 | (c>>6);
				*dst++=0x80 | (c & 0x3f);
			}else{
				if( dst+3>end ) break;
				*dst++=0xe0 | (c>>12);
				*dst++=0x80 | ((c>>6) & 0x3f);
				*dst++=0x80 | (c & 0x3f);
			}
		}
		if( dst<end ) *dst++=0;
	}
	
	void utf8ToChars( const char *p,wxChar *dst,int n ){
	
		while( n-- ){
			int c=*p++;
			
			if( c & 0x80 ){
				if( (c & 0xe0)==0xc0 ){
					c=((c & 0x1f)<<6) | (p[0] & 0x3f);
					p+=1;
				}else if( (c & 0xf0)==0xe0 ){
					c=((c & 0x0f)<<12) | ((p[0] & 0x3f)<<6) | (p[1] & 0x3f);
					p+=2;
				}
			}
			*dst++=c;
		}

	}
	
}

// ***** wxString::Rep *****

wxString::Rep *wxString::Rep::alloc( int length ){
	if( !length ) return &_nullRep;
	Rep *rep=(Rep*)wxGC::malloc( sizeof(Rep)+length*sizeof(wxChar) );
	rep->refs=1;
	rep->length=length;
	return rep;
}

// ***** wxString *****

wxString::wxString( const void *p ){

	const char *cp=(const char*)p;

	if( !cp ){
		_rep=&_nullRep;
		return;
	}

	int sz=strlen( cp );

	int n=countNullTerminatedUtf8Chars( cp,sz );

	if( n==-1 || n==sz ){
		_rep=Rep::create( cp,sz );
		return;
	}
	Rep *rep=Rep::alloc( n );
	utf8ToChars( cp,rep->data,n );
	_rep=rep;
}

wxString::wxString( const void *p,int sz ){

	const char *cp=(const char*)p;

	if( !cp ){
		_rep=&_nullRep;
		return;
	}

	int n=countUtf8Chars( cp,sz );

	if( n==-1 || n==sz ){
		_rep=Rep::create( cp,sz );
		return;
	}
	Rep *rep=Rep::alloc( n );
	utf8ToChars( cp,rep->data,n );
	_rep=rep;
}

wxString::wxString( const wxChar *data ):_rep( Rep::create( data ) ){
}

wxString::wxString( const wxChar *data,int length ):_rep( Rep::create( data,length ) ){
}

wxString::wxString( const wchar_t *data ):_rep( Rep::create( data ) ){
}

wxString::wxString( const wchar_t *data,int length ):_rep( Rep::create( data,length ) ){
}

int wxString::utf8Length()const{

	const wxChar *p=data();
	const wxChar *e=p+length();
	
	int n=0;
	
	while( p<e ){
		wxChar c=*p++;
		if( c<0x80 ){
			n+=1;
		}else if( c<0x800 ){
			n+=2;
		}else{
			n+=3;
		}
	}

	return n;
}

wxString::wxString( bool b ){

	_rep=Rep::create( b ? "True" : "False" );
}

wxString::wxString( int n ){

	char data[64];
	sprintf( data,"%d",n );
	_rep=Rep::create( data );
}

wxString::wxString( unsigned int n ){

	char data[64];
	sprintf( data,"%u",n );
	_rep=Rep::create( data );
}

wxString::wxString( long n ){

	char data[64];
	sprintf( data,"%ld",n );
	_rep=Rep::create( data );
}

wxString::wxString( unsigned long n ){

	char data[64];
	sprintf( data,"%lu",n );
	_rep=Rep::create( data );
}

wxString::wxString( long long n ){

	char data[64];
	sprintf( data,"%lld",n );
	_rep=Rep::create( data );
}

wxString::wxString( unsigned long long n ){

	char data[64];
	sprintf( data,"%llu",n );
	_rep=Rep::create( data );
}

wxString::wxString( float n ){

	char data[64];
	sprintf( data,"%.9g",n );
	_rep=Rep::create( data );
}

wxString::wxString( double n ){

	char data[64];
	sprintf( data,"%.17g",n );
	_rep=Rep::create( data );
}

void wxString::toCString( void *buf,int size )const{
	Rep *rep=_rep;
	charsToUtf8( rep->data,rep->length,(char*)buf,size );
}

void wxString::toWString( void *buf,int size )const{

	size=size/sizeof(wchar_t);
	if( size<=0 ) return;
	
	int sz=length();
	if( sz>size ) sz=size;
	
	for( int i=0;i<sz;++i ) ((wchar_t*)buf)[i]=data()[i];
	
	if( sz<size ) ((wchar_t*)buf)[sz]=0;
}

const char *wxString::c_str()const{

	static int _sz;
	static char *_tmp;

	int sz=utf8Length()+1;
	
#ifdef WX_THREADS
	std::mutex _mutex;
	_mutex.lock();
#endif

	if( sz>_sz ){
		::free( _tmp );
		_tmp=(char*)::malloc( _sz=sz );
	}
	
#ifdef WX_THREADS
	_mutex.unlock();
#endif
	
	toCString( _tmp,sz );
	return _tmp;
}

bool wxString::startsWith( const wxString &str )const{
	if( str.length()>length() ) return false;
	return t_memcmp( data(),str.data(),str.length() )==0;
}

bool wxString::endsWith( const wxString &str )const{
	if( str.length()>length() ) return false;
	return t_memcmp( data()+(length()-str.length()),str.data(),str.length() )==0;
}
	
wxString wxString::fromChar( int chr ){
	wchar_t chrs[]={ wchar_t(chr) };
	return wxString( chrs,1 );
}

wxArray<wxString> wxString::split( wxString sep )const{

	if( !sep.length() ){
		
		wxArray<wxString> bits=wxArray<wxString>( length() );
		
		bits.retain();
		
		for( int i=0;i<length();++i ){
			bits[i]=wxString( &data()[i],1 );
		}
		
		bits.release();
		
		return bits;
	}
	
	int i=0,i2,n=1;
	while( (i2=find( sep,i ))!=-1 ){
		++n;
		i=i2+sep.length();
	}
	
	wxArray<wxString> bits=wxArray<wxString>( n );
	
	bits.retain();
	
	if( n==1 ){
		bits[0]=*this;
	}else{
		i=0;n=0;
		while( (i2=find( sep,i ))!=-1 ){
			bits[n++]=slice( i,i2 );
			i=i2+sep.length();
		}
		bits[n]=slice( i );
	}
	
	bits.release();
	
	return bits;
}

wxString wxString::join( wxArray<wxString> bits )const{

	if( bits.length()==0 ) return wxString();
	if( bits.length()==1 ) return bits[0];
	
	int len=length() * (bits.length()-1);
	for( int i=0;i<bits.length();++i ) len+=bits[i].length();
	
	Rep *rep=Rep::alloc( len );
	wxChar *p=rep->data;

	p=t_memcpy( p,bits[0].data(),bits[0].length() );
	
	for( int i=1;i<bits.length();++i ){
		p=t_memcpy( p,data(),length() );
		p=t_memcpy( p,bits[i].data(),bits[i].length() );
	}
	
	return rep;
}

wxString wxString::fromChars( wxArray<int> chrs ){ 
	return Rep::create( chrs.data(),chrs.length() ); 
}

wxString wxString::operator-()const{
	Rep *rep=Rep::alloc( length() );
	const wxChar *p=data()+length();
	for( int i=0;i<rep->length;++i ) rep->data[i]=*--p;
	return rep;
}

wxString wxString::operator+( const wxString &str )const{

	if( !length() ) return str;
	if( !str.length() ) return *this;
	
	Rep *rep=Rep::alloc( length()+str.length() );
	t_memcpy( rep->data,data(),length() );
	t_memcpy( rep->data+length(),str.data(),str.length() );

	return rep;
}

wxString wxString::operator*( int n )const{
	Rep *rep=Rep::alloc( length()*n );
	wxChar *p=rep->data;
	for( int j=0;j<n;++j ){
		for( int i=0;i<length();++i ) *p++=data()[i];
	}
	return rep;
}

int wxString::find( wxString str,int from )const{
	if( from<0 ) from=0;
	for( int i=from;i<=length()-str.length();++i ){
		if( !t_memcmp( data()+i,str.data(),str.length() ) ) return i;
	}
	return -1;
}

int wxString::findLast( const wxString &str,int from )const{
	if( from<0 ) from=0;
	for( int i=length()-str.length();i>=from;--i ){
		if( !t_memcmp( data()+i,str.data(),str.length() ) ) return i;
	}
	return -1;
}

wxString wxString::slice( int from )const{
	int length=this->length();
	if( from<0 ){
		from+=length;
		if( from<0 ) from=0;
	}else if( from>length ){
		from=length;
	}
	if( !from ) return *this;
	return wxString( data()+from,length-from );
}

wxString wxString::slice( int from,int term )const{
	int length=this->length();
	if( from<0 ){
		from+=length;
		if( from<0 ) from=0;
	}else if( from>length ){
		from=length;
	}
	if( term<0 ){
		term+=length;
		if( term<from ) term=from;
	}else if( term<from ){
		term=from;
	}else if( term>length ){
		term=length;
	}
	if( !from && term==length ) return *this;
	return wxString( data()+from,term-from );
}

wxString wxString::toUpper()const{
	initLocale();
#if WX_ANDROID
	return invokeStaticStringMethod( jmethod_toUpper,*this );
#else
	Rep *rep=Rep::alloc( length() );
	for( int i=0;i<length();++i ) rep->data[i]=::towupper( data()[i] );
	return rep;
#endif
}

wxString wxString::toLower()const{
	initLocale();
#if WX_ANDROID
	return invokeStaticStringMethod( jmethod_toLower,*this );
#else
	Rep *rep=Rep::alloc( length() );
	for( int i=0;i<length();++i ) rep->data[i]=::towlower( data()[i] );
	return rep;
#endif
}

wxString wxString::capitalize()const{
	initLocale();
#if WX_ANDROID
	return invokeStaticStringMethod( jmethod_capitalize,*this );
#else
	if( !length() ) return &_nullRep;
	Rep *rep=Rep::alloc( length() );
	rep->data[0]=::towupper( data()[0] );
	for( int i=1;i<length();++i ) rep->data[i]=data()[i];
	return rep;
#endif
}

wxString wxString::trim()const{
	const wxChar *beg=data();
	const wxChar *end=data()+length();
	while( beg!=end && *beg<=32 ) ++beg;
	while( beg!=end && *(end-1)<=32 ) --end;
	if( end-beg==length() ) return *this;
	return wxString( beg,end-beg );
}

wxString wxString::trimStart()const{
	const wxChar *beg=data();
	const wxChar *end=data()+length();
	while( beg!=end && *beg<=32 ) ++beg;
	if( end-beg==length() ) return *this;
	return wxString( beg,end-beg );
}

wxString wxString::trimEnd()const{
	const wxChar *beg=data();
	const wxChar *end=data()+length();
	while( beg!=end && *(end-1)<=32 ) --end;
	if( end-beg==length() ) return *this;
	return wxString( beg,end-beg );
}

wxString wxString::dup( int n )const{
	Rep *rep=Rep::alloc( length()*n );
	wxChar *p=rep->data;
	for( int j=0;j<n;++j ){
		for( int i=0;i<length();++i ) *p++=data()[i];
	}
	return rep;
}

wxString wxString::padLeft( int w )const {
	if(length()>w) w=length();
	int pad=w-length();
	Rep *rep=Rep::alloc(w);
	wxChar *p=rep->data;
	for( int i=0;i<w;++i ){
		if(i<pad){
			*p++=' ';
		}else{
			*p++=data()[i-pad];
		}
	}
	return rep;
}

wxString wxString::padLeft( int w, const wxString ch )const {
	if(length()>w) w=length();
	int pad=w-length();
	wxChar c= !ch.length()?' ':ch.data()[0];
	Rep *rep=Rep::alloc(w);
	wxChar *p=rep->data;
	for( int i=0;i<w;++i ){
		if(i<pad){
			*p++=c;
		}else{
			*p++=data()[i-pad];
		}
	}
	return rep;
}

wxString wxString::padRight( int w )const {
	if(length()>w) w=length();
	int pad=w-length();
	Rep *rep=Rep::alloc(w);
	wxChar *p=rep->data;
	for( int i=0;i<w;++i ){
		if(i<pad){
			*p++=data()[i];
		}else{
			*p++=' ';
		}
	}
	return rep;
}

wxString wxString::padRight( int w, const wxString ch )const {
	if(length()>w) w=length();
	int pad=w-length();
	wxChar c= !ch.length()?' ':ch.data()[0];
	Rep *rep=Rep::alloc(w);
	wxChar *p=rep->data;
	for( int i=0;i<w;++i ){
		if(i<pad){
			*p++=data()[i];
		}else{
			*p++=c;
		}
	}
	return rep;
}

wxString wxString::replace( const wxString &str,const wxString &repl )const{

	int n=0;
	for( int i=0;; ){
		i=find( str,i );
		if( i==-1 ) break;
		i+=str.length();
		++n;
	}
	if( !n ) return *this;
	
	Rep *rep=Rep::alloc( length()+n*(repl.length()-str.length()) );
	
	wxChar *dst=rep->data;
	
	for( int i=0;; ){
	
		int i2=find( str,i );
		if( i2==-1 ){
			t_memcpy( dst,data()+i,(length()-i) );
			break;
		}
		
		t_memcpy( dst,data()+i,(i2-i) );
		dst+=(i2-i);
		
		t_memcpy( dst,repl.data(),repl.length() );
		dst+=repl.length();
		
		i=i2+str.length();
	}
	return rep;
}

int wxString::compare( const wxString &t )const{
	int len=length()<t.length() ? length() : t.length();
	for( int i=0;i<len;++i ){
		if( int n=data()[i]-t.data()[i] ) return n;
	}
	return length()-t.length();
}

wxString::operator wxInt()const{
	return std::atoi( c_str() );
}

wxString::operator wxByte()const{
	return operator wxInt() & 0xff;
}

wxString::operator wxUByte()const{
	return operator wxInt() & 0xffu;
}

wxString::operator wxShort()const{
	return operator wxInt() & 0xffff;
}

wxString::operator wxUShort()const{
	return operator wxInt() & 0xffffu;
}

wxString::operator wxUInt()const{
	wxUInt n=0;
	sscanf( c_str(),"%u",&n );
	return n;
}

wxString::operator wxLong()const{
	wxLong n=0;
	sscanf( c_str(),"%lld",&n );
	return n;
}

wxString::operator wxULong()const{
	wxULong n=0;
	sscanf( c_str(),"%llu",&n );
	return n;
}

wxString::operator float()const{
	return std::atof( c_str() );
}

wxString::operator double()const{
	return std::atof( c_str() );
}

// ***** CString *****

wxCString::wxCString( const wxString &str ){
	int size=str.utf8Length()+1;
	_data=(char*)wxGC::malloc( size );
	str.toCString( _data,size );
}

wxCString::~wxCString(){
	wxGC::free( _data );
}

wxCString::operator char*()const{
	return _data;
}

wxCString::operator signed char*()const{
	return (signed char*)_data;
}

wxCString::operator unsigned char*()const{
	return (unsigned char*)_data;
}

// ***** WString *****

wxWString::wxWString( const wxString &str ){
	int size=(str.length()+1)*sizeof(wchar_t);
	_data=(wchar_t*)wxGC::malloc( size );
	str.toWString( _data,size );
}

wxWString::~wxWString(){
	wxGC::free( _data );
}

wxWString::operator wchar_t*()const{
	return _data;
}
