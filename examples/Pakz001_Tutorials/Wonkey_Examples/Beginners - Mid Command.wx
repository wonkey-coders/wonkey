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
		Local a:="abcdefghijklmnopqrstuvwxyz"
		canvas.DrawText("a = "+a,0,0)
		canvas.DrawText("a.Mid(0,1) = "+a.Mid(0,1),0,20)
		canvas.DrawText("a.Mid(1,5) = "+a.Mid(1,5),0,40)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
