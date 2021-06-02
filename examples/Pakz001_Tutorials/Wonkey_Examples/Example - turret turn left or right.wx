#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field angle:Float,targetangle:Float
	Field turretxy:Vec2i
	Field turretw:Int=20,turreth:Int=20
	Method New()
		turretxy.x = 320
		turretxy.y = 240
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Get the target angle (from >> To)
		targetangle = getangle(turretxy.x,turretxy.y,Mouse.X,Mouse.Y)
		
		'
		' Find the shortest turn towards target angle (stackoverflow)
		
		' Make the angle and target angle suitable for comapisment		
		If (targetangle >= (angle + Pi))
		    angle += TwoPi
		ElseIf (targetangle < (angle - Pi))
		        targetangle += TwoPi
		End If
		' .05 is the turn speed
		Local directiondiff:Float = targetangle - angle
		
		If (directiondiff < -.05)
		    directiondiff = -.05
		End If
		If (directiondiff > .05)
		    directiondiff = .05
		End If
		angle+=directiondiff
	
		' draw the turret
		canvas.Color = Color.Blue
		canvas.DrawOval(turretxy.x,turretxy.y,turretw,turreth)
		canvas.Color = Color.White
		' turret center x and y 
		Local tcx:Int=turretxy.x+turretw/2
		Local tcy:Int=turretxy.y+turreth/2
		' target angle
		Local dx:Float,dy:Float
		dx = tcx+Cos(targetangle)*20
		dy = tcy+Sin(targetangle)*20
		
		' get the turret barrel angle
		Local tx:Float,ty:Float
		tx = tcx+Cos(angle)*20
		ty = tcy+Sin(angle)*20
		canvas.LineWidth = 5
		canvas.DrawLine(tcx,tcy,tx,ty)
		canvas.LineWidth = 2
		canvas.DrawLine(tcx,tcy,dx,dy)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 	

End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
