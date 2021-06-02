#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		canvas.Color = Color.Red
		canvas.DrawRect(0,10,90,90)
		canvas.Color = Color.Red*5
		canvas.DrawRect(100,10,90,90)
		canvas.Color = Color.Red/2
		canvas.DrawRect(200,10,90,90)
		canvas.Color = Color.Blue+.2
		canvas.DrawRect(300,10,90,90)
		canvas.Color = Color.Blue.Blend(Color.White,.7)
		canvas.DrawRect(400,10,90,90)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
