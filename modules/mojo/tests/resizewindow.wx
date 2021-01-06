#rem

Use enter to toggle fullscreen, arrow keys to move window, +shift to size!

#end

Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window
	
	Field _ticks:=0
	
	Field _time:Double

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags|WindowFlags.Resizable|WindowFlags.HighDPI )
		
	End

	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()
		
		If Keyboard.KeyHit( Key.Enter )
			
			If Fullscreen EndFullscreen() Else BeginFullscreen()
				
		Else If Keyboard.KeyDown( Key.LeftShift )
			
			If Keyboard.KeyDown( Key.Left )
				ResizeWindow( Frame.X-1,Frame.Y,Frame.Width+2,Frame.Height )
			Else If Keyboard.KeyDown( Key.Right )
				ResizeWindow( Frame.X+1,Frame.Y,Frame.Width-2,Frame.Height )
			Else If Keyboard.KeyDown( Key.Up )
				ResizeWindow( Frame.X,Frame.Y-1,Frame.Width,Frame.Height+2 )
			Else If Keyboard.KeyDown( Key.Down )
				ResizeWindow( Frame.X,Frame.Y+1,Frame.Width,Frame.Height-2 )
			Endif
			
		Else
			
			If Keyboard.KeyDown( Key.Left )
				ResizeWindow( Frame.X-1,Frame.Y,Frame.Width,Frame.Height )
			Else If Keyboard.KeyDown( Key.Right )
				ResizeWindow( Frame.X+1,Frame.Y,Frame.Width,Frame.Height )
			Else If Keyboard.KeyDown( Key.Up )
				ResizeWindow( Frame.X,Frame.Y-1,Frame.Width,Frame.Height )
			Else If Keyboard.KeyDown( Key.Down )
				ResizeWindow( Frame.X,Frame.Y+1,Frame.Width,Frame.Height )
			Endif
			
		Endif
		
		canvas.DrawText( "Hello World! Ticks="+_ticks+" FPS="+App.FPS,Width/2,Height/2,.5,.5 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
