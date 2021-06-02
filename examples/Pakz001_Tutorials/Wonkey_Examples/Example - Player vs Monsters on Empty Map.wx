#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class enemy
	Field x:Float,y:Float
	Field ms:Float 'movement speed
	Field w:Int=32
	Field h:Int=32
	Field hp:Int
	Field hpceil:Int
	Field direction:String="up" ' left/right/up/down
	Field current:Bool=False 'if being updated
	Field deleteme:Bool=False
	Method New()
		' find a spot to place the new enemy
		Local exitloop:Bool=False
		While exitloop=False
			exitloop = True
			Local nx:Int = Rnd(50,640-50)
			Local ny:int = Rnd(50,480-50)			
			For Local i:=Eachin myenemy
				If distance(nx,ny,i.x,i.y) < 30 Or distance(myplayer.x,myplayer.y,nx,ny) < 250
					exitloop = False
				End If
			Next
			If exitloop = True Then
				x = nx
				y = ny
			End If
		Wend
		' Here we set the movement speed
		ms = Rnd(.1,.5)
		' Here we set the hitpoints
		hp = Rnd(1,50)
		' the ceiling is what he has or had at start (powerbar)
		hpceil = hp
	End Method
	Method update()
		current=True
		' store the old location
		Local oldx:Float=x
		Local oldy:Float=y
		' move the enemy towards the player
		If collide(x+1,y) = False And x < myplayer.x Then 
			x+=ms
			direction = "right"
		End If
		If collide(x-1,y) = False And x > myplayer.x Then 
			x-=ms
			direction = "left"
		End If
		If collide(x,y+1) = False And y < myplayer.y Then 
			y+=ms
			direction = "down"
		End If
		If collide(x,y-1) = False And y > myplayer.y Then 
			y-=ms
			direction = "up"
		End If
		untangle()
		current=False
	End Method
	Method untangle()
		For Local i:=Eachin myenemy
			If i.current=False
				If distance(i.x,i.y,x,y) < w
					Local a:Int
					a = getangle(i.x,i.y,x,y)
					x += Cos(a)*1
					y += Sin(a)*1
				End If
			End If
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Red
		canvas.DrawOval(x-w/2,y-w/2,w,w)
		'powerbar
		Local current:Float=(Float(w)/Float(hpceil))*hp
		
		canvas.Color = Color.Black
		canvas.DrawRect(x-w/2,y+w/2,w,5)
		canvas.Color = Color.Red
		canvas.DrawRect(x-w/2,y+1+w/2,current,3)
	End Method
	Method collide:Bool(xx:Int,yy:Int)
		For Local i:=Eachin myenemy
			If i.current = False
				If distance(xx,yy,i.x,i.y) < w Then Return True
			End If
		Next
		Return False
	End Method
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
    	Return Abs(x2-x1)+Abs(y2-y1)
	End Function	
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 		
End Class


Class player
	Field x:Float,y:Float
	Field w:Int=32
	Field h:Int=32
	Field wx:Int,wy:Int
	Field direction:String="up" ' up/left/down/right
	Field weapondamage:Int=3
	Field swing:Bool=False
	Field swingcountdown:Int=0
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		direction = "up"
	End Method
	Method update()
		updatecontrols()
		weaponenemies()
	End Method
	Method weaponenemies()
		If swing = False Then Return
		For Local i:=Eachin myenemy
			If distance(i.x,i.y,wx,wy) < 48
				Local a:Int=getangle(wx,wy ,i.x,i.y)
				i.x += Cos(a) * 32
				i.y += Sin(a) * 32
				i.hp -= weapondamage
				If i.hp<1 Then i.deleteme = True
			End If			
		Next
	End Method
	Method updatecontrols()
	    ' store the location of the player
		Local oldx:Int=x
		Local oldy:Int=y
		'handle the movement
		If Keyboard.KeyDown(Key.Right) Then 
			x+=1
			direction = "right"
			swing=False
		End If
		If Keyboard.KeyDown(Key.Left) Then 
			x-=1
			direction = "left"
			swing=False
		End If
		If Keyboard.KeyDown(Key.Up) Then 
			y-=1
			direction = "up"
			swing=False
		End If
		If Keyboard.KeyDown(Key.Down) Then 
			y+=1
			direction = "down"
			swing=False
		End If
		'Handle the weapon
		If swing = False
			If Keyboard.KeyDown(Key.Space) Then 
				swing=True
				If direction = "left" Then wx=x-w ; wy=y
				If direction = "right" Then wx=x+w ; wy=y
				If direction = "up" Then wx=x ; wy=y-h
				If direction = "down" Then wx=x ; wy=y+h				
				swingcountdown = 20
			End If
		Else
			swingcountdown-=1
			If swingcountdown<0 Then swing=False
		End If
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Yellow
		canvas.DrawOval(x-w/2,y-w/2,w,w)
		If swing = True
			'where does the swing graphic get drawn
			canvas.DrawOval(wx-w/2,wy-w/2,w,w)
		End If
	End Method
	Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
    	Return Abs(x2-x1)+Abs(y2-y1)
	End Function	

End Class


Global myplayer:player
Global myenemy:List<enemy> = New List<enemy>

Class MyWindow Extends Window

	Method New()
        myplayer = New player(Width/2,Height/2)		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		
		'Update everything
    	myplayer.update() 
    	' update the enemies
    	For Local i:=Eachin myenemy
    		i.update()
    	Next
    	' if enemy hitpoint below 1 then remove him from list
    	For Local i:=Eachin myenemy
    		If i.deleteme = True Then myenemy.Remove(i)
    	Next

		If myenemy.Empty
			Local ecnt:Int=Rnd(2,10)
	        For Local i:=0 Until ecnt
    	    	myenemy.AddLast(New enemy())
        	Next
		End If		
		
		'Draw everything
        For Local i:=Eachin myenemy
        	i.draw(canvas)
        Next
        myplayer.draw(canvas)


        canvas.Color = Color.White
        canvas.DrawText("Player vs Monsters on empty map",0,0)
        canvas.DrawText("Space = Weapon , Cursor l/r/u/d = movement",0,20 )
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
