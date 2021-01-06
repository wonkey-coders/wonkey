
#ifndef WX_FILESYSTEM_H
#define WX_FILESYSTEM_H

#include <wxwonkey.h>
#include <wxplatform.h>

namespace wxFileSystem{

	wxString appDir();
	
	wxString appPath();
	
	wxArray<wxString> appArgs();
	
	wxBool copyFile( wxString srcPath,wxString dstPath );
	
#if WX_IOS
	wxString getSpecialDir( wxString name );
#endif

#if WX_ANDROID
	FILE *fopenAsset( void *asset );
#endif

}

#endif
