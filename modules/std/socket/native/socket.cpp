
#include "socket.h"

#include "../../async/native/async.h"
#include "../../fiber/native/fiber.h"

#if _WIN32

#include <Ws2tcpip.h>

typedef int socklen_t;

#else

#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#define closesocket close
#define ioctlsocket ioctl

#endif

namespace wxSocket{

	struct Future : public wxAsync::Event{
		
		int fiber;
		int result=-1;
				
		Future():fiber( wxFiber::getCurrentFiber() ){}
				
		void dispatch(){
		
			wxFiber::resumeFiber( fiber );
		}
		
		void set( int result ){
		
			this->result=result;
			
			post();
		}
		
		int get(){
		
			wxFiber::suspendCurrentFiber();
			
			return result;
		}
	};
	
	int err(){
#if _WIN32	
		return WSAGetLastError();
#else
		return errno;
#endif
	}
	
	int init(){
		static bool done;
		if( done ) return 1;
		done=true;
#if _WIN32	
		WSADATA wsa;
		WSAStartup( MAKEWORD(2,2),&wsa );
#endif
		return 1;
	}

	void dontBlock( int sock ){
		//make non-blocking
		u_long cmd=1;
		ioctlsocket( sock,FIONBIO,&cmd );
	}
   
	bool wouldBlock(){
#if _WIN32
		return WSAGetLastError()==WSAEWOULDBLOCK;
#else
		return errno==EAGAIN || errno==EWOULDBLOCK;
#endif
	}
	
	int _connect( const char *hostname,const char *service,int type,int flags ){
	
		addrinfo hints;
		memset( &hints,0,sizeof( hints ) );

		hints.ai_family=AF_UNSPEC;
		hints.ai_socktype=(type==1) ? SOCK_DGRAM : SOCK_STREAM;
		hints.ai_protocol=(type==1) ? IPPROTO_UDP : IPPROTO_TCP;
		if( (flags&1)==1 ) hints.ai_flags|=AI_PASSIVE;
		if( (flags&6)==2 ) hints.ai_family=AF_INET;
		if( (flags&6)==4 ) hints.ai_family=AF_INET6;
		if( hostname && !hostname[0] ) hostname=0;

		addrinfo *pres=0;
		if( ::getaddrinfo( hostname,service,&hints,&pres ) ) return -1;
		
		int sock=-1;
		
		for( addrinfo *res=pres;res;res=res->ai_next ){
		
			sock=::socket( res->ai_family,res->ai_socktype,res->ai_protocol );
			if( sock==-1 ) continue;
#if _WIN32		
			if( res->ai_family==AF_INET6 ){
				int value=0,sz=sizeof( value );	
				const char *ip=(const char*)&value;
				::setsockopt( sock,IPPROTO_IPV6,IPV6_V6ONLY,ip,sz );
			}
#endif
			if( !connect( sock,res->ai_addr,res->ai_addrlen ) ) break;
		
			::closesocket( sock );
			sock=-1;
		}
		
		freeaddrinfo( pres );
		
		return sock;
	}
	
	int _bind( const char *hostname,const char *service,int type,int flags ){
	
		addrinfo hints;
		memset( &hints,0,sizeof( hints ) );
		
		hints.ai_family=AF_UNSPEC;
		hints.ai_socktype=(type==1) ? SOCK_DGRAM : SOCK_STREAM;
		hints.ai_protocol=(type==1) ? IPPROTO_UDP : IPPROTO_TCP;
		if( (flags&1)==1 ) hints.ai_flags|=AI_PASSIVE;
		if( (flags&6)==2 ) hints.ai_family=AF_INET;
		if( (flags&6)==4 ) hints.ai_family=AF_INET6;
		if( hostname && !hostname[0] ) hostname=0;
		
		addrinfo *pres=0;
		if( ::getaddrinfo( hostname,service,&hints,&pres ) ) return -1;
		
		int sock=-1;
		
		for( addrinfo *res=pres;res;res=res->ai_next ){
		
			sock=::socket( res->ai_family,res->ai_socktype,res->ai_protocol );
			if( sock==-1 ) continue;
			
#if _WIN32		
			if( res->ai_family==AF_INET6 ){
				int value=0,sz=sizeof( value );	
				const char *ip=(const char*)&value;
				::setsockopt( sock,IPPROTO_IPV6,IPV6_V6ONLY,ip,sz );
			}
#endif
			if( !::bind( sock,res->ai_addr,res->ai_addrlen ) ) break;
				
			::closesocket( sock );
			sock=-1;
		}
		
		freeaddrinfo( pres );

		return sock;
	}
	
	int _listen( const char *hostname,const char *service,int backlog,int flags ){

		int sock=_bind( hostname,service,2,flags );
			
		if( sock!=-1 ) ::listen( sock,backlog );
		
		return sock;
	}
	
