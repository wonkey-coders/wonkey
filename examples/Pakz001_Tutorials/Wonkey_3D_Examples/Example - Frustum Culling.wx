#Import "<std>"
#Import "<mojo>"

' Frustum Culling
' Every tile would be a mesh. The frustum culling would 
' find what is visible in the camera and what not would not
' be drawn.
'

Using std..
Using mojo..


Class MyWindow Extends Window

	' Our camera angle
	Field angle:Float

	Method New()

	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Our base coordinates
		' and left side and right side coordinates
		' of triangle
		Local b:Vec2i
		Local l:Vec2i
		Local r:Vec2i
		
		' base is the center of the screen
		b.X = 320
		b.Y = 240
		' left and right side coordinates
		l.X=b.X+(Cos(angle-Pi/4)*250)
		l.Y=b.Y+(Sin(angle-Pi/4)*250)
		r.X=b.X+(Cos(angle+Pi/4)*250)
		r.Y=b.Y+(Sin(angle+Pi/4)*250)
		
		' Draw our frustrum lines
		canvas.DrawLine(b.X,b.Y,l.X,l.Y)
		canvas.DrawLine(b.X,b.Y,r.X,r.Y)
	
		' Here we draw our map. The green tiles
		' would be visible and the red ones would
		' not be visible
		'
		For Local y:Int=0 Until 20
		For Local x:Int=0 Until 20
			If pointintriangle2d(x*32,y*32,b.X,b.Y,l.X,l.Y,r.X,r.Y)
				canvas.Color = Color.Green	
			Else
				canvas.Color = Color.Red
			End if
			canvas.DrawRect(x*32,y*32,32,32)
		Next
		Next
		
		' Move the camera angle
		If Keyboard.KeyDown(Key.Left) Then angle-=.1 
		If Keyboard.KeyDown(Key.Right) Then angle+=.1
		
		canvas.Color = Color.White
		canvas.DrawText("Use cursor left and right to move camera angle.",0,0)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	

End	Class



' Here is the point in triangle collision function
' by RaGR (Ralph G. Roeske). from blitzbasic.com
' px,py = pixel x and y to test collision with
' x1,y1,x2,y2,x3,y3 = The triangle points
Function pointintriangle2d:bool(px:Float,pz:Float, x1:Float,y1:Float,x2:Float,y2:Float,x3:Float,y3:Float) 
    Local bc:Float,ca:Float,ab:Float,ap:Float,bp:Float,cp:Float,abc:Float
    bc = x2*y3 - y2*x3 
    ca = x3*y1 - y3*x1 
    ab = x1*y2 - y1*x2
    ap = x1*pz - y1*px
    bp = x2*pz - y2*px
    cp = x3*pz - y3*px
    abc = Sgn(bc + ca + ab)
    If (abc*(bc-bp+cp)>=0) And (abc*(ca-cp+ap)>=0) And (abc*(ab-ap+bp)>=0) Return True
	Return False
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
