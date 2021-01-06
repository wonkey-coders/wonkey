
Namespace freetype

#Import "freetype-2.6.3/include/*.h"
#Import "<ft2build.h>"

#Import "freetype-2.6.3/src/base/ftbase.c"
#Import "freetype-2.6.3/src/base/ftapi.c"
#Import "freetype-2.6.3/src/base/ftbbox.c"
#Import "freetype-2.6.3/src/base/ftfntfmt.c"
#Import "freetype-2.6.3/src/base/ftbdf.c"
#Import "freetype-2.6.3/src/base/ftbitmap.c"
#Import "freetype-2.6.3/src/base/ftdebug.c"
#Import "freetype-2.6.3/src/base/ftgasp.c"
#Import "freetype-2.6.3/src/base/ftfstype.c"
#Import "freetype-2.6.3/src/base/ftglyph.c"
#Import "freetype-2.6.3/src/base/ftgxval.c"
#Import "freetype-2.6.3/src/base/ftinit.c"
#Import "freetype-2.6.3/src/base/ftlcdfil.c"
#Import "freetype-2.6.3/src/base/ftmm.c"
#Import "freetype-2.6.3/src/base/ftotval.c"
#Import "freetype-2.6.3/src/base/ftpfr.c"
#Import "freetype-2.6.3/src/base/ftstroke.c"
#Import "freetype-2.6.3/src/base/ftsynth.c"
#Import "freetype-2.6.3/src/base/ftsystem.c"
#Import "freetype-2.6.3/src/base/fttype1.c"
#Import "freetype-2.6.3/src/base/ftwinfnt.c"

'#Import "freetype-2.6.3/src/base/ftxf86.c"

#Import "freetype-2.6.3/src/base/ftpatent.c"
#Import "freetype-2.6.3/src/autofit/autofit.c"
#Import "freetype-2.6.3/src/bdf/bdf.c"
#Import "freetype-2.6.3/src/cache/ftcache.c"
#Import "freetype-2.6.3/src/cff/cff.c"
#Import "freetype-2.6.3/src/cid/type1cid.c"
#Import "freetype-2.6.3/src/gzip/ftgzip.c"
#Import "freetype-2.6.3/src/lzw/ftlzw.c"
#Import "freetype-2.6.3/src/otvalid/otvalid.c"
#Import "freetype-2.6.3/src/pcf/pcf.c"
#Import "freetype-2.6.3/src/pfr/pfr.c"
#Import "freetype-2.6.3/src/psaux/psaux.c"
#Import "freetype-2.6.3/src/pshinter/pshinter.c"

#Import "freetype-2.6.3/src/psnames/psmodule.c"

'#Import "freetype-2.6.3/src/psnames/psnames.c"	'#included by psmodule.c!

#Import "freetype-2.6.3/src/raster/raster.c"
#Import "freetype-2.6.3/src/sfnt/sfnt.c"
#Import "freetype-2.6.3/src/smooth/smooth.c"
#Import "freetype-2.6.3/src/truetype/truetype.c"
#Import "freetype-2.6.3/src/type1/type1.c"
#Import "freetype-2.6.3/src/type42/type42.c"
#Import "freetype-2.6.3/src/winfonts/winfnt.c"

Extern

Const FT_LOAD_DEFAULT:Int
Const FT_LOAD_NO_SCALE:Int
Const FT_LOAD_NO_HINTING:Int
Const FT_LOAD_RENDER:Int
Const FT_LOAD_NO_BITMAP:Int
Const FT_LOAD_VERTICAL_LAYOUT:Int
Const FT_LOAD_FORCE_AUTOHINT:Int
Const FT_LOAD_CROP_BITMAP:Int
Const FT_LOAD_PEDANTIC:Int
Const FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH:Int
Const FT_LOAD_NO_RECURSE:Int
Const FT_LOAD_IGNORE_TRANSFORM:Int
Const FT_LOAD_MONOCHROME:Int
Const FT_LOAD_LINEAR_DESIGN:Int
Const FT_LOAD_NO_AUTOHINT:Int
Const FT_LOAD_COLOR:Int
Const FT_LOAD_COMPUTE_METRICS:Int

