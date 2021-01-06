
#ifndef WX_REQUESTERS_H
#define WX_REQUESTERS_H

#include <wxwonkey.h>

namespace wxRequesters{

	void Notify( wxString title,wxString text,wxBool serious );

	wxBool Confirm( wxString title,wxString text,wxBool serious );

	wxInt Proceed( wxString title,wxString text,wxBool serious );

	wxString RequestFile( wxString title,wxString filters,wxBool save,wxString path );

	wxString RequestDir( wxString title,wxString dir );
	
	void OpenUrl( wxString url );
}

#endif
