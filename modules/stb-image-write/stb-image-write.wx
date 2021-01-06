
Namespace stb.image

#Import "native/stb_image_write.c"
#Import "native/stb_image_write.h"

Extern

Alias stbi_write_func:Void( context:Void Ptr,data:Void Ptr,size:Int )

Function stbi_write_png:Int( filename:CString,w:Int,h:Int,comp:Int,data:Void Ptr,stride_in_bytes:Int )
Function stbi_write_bmp:Int( filename:CString,w:Int,h:Int,comp:Int,data:Void Ptr )
Function stbi_write_tga:Int( filename:CString,w:Int,h:Int,comp:Int,data:Void Ptr )
Function stbi_write_hdr:Int( filename:CString,w:Int,h:Int,comp:Int,data:Void Ptr )

Function stbi_write_png_to_func:Int( func:stbi_write_func,context:Void Ptr,w:Int,h:Int,comp:Int,data:Void Ptr,stride_in_bytes:Int )
Function stbi_write_bmp_to_func:Int( func:stbi_write_func,context:Void Ptr,w:Int,h:Int,comp:Int,data:Void Ptr )
Function stbi_write_tga_to_func:Int( func:stbi_write_func,context:Void Ptr,w:Int,h:Int,comp:Int,data:Void Ptr )
Function stbi_write_hdr_to_func:Int( func:stbi_write_func,context:Void Ptr,w:Int,h:Int,comp:Int,data:Void Ptr )
