
Namespace zlib

#Import "zlib-1.2.11/adler32.c"
#Import "zlib-1.2.11/compress.c"
#Import "zlib-1.2.11/crc32.c"
#Import "zlib-1.2.11/deflate.c"
'#Import "zlib-1.2.11/gzclose.c"
'#Import "zlib-1.2.11/gzlib.c"
'#Import "zlib-1.2.11/gzread.c"
'#Import "zlib-1.2.11/gzwrite.c"
#Import "zlib-1.2.11/infback.c"
#Import "zlib-1.2.11/inffast.c"
#Import "zlib-1.2.11/inflate.c"
#Import "zlib-1.2.11/inftrees.c"
#Import "zlib-1.2.11/trees.c"
#Import "zlib-1.2.11/uncompr.c"
#Import "zlib-1.2.11/zutil.c"

#Import "zlib-1.2.11/*.h"
#Import "<zlib.h>"

Extern

'PITA zlib ulong define
Struct z_uLong="uLong"
End

Const Z_OK:Int
Const Z_STREAM_END:Int
Const Z_NEED_DICT:Int
Const Z_ERRNO:Int
Const Z_STREAM_ERROR:Int
Const Z_DATA_ERROR:Int
Const Z_MEM_ERROR:Int
Const Z_BUF_ERROR:Int
Const Z_VERSION_ERROR:Int

Function compress:Int( dest:UByte Ptr,destLen:z_uLong Ptr,source:UByte Ptr,sourceLen:UInt )
Function compress2:Int( dest:UByte Ptr,destLen:z_uLong Ptr,source:UByte Ptr,sourceLen:UInt,level:Int )
Function uncompress:Int( dest:UByte Ptr,destLen:z_uLong Ptr,source:UByte Ptr,sourceLen:UInt )
Function compressBound:UInt( sourceLen:UInt )


