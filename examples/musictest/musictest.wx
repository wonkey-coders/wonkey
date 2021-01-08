#rem

Simple music demo, with timed lyrics

Note: PlayMusic path must be a file system path so ths wont work on android yet.

#end
Namespace myapp

#Import "<std>"
#Import "<mojo>"

#Import "ACDC_-_Back_In_Black-sample.ogg"

Using std..
Using mojo..

Class MyWindow Extends Window
	
	Field _channel:Channel
	
	Field lyrics:TimedLyrics
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		lyrics = New TimedLyrics
		
		StartMusic()
	End
	
	Method StartMusic()
		
		_channel=Audio.PlayMusic( "asset::ACDC_-_Back_In_Black-sample.ogg",Lambda()
		
			Print "Music Finished!"
			
		End )
		
	End
	
	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()
		
		canvas.DrawText( 
		"Music Test: Hit [Enter] to "+
		(_channel ? "stop" Else "start")+
		(_channel ? ", [Space] to "+(_channel.Paused ? "resume" Else "pause") Else "")+
		(_channel ? ",  Sample="+_channel.PlayheadSample+", Time="+_channel.PlayheadTime Else ""),
		0,0 )
		
		If _channel lyrics.Render(canvas,_channel.PlayheadTime,Width/2,Height/2)
		
		'Stop/Start?
		If Keyboard.KeyHit( Key.Enter ) Or Mouse.ButtonHit( MouseButton.Left )
			If _channel 
				_channel.Stop()
				_channel=Null
			Else
				StartMusic()
			Endif
		Endif
		
		'Pause/Resume?
		If Keyboard.KeyHit( Key.Space ) Or Mouse.ButtonHit( MouseButton.Right )
			If _channel
				_channel.Paused=Not _channel.Paused
			Endif
		Endif
		
	End
 	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

Class TimedText
	Field time:Float
	Field text:String

	Method New(time:Float,text:String)
		Self.time = time
		Self.text = text
	End		
	
End 
	
Class TimedLyrics
	
	Field _lyr:= New Stack<TimedText>
	

	Method New ()
	
		_lyr.Add(New TimedText(2,"Back in black"))
		_lyr.Add(New TimedText(3.3,"I hit the sack"))
		_lyr.Add(New TimedText(4.7,"I've been too long I'm glad to be back"))
		_lyr.Add(New TimedText(7,"Yes, I'm let loose"))
		_lyr.Add(New TimedText(8.5,"From the noose"))
		_lyr.Add(New TimedText(10,"That's kept me hanging about"))
		_lyr.Add(New TimedText(12.5,"I've been looking at the sky"))
		_lyr.Add(New TimedText(13.2,"'Cause it's gettin' me high"))
		_lyr.Add(New TimedText(15,"Forget the hearse 'cause I never die"))
		_lyr.Add(New TimedText(17,"I got nine lives"))
		_lyr.Add(New TimedText(19.3,"Cat's eyes"))
		_lyr.Add(New TimedText(20.5,"Abusin' every one of them and running wild"))
 	End
 	
 	Method FindText:String (time:Float)
	 	Local bestmatch:String 
		For Local tt:= Eachin _lyr
			If time>=tt.time
				bestmatch = tt.text
			Endif 		
	 	Next
	 	
	 	Return bestmatch
	End
	 	
 	
 	Method Render(canvas:Canvas,time:Float,x:Int,y:Int)
	 	
	 	
	 	canvas.DrawText(FindText(time),x,y,0.5,0.5)
	 	
	 	
	End  	
 	
 	
End