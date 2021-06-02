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
		canvas.DrawText("Clamp example",0,0)
		canvas.DrawText("a value = -10. b value = Clamp(a,0,10)",0,20)
		Local a:Int=-10
		' If the value of the clamp is lower then the lowest clamp value is set
		' if the value of the clamp is higher then the highest clamp value is set
		Local b:Int=Clamp(a,0,10)
		canvas.DrawText("value b after clamping = "+b,0,40)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
