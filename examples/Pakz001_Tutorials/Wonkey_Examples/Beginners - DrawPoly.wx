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
		' Draw the Poly
		canvas.Clear(Color.Black)
		canvas.Color = Color.Blue
		Local pol:= new Float[6]
		pol[0] = Mouse.X
		pol[1] = Mouse.Y
		pol[2] = 500
		pol[3] = 200
		pol[4] = 100
		pol[5] = 200
		canvas.DrawPoly(pol)
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
