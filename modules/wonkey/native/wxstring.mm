
#include "wxstring.h"

//wxString::wxString( const NSString *str ):_rep( Rep::create( str ? str.UTF8String : "" ) ){
wxString::wxString( const NSString *str ):_rep( Rep::alloc( str.length ) ){
	[str getCharacters:(unichar*)data() range:NSMakeRange(0,length())];
}

NSString *wxString::ToNSString()const{

//	return [NSString stringWithUTF8String:c_str()];
	return [NSString stringWithCharacters:(unichar*)data() length:length()];
}
