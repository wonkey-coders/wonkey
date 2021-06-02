'
' Line segment vs Circle collision
'
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)
        ' the mouse location for circle to line collision
        Local cx:Float=Mouse.X,cy:Float=Mouse.Y
        Local cr:Int=20 'circle radius
        'draw the circle
        canvas.DrawCircle(cx,cy,cr)
        ' line coordinates
        Local l1:Int[]=New Int[](100,100,200,200) ' line x1,y1,x2,y2
        Local l2:Int[]=New Int[](250,100,290,300)
        ' draw the lines
        canvas.Color = Color.Grey
    	canvas.DrawLine(l1[0],l1[1],l1[2],l1[3]) 'x1,y1,x2,y2
    	canvas.DrawLine(l2[0],l2[1],l2[2],l2[3]) ',,

 		canvas.Color = Color.White
 		' check the collisions
 		If circlelinecollide(l1[0],l1[1],l1[2],l1[3],cx,cy,cr)
 			canvas.DrawText("Collide line 1",0,20)
 		Else
 			canvas.DrawText("No Collide line 1",0,20)
 		End If
 		If circlelinecollide(l2[0],l2[1],l2[2],l2[3],cx,cy,cr)
 			canvas.DrawText("Collide line 2",0,40)
 		Else
 			canvas.DrawText("No Collide line 2",0,40)
 		End If
 		
 		canvas.DrawText("Move Mouse around to check collisions with lines.",0,0)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

'
' Line(segment) to Circle Collision
'
Function circlelinecollide:Bool(sx1:Int, sy1:Int, sx2:Int, sy2:Int, cx:Int, cy:Int,cr:Float)
    Local xDelta:Float = sx2 - sx1
    Local yDelta:Float = sy2 - sy1
    Local px:Int,py:Int
    Local u:Float

    If ((xDelta = 0) And (yDelta = 0))    
     	Print("Segment start equals segment end")
    	
    End If

    u = ((cx - sx1) * xDelta + (cy - sy1) * yDelta) / (xDelta * xDelta + yDelta * yDelta)

    If (u < 0)
     	px = sx1
      	py = sy1
    Else If (u > 1)
    	px = sx2
    	py = sy2
    Else
    	px = Int(Floor(sx1 + u * xDelta))
    	py = Int(Floor(sy1 + u * yDelta))
    End If
	' If the distance of the circle to the closest point in the line
	' is less then the radius then there is a collision
	Local d:Int= Sqrt( Pow(px - cx,2) + Pow(py - cy,2))
	If d<=(cr) Then Return True
	Return False
End Function


Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
