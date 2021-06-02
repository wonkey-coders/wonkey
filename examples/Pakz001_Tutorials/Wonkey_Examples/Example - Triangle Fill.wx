#Import "<std>"
#Import "<mojo>"

'
' Fill triangles using the bresenham algorithm
'

Using std..
Using mojo..

Class filledtriangle
	' These variables are the points of
	' the triangle.
	Field x1:Int,y1:Int
	Field x2:Int,y2:Int
	Field x3:Int,y3:Int
	' This variable is the y of the triangle
	' that has the lowest value.
	Field lowesty:Int
	' This is the total height of the triangle.
	Field sizey:Int
	' These arrays hold the x coordinates with
	' which we draw the lines.
	Field lefty:Int[]
	Field righty:Int[]
	' Here we create and draw the triangle.
	Method New(canvas:Canvas,x1:Int,y1:int,x2:Int,y2:int,x3:int,y3:int)
		' In order to draw below ZERO we add a value to the inputted
		' coordinates. We decrease this amount when drawing the
		' actual triangles on the canvas.
		Local offscreen:Int=10000
		x1 += offscreen
		y1 += offscreen
		x2 += offscreen
		y2 += offscreen
		x3 += offscreen
		y3 += offscreen
		' We need to know which coordinate has the lowest
		' y value and we put that in the lowesty variable.
		'find lowest
		If y1<y2 And y1<y3 Then lowesty = y1
		If y2<y1 And y2<y3 Then lowesty = y2
		If y3<y1 And y3<y2 Then lowesty = y3
		' We also need to know the total height of the
		' triangle so we can create a array of that size
		' where we store the left and right side line
		' coordinates in.
		'find height
		If y1>y2 And y1>y3 Then sizey = y1-lowesty
		If y2>y1 And y2>y3 Then sizey = y2-lowesty
		If y3>y1 And y3>y2 Then sizey = y3-lowesty
		'
		' If there is nothing to draw then
		' exit this method.
		If sizey = 0 Then Return
		' Create two arrays which will hold the coordinates
		' for the lines inside the triangles. The x coordinates.
		lefty = New Int[sizey+1]
		righty = New Int[sizey+1]
		' Here we fill the lefty and righty arrays with the
		' x coordinates of the lines inside the triangles.
		bline(x1,y1,x2,y2)
		bline(x2,y2,x3,y3)
		bline(x1,y1,x3,y3)
		' Here we draw the lines inside the triangles. Filling
		' it. You can do per pixel for colloring ect.
		For Local y:Int=0 until sizey
			canvas.DrawLine(lefty[y]-offscreen,lowesty+y-offscreen,righty[y]-offscreen,lowesty+y-offscreen)
		Next
	End Method
	'
	' This is the bresenham algorithm. It is modified so
	' it fills two arrays with the x coordinates of the
	' lines inside the triangles.
	Method bline:Void(x4:Int,y4:Int,x5:Int,y5:Int)
	    Local dx:Int, dy:Int, sx:Int, sy:Int, e:Int
	    dx = Abs(x5 - x4)
	    sx = -1
	    If x4 < x5 Then sx = 1      
	    dy = Abs(y5 - y4)
	    sy = -1
	    If y4 < y5 Then sy = 1
	    If dx < dy Then 
	        e = dx / 2 
	    Else 
	        e = dy / 2          
	    End If
	    Local exitloop:Bool=False
	    While exitloop = False
			' Here we fill the left and right sides arrays.
			' we draw lines between these later on to fill the triangle		  	      		
	      	
	    	If lefty[y4-lowesty] = 0 Then 'If left not used then fill left
	     		lefty[y4-lowesty] = x4
	    	Elseif righty[y4-lowesty] = 0 'if right not used then fill right
	   			righty[y4-lowesty] = x4	
	     	Else 'if both sides are filled
		    	If lefty[y4-lowesty] = x4 Then  'overwrite same value
			    	lefty[y4-lowesty] = x4
				Else 'write new value
					righty[y4-lowesty] = x4	
				End If   	
	      	End If
	  

	      If x4 = x5 
	          If y4 = y5
	              exitloop = True
	          End If
	      End If
	      If dx > dy Then
	          x4 += sx ; e -= dy 
	           If e < 0 Then e += dx ; y4 += sy
	      Else
	          y4 += sy ; e -= dx 
	          If e < 0 Then e += dy ; x4 += sx
	      Endif

	    Wend
	
	End Method
		
End Class

Class MyWindow Extends Window
	' cnt is used for the seed
	Field cnt:Int
	' mytriangle is used to draw a triangle
	Field mytriangle:filledtriangle
	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Always draw the same using this seed
		SeedRnd(cnt)
		' Draw 100 triangles
		For Local i:=0 Until 100
			Local x1:Int=Rnd(0,Width)
			Local y1:Int=Rnd(0,Height)
			Local x2:Int=x1+Rnd(-80,80)
			Local y2:Int=y1+Rnd(-80,80)
			Local x3:Int=x1+Rnd(-80,80)
			Local y3:Int=y1+Rnd(-80,80)		
			canvas.Color = New Color(Rnd(1),Rnd(1),Rnd(1))
			mytriangle = New filledtriangle(canvas,x1,y1,x2,y2,x3,y3)
		Next
		' Draw some text
		canvas.Color = Color.Black
		canvas.DrawText("Press the space bar or lmb to draw new set",0,0)
		' If pressed space then new set of triangles
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Then cnt+=1
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
