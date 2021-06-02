#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field cx:Int=150,cy:Int=150
	Field cr:Int=50

	Method New()
	End Method
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' Draw the things to the canvas.
		canvas.DrawCircle(Mouse.X,Mouse.Y,32)
		canvas.DrawCircle(cx,cy,cr)
		'
		' Here we do the collision
		If circleoverlap(Mouse.X,Mouse.Y,32,cx,cy,cr)
			canvas.DrawText("Collision",0,0)
		Else 'if no collision
			canvas.DrawText("No Collision",0,0)
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function

' This is the circle circle overlap function
' x,y,radius vs x,y,radius
' returns true if collides
'
Function circleoverlap:Bool(x1:Int,y1:Int,r1:Int,x2:Int,y2:Int,r2:Int)
    Local dx:Int = x1-x2
    Local dy:Int = y1-y2
    Local r:Int = r1+r2
    If dx*dx+dy*dy <= r*r Then Return True Else Return False
End Function
