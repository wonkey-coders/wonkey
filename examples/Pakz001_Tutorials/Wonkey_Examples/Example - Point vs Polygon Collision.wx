  
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	' The variable for a line on the screen 

	Field polygonx:Int[],polygony:Int[]
	
	Method New()
		polygonx = New Int[4]
		polygony = New Int[4]
		polygonx[0] = 50
		polygony[0] = 50
		polygonx[1] = 150
		polygony[1] = 100
		polygonx[2] = 150
		polygony[2] = 200
		polygonx[3] = 100
		polygony[3] = 100
	End Method
	
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		
		'
		drawpoly(canvas)
		If pointpolycollide(Mouse.X,Mouse.Y) =True Then 
			canvas.Color = Color.White
			canvas.DrawText("Collision",0,0)
		End If
		
		canvas.Color = Color.White
		canvas.DrawText("Move mouse inside and outside of polygon",320,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Method drawpoly(canvas:Canvas)
		canvas.Color = Color.White
		For Local i:Int=1 Until polygonx.GetSize(0)
			canvas.DrawLine(polygonx[i-1],polygony[i-1],polygonx[i],polygony[i])			
		Next
		canvas.DrawLine(polygonx[0],polygony[0],polygonx[polygonx.GetSize(0)-1],polygony[polygony.GetSize(0)-1])
	End Method
	Method pointpolycollide:Bool(pointx:Int,pointy:Int)
		Local collisioncount:Int=0
		Local sx:Int=Rnd(640),sy:Int=Rnd(480)
		If Rnd()<.5 Then sx-=1000 Else sx+=1000
		If Rnd()<.5 Then sy-=1000 Else sy+=1000
		For Local i:Int=1 Until polygonx.GetSize(0)
			If get_line_intersection(polygonx[i-1],polygony[i-1],polygonx[i],polygony[i],pointx,pointy,sx,sy) Then collisioncount+=1			
		Next
		If get_line_intersection(polygonx[0],polygony[0],polygonx[polygonx.GetSize(0)-1],polygony[polygony.GetSize(0)-1],pointx,pointy,sx,sy) Then collisioncount+=1
		'
		If (collisioncount Mod 2) > 0 Then Return True
		
		'
		Return False
	End Method
End	Class

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
