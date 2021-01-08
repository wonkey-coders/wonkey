
Namespace test

#Import "<win32>"

Using win32..

Function MyWndProc:LRESULT_WINAPI( hwnd:HWND,uMsg:UInt,wParam:WPARAM,lParam:LPARAM )
	
	Return DefWindowProcW( hwnd,uMsg,wParam,lParam )
End

Function Main()
	
	Local clsname:="MyWindowClass"
	
	Local wndclass:WNDCLASSW
	wndclass.style=0
	wndclass.lpfnWndProc=MyWndProc
	wndclass.hInstance=GetModuleHandleW( Null )
	wndclass.lpszClassName=Cast<WCHAR Ptr>( libc.malloc( clsname.Length*2+2 ) )
	clsname.ToWString( wndclass.lpszClassName,clsname.Length*2+2 )
	
	Local cls:=RegisterClassW( Varptr wndclass )
	
	Local hwnd:=CreateWindowW( clsname,"My Window!",WS_OVERLAPPEDWINDOW|WS_VISIBLE,16,16,256,256,Null,Null,wndclass.hInstance,Null )
	
	Local msg:MSG
	
	While GetMessage( Varptr msg,Null,0,0 )
		
		TranslateMessage( Varptr msg )
		
		DispatchMessage( Varptr msg )
		
	Wend
		
		
End
