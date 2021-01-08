
Namespace stb.truetype

#Import "native/stb_truetype.c"
#Import "native/stb_truetype.h"

Extern

Struct stbtt_fontinfo
End

Struct stbtt_bakedchar
	Field x0:UShort
	Field y0:UShort
	Field x1:UShort
	Field y1:UShort
	Field xoff:Float
	Field yoff:Float
	Field xadvance:Float
End

Function stbtt_InitFont:Int( info:stbtt_fontinfo Ptr,data:UByte Ptr,offset:Int )
Function stbtt_FindGlyphIndex:Int( info:stbtt_fontinfo Ptr,unicode_codepoint:Int )
Function stbtt_ScaleForPixelHeight:Float( info:stbtt_fontinfo Ptr,pixels:Float )

Function stbtt_GetFontVMetrics:Void( info:stbtt_fontinfo Ptr,ascent:Int Ptr,descent:Int Ptr,lineGap:Int Ptr )
Function stbtt_GetCodepointHMetrics:Void( info:stbtt_fontinfo Ptr,codepoint:Int,advanceWidth:Int Ptr,leftSideBearing:Int Ptr )
Function stbtt_GetCodepointKernAdvance:Int( info:stbtt_fontinfo Ptr,ch1:Int,ch2:Int )

Function stbtt_GetGlyphHMetrics:Void( info:stbtt_fontinfo Ptr,glyph:Int,advanceWidth:Int Ptr,leftSideBearing:Int Ptr )

Function stbtt_MakeGlyphBitmap:Void( info:stbtt_fontinfo Ptr,output:UByte Ptr,out_w:Int,out_h:Int,out_stride:Int,scale_x:Float,scale_y:Float,glyph:Int )
Function stbtt_GetGlyphBitmapBox:Void( info:stbtt_fontinfo Ptr,glyph:Int,scale_x:Float,scale_y:Float,ix0:Int Ptr,iy0:Int Ptr,ix1:Int Ptr,iy1:Int Ptr )

Function stbtt_BakeFontBitmap( data:UByte Ptr,offset:Int,pixel_height:Float,pixels:UByte Ptr,pw:Int,ph:Int,first_char:Int,num_chars:Int,chardata:stbtt_bakedchar Ptr )
