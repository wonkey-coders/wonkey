#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class map
    Field tilewidth:Float
    Field tileheight:Float
    Field mapwidth:Int
    Field mapheight:Int
    Field screenwidth:Int
    Field screenheight:Int
    Field map:Int[,]
    Method New(    screenwidth:Int,
                screenheight:Int,
                mapwidth:Int,
                mapheight:Int)
        Self.screenwidth = screenwidth
        Self.screenheight = screenheight
        Self.mapwidth = mapwidth
        Self.mapheight = mapheight
        Self.tilewidth = Float(screenwidth)/Float(mapwidth)
        Self.tileheight = Float(screenheight)/Float(mapheight)
        map = New Int[mapwidth,mapheight]
'        For Local i=0 Until mapwidth
 '           map[i] = New Int[mapheight]
  '      Next
        map[mapwidth/2,mapheight/2] = 3 ' 3 is a door
        makemap()
    End Method
    Method makemap()
        Local timeout:Int
        While timeout<(mapwidth*mapheight)*20
            timeout+=1
            Local x:Int=Rnd(11,mapwidth-11)
            Local y:Int=Rnd(11,mapheight-11)
            If map[x,y] = 3
                makeroom(x,y)
            End If
        Wend    
        'here we turn doors into walls
        'if they should be walls
        For Local y1:int=1 Until mapheight-1
        For Local x1:Int=1 Until mapwidth-1
            If map[x1,y1] = 3
            Local cnt:Int=0
            For Local y2:Int=y1-1 To y1+1
            For Local x2:int=x1-1 To x1+1
                If map[x2,y2] = 2 Then cnt+=1
            Next
            Next
            If cnt>3 Then map[x1,y1] = 2
            End If
        Next
        Next
        'here we turn doors into walls if they
        ' touch tiles that are nothing (0)
        For Local y1:Int=1 Until mapheight-1
        For Local x1:int=1 Until mapwidth-1
            If map[x1,y1] = 3
            Local cnt:Int=0
            For Local y2:Int=y1-1 To y1+1
            For Local x2:int=x1-1 To x1+1
                If map[x2,y2] = 0 Then cnt+=1
            Next
            Next
            If cnt>0 Then map[x1,y1] = 2
            End If
        Next
        Next        
        'here we turn the doors into floors
        For Local y1:Int=0 Until mapheight
        For Local x1:int=0 Until mapwidth
            If map[x1,y1] = 3 Then map[x1,y1] = 1
        Next
        Next
    End Method
    Method makeroom(x:Int,y:Int)
        Local side:String
        If map[x,y-1] = 0
            side="up"
        Elseif map[x+1,y] = 0
            side="right"
        Elseif map[x,y+1] = 0
            side="down"
        Elseif map[x-1,y] = 0
            side="left"
        End If        
        Local w:Int=Rnd(5,10)
        Local h:Int=Rnd(5,10)
        If side="up"
            Local x1:Int=x-w/2
            Local y1:Int=y-h
            If roomfits(x1,y1,w,h)
                insertroom(x1,y1,w,h+1)
                'door up
                map[x1+Rnd(2,w-2),y1] = 3
                ' door right
                map[x1+w-1,y1+Rnd(2,h-2)] = 3
                'door left
                map[x1,y1+Rnd(2,h-2)] = 3
            End If                        
            
        End If
        If side="right"
            Local x1:Int=x+1
            Local y1:Int=y-h/2
            If roomfits(x1,y1,w,h)
                insertroom(x1-1,y1,w,h)
                'door up
                map[x1+Rnd(2,w-2),y1] = 3
                'door down
                map[x1+Rnd(2,w-2),y1+h-1] = 3
                ' door right
                map[x1+w-2,y1+Rnd(2,h-2)] = 3                
            End If
        End If
        If side="left"
            Local x1:Int=x-w
            Local y1:Int=y-h/2
            If roomfits(x1,y1,w,h)
                insertroom(x1,y1,w+1,h)
                'door up
                map[x1+Rnd(2,w-2),y1] = 3
                'door down
                map[x1+Rnd(2,w-2),y1+h-1] = 3                
                'door left
                map[x1,y1+Rnd(2,h-2)] = 3

            End If            
        End If
        If side="down"
            Local x1:Int=x-w/2
            Local y1:Int=y+1
            If roomfits(x1,y1,w,h)
                insertroom(x1,y1-1,w,h)
                'door down
                map[x1+Rnd(2,w-2),y1+h-2] = 3                
                'door left
                map[x1,y1+Rnd(2,h-2)] = 3                
                ' door right
                map[x1+w-1,y1+Rnd(2,h-2)] = 3                

            End If                        
        End If
    End Method
    Method insertroom(x:Int,y:int,w:int,h:int)
        For Local y2:Int=y Until y+h
        For Local x2:Int=x Until x+w
            If map[x2,y2] <> 3 Then map[x2,y2] = 2
        Next
        Next

        For Local y2:Int=y+1 Until y+h-1
        For Local x2:Int=x+1 Until x+w-1
            map[x2,y2] = 1
        Next
        Next
    End Method
    Method roomfits:Bool(x:Int,y:Int,w:Int,h:Int)
        For Local y1:Int=y Until y+h
        For Local x1:Int=x Until x+w
            If map[x1,y1] = 1 Then Return False
        Next
        Next
        Return True
    End Method
    Method draw(canvas:Canvas)
        For Local y:Int=0 Until mapheight
        For Local x:Int=0 Until mapwidth
            Select map[x,y]
                Case 0
                Case 1'floor
                canvas.Color = New Color(.2,.2,.2)
                canvas.DrawRect(x*tilewidth,
                            y*tileheight,
                            tilewidth+1,
                            tileheight+1)
                Case 2'wall
                canvas.Color = Color.Grey                
                canvas.DrawRect (x*tilewidth,
                            y*tileheight,
                            tilewidth+1,
                            tileheight+1)
                Case 3'wall
                canvas.Color = New Color(.8,.8,.8)
                'SetColor 244,244,0
                canvas.DrawRect(x*tilewidth,
                            y*tileheight,
                            tilewidth+1,
                            tileheight+1)

            End Select
        Next
        Next
    End Method
