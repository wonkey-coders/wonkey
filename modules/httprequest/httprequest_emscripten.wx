
Namespace httprequest

#Import "<emscripten>"

Using emscripten..

Class HttpRequest Extends HttpRequestBase
	
	Method New()
	End
	
	Protected
	
	Method OnSend( text:String ) Override
		
		Local attr:emscripten_fetch_attr_t
		
		emscripten_fetch_attr_init( Varptr attr )
		
		_req.ToCString( attr.requestMethod,4 )
		attr.attributes=EMSCRIPTEN_FETCH_LOAD_TO_MEMORY
		attr.onsuccess=FetchSuccess
		attr.onerror=FetchError
		
		SetReadyState( ReadyState.Loading )
		
		_fetch=emscripten_fetch( Varptr attr,_url )
		
		_sending.Add( Self )
	End
	
	Method OnCancel() Override
		
		If Not _fetch Return
		
		Close()
		
		SetReadyState( ReadyState.Error )
	End
	
	Private
	
	Field _fetch:emscripten_fetch_t Ptr
	
	Global _sending:=New Stack<HttpRequest>
	
	Method Close()
		
		If Not _fetch Return
		
		_sending.Remove( Self )
		
		emscripten_fetch_close( _fetch )
		
		_fetch=Null
	End
	
	Method Success()
		
		_response=String.FromCString( _fetch->data,_fetch->numBytes )
		
		_status=_fetch->status
		
		SetReadyState( ReadyState.Done )
		
		Close()
	End
	
	Method Error()
		
		_status=_fetch->status
		
		SetReadyState( ReadyState.Error )
		
		Close()
	End
	
	Function FindRequest:HttpRequest( fetch:emscripten_fetch_t Ptr )

		For Local request:=Eachin _sending

			If request._fetch=fetch Return request
		Next
		
		Return Null
	End
	
	Function FetchSuccess( fetch:emscripten_fetch_t Ptr )
		
		FindRequest( fetch )?.Success()
	End
	
	Function FetchError( fetch:emscripten_fetch_t Ptr )

		FindRequest( fetch )?.Error()
	End
		
	
End
