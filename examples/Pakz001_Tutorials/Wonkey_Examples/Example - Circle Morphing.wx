#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' 
Class circlemorph
	Field numpoints:Int
	Field circlearray:Int[,]
	Field trianglearray:Int[,]
	Field drawarray:Int[,]
	' perc is the percentage between morph (0 to 1)
	' float is how fast we will morph
	Field perc:Float,ms:Float=.01
	Method New(numpoints:Int)
		Self.numpoints = numpoints
		circlearray = New Int[numpoints,2]
		trianglearray = New Int[numpoints,2]
		drawarray = New Int[numpoints,2]
		makearrays()
	End Method
	' Move the draw points between the circle and triangle
	Method update()				
		perc+=ms
		If perc>=1 Or perc<=0 Then ms=-ms		
		For Local i:Int=0 Until numpoints
			drawarray[i,0] = lerp(perc,circlearray[i,0],trianglearray[i,0])
			drawarray[i,1] = lerp(perc,circlearray[i,1],trianglearray[i,1])
		Next
	End Method
	' Create the triangle and the circle points
	Method makearrays()
		' create the circle points
		Local stp:Float=TwoPi/numpoints
		Local angle:Float=0
		For Local i:Int=0 Until numpoints
			circlearray[i,0] = Cos(angle)*50
			circlearray[i,1] = Sin(angle)*50
			angle+=stp
		Next		
		'create the triangle points
		Local x1:Int=(Cos(0)*150)
		Local y1:Int=(Sin(0)*150)
		Local x2:Int=Cos(Pi/2)*150
		Local y2:Int=Sin(Pi/2)*150
		Local x3:Int=Cos(TwoPi)*150
		Local y3:Int=Sin(TwoPi)*150
		stp = 1/(numpoints/3)
		For Local i:Int=0 Until numpoints/3
			trianglearray[i,0] = lerp(stp*i,x1,x2)
			trianglearray[i,1] = lerp(stp*i,y1,y2)
		Next
		For Local i:Int=0 Until numpoints/3
			trianglearray[i+(numpoints/3),0] = lerp(stp*i,x2,x3)
			trianglearray[i+(numpoints/3),1] = lerp(stp*i,y2,y3)
		Next
		For Local i:Int=0 Until numpoints/3
			trianglearray[i+(numpoints-(numpoints/3)),0] = lerp(stp*i,x3,x1)
			trianglearray[i+(numpoints-(numpoints/3)),1] = lerp(stp*i,y3,y1)
		Next

	End Method
	' Draw lines between the points
	Method draw(canvas:Canvas)		
		canvas.Color = Color.White
'		For Local i:=1 Until numpoints
'			canvas.DrawLine(circlearray[i-1,0],circlearray[i-1,1],circlearray[i,0],circlearray[i,1])
'		Next
'		canvas.DrawLine(circlearray[0,0],circlearray[0,1],circlearray[numpoints-1,0],circlearray[numpoints-1,1])
'		For Local i:=1 Until numpoints
'			canvas.DrawLine(trianglearray[i-1,0],trianglearray[i-1,1],trianglearray[i,0],trianglearray[i,1])
'		Next
'		canvas.DrawLine(trianglearray[0,0],trianglearray[0,1],trianglearray[numpoints-1,0],trianglearray[numpoints-1,1])
		For Local i:=1 Until numpoints
			canvas.DrawLine(drawarray[i-1,0],drawarray[i-1,1],drawarray[i,0],drawarray[i,1])
		Next
		canvas.DrawLine(drawarray[0,0],drawarray[0,1],drawarray[numpoints-1,0],drawarray[numpoints-1,1])

	End Method
	' Percentage 0 to 1 gives number between a and b
	Function lerp:double(t:double , a:double, b:double) 
		return a + t * (b - a)
	End Function 		
End Class

Class MyWindow Extends Window
	Field cm:circlemorph
	Method New()
		cm = New circlemorph(100)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)
		canvas.Translate(Width/2,Height/2)
		cm.update()
		cm.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
