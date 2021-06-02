#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field r:bool
	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Keyboard.KeyReleased(Key.F1)
			r=Confirm("Title","Is this true?",False)
		End If
		canvas.DrawText("Press F1 for Notify Request",0,0)
		If r=False then	canvas.DrawText("Last request return value r = false",0,20)
		If r=true then	canvas.DrawText("Last request return value r = true",0,20)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
