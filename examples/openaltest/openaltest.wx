
Namespace openaltest

#import "<std>"
#import "<mojo>"
#import "<openal>"

#import "fine_morning.wav"

Using std..
Using mojo..
Using openal..

Function ALFormat:ALenum( format:AudioFormat )
	Local alFormat:ALenum
	Select format
	Case AudioFormat.Mono8
		alFormat=AL_FORMAT_MONO8
	Case AudioFormat.Mono16
		alFormat=AL_FORMAT_MONO16
	Case AudioFormat.Stereo8
		alFormat=AL_FORMAT_STEREO8
	Case AudioFormat.Stereo16
		alFormat=AL_FORMAT_STEREO16
	End
	Return alFormat
End

Function ALSourceState:String( src:ALuint )
	Local alState:ALint
	alGetSourcei( src,AL_SOURCE_STATE,Varptr alState )
	
	Local state:=String( alState )+" ?????"
	Select alState
	Case AL_INITIAL
		state="initial"
	Case AL_PLAYING
		state="playing"
	Case AL_PAUSED
		state="paused"
	Case AL_STOPPED
		state="stopped"
	End
	Return state
End

Function LoadALBuffer:ALuint( path:String )

	Local audio:=AudioData.Load( "asset::fine_morning.wav" )
	If Not audio Return 0
	
	Local buf:ALuint
	alGenBuffers( 1,Varptr buf )
	alBufferData( buf,ALFormat( audio.Format ),audio.Data,audio.Size,audio.Hertz )
	audio.Discard()
	
	Return buf
End

Class MyWindow Extends Window

	Field bufs:=New ALuint[2]
	Field src:ALuint
	Field proc:ALuint

	Method New()
		Local device:=alcOpenDevice( Null )
		Assert( device,"Failed to open OpenAL device" )
		
		Local context:=alcCreateContext( device,Null )
		Assert( context,"Failed to create OpenAL context" )
		
		Assert( alcMakeContextCurrent( context ) )
		
		bufs[0]=LoadALBuffer( "asset::find_morning.wav" )
		bufs[1]=LoadALBuffer( "asset::find_morning.wav" )
		Assert( bufs[0] And bufs[1],"Failed to load buffer" )

		alGenSources( 1,Varptr src )
		
		alSourceQueueBuffers( src,2,Varptr bufs[0] )
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		Local state:=ALSourceState( src )
		
		Local proc:ALint
		alGetSourcei( src,AL_BUFFERS_PROCESSED,Varptr proc )
		
		If proc<>Self.proc
			Local tmp:ALuint
			alSourceUnqueueBuffers( src,1,Varptr tmp )
			alSourceQueueBuffers( src,1,Varptr tmp )
			Self.proc=proc
		Endif
		
		canvas.DrawText( "source state="+state+" (SPACE to change) proc="+proc,0,0 )
		
		If Keyboard.KeyPressed( Key.Space )
			Select state
			Case "initial","stopped","paused"
				alSourcePlay( src )
			Case "playing"
				alSourcePause( src )
			End
			Print state+"->"+ALSourceState( src )
		Endif
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
	
End