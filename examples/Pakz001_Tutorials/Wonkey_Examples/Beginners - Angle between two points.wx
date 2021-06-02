#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Color = Color.White
		Local x1:Int=Width/2
		Local y1:Int=Height/2
		Local x2:Int=Mouse.X
		Local y2:Int=Mouse.Y
		Local angle:Float=getangle(x1,y1,x2,y2)
		canvas.DrawRect(x1,y1,2,2)
		canvas.DrawRect(x2,y2,2,2)
		Local x3:Int=x1+Cos(angle)*50
		Local y3:Int=y1+Sin(angle)*50
		canvas.DrawLine(x1,y1,x3,y3)
		'press escape to end
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method		
End	Class

Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
	Return ATan2(y2-y1, x2-x1)
End Function 

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
