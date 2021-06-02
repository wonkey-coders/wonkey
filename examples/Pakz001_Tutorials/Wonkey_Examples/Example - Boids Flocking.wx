#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class obstacle
	Field x:Float,y:Float
	Field radius:Int
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		Self.radius = 20	
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Yellow
		canvas.DrawCircle(x,y,radius)
	End Method	
End Class

Class boid
	Field friendlist:List<boid> = New List<boid>
	Field x:Float,y:Float,angle:Float
	Field vx:Float,vy:Float
	Field alignspeed:Float = 8
	Field speed:Float = 3
	Field smoothturn:Float = 25
	Field radius:Float = 10
	Field cohesionfactor:Float = 100
	Field friendradius:Float = 75
	Field frienddistance:Float = 30
	Field friendsqradius:Float
	Field friendsqrdistance:Float
	Field obstaclemargin:Float = 2
	Method New()
		friendsqradius = friendradius*friendradius
		friendsqrdistance = frienddistance*frienddistance
	End Method
	Method create(count:Int)
		For Local i:=0 Until count
			Local newboid:boid = New boid()
			newboid.x = Rnd(640)
			newboid.y = Rnd(480)
			newboid.angle = Rnd(360)
			boidlist.AddLast(newboid)
		Next
	End Method
	Method update()
		getfriends()
		If friendlist.Count() > 0
			vx = 0
			vy = 0
			cohesion()
			obstacle()
			distance()
			align()
		Else
			obstacle()
		End If		
		' Clamp the movement speed
 		If vx < -2 Then vx = -2 
 		If vy < -2 Then vy = -2
 		If vx > 2 Then vx = 2
 		If vy > 2 Then vy = 2
		move()
	End Method
	Method obstacle()
		For Local i:=Eachin myobstacle
			Local diffx:Float = x - i.x
			Local diffy:Float = y - i.y
			Local sqrdistance:Float=diffx*diffx+diffy*diffy
			If diffx*diffx+diffy*diffy < i.radius*i.radius*i.radius/obstaclemargin
				vx -= (i.x - x) / Sqrt(sqrdistance) 
				vy -= (i.y - y) / Sqrt(sqrdistance)
			End If
		Next
	End Method
	Method cohesion()
		Local centerx:Float
		Local centery:Float
		For Local i:= Eachin friendlist
			centerx += i.x
			centery += i.y
		Next
		centerx /= friendlist.Count()
		centery /= friendlist.Count()
		vx += (centerx-x) / cohesionfactor
		vy += (centery-y) / cohesionfactor
	End Method
	Method distance()
		For Local i:=Eachin friendlist
			Local diffx:Float=x-i.x
			Local diffy:Float=y-i.y
			Local sqrdistance:Float=diffx*diffx+diffy*diffy
			If diffx*diffx+diffy*diffy < friendsqrdistance
				vx -= (i.x - x) / Sqrt(sqrdistance)
				vy -= (i.y - y) / Sqrt(sqrdistance)
			End If
		Next
	End Method
	Method align()
		Local sumvx:Float
		Local sumvy:Float
		For Local i:=Eachin friendlist
			sumvx += i.vx
			sumvy += i.vy
		Next
		sumvx /= friendlist.Count()
		sumvy /= friendlist.Count()
		vx += (sumvx - vx) / alignspeed
		vy += (sumvy - vy) / alignspeed
	End Method
	Method move()
 		x += vx
		y += vy
		angle = smoothrotate(x,y,angle,x+vx,y+vy,smoothturn)
		x += Cos(angle) * speed
		y += Sin(angle) * speed
		If x<0 Then x = 640
		If y<0 Then y = 480
		If x>640 Then x = 0
		If y>480 Then y = 0
	End Method
	Method getfriends()
		friendlist.Clear()
		For Local i:=Eachin boidlist
			Local diffx:Float=x-i.x
			Local diffy:Float=y-i.y			
			If diffx*diffx+diffy*diffy < friendsqradius
				If i <> Self Then 
					friendlist.AddLast(i)
				End If
			End If
		Next
	End Method
	Method updateall()
		For Local i:=Eachin boidlist
			i.update()
		Next
	End Method
	Method drawall(canvas:Canvas)
		For Local i:=Eachin boidlist
			i.draw(canvas)
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawCircle(x,y,10)
	End Method
	Function smoothrotate:Float(sourceX:Float,sourceY:Float,sourceAngle:Float,destX:Float,destY:Float,smooth:Float)
		' Thanks to BlackSp1der on BB forums for this piece of code ! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		Local targetAngle:Float = ATan2(sourceY-destY,sourceX-destX)
		Local tempAngle:Float = targetAngle - Sgn(targetAngle-sourceAngle) * 360
		If Abs(targetAngle-sourceAngle) > Abs(tempAngle-sourceAngle) Then targetAngle = tempAngle
		If sourceAngle <> targetAngle Then sourceAngle = sourceAngle - Sgn(targetAngle-sourceAngle) * (180-Abs(targetAngle-sourceAngle)) / (1+smooth)
		If sourceAngle >= 360 Then sourceAngle -= 360 Else If sourceAngle < 0 Then sourceAngle += 360
		Return sourceAngle
	End Function	
End Class

Global myobstacle:List<obstacle>
Global boidlist:List<boid> = New List<boid>



Class MyWindow Extends Window
	Field myboid:boid
	
	Method New()
		myobstacle = New List<obstacle>
    	For Local i:Int = 0 Until 10
    		myobstacle.AddLast(New obstacle(Rnd(640),Rnd(480)))
    	Next
        myboid = New boid()
        myboid.create(20)
		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 

    	If Mouse.ButtonReleased(MouseButton.Left) Then myobstacle.AddLast(New obstacle(Mouse.X,Mouse.Y))
    	If Keyboard.KeyReleased(Key.Space) Then 
    		For Local i:Int = 0 Until 10
    			myobstacle.AddLast(New obstacle(Rnd(640),Rnd(480)))
    		Next
    	End If

		myboid.updateall() 

        myboid.drawall(canvas)
        
        For Local i:=Eachin myobstacle
        	i.draw(canvas)
        Next' if key escape then quit

		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
