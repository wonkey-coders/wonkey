
#include "requesters.h"

#import <UIKit/UIKit.h>

void wxRequesters::OpenUrl( wxString url ){

	NSURL *nsurl=[NSURL URLWithString:url.ToNSString()];
	
	if( nsurl ) [[UIApplication sharedApplication] openURL:nsurl];
}

