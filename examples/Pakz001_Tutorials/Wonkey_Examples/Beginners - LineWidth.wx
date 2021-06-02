#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		
		canvas.LineWidth = 1
		canvas.DrawLine(50,50,100,100)
		canvas.LineWidth = 3
		canvas.DrawLine(50,50,200,100)
		canvas.LineWidth = 10
		canvas.DrawLine(50,50,300,100)
		
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
