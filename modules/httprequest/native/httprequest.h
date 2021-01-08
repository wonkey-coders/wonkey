
#ifndef WX_HTTPREQUEST_H
#define WX_HTTPREQUEST_H

#include <wxwonkey.h>

#if __APPLE__

struct wxHttpRequest : public wxObject{

	struct Rep;	//NS stuff...
		
	Rep *_rep;
	
	int readyState=0;
	wxString response;
	int status=-1;
	
	wxFunction<void()> readyStateChanged;
	
	wxHttpRequest();
	~wxHttpRequest();
	
	void open( wxString req,wxString url );
	void setHeader( wxString name,wxString value );
	void send( wxString text,float timeout );
	void cancel();
	
	void setReadyState( int state );
	
	void gcMark();
};
	
#else

#include <jni.h>

namespace wxHttpRequest{

	extern wxFunction<void( jobject,wxInt )> onReadyStateChanged;
	
	extern wxFunction<void( jobject,wxString,wxInt,wxInt )> onResponseReceived;

}

#endif

#endif