Const FT_RENDER_MODE_NORMAL:Int
Const FT_RENDER_MODE_LIGHT:Int
Const FT_RENDER_MODE_MONO:Int
Const FT_RENDER_MODE_LCD:Int
Const FT_RENDER_MODE_LCD_V:Int

Const FT_LOAD_TARGET_NORMAL:Int
Const FT_LOAD_TARGET_LIGHT:Int
Const FT_LOAD_TARGET_MONO:Int
Const FT_LOAD_TARGET_LCD:Int
Const FT_LOAD_TARGET_LCD_V:Int

Const FT_SIZE_REQUEST_TYPE_NOMINAL:Int
Const FT_SIZE_REQUEST_TYPE_REAL_DIM:Int
Const FT_SIZE_REQUEST_TYPE_BBOX:Int
Const FT_SIZE_REQUEST_TYPE_CELL:Int
Const FT_SIZE_REQUEST_TYPE_SCALES:Int

Alias FT_Error:Int		'int
Alias FT_Int:Int
Alias FT_Int32:Int		'signed XXX
Alias FT_UInt:UInt		'unsigned int
Alias FT_Long:Int		'signed long
Alias FT_ULong:ULong	'unsigned long
Alias FT_F26Dot6:Int	'signed long
Alias FT_Pos:Int		'signed long
Alias FT_Short:Short	'signed short

Struct FT_Vector

	Field x:FT_Pos
	Field y:FT_Pos
	
End

Struct FT_BBox

	Field xMin:FT_Pos,yMin:FT_Pos
	Field xMax:FT_Pos,yMax:FT_Pos

End

Struct FT_Bitmap

	Field rows:UInt
	Field width:UInt
	Field pitch:Int
	Field buffer:UByte Ptr
	Field num_grays:UShort
	Field pixel_mode:UByte
	Field palette_mode:UByte
	Field palette:Void Ptr
	
End

Struct FT_Size_Metrics

	Field ascender:FT_Pos
	Field descender:FT_Pos
	Field height:FT_Pos
	Field max_advance:FT_Pos
	
End

Struct FT_Glyph_Metrics

	Field width:FT_Pos
	Field height:FT_Pos
	
	Field horiBearingX:FT_Pos
	Field horiBearingY:FT_Pos
	Field horiAdvance:FT_Pos
	
	Field vertBearingX:FT_Pos
	Field vertBearingY:FT_Pos
	Field vertAdvance:FT_Pos

End

Struct FT_Size_RequestRec="FT_Size_RequestRec_"

	Field type:int	'FT_Size_Request_Type
	Field width:FT_Long
	Field height:FT_Long
	Field horiResolution:FT_UInt
	Field vertResolution:FT_UInt
	
End

Struct FT_SizeRec="FT_SizeRec_"

	Field metrics:FT_Size_Metrics
End

Struct FT_LibraryRec="FT_LibraryRec_"

End

Struct FT_GlyphSlotRec="FT_GlyphSlotRec_"

	Field metrics:FT_Glyph_Metrics
	
	Field advance:FT_Vector
	
	Field bitmap:FT_Bitmap
	Field bitmap_left:FT_Int
	Field bitmap_top:FT_Int
	
End

Struct FT_FaceRec="FT_FaceRec_"

	Field num_glyphs:FT_Long
	
	Field bbox:FT_BBox
	
	Field ascender:FT_Short		'+ve!
	Field descender:FT_Short	'-ve!
	Field height:FT_Short		'ascender-descender!

	Field glyph:FT_GlyphSlotRec Ptr
	Field size:FT_SizeRec Ptr
End

Alias FT_Library:FT_LibraryRec Ptr
Alias FT_Face:FT_FaceRec Ptr
Alias FT_GlyphSlot:FT_GlyphSlotRec Ptr

Function FT_Init_FreeType:FT_Error( library:FT_Library Ptr )
Function FT_Done_FreeType:FT_Error( library:FT_Library )

Function FT_New_Face:FT_Error( library:FT_Library,filepathname:CString,face_index:FT_Long,aface:FT_Face Ptr )
Function FT_New_Memory_Face:FT_Error( library:FT_Library,file_base:UByte Ptr,file_size:FT_Long,file_index:FT_Long,aface:FT_Face Ptr )
Function FT_Done_Face:FT_Error( face:FT_Face )

