#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field x1:Int=100,y1:Int=100
	Field x2:Int=200,y2:Int=200
	Field x3:Int=50,y3:Int=200
	
	Method New()
		Title="Point in Triangle Collision Function"
	End Method
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' Draw the things to the canvas.
		canvas.DrawTriangle(x1,y1,x2,y2,x3,y3)
		'93
		' Here we do the collision
		If pointintriangle2d(Mouse.X,Mouse.Y,x1,y1,x2,y2,x3,y3)
			canvas.DrawText("Collision",0,0)
		Else 'if no collision
			canvas.DrawText("No Collision",0,0)
		End If
		'
		canvas.DrawText("Move mouse inside triangle...",100,Height-20)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function

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