End Class

Class enemy
	Field x:Float,y:Float
	Field ms:Float 'movement speed
	Field w:Int=mymap.tilewidth-8
	Field h:Int=mymap.tileheight-8
	Field hp:Int
	Field hpceil:Int
	Field direction:String="up" ' left/right/up/down
	Field current:Bool=False 'if being updated
	Field deleteme:Bool=False
	Method New()
		' find a spot to place the new enemy
		Local exitloop:Bool=False
		Local cnt:Int=0
		While exitloop=False
			exitloop = True
			Local nx:Int = Rnd(50,640-50)
			Local ny:int = Rnd(50,480-50)	
			Local mx:Int=nx/mymap.tilewidth		
			Local my:Int=ny/mymap.tileheight
			If mymap.map[mx,my] <> 1 Then exitloop = False
			For Local i:=Eachin myenemy
				If distance(nx,ny,i.x,i.y) < 30 Or distance(myplayer.x,myplayer.y,nx,ny) < 250-cnt
					exitloop = False
				End If
			Next
			If exitloop = True Then
				x = nx
				y = ny
			End If
			cnt+=1
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
					Local nx:Float=x
					Local ny:Float=y
					nx += Cos(a)*1
					ny += Sin(a)*1
					Local mx:Int=nx/mymap.tilewidth
					Local my:Int=ny/mymap.tileheight
					If mymap.map[mx,my] = 1
						x = nx
						y = ny
					End If
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
		Local mx:Int=xx/mymap.tilewidth
		Local my:Int=yy/mymap.tileheight
		If mymap.map[mx,my] <> 1 Then Return true		
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
	Field w:Int=mymap.tilewidth-8
	Field h:Int=mymap.tileheight-8
	Field wx:Int,wy:Int
	Field direction:String="up" ' up/left/down/right
	Field weapondamage:Int=3
	Field swing:Bool=False
	Field swingcountdown:Int=0
	Method New()
		Self.x = x
		Self.y = y
		Local exitloop:Bool=False
		While exitloop = False
			x = Rnd(640)
			y = Rnd(480)
			Local mx:Int=x/mymap.tilewidth
			Local my:Int=y/mymap.tileheight
			If mymap.map[mx,my] = 1 Then exitloop = True
		Wend
		direction = "up"
	End Method
	Method update()
		updatecontrols()
		weaponenemies()
	End Method
	Method weaponenemies()
		If swing = False Then Return
		For Local i:=Eachin myenemy
			If distance(i.x,i.y,wx,wy) < w+5
				'make sure the weapon does not hit throught 
				' walls
				Local mx:Int=wx/mymap.tilewidth
				Local my:Int=wy/mymap.tileheight
				If mymap.map[mx,my] <> 1 Then Exit			
				'distance from the weapon
				Local a:Int=getangle(wx,wy ,i.x,i.y)
				For Local ww:Int=0 Until w				
					Local nx:Float=i.x
					Local ny:Float=i.y				
					nx += Cos(a) * 1
					ny += Sin(a) * 1
					Local mx:Int=nx/mymap.tilewidth
					Local my:Int=ny/mymap.tileheight
					If mymap.map[mx,my] = 1 Then
						i.x = nx
						i.y = ny
					Else
						Exit
					End If					
				next
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
		If collide(x+1,y)=False And Keyboard.KeyDown(Key.Right) Then 
			x+=1
			direction = "right"
			swing=False
		End If
		If collide(x-1,y)=False And Keyboard.KeyDown(Key.Left) Then 
			x-=1
			direction = "left"
			swing=False
		End If
		If collide(x,y-1)=False And Keyboard.KeyDown(Key.Up) Then 
			y-=1
			direction = "up"
			swing=False
		End If
		If collide(x,y+1)=False And Keyboard.KeyDown(Key.Down) Then 
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
	' collide with map
	Method collide:Bool(xx:Int,yy:Int)
		Local mx:Int=xx/mymap.tilewidth
		Local my:Int=yy/mymap.tileheight
		If mymap.map[mx,my] <> 1 Then Return True
		Return False
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
Global mymap:map

Class MyWindow Extends Window

	Method New()
		mymap = New map(640,480,30,30)
        myplayer = New player()		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.Clear(Color.Black)
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
			Local ms:Int=Rnd(30,36)
	    	mymap = New map(640,480,ms,ms)
	        myplayer = New player() 			
			Local ecnt:Int=Rnd(2,10)
	        For Local i:=0 Until ecnt
    	    	myenemy.AddLast(New enemy())
        	Next
		End If		
		
		'Draw everything
		
		mymap.draw(canvas)  
		
        For Local i:=Eachin myenemy
        	i.draw(canvas)
        Next
        myplayer.draw(canvas)


        canvas.Color = Color.White
        canvas.DrawText("Player vs Monsters on Random Map",0,0)
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