	int connect( const char *hostname,const char *service,int type,int flags ){
	
		int sock=-1;
		
		if( wxFiber::getCurrentFiber() ){

			Future future;
			
			std::thread thread( [=,&future](){

				future.set( _connect( hostname,service,type,flags ) );
	
			} );
			
			sock=future.get();
			
			thread.join();

		}else{
		
			sock=_connect( hostname,service,type,flags );
		}
		
		return sock;
	}
	
	int bind( const char *hostname,const char *service,int flags ){
	
		int sock=-1;
		
		if( wxFiber::getCurrentFiber() ){

			Future future;
			
			std::thread thread( [=,&future](){
			
				future.set( _bind( hostname,service,1,flags ) );
	
			} );
			
			sock=future.get();

			thread.join();
			
		}else{
		
			sock=_bind( hostname,service,1,flags );
		}
		
		return sock;
	}
	
	int listen( const char *hostname,const char *service,int backlog,int flags ){
	
		int sock=-1;
		
		if( wxFiber::getCurrentFiber() ){

			Future future;
			
			std::thread thread( [=,&future](){
			
				future.set( _listen( hostname,service,backlog,flags ) );
	
			} );
			
			sock=future.get();
			
			thread.join();
			
		}else{
		
			sock=_listen( hostname,service,backlog,flags );
		}
		
		return sock;
	}
	
	int accept( int socket ){
	
		sockaddr_storage clientaddr;

		socklen_t addrlen=sizeof( clientaddr );
		
		int newsock=-1;
		
		if( wxFiber::getCurrentFiber() ){
		
			Future future;
			
			std::thread thread( [&,socket](){
			
				future.set( ::accept( socket,(sockaddr*)&clientaddr,&addrlen ) );
			} );
			
			newsock=future.get();
			
			thread.join();
		
		}else{
			
			newsock=::accept( socket,(struct sockaddr*)&clientaddr,&addrlen );
		}
		
		return newsock;
	}
	
	void close( int socket ){
	
		if( wxFiber::getCurrentFiber() ){
		
			Future future;
			
			std::thread thread( [=,&future](){
			
				future.set( ::closesocket( socket ) );
				
			} );
			
			future.get();
			
			thread.join();
			
		}else{

			::closesocket( socket );
		}
	}
	
	int cansend( int socket ){
		return 0;
	}
	
	int canrecv( int socket ){
#if _WIN32
		u_long count=0;
		if( ioctlsocket( socket,FIONREAD,&count )==-1 ) count=0;
#else
		int count=0;
		if( ioctl( socket,FIONREAD,&count )==-1 ) count=0;
#endif
		return count;
	}
	
	int send( int socket,void *data,int size ){
	
		int n=-1;
		
		if( wxFiber::getCurrentFiber() && cansend( socket )==0 ){//<size ){
			
			Future future;
				
			std::thread thread( [=,&future](){
				
				future.set( ::send( socket,(const char*)data,size,0 ) );
					
			} );

			n=future.get();
				
			thread.join();
				
		}else{
	
			n=::send( socket,(const char*)data,size,0 );
		}
			
		if( n==-1 ){
			printf( "socket_send error! err=%i, socket=%i, data=%p, size=%i\n",err(),socket,data,size );fflush( stdout );
		}
		
		return n;
	}
	
	int sendto( int socket,void *data,int size,const void *addr,int addrlen ){
	
		int n=-1;
		
		if( wxFiber::getCurrentFiber() && cansend( socket )==0 ){//<size  ){
			
			Future future;
				
			std::thread thread( [=,&future](){
				
				future.set( ::sendto( socket,(const char*)data,size,0,(const sockaddr*)addr,addrlen ) );
					
			} );
				
			n=future.get();
				
			thread.join();
				
		}else{
	
			n=::sendto( socket,(const char*)data,size,0,(const sockaddr*)addr,addrlen );
		}
			
		if( n==-1 ){
			printf( "socket_sendto error! err=%i, socket=%i, data=%p, size=%i\n",err(),socket,data,size );fflush( stdout );
		}
		
		return n;
	}
	
	int recv( int socket,void *data,int size ){
	
		int n=-1;
		
		if( wxFiber::getCurrentFiber() && canrecv( socket )==0 ){//<size ){
		
			Future future;
			
			std::thread thread( [=,&future](){
			
				future.set( ::recv( socket,(char*)data,size,0 ) );
				
			} );
			
			n=future.get();
			
			thread.join();
			
		}else{

			n=::recv( socket,(char*)data,size,0 );
		}
		
		if( n==-1 ){
			printf( "socket_recv error! err=%i, msg=%s, socket=%i, data=%p, size=%i\n",err(),strerror( err() ),socket,data,size );fflush( stdout );
		}
		
		return n;
	}
	
