#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		canvas.Color = Color.White
		Local a:Float=edistance(Mouse.X,Mouse.Y,320,240)
		Local b:Float=distance(Mouse.X,Mouse.Y,320,240)
		canvas.DrawText("Uclidean distance :"+a,0,0)
		canvas.DrawText("Manhattan distance :"+b,0,20)
		canvas.DrawLine(Mouse.X,Mouse.Y,320,240)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method
	Function edistance:Float(x1:Float,y1:Float,x2:Float,y2:Float) 
		Return Sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) )
	End Function
    ' Manhattan Distance (less precise)
    Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
	    Return Abs(x2-x1)+Abs(y2-y1)   
    End Function
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
