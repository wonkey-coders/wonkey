#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field point1:Vec2i,point2:Vec2i
	Method New()
		point2.x = 320
		point2.y = 240
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		point1.x = Mouse.X
		point1.y = Mouse.Y
		
		canvas.Color = Color.White
		canvas.DrawCircle(point2.x,point2.y,20)
		
		canvas.LineWidth = 3
		canvas.DrawLine(point1.x,point1.y,point2.x,point2.y)
		
		canvas.DrawText(getangle(point2.x,point2.y,point1.x,point1.y),0,0)
		canvas.DrawText("Pi : "+Pi,0,20)
		canvas.DrawText("TwoPi : "+TwoPi,0,40)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method
	'
	' Return the angle from - to in float
	Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
