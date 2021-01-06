
#include "requesters.h"

#import <Cocoa/Cocoa.h>

namespace{

	typedef int (*AlertPanel)( 
		NSString *title,
		NSString *msg,
		NSString *defaultButton,
		NSString *alternateButton,
		NSString *otherButton );
	
	NSWindow *keyWin;
	NSOpenGLContext *glContext;
	
	void beginPanel(){
	
		glContext=[NSOpenGLContext currentContext];

		keyWin=[NSApp keyWindow];
	}
	
	void endPanel(){

		if( glContext ) [glContext makeCurrentContext];

		if( keyWin ) [keyWin makeKeyWindow];
	}
	
	NSString *ConvString( wxString str ){
		return [NSString stringWithCharacters:(const unichar*)str.data() length:str.length()];
	}
	
	wxString ConvString( NSString *str ){
		int n=[str length];
		unichar *buf=new unichar[ n ];
		[str getCharacters:buf range:NSMakeRange( 0,n )];
		wxString t=wxString( buf,n );
		delete[] buf;
		return t;
	}
}

void wxRequesters::Notify( wxString title,wxString text,wxBool serious ){

	AlertPanel panel=(AlertPanel) ( serious ? (void*)NSRunCriticalAlertPanel : (void*)NSRunAlertPanel );
	
	beginPanel();
	
	panel( ConvString( title ),ConvString( text ),@"OK",0,0 );
	
	endPanel();
}

wxBool wxRequesters::Confirm( wxString title,wxString text,wxBool serious ){

	AlertPanel panel=(AlertPanel) ( serious ? (void*)NSRunCriticalAlertPanel : (void*)NSRunAlertPanel );
	
	beginPanel();
	
	int n=panel( ConvString( title ),ConvString( text ),@"OK",@"Cancel",0 );

	endPanel();
	
	switch( n ){
	case NSAlertDefaultReturn:return 1;
	}
	return 0;
}

int wxRequesters::Proceed( wxString title,wxString text,wxBool serious ){

	AlertPanel panel=(AlertPanel) ( serious ? (void*)NSRunCriticalAlertPanel : (void*)NSRunAlertPanel );
	
	beginPanel();
	
	int n=panel( ConvString( title ),ConvString( text ),@"Yes",@"No",@"Cancel" );
	
	endPanel();
	
	switch( n ){
	case NSAlertDefaultReturn:return 1;
	case NSAlertAlternateReturn:return 0;
	}
	return -1;
}

wxString wxRequesters::RequestFile( wxString title,wxString filter,wxBool save,wxString path ){

	wxString file,dir;
	int i=path.findLast( "\\" );
	if( i!=-1 ){
		dir=path.slice( 0,i );
		file=path.slice( 1+1 );
	}else{
		file=path;
	}
	
	NSMutableArray *nsfilter=0;
	bool allowOthers=true;

	if( filter.length() && !save ){
	
		nsfilter=[NSMutableArray arrayWithCapacity:10];
		
		allowOthers=false;
		
		if( filter.find( ":" )!=-1 ){

			int i0=0;
			while( i0<filter.length() ){
			
				int i1=filter.find( ":",i0 );
				if( i1==-1 ) break;
				i1+=1;
				
				int i2=filter.find( ";",i1 );
				if( i2==-1 ) i2=filter.length();
				
				while( i1<i2 ){
				
					int i3=filter.find( ",",i1 );
					if( i3==-1 ) i3=i2;
					
					wxString ext=filter.slice( i1,i3 );
					if( ext==WX_T("*") ){
						allowOthers=true;
					}else{
						[nsfilter addObject:ConvString( ext )];
					}
					i1=i3+1;
				}
				i0=i2+1;
			}
			
		}else{
		
			int i0=0;
			while( i0<filter.length() ){
			
				int i1=filter.find( ",",i0 );
				if( i1==-1 ) i1=filter.length();
				
				wxString ext=filter.slice( i0,i1 );
				if( ext==WX_T("*") ){
					allowOthers=true;
				}else{
					[nsfilter addObject:ConvString( ext )];
				}
				
				i0=i1+1;
			}
		}
	}

	if( ![nsfilter count] ){
		nsfilter=0;
		allowOthers=true;
	}
	
	NSString *nsdir=0;
	NSString *nsfile=0;
	NSString *nstitle=0;
	NSMutableArray *nsexts=0;

	if( dir.length() ) nsdir=ConvString( dir );
	if( file.length() ) nsfile=ConvString( file );
	if( title.length() ) nstitle=ConvString( title );

	beginPanel();
	
	wxString str;

	if( save ){
		NSSavePanel *panel=[NSSavePanel savePanel];
		
		if( nstitle ) [panel setTitle:nstitle];
		
		if( nsfilter ){
			[panel setAllowedFileTypes:nsfilter];
			[panel setAllowsOtherFileTypes:allowOthers];
		}
		
		if( [panel runModalForDirectory:nsdir file:nsfile]==NSFileHandlingPanelOKButton ){
			str=ConvString( [panel filename] );
		}

	}else{
		NSOpenPanel *panel=[NSOpenPanel openPanel];

		if( nstitle ) [panel setTitle:nstitle];
		
		if( allowOthers ) nsfilter=0;
		
		if( [panel runModalForDirectory:nsdir file:nsfile types:nsfilter]==NSFileHandlingPanelOKButton ){
			str=ConvString( [panel filename] );
		}
	}

	endPanel();

	return str;
}

wxString wxRequesters::RequestDir( wxString title,wxString dir ){

	NSString *nsdir=0;
	NSString *nstitle=0;
	NSOpenPanel *panel;
	
	if( dir.length() ) nsdir=ConvString( dir );
	if( title.length() ) nstitle=ConvString( title );

	panel=[NSOpenPanel openPanel];
	
	[panel setCanChooseFiles:NO];
	[panel setCanChooseDirectories:YES];
	[panel setCanCreateDirectories:YES];
	
	if( nstitle ) [panel setTitle:nstitle];

	beginPanel();
	
	wxString str;
	
	if( [panel runModalForDirectory:nsdir file:0 types:0]==NSFileHandlingPanelOKButton ){
	
		str=ConvString( [panel filename] );
	}

	endPanel();
	
	return str;
}

void wxRequesters::OpenUrl( wxString url ){

	if( CFURLRef cfurl=CFURLCreateWithBytes( 0,(const UInt8*)url.c_str(),url.length(),kCFStringEncodingASCII,0 ) ){
		LSOpenCFURLRef( cfurl,0 );
		CFRelease( cfurl );
	}
}
