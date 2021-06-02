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
		canvas.DrawText("FromChar example",0,0)
		canvas.DrawText("String.FromChar value of letter 97="+String.FromChar(97),0,20)
		canvas.DrawText("String.FromChar value of letter 65="+String.FromChar(65),0,40)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
