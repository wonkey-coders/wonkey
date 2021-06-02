#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		Title="Lambda example 1"
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' Here you create a lambda function nearby where you want to use it.
		' You do not have to create a different function for this elsewere in the
		' code.
		'
		Local add := Lambda:Int(a:Int, b:Int)
			Return a + b
		End Lambda
		
		canvas.DrawText("Lambda function result : "+add(10,10),0,40)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
