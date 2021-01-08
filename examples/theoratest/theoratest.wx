Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<theoraplayer>"

#Import "konqi.ogv"

Using std..
Using mojo..
Using theoraplayer..

Class MyWindow Extends Window

	Field audiofactory:AudioInterfaceFactory
	
	Field vidman:VideoManager
	
	Field data:DataBuffer
	
	Field vidclip:VideoClip
	
	Field image:Image
	
	Field time:Double
	
	Field gain:float=1

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		vidman=VideoManager.getInstance()
		
		audiofactory=New OpenAL_AudioInterfaceFactory
		
		vidman.setAudioInterfaceFactory( audiofactory )
		
		data=DataBuffer.Load( "asset::konqi.ogv" )
		
		vidclip=vidman.createVideoClip( data.Data,data.Length )
'		vidclip=vidman.createVideoClip( AssetsDir()+"konqi.ogv" )
		If Not vidclip Print "Can't load vidclip!"
		
		image=New Image( vidclip.getWidth(),vidclip.getHeight(),PixelFormat.RGB24,TextureFlags.Dynamic )
		
		vidclip.play()
		
		time=Now()
		
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		Local now:=Now()
		
		Local elapsed:=now-time
		
		time=now
		
		vidman.update( elapsed )
	
'		vidclip.updateTimerToNextFrame()	'play full speed...
		
		Local frame:=vidclip.fetchNextFrame()
		
		If frame
		
			Local pixmap:=New Pixmap( vidclip.getWidth(),vidclip.getHeight(),PixelFormat.RGB24,frame.getBuffer(),vidclip.getWidth()*3 )
			
			image.Texture.PastePixmap( pixmap,0,0 )
			
			vidclip.popFrame()
		
		Endif
		
		If Keyboard.KeyPressed( Key.Up )
			gain=Min( gain+.125,1.0 )
			vidclip.setAudioGain( gain )
		Else If Keyboard.KeyPressed( Key.Down )
			gain=Max( gain-.125,0.0 )
			vidclip.setAudioGain( gain )
		Endif
		
		canvas.BlendMode=BlendMode.Opaque
		
		canvas.DrawRect( 0,0,Width,Height,image )
		
		canvas.DrawText( "Time position="+vidclip.getTimePosition()+", duration="+vidclip.getDuration(),0,0 )
		
		canvas.DrawText( "Audio gain="+vidclip.getAudioGain(),0,16 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
