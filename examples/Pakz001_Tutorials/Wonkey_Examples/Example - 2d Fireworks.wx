#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' This is the particle class - Each particle is a part
' of the fireworks. It starts a light and heads in a 
' direction and dims out...
Class particle
	'fields
	Field x:Float,y:Float
	Field direction:Double
	Field speed:Float
	Field col:Color
	Field deleteme:Bool
	Field time:Int
	Method New(x:Int,y:Int,direction:Double)
			Self.x = x
			Self.y = y
			Self.speed = 3
			If Rnd(20)<3 Then Self.speed += Rnd(-.5,.5)
			Self.direction = direction
			Self.col = New Color(1,1,1)
	End Method 
	Method update()
		time+=1
		' If burn out then flag for delete
		If time > 60 Then deleteme = True
		' update the position
		x+=Cos(direction)*speed
		y+=Sin(direction)*speed
		' Dim out the color.
		col = New Color(col.R-1.0/60,col.G-1.0/60,col.B-1.0/60)
		' Slow the speed by a fraction
		speed -= speed/60
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = col
		canvas.DrawCircle(x,y,2)
	End Method	
End Class

Global myparticle:List<particle> = New List<particle>

Class MyWindow Extends Window
	
	Method New()
		Title="Fireworks..."
		'
		ClearColor = Color.Black
		'
		'
	End Method
	Method update()
		' Here we create the fireworks.
		' At a random situation
		If Rnd(100)<10
			' create a point (x,y)
			Local x:Int=Rnd(0,Width)
			Local y:Int=Rnd(0,Height)
			' 20 or so particles in a random direction
			For Local i:Int=0 Until 20
				myparticle.Add(New particle(x,y,Rnd(TwoPi)))
			Next
		End If
		' Update each particle
		For Local i:=Eachin myparticle
			i.update()
		Next
		' Delete flagged out particles
		For Local i:=Eachin myparticle
			If i.deleteme = True Then myparticle.Remove(i)
		Next		
	End Method	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' Here we call the update method
		update()
		'
		' Draw the particles
		For Local i:=Eachin myparticle
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

