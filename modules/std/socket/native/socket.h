
#ifndef WX_STD_SOCKET_H
#define WX_STD_SOCKET_H

#include <wxwonkey.h>

namespace wxSocket{

	int init();

	int connect( const char *hostname,const char *service,int type,int flags );
	
	int bind( const char *hostname,const char *service,int flags );

	int listen( const char *hostname,const char *service,int backlog,int flags );

	int accept( int socket );
	
	void close( int socket );
	
	int send( int socket,void *data,int size );

	int recv( int socket,void *data,int size );
	
	int sendto( int socket,void *data,int size,const void *sockaddr,int addrlen );
	
	int recvfrom( int socket,void *data,int size,void *sockaddr,int *addrlen );
	
	void setopt( int socket,wxString name,int value );
	
	int getopt( int socket,wxString name );
	
	int cansend( int socket );
	
	int canrecv( int socket );
	
	int getsockaddr( int socket,void *sockaddr,int *addrlen );

	int getpeeraddr( int socket,void *sockaddr,int *addrlen );

	int sockaddrname( const void *sockaddr,int addrlen,char *host,char *service );
	
	int select( int n_read,int *r_socks,int n_write,int *w_socks,int n_except,int *e_socks,int millis );
}

#endif
