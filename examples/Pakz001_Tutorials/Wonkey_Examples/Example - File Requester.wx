#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance



Class MyWindow Extends Window
	
	Field filename:="Nothing"
	
	Method New()
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit		
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		If Keyboard.KeyReleased(Key.R) Then
			filename = RequestFile("Load the file")
		End if
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("R - File Requester",0,0)
		canvas.DrawText(filename,0,15)
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
