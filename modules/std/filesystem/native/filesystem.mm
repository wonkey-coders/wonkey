
#include "filesystem.h"

#include <UIKit/UIKit.h>

wxString wxFileSystem::getSpecialDir( wxString name ){

	NSString *dir=0;

	if( name=="assets" ){
		
		dir=[[NSBundle mainBundle] resourcePath];
		
		dir=[dir stringByAppendingString:@"/assets"];
		
	}else if( name=="internal" ){

//		old school...	
//		dir=[@"~/Documents" stringByExpandingTildeInPath];
		
		dir=[[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject].path;
	
	}else if( name=="external" ){	//no sdcard on ios?!?
	
	}

	if( dir ) return wxString( dir )+"/";
	
	return "";
}