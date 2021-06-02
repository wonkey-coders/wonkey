#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		Title="Lambda example 3"
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' Here you create a lambda function nearby where you want to use it.
		' You can modify global things inside lambda functions
		'
		global z:Int
		Local tst := Lambda()
			z=10
		End Lambda
		tst()

		canvas.DrawText("Lambda function result : "+z,0,40)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
