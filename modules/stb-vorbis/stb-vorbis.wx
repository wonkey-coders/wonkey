
#import "<libc>"

#import "native/stb-vorbis.c"
#import "native/stb-vorbis.h"

Namespace stb.vorbis

Extern

Struct stb_vorbis
End

Struct stb_vorbis_alloc
End

Struct stb_vorbis_info
	
	Field sample_rate:UInt
	Field channels:Int

	Field setup_memory_required:UInt
	Field setup_temp_memory_required:UInt
	Field temp_memory_required:UInt

	Field max_frame_size:Int
End

Function stb_vorbis_open_filename:stb_vorbis Ptr( filename:CString,error:Int Ptr,alloc_buffer:stb_vorbis_alloc Ptr )
Function stb_vorbis_open_file:stb_vorbis Ptr( f:libc.FILE Ptr,close_handle_on_close:Int,error:Int Ptr,alloc_buffer:stb_vorbis_alloc Ptr )
	
Function stb_vorbis_close( f:stb_vorbis Ptr )

Function stb_vorbis_get_info:stb_vorbis_info( f:stb_vorbis Ptr )
	
Function stb_vorbis_stream_length_in_samples:UInt( f:stb_vorbis Ptr )
Function stb_vorbis_stream_length_in_seconds:Float( f:stb_vorbis Ptr )
	
Function stb_vorbis_get_samples_short_interleaved:Int( f:stb_vorbis Ptr,channels:Int,buffer:Short Ptr,num_shorts:Int )
Function stb_vorbis_get_samples_short:Int( f:stb_vorbis Ptr,channels:Int,buffer:Short Ptr Ptr,num_samples:Int )

Function stb_vorbis_decode_memory:Int( mem:UByte Ptr,len:Int,channels:Int Ptr,sample_rate:Int Ptr,output:Short Ptr Ptr )
