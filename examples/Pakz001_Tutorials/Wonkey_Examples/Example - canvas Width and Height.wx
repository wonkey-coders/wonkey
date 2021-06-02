#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Width of the canvas - ",0,0)
		canvas.DrawText(canvas.Viewport.Width,320,0)
		canvas.DrawText("Height of the canvas  - ",0,15)
		canvas.DrawText(canvas.Viewport.Height,320,15)
	End Method	
	
	Method OnKeyEvent( event:KeyEvent ) Override	
		Select event.Type
			Case EventType.KeyDown
			Select event.Key
				Case Key.Escape
			    instance.Terminate() 'exit with escape			    
			End Select
		End Select		
	End Method
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
