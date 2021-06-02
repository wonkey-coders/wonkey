#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance



Class MyWindow Extends Window
	
	Method New()
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Mouse Button Left Down :"+Mouse.ButtonDown(MouseButton.Left),0,0)
		canvas.DrawText("Mouse Button Left Released :"+Mouse.ButtonReleased(MouseButton.Left),0,15)
		canvas.DrawText("Mouse Button Left Pressed :"+Mouse.ButtonPressed(MouseButton.Left),0,30)
		
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
