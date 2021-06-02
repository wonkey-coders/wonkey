  
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	' The variable for a line on the screen 

	Field polygon1x:Int[],polygon1y:Int[]
	Field polygon2x:Int[],polygon2y:Int[]
	
	Method New()
		polygon1x = New Int[4]
		polygon1y = New Int[4]
		polygon1x[0] = 0 + 200
		polygon1y[0] = 0 + 200
		polygon1x[1] = 50 + 200
		polygon1y[1] = 0 + 200
		polygon1x[2] = 50 + 200
		polygon1y[2] = 50 + 200
		polygon1x[3] = -20 + 200
		polygon1y[3] = 50 + 200
		
		
		polygon2x = New Int[4]
		polygon2y = New Int[4]
		polygon2x[0] = 0 
		polygon2y[0] = 0 
		polygon2x[1] = 100
		polygon2y[1] = 50
		polygon2x[2] = 100
		polygon2y[2] = 150
		polygon2x[3] = 50
		polygon2y[3] = 50

	End Method
	
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' update the position of the second polygon
		polygon2x[0] = 0 + Mouse.X
		polygon2y[0] = 0 + Mouse.Y
		polygon2x[1] = 50 +100+ Mouse.X
		polygon2y[1] = 0 + Mouse.Y
		polygon2x[2] = 50 +100+ Mouse.X
		polygon2y[2] = 100 +100 +Mouse.Y
		polygon2x[3] = 0 + Mouse.X
		polygon2y[3] = 0  +100+Mouse.Y
		'
		'
		drawpolygon(canvas,polygon1x,polygon1y)
		drawpolygon(canvas,polygon2x,polygon2y)
		'
		canvas.Color = Color.White
		If polypolycollide(polygon1x,polygon1y,polygon2x,polygon2y)
			canvas.DrawText("Collision",0,0)
		Else
			canvas.DrawText("---- No Collision",0,0)
		End If
		
		canvas.Color = Color.White
		canvas.DrawText("Move mouse inside and outside of polygon",320,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Method drawpolygon(canvas:Canvas,polygonx:Int[],polygony:Int[])
		canvas.Color = Color.White
		For Local i:Int=1 Until polygonx.GetSize(0)
			canvas.DrawLine(polygonx[i-1],polygony[i-1],polygonx[i],polygony[i])			
		Next
		canvas.DrawLine(polygonx[0],polygony[0],polygonx[polygonx.GetSize(0)-1],polygony[polygony.GetSize(0)-1])
	End Method
	
End	Class

Function polypolycollide:Bool(poly1x:Int[],poly1y:Int[],poly2x:Int[],poly2y:Int[])
	'first check if the second polygon is inside the first polygon
	Local x:Int=-5000,y:Int=-5000
	Local cnt:Int=0
	For Local i:Int=1 Until poly1x.GetSize(0)
		If get_line_intersection(x,y,poly2x[0],poly2y[0],poly1x[i-1],poly1y[i-1],poly1x[i],poly1y[i]) Then cnt+=1
	Next
	If get_line_intersection(x,y,poly2x[0],poly2y[0],poly1x[poly1x.GetSize(0)-1],poly1y[poly1x.GetSize(0)-1],poly1x[0],poly1y[0]) Then cnt+=1
	'
	If (cnt Mod 2) > 0	Then Return True
	'Now check if the first polygon is inside the second polygon
	x=-5000
	y=-5000
	cnt=0
	For Local i:Int=1 Until poly2x.GetSize(0)
		If get_line_intersection(x,y,poly1x[0],poly1y[0],poly2x[i-1],poly2y[i-1],poly2x[i],poly2y[i]) Then cnt+=1
	Next
	If get_line_intersection(x,y,poly1x[0],poly1y[0],poly2x[poly2x.GetSize(0)-1],poly2y[poly2x.GetSize(0)-1],poly2x[0],poly2y[0]) Then cnt+=1
	'
	If (cnt Mod 2) > 0	Then Return True

	'
	' Now check if any of the lines of the two polygons touch
	For Local i:Int=1 Until poly1x.GetSize(0)
	For Local j:Int=1 Until poly2x.GetSize(0)
		If get_line_intersection(poly2x[j-1],poly2y[j-1],poly2x[j],poly2y[j],poly1x[i-1],poly1y[i-1],poly1x[i],poly1y[i]) Then Return True
	Next
	Next
	For Local j:Int=1 Until poly2x.GetSize(0)
		If get_line_intersection(poly2x[j-1],poly2y[j-1],poly2x[j],poly2y[j],poly1x[0],poly1y[0],poly1x[poly1x.GetSize(0)-1],poly1y[poly1x.GetSize(0)-1]) Then Return True
	Next
	For Local j:Int=1 Until poly1x.GetSize(0)
		If get_line_intersection(poly1x[j-1],poly1y[j-1],poly1x[j],poly1y[j],poly2x[0],poly2y[0],poly2x[poly1x.GetSize(0)-1],poly2y[poly2x.GetSize(0)-1]) Then Return True
	Next

	'There was no Collision between the two polygons ___ Return
	Return False
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function


'// Returns 1 if the lines intersect, otherwise 0.  Andre la moth.
Function get_line_intersection:Bool(p0_x:Float, p0_y:Float, p1_x:Float, p1_y:Float, p2_x:Float,p2_y:Float, p3_x:Float, p3_y:Float)
	
    Local s1_x:Float, s1_y:Float, s2_x:Float, s2_y:Float
    s1_x = p1_x - p0_x     
    s1_y = p1_y - p0_y
    s2_x = p3_x - p2_x
    s2_y = p3_y - p2_y

    Local s:Float, t:Float
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y)
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y)

    If (s >= 0 And s <= 1 And t >= 0 And t <= 1) Then Return True
    

    Return False '// No collision
End Function
End Function