Function FT_Set_Char_Size:FT_Error( face:FT_Face,char_width:FT_F26Dot6,char_height:FT_F26Dot6,horz_resolution:FT_UInt,vert_resolution:FT_UInt )
Function FT_Set_Pixel_Sizes:FT_Error( face:FT_Face,pixel_width:FT_UInt,pixel_height:FT_UInt )
Function FT_Request_Size:FT_Error( face:FT_Face,req:FT_Size_RequestRec Ptr )

Function FT_Get_Char_Index:FT_UInt( face:FT_Face,charcode:FT_ULong )

Function FT_Get_First_Char:FT_ULong( face:FT_Face,agindex:FT_UInt Ptr )
Function FT_Get_Next_Char:FT_ULong( face:FT_Face,char_code:FT_ULong,agindex:FT_UInt Ptr )
	
Function FT_Get_Kerning( face:FT_Face,left_glyph:FT_UInt,right_glyph:FT_UInt,kern_mode:FT_UInt,akerning:FT_Vector Ptr )

Function FT_Load_Char:FT_Error( face:FT_Face,char_code:FT_ULong,load_flags:Int )
Function FT_Load_Glyph:FT_Error( face:FT_Face,glyph_index:FT_UInt,load_flags:Int )
Function FT_Render_Glyph:FT_Error( slot:FT_GlyphSlot,render_mode:Int )

Function FT_HAS_KERNING:Int( face:FT_Face )
	
#rem
'**** old *****

Function FT_Init_FreeType( ft_lib:Byte Ptr Ptr )

Function FT_Done_FreeType( ft_lib:Byte Ptr )
Function FT_Done_Face( ft_face:Byte Ptr )
Function FT_Done_Glyph( ft_glyph:Byte Ptr )

Function FT_New_Face( ft_lib:Byte Ptr,arg:CString,faceIndex:Int,ft_face:Byte Ptr Ptr )
Function FT_New_Memory_Face( ft_lib:Byte Ptr,buf:Byte Ptr,size:Int,faceIndex:Int,ft_face:Byte Ptr Ptr )

Function FT_Set_Pixel_Sizes( ft_face:Byte Ptr,width:Int,height:Int )
Function FT_Get_Char_Index( ft_face:Byte Ptr,index:Int )
Function FT_Set_Charmap( ft_face:Byte Ptr,charmap:Int )

Function FT_Load_Char( ft_face:Byte Ptr,index:Int,flags:Int )
Function FT_Load_Glyph( ft_face:Byte Ptr,index:Int,flags:Int )
Function FT_Render_Glyph( ft_glyph:Byte Ptr,mode:Int )

Struct FTFace
	Field	numfaces:Int,index:Int,flags:Int,style:Int,numglyphs:Int
	Field	fname:Byte Ptr
	Field	sname:Byte Ptr
	Field	numsizes:Int
	Field	sizes:Int Ptr
	Field	numcharmaps:Int
	Field	charmaps:Int Ptr
	Field	genericdata:Byte Ptr,genericdestructor:Int
	Field	bx0:Int,by0:Int,bx1:Int,by1:Int
	Field	unitsperem:Short
	Field	ascender:Short
	Field	descender:Short
	Field	height:Short
	Field	maxawidth:Short
	Field	maxahieght:Short
	Field	underlinepos:Short
	Field	underlinethick:Short
	Field	glyphslot:Int Ptr	
	Field	metrics:Byte Ptr
End

Struct FTMetrics
	Field	mface:Int,mgeneric0:Int,mgeneric1:Int
	Field	xppem:Short,yppem:Short
	Field	xscale:Int,yscale:Int
	Field	ascend:Int,descend:Int,height:Int,max_advance:Int
End

Struct FTGlyph
	Field	lib:Int,face:Int,nextglyph:Int,reserved:Int
	Field	genericdata:Byte Ptr,genericdestructor:Int	
	Field	metric_width:Int,metric_height:Int,metric_horibearingx:Int,metric_horibearingy:Int
	Field	metric_horiadvance:Int,metric_vertbearingx:Int,metric_vertbearingy:Int,metric_vertadvance:Int
	Field	hadvance:Int,vadvance:Int
    Field	advancex:Int,advancey:Int
	Field	glyphformat:Int
	Field	rows:Int,width:Int,pitch:Int
	Field	buffer:Byte Ptr
End
#end
