#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance



Class MyWindow Extends Window
	
	Method New()
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Loop with sync
		Local kd:=False
		If Keyboard.KeyDown(Key.Space) Then kd=true
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		If kd = True Then
			canvas.DrawText("Space is pressed",0,0)
			Else
			canvas.DrawText("Space is not pressed",0,0)
		End If
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
