
#include "requesters.h"

#include <limits.h>

#include "tinyfiledialogs.h"

void wxRequesters::Notify( wxString title,wxString text,wxBool serious ){

	tinyfd_messageBox( wxCString( title ),wxCString( text ),"ok",serious ? "error" : "info",1 );
}

wxBool wxRequesters::Confirm( wxString title,wxString text,wxBool serious ){

	return tinyfd_messageBox( wxCString( title ),wxCString( text ),"okcancel",serious ? "error" : "info",1 );
}

wxInt wxRequesters::Proceed( wxString title,wxString text,wxBool serious ){

	// Ok, no yesnocancal in tinyfd so we'll use kdialog...
	
	int result=tinyfd_messageBox( wxCString( title ),wxCString( text ),"yesnocancel",serious ? "error" : "info",1 );
	
	return result==2 ? -1 : result;
	
/*	
	wxString cmd=wx_T( "kdialog --title \"" )+title+"\" --yesnocancel \""+text+"\"";

	int result=system( cmd.c_str() );
	
	if( result==0 ) return 1;	//YES
	if( result==256 ) return 0;	//NO
	return -1;					//CANCEL
*/
}

wxString wxRequesters::RequestFile( wxString title,wxString exts,wxBool save,wxString path ){

	if( path=="" ) path=".";
		
	if( save ){
		return tinyfd_saveFileDialog( wxCString( title ),wxCString( path ),0,0,0 );
	}else{
		return tinyfd_openFileDialog( wxCString( title ),wxCString( path ),0,0,0,0 );
	}
}

wxString wxRequesters::RequestDir( wxString title,wxString dir ){

	if( dir=="" ) dir=".";
		
	return tinyfd_selectFolderDialog( wxCString( title ),wxCString( dir ) );
}

void wxRequesters::OpenUrl( wxString url ){

	system( ( wxString( "xdg-open \"" )+url+"\"" ).c_str() );
}
