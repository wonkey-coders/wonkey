
#ifndef WX_RESOURCE_H
#define WX_RESOURCE_H

#include <wxwonkey.h>

class wxResource : public wxObject{

	bool _discarded=false;

public:

	wxResource();

	virtual void gcFinalize();
	
	void discard();
	
protected:
	
	virtual void onDiscard();
	
	virtual void onFinalize();
};

#endif