	int recvfrom( int socket,void *data,int size,void *addr,int *addrlen ){
	
		int n=-1;

		if( wxFiber::getCurrentFiber() && canrecv( socket )==0 ){//<size ){
		
			Future future;
			
			std::thread thread( [=,&future](){
			
				future.set( recvfrom( socket,(char*)data,size,0,(sockaddr*)addr,(socklen_t*)addrlen ) );
				
			} );
			
			n=future.get();
			
			thread.join();
			
		}else{

			n=::recvfrom( socket,(char*)data,size,0,(sockaddr*)addr,(socklen_t*)addrlen );
		}
		
		if( n==-1 ){
			printf( "socket_recvfrom error! err=%i, socket=%i, data=%p, size=%i\n",err(),socket,data,size );fflush( stdout );
		}
		
		return n;
	}
	
	void setopt( int socket,wxString name,int value ){
	
		const char *ip=(const char*)&value;
		int sz=sizeof( value );
		
		if( name=="TCP_NODELAY" ){
			setsockopt( socket,IPPROTO_TCP,TCP_NODELAY,ip,sz );
		}else if( name=="SO_REUSEADDR" ){
			setsockopt( socket,SOL_SOCKET,SO_REUSEADDR,ip,sz );
		}else if( name=="SO_SNDTIMEO" ){
			setsockopt( socket,SOL_SOCKET,SO_SNDTIMEO,ip,sz );
		}else if( name=="SO_RCVTIMEO" ){
			setsockopt( socket,SOL_SOCKET,SO_RCVTIMEO,ip,sz );
		}else if( name=="SO_BROADCAST" ){
			setsockopt( socket,SOL_SOCKET,SO_BROADCAST,ip,sz );
		}
	}
	
	int getopt( int socket,wxString name ){

		int value=-1;
		
		char *ip=(char*)&value;
		int sz=sizeof( value );
		
		if( name=="TCP_NODELAY" ){
			getsockopt( socket,IPPROTO_TCP,TCP_NODELAY,ip,(socklen_t*)&sz );
		}else if( name=="SO_REUSEADDR" ){
			getsockopt( socket,SOL_SOCKET,SO_REUSEADDR,ip,(socklen_t*)&sz );
		}else if( name=="SO_SNDTIMEO" ){
			getsockopt( socket,SOL_SOCKET,SO_SNDTIMEO,ip,(socklen_t*)&sz );
		}else if( name=="SO_RCVTIMEO" ){
			getsockopt( socket,SOL_SOCKET,SO_RCVTIMEO,ip,(socklen_t*)&sz );
		}else if( name=="SO_BROADCAST" ){
			getsockopt( socket,SOL_SOCKET,SO_BROADCAST,ip,(socklen_t*)&sz );
		}
		
		return value;
	}
	
	int getsockaddr( int socket,void *addr,int *addrlen ){
	
		return getsockname( socket,(sockaddr*)addr,(socklen_t*)addrlen );
	}
	
	int getpeeraddr( int socket,void *addr,int *addrlen ){
	
		return getpeername( socket,(sockaddr*)addr,(socklen_t*)addrlen );
	}
	
	int sockaddrname( const void *addr,int addrlen,char *host,char *service ){
	
		int flags=0;//NI_NUMERICHOST|NI_NUMERICSERV;
	
		return getnameinfo( (const sockaddr*)addr,addrlen,host,1023,service,79,flags );
	}
	
	int select( int n_read,int *r_socks,int n_write,int *w_socks,int n_except,int *e_socks,int millis ){
	
		fd_set r_set,w_set,e_set;
		
		int n=-1;
		
		FD_ZERO( &r_set );
		for( int i=0;i<n_read;++i ){
			FD_SET( r_socks[i],&r_set );
			if( r_socks[i]>n ) n=r_socks[i];
		}
		FD_ZERO( &w_set );
		for( int i=0;i<n_write;++i ){
			FD_SET( w_socks[i],&w_set );
			if( w_socks[i]>n ) n=w_socks[i];
		}
		FD_ZERO( &e_set );
		for( int i=0;i<n_except;++i ){
			FD_SET( e_socks[i],&e_set );
			if( e_socks[i]>n ) n=e_socks[i];
		}
		
		struct timeval tv,*tvp;
			
		if( millis<0 ){
			tvp=0;
		}else{
			tv.tv_sec=millis/1000;
			tv.tv_usec=(millis%1000)*1000;
			tvp=&tv;
		}
		
		int r=select( n+1,&r_set,&w_set,&e_set,tvp );
		if( r<0 ) return r;
		
		for( int i=0;i<n_read;++i ){
			if( !FD_ISSET(r_socks[i],&r_set) ) r_socks[i]=0;
		}
		for( int i=0;i<n_write;++i ){
			if( !FD_ISSET(w_socks[i],&w_set) ) w_socks[i]=0;
		}
		for( int i=0;i<n_except;++i ){
			if( !FD_ISSET(e_socks[i],&e_set) ) e_socks[i]=0;
		}
		
		return r;
	}
	
}