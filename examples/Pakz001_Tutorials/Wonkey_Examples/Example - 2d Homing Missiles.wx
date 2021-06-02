#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class missile
	Field x:Double,y:Double
	Field currentangle:Double	
	Field deleteme:Bool
	Method New(x:Double,y:Double)
		Self.x = x
		Self.y = y
	End Method
	Method update(mx:Double,my:Double)
		'Home the missile
        local targetx:Double = mx - x
        local targety:Double = my - y
        currentangle = ATan2(targety, targetx) * 180 / Pi
        '2 here below is the movement speed
        Local vx:Double = 2 * (90 - Abs(currentangle)) / 90
	    local vy:Double
	    if (currentangle < 0)
	        vy = -2 + Abs(vx)
	    Else
	        vy = 2 - Abs(vx)
		End if		     
	    x += vx
	    y += vy
	    'if collide then set remove flag
	    If rectsoverlap(mx-5,my-5,10,10,x-5,y-5,10,10) Then deleteme = true
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Black
		canvas.DrawCircle(x,y,5)
	End Method
	Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	Function
End Class

Global mymissile:List<missile> = New List<missile>

Class MyWindow Extends Window
	
	Method New()
		For Local i:Int=0 until 5
			mymissile.Add(New missile(Rnd(Width),Rnd(Height)))
		Next
	End Method	
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		'Update the missiles
		For Local i:=Eachin mymissile
			i.update(Mouse.X,Mouse.Y)
		Next
		For Local i:=Eachin mymissile
			If i.deleteme Then 
				mymissile.Remove(i)
				mymissile.Add(New missile(Rnd(Width),Height+50))
			End If
		Next

		'Draw the missile
		For Local i:=Eachin mymissile
			i.draw(canvas)
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function

