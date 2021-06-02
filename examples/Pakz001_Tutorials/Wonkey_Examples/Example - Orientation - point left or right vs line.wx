#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field point1:Vec2i,point2:Vec2i
	Field point3:Vec2i
	Field time:Int
	Method New()
		newline()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		time+=1		
		'draw the line
		canvas.Color = Color.White
		canvas.DrawLine(point1,point2)
		canvas.DrawText("p1",point1.x,point1.y)
		canvas.DrawText("p2",point2.x,point2.y)
		canvas.Color = Color.Red
		canvas.DrawCircle(point3.x,point3.y,20)
		canvas.Color = Color.Yellow		
		Local side:Int = orientation(point1.x,point1.y,point2.x,point2.y,point3.x,point3.y)
		Local t:String="point is on the line."		
		If side<0 Then t="Point is on the left side of the line." 
		If side>0 Then t="Point is on the right side of the line." 
		canvas.DrawText(t,0,0)
		If Keyboard.KeyReleased(Key.Space) Or time>120 Then newline() ; time=0
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		
	End Method	

	Method newline()
		point1 = New Vec2i(Rnd(50,590),Rnd(50,430))
		Local x:Int=Rnd(40,90),y:Int=Rnd(40,90)
		If Rnd()<.5 Then x=-x
		If Rnd()<.5 Then y=-y		
		point2 = New Vec2i(point1.x+x,point1.y+y)		
		point3 = New Vec2i(Rnd(640),Rnd(480))
	End Method
	
End	Class
'
' This is the orientation function. It returns -1 if the point is left of the inputted line.
' 0 if on the same and 1 if on the right of the line.
'
Function orientation:Int(ax:Int,ay:Int,bx:Int,by:Int,cx:Int,cy:Int)
	Return Sgn((bx-ax)*(cy-ay)-(by-ay)*(cx-ax))	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
