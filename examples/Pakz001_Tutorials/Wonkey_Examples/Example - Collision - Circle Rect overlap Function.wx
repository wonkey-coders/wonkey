#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	' circle x and y and radius
	Field cx:Int=100,cy:Int=100
	Field cr:Int=50
	
	Method New()
		Title="Circle Rectagle Collision Function"
	End Method
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' Draw the things to the canvas.
		canvas.DrawCircle(cx,cy,cr)
		canvas.DrawRect(Mouse.X,Mouse.Y,50,50)
		'
		' Here we do the collision
		If circlerectcollide(cx,cy,cr,Mouse.X,Mouse.Y,50,50)
			canvas.DrawText("Collision",0,0)
		Else 'if no collision
			canvas.DrawText("No Collision",0,0)
		End If
		'
		canvas.DrawText("Move mouse inside cirle...",100,Height-20)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function

' Here is the circle vs rectangle collide function
' input :
' circlex,circley,circleradius
' rectx,recty,rectwidth,rectheight
' Returns : True or False
Function circlerectcollide:Bool(cx:Int,cy:Int,cr:Int, rx:Int,ry:Int,rw:Int,rh:Int)
    Local closestx:Float = Clamp(cx, rx, rx+rw)
    Local closesty:Float = Clamp(cy, ry, ry+rh)
    Local distancex :Float = cx - closestx
    Local distancey:Float = cy - closesty
    Local distancesquared:Float = (distancex * distancex) + (distancey * distancey)
    Return distancesquared < (cr * cr)
End Function
