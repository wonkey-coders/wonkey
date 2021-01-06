
#ifndef WX_ARRAY_H
#define WX_ARRAY_H

#ifdef WX_THREADS
#include "wxgc_mx.h"
#else
#include "wxgc.h"
#endif

template<class T,int D> struct wxArray{

	struct Rep : public wxGCNode{
	
		int _sizes[D];
		T _data[0];
		
		Rep(){
			memset( _sizes,0,sizeof(_sizes) );
		}
			
		Rep( int sizes[] ){
			wxGC::beginCtor( this );
				
			memcpy( _sizes,sizes,D*sizeof(int) );
				
			for( int i=0;i<_sizes[D-1];++i ) new( &_data[i] ) T();
		}
			
		~Rep(){
			for( int i=0;i<_sizes[D-1];++i ) _data[i].~T();
		}
	
		virtual const char *typeName()const{
			return "wxArray::Rep";
		}
			
		virtual void gcMark(){
			for( int i=0;i<_sizes[D-1];++i ) wxGCMark( _data[i] );
		}
		
		virtual void dbEmit(){
			int n=_sizes[D-1];if( n>100 ) n=100;
			for( int i=0;i<n;++i ){
				char buf[16];
				sprintf( buf,"[%i]",i );
				wxDBEmit( buf,&_data[i] );
			}
		}
	};
	
	Rep *_rep=nullptr;

	wxArray(){
	}
	
	wxArray( const wxArray &t ){
	
		wxGC::enqueue( t._rep );
		
		_rep=t._rep;
	}
		
	template<class...Args> explicit wxArray( Args...args ){
		
		int sizes[]{ args... };
		for( int i=1;i<D;++i ) sizes[i]*=sizes[i-1];
			
		if( !sizes[D-1] ) return;
			
		void *p=wxGC::malloc( sizeof( Rep )+sizes[D-1]*sizeof(T) );
	
		_rep=new( p ) Rep( sizes );
			
		wxGC::endCtor( _rep );
	}
		
	template<class...Args> explicit wxArray( std::initializer_list<T> init,Args...args ){
		
		int sizes[]{ args... };
		for( int i=1;i<D;++i ) sizes[i]*=sizes[i-1];
			
		if( !sizes[D-1] ) return;
			
		void *p=wxGC::malloc( sizeof( Rep )+sizes[D-1]*sizeof(T) );
			
		_rep=new( p ) Rep( sizes );
		
		int i=0,n=sizes[D-1];
		wxDebugAssert( n==init.size(),"Incorrect number of array initializers" );

		for( auto it=init.begin();i<n; )_rep->_data[i++]=*it++;
			
		wxGC::endCtor( _rep );
	}
	
	void retain()const{
		wxGC::retain( _rep );
	}
	
	void release()const{
		wxGC::release( _rep );
	}
	
	void discard(){
		_rep=nullptr;
	}
		
	T *data(){
		return _rep->_data;
	}
		
	const T *data()const{
		return _rep->_data;
	}
		
	int length()const{
		return _rep ? _rep->_sizes[D-1] : 0;
	}
		
	int size( int q )const{
		wxDebugAssert( q>=0 && q<D,"Array dimension out of range" );
			
		return _rep ? (q ? _rep->_sizes[q]/_rep->_sizes[q-1] : _rep->_sizes[0]) : 0;
	}
	
	wxArray &operator=( const wxArray &t ){
	
		wxGC::enqueue( t._rep );
		
		_rep=t._rep;
		
		return *this;
	}
		
	T &operator[]( int index ){
		wxDebugAssert( index>=0 && index<length(),"Array index out of range" );
			
		return data()[index];
	}
	
	T &at( int index ){
		wxDebugAssert( index>=0 && index<length(),"Array index out of range" );
				
		return data()[index];
	}
		
	//slower N-D version
	template<class...Args> T &at( Args...args ){
		
		const int indices[]{args...};
			
		int index=indices[0];
		wxDebugAssert( index>=0 && _rep,"Array index out of range" );
			
		for( int i=1;i<D;++i ){
			wxDebugAssert( indices[i]>=0 && index<_rep->_sizes[i-1],"Array index out of range" );
				
			index+=indices[i]*_rep->_sizes[i-1];
		}
			
		wxDebugAssert( index<length(),"Array index out of range" );
			
		return data()[index];
	}
		
	operator bool()const{
		
		return _rep;
	}
		
	wxArray<T,1> slice( int from )const{
	
		return slice( from,length() );
	}
		
	wxArray<T,1> slice( int from,int term )const{
		
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
			
		int newlen=term-from;
			
		wxArray<T,1> r{newlen};
			
		for( int i=0;i<newlen;++i ) r.data()[i]=data()[from+i];
			
		return r;
	}
	
	wxArray<T,1> resize( int newLength )const{
		wxDebugAssert( newLength>=0,"Array Resize new length must not be negative" );
			
		int ncopy=length();
		if( ncopy>newLength ) ncopy=newLength;
	
		auto r=wxArray<T,1>( newLength );
			
		for( int i=0;i<ncopy;++i ) r.data()[i]=data()[i];
			
		return r;
	}
		
	void copyTo( wxArray<T,1> dst,int offset,int dstOffset,int count )const{
		wxDebugAssert( offset>=0 && dstOffset>=0 && count>=0 && offset+count<=length() && dstOffset+count<=dst.length(),"Array CopyTo parameters out of range" );
			
		if( dst._rep==_rep && dstOffset>offset ){
			for( int i=count-1;i>=0;--i ) dst.data()[dstOffset+i]=data()[offset+i];
		}else{
			for( int i=0;i<count;++i ) dst.data()[dstOffset+i]=data()[offset+i];
		}
	}
};

template<class T,int D> wxString wxDBType( wxArray<T,D> *p ){
	return wxDBType<T>()+"[]";
}

template<class T,int D> wxString wxDBValue( wxArray<T,D> *p ){
	char buf[64];
	sprintf( buf,"@%p",*(void**)(&p->_rep) );
	return wxString( buf )+"["+wxString( p->length() )+"]";
}

template<class T,int D> void wxGCMark( wxArray<T,D> arr ){
	wxGC::enqueue( arr._rep );
}

#endif
