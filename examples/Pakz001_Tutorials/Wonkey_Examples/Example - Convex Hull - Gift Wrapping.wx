#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	' create our points
	Field numpoints:Int=20
	Field point:Vec2i[]
	' our lines around the set of points
	Field wrap:Stack<Vec2i>
	Method New()
		wrapit()

	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		' Draw the convex hull or gift wrap
		' First the points
		canvas.Color=Color.White
		For Local i:Int=0 Until point.Length
			canvas.DrawRect(point[i].x,point[i].y,2,2)
		Next		
		' here the lines around the points
		For Local i:Int=1 Until wrap.Length			
			canvas.DrawLine(wrap[i].x,wrap[i].y,wrap[i-1].x,wrap[i-1].y)
		Next
		canvas.DrawLine(wrap[0].x,wrap[0].y,wrap[wrap.Length-1].x,wrap[wrap.Length-1].y)
		'
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	

	'
	' This is the wrapping routine. It creates a set of points and then
	' takes the left most point and then checks from the other points for
	' the next points if there are no more points on the left side. Thus
	' creating a set of lines around all the other points.
	'
	Method wrapit()
		SeedRnd(Microsecs())
		' create our points
		point = New Vec2i[numpoints]
		For Local i:Int=0 Until numpoints
			point[i].x = Rnd(100,640-100)
			point[i].y = Rnd(100,480-100)
		Next
		' create our stack for the wrap lines
		wrap = New Stack<Vec2i>		
		' find our left most point
		Local lp:Vec2i = New Vec2i(1000,1000)
		For Local i:Int=0 Until numpoints
			If point[i].x<lp.x Then lp.x = point[i].x ; lp.y=point[i].y
		Next
		' create our end point
		Local endpoint:Vec2i = New Vec2i()
		
	    Repeat
		    ' push the current left most point to the stack
	    	wrap.Push(lp)
	    	' get a new end point
	    	endpoint = point[0]
			' find the next point with no more on the left of our current (lp)left point
	    	For Local i:Int=1 Until numpoints
	        	If ((lp=endpoint) Or (orientation(lp.x,lp.y,endpoint.x,endpoint.y,point[i].x,point[i].y)=-1))
	    	    	endpoint = point[i]
	       		End If
			Next
	        lp=endpoint
	
	    Until Not(endpoint <> wrap.Get(0)) 'when at the start point then end
	End Method
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function

'Return if a point is left or center or right side of a line.
'line a to b and point left(<0) or center(0) or right(>0) is c
Function orientation:Int(ax:Int,ay:Int,bx:Int,by:Int,cx:Int,cy:Int)
	Return Sgn((bx-ax)*(cy-ay)-(by-ay)*(cx-ax))	
End Function
