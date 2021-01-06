
#Import "<libc>"

Namespace std.audio

Private

Using std.stream

Struct WAV_Header
	Field RIFF:Int
	Field len:Int
	Field WAVE:Int
End

Struct FMT_Chunk
	Field compType:Short
	Field numChannels:Short
	Field samplesPerSec:Int
	Field avgBytesPerSec:Int
	Field blockalignment:Short
	Field bitsPerSample:Short
End

Function ReadWAV:AudioData( stream:std.stream.Stream )

	Local wav:=New WAV_Header
	Local wav_sz:=libc.sizeof( wav )
	
	If stream.Read( Varptr wav,wav_sz )<>wav_sz Return Null

	If wav.RIFF<>$46464952 Return Null
	If wav.WAVE<>$45564157 Return Null
	
	Local format:AudioFormat
	Local hertz:Int
	
	While Not stream.Eof
		
		Local tag:=stream.ReadInt()
		Local size:=stream.ReadInt()
		
		Local aligned_size:=size+(size&1)	'chunk size *including* 2 byte alignment of next chunk.
		
		Select tag
		Case $20746d66		'FMT
			
			Local fmt:=New FMT_Chunk
			Local fmt_sz:=sizeof( fmt )
			
			'read FMT chunk data
			If fmt_sz>size Or stream.Read( Varptr fmt,fmt_sz )<>fmt_sz Return Null
			
			'skip to next chunk
			Local n:=aligned_size-fmt_sz
			If n And stream.Skip( n )<>n Return Null
			
			If fmt.compType<>1 Return Null
			
			If fmt.numChannels=1 And fmt.bitsPerSample=8
				format=AudioFormat.Mono8
			Else If fmt.numChannels=1 And fmt.bitsPerSample=16
				format=AudioFormat.Mono16
			Else If fmt.numChannels=2 And fmt.bitsPerSample=8
				format=AudioFormat.Stereo8
			Else If fmt.numChannels=2 And fmt.bitsPerSample=16
				format=AudioFormat.Stereo16
			Else
				Return Null
			Endif
			
			hertz=fmt.samplesPerSec
			
			Continue
			
		Case $61746164		'DATA
			
			If Not format Return null
			
			Local bps:=BytesPerSample( format )
			
			Local length:=aligned_size/bps
			
			Local data:=New AudioData( length,format,hertz )

			stream.Read( data.Data,length*bps )
			
			Return data
		End
		
		'skip to next chunk
		If stream.Skip( aligned_size )<>aligned_size Return Null
		
	Wend
	
	Return Null

End

Internal

Function LoadAudioData_WAV:AudioData( path:String )

	Local stream:=std.stream.Stream.Open( path,"r" )
	If Not stream Return Null
	
	Local data:=ReadWAV( stream )
	
	stream.Close()
	Return data

End
