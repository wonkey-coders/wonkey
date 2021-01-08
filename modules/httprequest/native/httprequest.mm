
#include "httprequest.h"

#include "../../std/async/native/async.h"

struct wxHttpRequest::Rep{

	NSMutableURLRequest *_req=0;

	NSURLSessionDataTask *_dataTask=0;
};

wxHttpRequest::wxHttpRequest(){

	_rep=new Rep;
}

wxHttpRequest::~wxHttpRequest(){

#if !__has_feature(objc_arc)
	if( _rep->_req ) [_rep->_req release];
#endif

	delete _rep;
}
	
void wxHttpRequest::open( wxString req,wxString url ){
	
	if( readyState!=0 ) return;
	
	_rep->_req=[[NSMutableURLRequest alloc] init];
		
	[_rep->_req setHTTPMethod:req.ToNSString()];
	
	[_rep->_req setURL:[NSURL URLWithString:url.ToNSString()]];
	
	if( [_rep->_req respondsToSelector:@selector(setAllowsCellularAccess:)] ){
		[_rep->_req setAllowsCellularAccess:YES];
	}
	
	setReadyState( 1 );
}
	
void wxHttpRequest::setHeader( wxString name,wxString value ){
	
	if( readyState!=1 ) return;
		
	[_rep->_req setValue:value.ToNSString() forHTTPHeaderField:name.ToNSString()];
}

void wxHttpRequest::send( wxString text,float timeout ){
	
	if( readyState!=1 ) return;
	
	NSURLSession *session=[NSURLSession sharedSession];
		
	_rep->_dataTask=[session dataTaskWithRequest:_rep->_req completionHandler:
	
	^( NSData *data,NSURLResponse *response,NSError *error ){
	
		if( !error ){
		
			NSString *str=[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		
			this->response=wxString( str );
			
#if !__has_feature(objc_arc)
			[str release];
#endif

		    status=[(NSHTTPURLResponse*)response statusCode];
		    
		    setReadyState( 4 );
		    
		}else{
		
			setReadyState( 5 );
		}
		
		wxGC::release( this );
	}
	
	];
	
	[_rep->_dataTask resume];

	wxGC::retain( this );
	
	setReadyState( 3 );
}

void wxHttpRequest::cancel(){

	if( _rep->_dataTask ) [_rep->_dataTask cancel];
}

void wxHttpRequest::setReadyState( int state ){

	readyState=state;
	
	readyStateChanged();
}

void wxHttpRequest::gcMark(){

	wxGCMark( readyStateChanged ); 
}

