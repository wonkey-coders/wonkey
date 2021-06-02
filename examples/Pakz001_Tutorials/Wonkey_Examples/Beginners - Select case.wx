#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		Title="Select Case Example"
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		Local out1:String
		Local out2:string
		Local a:String="ab"
		'
		Select a
			Case "a"
				out1 = "string was value :"+a
			Case "ab","abc"
				out1 = "string was value :"+a
			Default
				out1 = "string was value :"+a
		End Select 
		'	
		Local b:Int=1
		'
		Select b
			Case 1,2,3,4
				out2 = "integer was value : "+b
			Case 10
				out2 = "integer was value : "+b
			Default
				out2 = "integer was value : "+b
		End Select 
		'
		canvas.DrawText("a was : "+out1+" - b was : "+out2,0,50)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
