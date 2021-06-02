#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class MyWindow Extends Window

	Field angle:=0.0

	Method New()
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Loop with sync
		angle+=0.05
		If angle>Pi*2 Then angle=0
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText(angle,0,0)
		canvas.DrawText("2xPi is full circle",0,15)
		canvas.DrawLine(320,200,320+Cos(angle)*20,200+Sin(angle)*20)
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
