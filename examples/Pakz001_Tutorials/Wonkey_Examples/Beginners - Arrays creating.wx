#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Field myarray1:Int[] = New Int[](0,1,2,3,4,5,6,7,8,9)
	Field myarray2:String[,] = New String[10,10]
	Field myarray3:String[,,] = New String[10,10,10]
	Method New()
		myarray1[0] = 10
		myarray2[0,0] = "test1"
		myarray3[0,0,0] = "test2"
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		canvas.Color = Color.White
		canvas.DrawText(myarray1[0],0,20)
		canvas.DrawText(myarray2[0,0],0,40)
		canvas.DrawText(myarray3[0,0,0],0,60) 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
