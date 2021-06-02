#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		Local loc:=0		
		For local i:=10 Until 0 Step -1
			canvas.DrawText("integer negative i:"+i,100,100+loc)
			loc+=10
		Next
		loc=0
		For Local i:=10.0 To 0 Step -0.5
			canvas.DrawText("float negative i:"+i,320,100+loc)
			loc+=10
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
