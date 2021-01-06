
#include "wxwonkey.h"
#include "wxplatform.h"

#if WX_IOS

void wx_print( wxString str ){

	NSLog( @"WX: %@",[NSString stringWithUTF8String:str.c_str() ] );
}

void wx_printf( const char *fmt,...){

    va_list args;
    
    va_start( args,fmt );
    
    NSLog( @"WX: %@",[[NSString alloc] initWithFormat:[NSString stringWithUTF8String:fmt] arguments:args] );
    
    va_end(args);
}

#endif
