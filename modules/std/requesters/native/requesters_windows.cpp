
#include "requesters.h"

#include <windows.h>
#include <shlobj.h>

namespace{

	HWND focHwnd;

	void beginPanel(){
		focHwnd=GetFocus();
	}

	void endPanel(){
		SetFocus( focHwnd );
	}

	int panel( wxString title,wxString text,int flags ){
		beginPanel();
		int n=MessageBoxW( GetActiveWindow(),wxWString( text ),wxWString( title ),flags );
		endPanel();
		return n;
	}
	
	WCHAR *tmpWString( wxString str ){
		WCHAR *p=(WCHAR*)malloc( str.length()*2+2 );
		memcpy( p,str.data(),str.length()*2 );
		p[str.length()]=0;
		return p;
	}
	
	int CALLBACK BrowseForFolderCallbackW( HWND hwnd,UINT uMsg,LPARAM lp,LPARAM pData ){
		wchar_t szPath[MAX_PATH];
		switch( uMsg ){
		case BFFM_INITIALIZED:
			SendMessageW( hwnd,BFFM_SETSELECTIONW,TRUE,pData );
			break;
		case BFFM_SELCHANGED: 
			if( SHGetPathFromIDListW( (LPITEMIDLIST)lp,szPath ) ){
				SendMessageW( hwnd,BFFM_SETSTATUSTEXTW,0,(LPARAM)szPath );
			}
			break;
		}
		return 0;
	}
	
	int CALLBACK BrowseForFolderCallbackA( HWND hwnd,UINT uMsg,LPARAM lp,LPARAM pData ){
		char szPath[MAX_PATH];
		switch( uMsg ){
		case BFFM_INITIALIZED:
			SendMessageA( hwnd,BFFM_SETSELECTIONA,TRUE,pData );
			break;
		case BFFM_SELCHANGED: 
			if( SHGetPathFromIDListA( (LPITEMIDLIST)lp,szPath ) ){
				SendMessageA( hwnd,BFFM_SETSTATUSTEXTA,0,(LPARAM)szPath );
			}
			break;
		}
		return 0;
	}
}
	
void wxRequesters::Notify( wxString title,wxString text,wxBool serious ){
	int flags=(serious ? MB_ICONWARNING : MB_ICONINFORMATION)|MB_OK|MB_APPLMODAL|MB_TOPMOST;
	panel( title,text,flags );
}

wxBool wxRequesters::Confirm( wxString title,wxString text,wxBool serious ){
	int flags=(serious ? MB_ICONWARNING : MB_ICONINFORMATION)|MB_OKCANCEL|MB_APPLMODAL|MB_TOPMOST;
	int n=panel( title,text,flags );
	if( n==IDOK ) return 1;
	return 0;
}

int wxRequesters::Proceed( wxString title,wxString text,wxBool serious ){
	int flags=(serious ? MB_ICONWARNING : MB_ICONINFORMATION)|MB_YESNOCANCEL|MB_APPLMODAL|MB_TOPMOST;
	int n=panel( title,text,flags );
	if( n==IDYES ) return 1;
	if( n==IDNO ) return 0;
	return -1;
}

wxString wxRequesters::RequestFile( wxString title,wxString exts,wxBool save,wxString path ){

	wxString file,dir;
	path=path.replace( "/","\\" );
		
	int i=path.findLast( "\\" );
	if( i!=-1 ){
		dir=path.slice( 0,i );
		file=path.slice( i+1 );
	}else{
		file=path;
	}

	if( file.length()>MAX_PATH ) return "";

	if( exts.length() ){
		if( exts.find( ":" )==-1 ){
			exts=wxString( "Files\0*.",8 )+exts;
		}else{
			exts=exts.replace( ":",wxString( "\0*.",3 ) );
		}
		exts=exts.replace( ";",wxString( "\0",1 ) );
		exts=exts.replace( ",",";*." )+wxString( "\0",1 );
	}

	WCHAR buf[MAX_PATH+1];
	memcpy( buf,file.data(),file.length()*2 );
	buf[file.length()]=0;

	OPENFILENAMEW of={sizeof(of)};

	of.hwndOwner=GetActiveWindow();
	of.lpstrTitle=tmpWString( title );
	of.lpstrFilter=tmpWString( exts );
	of.lpstrFile=buf;
	of.lpstrInitialDir=dir.length() ? tmpWString( dir ) : 0;
	of.nMaxFile=MAX_PATH;
	of.Flags=OFN_HIDEREADONLY|OFN_NOCHANGEDIR;
	
	wxString str;
	
	beginPanel();
	
	if( save ){
		of.lpstrDefExt=L"";
		of.Flags|=OFN_OVERWRITEPROMPT;
		if( GetSaveFileNameW( &of ) ){
			str=wxString( buf );
		}
	}else{
		of.Flags|=OFN_FILEMUSTEXIST;
		if( GetOpenFileNameW( &of ) ){
			str=wxString( buf );
		}
	}
	
	endPanel();
	
	free( (void*)of.lpstrTitle );
	free( (void*)of.lpstrFilter );
	free( (void*)of.lpstrInitialDir );
	
	str=str.replace( "\\","/" );
	
	return str;
}

wxString wxRequesters::RequestDir( wxString title,wxString dir ){

	CoInitialize( 0 );
	
	dir=dir.replace( "/","\\" );

	LPMALLOC shm;
	BROWSEINFOW bi={0};
	
	WCHAR buf[MAX_PATH],*p;
	GetFullPathNameW( wxWString( dir ),MAX_PATH,buf,&p );
	
	bi.hwndOwner=GetActiveWindow();
	bi.lpszTitle=tmpWString( title );
	bi.ulFlags=BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;
	bi.lpfn=BrowseForFolderCallbackW;
	bi.lParam=(LPARAM)buf;
	
	beginPanel();

	wxString str;
	
	if( ITEMIDLIST *idlist=SHBrowseForFolderW( &bi ) ){
	
		SHGetPathFromIDListW( idlist,buf );
		str=wxString( buf );
		
		//SHFree( idlist );	//?!?
		
		str=str.replace( "\\","/" );
		if( !str.endsWith( "/" ) ) str+="/";
	}
	
	endPanel();
	
	free( (void*)bi.lpszTitle );

	return str;
}

void wxRequesters::OpenUrl( wxString url ){

	CoInitializeEx( NULL,COINIT_APARTMENTTHREADED|COINIT_DISABLE_OLE1DDE );
	
	ShellExecute( HWND_DESKTOP,0,url.c_str(),0,0,SW_SHOWNORMAL );
//	ShellExecute( HWND_DESKTOP,"open",url.c_str(),0,0,SW_SHOWNORMAL );
}
