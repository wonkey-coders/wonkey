
#ifndef WX_STD_PROCESS_H
#define WX_STD_PROCESS_H

#include <wxwonkey.h>

class wxProcess : public wxObject{
public:

	wxProcess();
	~wxProcess();
	
	void discard();
	
	wxFunction<void()> finished;

	wxFunction<void()> stdoutReady;
	
	wxBool start( wxString cmd );
	
	wxInt exitCode();
	
	wxInt stdoutAvail();
	
	wxString readStdout();
	
	wxInt readStdout( void *buf,wxInt count );
	
	wxInt writeStdin( wxString str );
	
	wxInt writeStdin( void *buf,wxInt count );
	
	void sendBreak();
	
	void terminate();
	
private:
	struct Rep;
	
	Rep *_rep;
	
	void gcMark();
};

#endif
