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
		'
		canvas.DrawText("Min example",0,0)
		Local a:Int=10
		Local b:Int=20
		Local c:Int=Min(a,b)
		canvas.DrawText("Lowest of a("+a+") and b("+b+") = "+c,0,40)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
