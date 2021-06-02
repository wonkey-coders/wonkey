#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance


Class MyWindow Extends Window

	Method New()		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()				
		' Draw the Triangle
		canvas.Clear(Color.Black)
		canvas.Color = Color.Blue
		canvas.DrawTriangle(New Vec2f(Mouse.X,Mouse.Y),New Vec2f(200,200),New Vec2f(50,200))
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
