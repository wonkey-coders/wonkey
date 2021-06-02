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
		Local a:="test1"
		Local b:="test2"
		canvas.DrawText("a="+a,0,0)
		canvas.DrawText("b="+b,0,20)
		If a=b Then
			canvas.DrawText("a and b is the same",0,50)
			Else
			canvas.DrawText("a and b is different",0,70) 
		End If
		Local c:="test3"
		Local d:="test3"
		canvas.DrawText("c="+c,0,110)
		canvas.DrawText("d="+d,0,130)
		If c=d Then
			canvas.DrawText("c and d is the same",0,170)
			Else
			canvas.DrawText("c and d is different",0,190)
		End If
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
