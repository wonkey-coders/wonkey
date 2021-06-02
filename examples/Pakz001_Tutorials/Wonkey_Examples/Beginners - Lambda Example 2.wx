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
		' Here we create a lambda that returns a string.
		' 		
		Local append := Lambda:String(a:String,b:String)
			Return a+b
		End lambda
		
		canvas.DrawText("Lambda function result : "+append("conn","-ect"),0,40)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
