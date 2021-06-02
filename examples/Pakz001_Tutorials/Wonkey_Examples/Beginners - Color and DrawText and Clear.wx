#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		' The color goes from 0.0 to 1.0
		' red,green,blue,alpha
		' you can also set color by
		' canvas.Color = Color.Black 'ect
		canvas.Clear(New Color(0,0,0,1))
		canvas.Color = New Color(0.5,0,0,1)
		canvas.DrawText("Test....",0,0)		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
