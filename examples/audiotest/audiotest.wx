
Namespace myapp

#Import "<std>"
#Import "<mojo>"

'#import "fine_morning.wav"
#import "fine_morning.ogg"

Using std..
Using mojo..

Class MyWindow Extends Window

	Field sound:Sound
	Field channel:Channel
	
	Method New()

'		sound=Sound.Load( "asset::fine_morning.wav" )
		sound=Sound.Load( "asset::fine_morning.ogg" )
		channel=New Channel
		
'		SineWave()

	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
	
		canvas.DrawText( "1:Play, 2:Loop, 3:Pause, 4:Stop, 5/6:Volume 7/8:Rate 9/0:Pan",0,0 )
	
		canvas.DrawText( "Playing="+Int( channel.Playing ),0,24 )
		canvas.DrawText( "Paused="+Int( channel.Paused ),0,40 )
		canvas.DrawText( "Volume="+channel.Volume,0,56 )
		canvas.DrawText( "Rate="+channel.Rate,0,72 )
		canvas.DrawText( "Pan="+channel.Pan,0,88 )
		canvas.DrawText( "PlayheadSample="+channel.PlayheadSample,0,104 )
		canvas.DrawText( "PlayheadTime="+channel.PlayheadTime,0,120 )

	End
	
	Method OnKeyEvent( event:KeyEvent ) Override
	
		Select event.Type
		Case EventType.KeyDown
			Select event.Key
			Case Key.Key1
				channel.Play( sound )
			Case Key.Key2
				channel.Play( sound,True )
			Case Key.Key3
				channel.Paused=Not channel.Paused
			Case Key.Key4
				channel.Stop()
			Case Key.Key5
				channel.Volume-=.125
			Case Key.Key6
				channel.Volume+=.125
			Case Key.Key7
				channel.Rate*=1.125
			Case Key.Key8
				channel.Rate/=1.125
			Case Key.Key9
				channel.Pan-=.25
			Case Key.Key0
				channel.Pan+=.25
			End
		End
	End
	
	Method SineWave()

#if __TARGET__<>"emscripten"	
	
		New Fiber( Lambda()
		
			Const len:=1024
			
			Local sine:=New UByte[len]
			Local sineData:=New AudioData( len,AudioFormat.Mono8,22050,Cast<UByte Ptr>( sine.Data ) )
			
			For Local i:=0 Until len
				sine[i]=Sin( Float(i)/len * Pi*2 * 16 ) * 127.5 + 127.5
			Next
			
			Local sineChan:=New Channel
			
			Repeat
			
				If Keyboard.KeyDown( Key.Up )
					sineChan.Rate*=1.00125
				Else If Keyboard.KeyDown( Key.Down )
					sineChan.Rate/=1.00125
				Endif
				
				sineChan.Queue( sineData )
				
			Forever
			
		End )

#Endif

	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
