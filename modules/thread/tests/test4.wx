
#rem

Proof of concept for music playback in monkey2!

#end
Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<thread>"
#Import "<stb-vorbis>"

#Import "threads.ogg"

Using std..
Using mojo..

Using libc
Using openal
Using stb.vorbis

Function PlayMusic:Bool( path:String,finished:Void()=Null )
	
	Local file:=OpenCFile( path,"r" )
	If Not file 
		Print "Failed to open file '"+path+"'"
		Return False
	Endif
	
	Local error:Int=0
	Local vorbis:=stb_vorbis_open_file( file,0,Varptr error,Null )
	If Not vorbis 
		Print "Failed to open stb_vorbis, error="+error
		fclose( file )
		Return False
	Endif
	
	'OK, we're doing it!
	
	New Thread( Lambda()

		Const buffer_ms:UInt=100

		Const numbufs:=3
		
		Local info:=stb_vorbis_get_info( vorbis )

		Local format:=info.channels=2 ? AL_FORMAT_STEREO16 Else AL_FORMAT_MONO16
		
		Local nsamples:=buffer_ms*info.sample_rate/1000
		
		Local buffer_size:=nsamples * (info.channels=2 ? 4 Else 2)
		
		Local vorbis_data:=Cast<Short Ptr>( GCMalloc( buffer_size ) )

		Local source:ALuint
		alGenSources( 1,Varptr source )
	
		Const buffers:=New ALuint[numbufs]
		alGenBuffers( numbufs,buffers.Data )
		
		Local n:=buffer_size
		
		For Local i:=0 Until numbufs
			
			If n n=stb_vorbis_get_samples_short_interleaved( vorbis,info.channels,vorbis_data,buffer_size/2 )
	
			alBufferData( buffers[i],format,vorbis_data,buffer_size,info.sample_rate )
		Next

		alSourceQueueBuffers( source,numbufs,buffers.Data )
			
		alSourcePlay( source )
			
		Print "Playing music..."
		
		Repeat
			
			'decode more...				
			If n n=stb_vorbis_get_samples_short_interleaved( vorbis,info.channels,vorbis_data,buffer_size/2 )
					
			Local state:ALenum
			
			Repeat
				
				alGetSourcei( source,AL_SOURCE_STATE,Varptr state )
				If state=AL_STOPPED Exit
				
				If state=AL_PLAYING
					
					Local processed:ALint
					alGetSourcei( source,AL_BUFFERS_PROCESSED,Varptr processed )
					
					If processed Exit
					
				Endif
				
				Sleep( buffer_ms/2/1000.0 )
				
			Forever
			
			If state=AL_STOPPED Exit
			
			Local buffer:ALuint
			
			alSourceUnqueueBuffers( source,1,Varptr buffer )
			
			If Not n Continue
				
			alBufferData( buffer,format,vorbis_data,buffer_size,info.sample_rate )
					
			alSourceQueueBuffers( source,1,Varptr buffer )
			
		Forever

		print "Music done."
 			
		alSourceStop( source )
			
		alDeleteBuffers( numbufs,buffers.Data )
		
		GCFree( vorbis_data )
			
		stb_vorbis_close( vorbis )
			
		fclose( file )
		
		alDeleteSources( 1,Varptr source )
		
		finished()
		
	End ).Detach()
	
	Return True
	
End

Class MyWindow Extends Window

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		PlayMusic( "asset::threads.ogg" )
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
	
		canvas.DrawText( "Hello World!",Width/2,Height/2,.5,.5 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
