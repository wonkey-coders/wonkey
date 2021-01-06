
Namespace stb.image

#Import "<libc>"

#Import "native/stb_image.cpp"
#Import "native/stb_image.h"

Extern

Struct stbi_char="char"
End

Struct stbi_io_callbacks
	Field read:Int( Void Ptr,stbi_char Ptr,Int )
	Field skip:Void( Void Ptr,Int )
	Field eof:Int( Void Ptr )
End

Function stbi_load:UByte Ptr( filename:CString,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_load_from_memory:UByte Ptr( buffer:UByte Ptr,len:Int,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_load_from_callbacks:UByte Ptr( clbk:stbi_io_callbacks Ptr,user:Void Ptr,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_load_from_file:UByte Ptr( f:libc.FILE Ptr,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_loadf:Float Ptr( filename:CString,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_loadf_from_memory:Float Ptr( buffer:UByte Ptr,len:Int,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_loadf_from_callbacks:Float Ptr( clbk:stbi_io_callbacks Ptr,user:Void Ptr,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
Function stbi_loadf_from_file:float Ptr( f:libc.FILE Ptr,x:Int Ptr,y:Int Ptr,comp:Int Ptr,req_comp:Int )
	
Function stbi_image_free( data:Void Ptr )

Function stbi_is_hdr_from_callbacks:Int( clbk:stbi_io_callbacks Ptr,user:Void Ptr )
Function stbi_is_hdr_from_memory:Int( buffer:UByte Ptr,len:Int )
Function stbi_is_hdr:Int( filename:CString )
Function stbi_is_hdr_from_file:Int( f:libc.FILE Ptr )

Function stbi_ldr_to_hdr_gamma( gamma:Float )
Function stbi_ldr_to_hdr_scale( scale:Float )
Function stbi_hdr_to_ldr_gamma( gamma:Float )
Function stbi_hdr_to_ldr_scale( scale:Float )

