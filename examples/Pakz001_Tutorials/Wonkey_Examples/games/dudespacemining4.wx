'
' tilevalues
'
' 1 = rock
' 2 = rock left top
' 3 = rock right top
' 4 = rock left bottom
' 5 = rock right bottom
' 6 = background rock(cave)
' 7 = rock ore1(crystal)
' 8 = rock ore2(metal)
' 9 = space station left top
' 10 = space station right top
' 11 = space station left bottom
' 12 = space station right bottom
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' global game variables
Global startx:Int,starty:Int
Global gamestate:String="world" 'world/shipinventory/minimap
	' The c64 palette (16 colors)
Global c64color:Color[]

Global debugx1:Int,debugy1:Int,debugx2:Int,debugy2:Int
Global debugr1:Int
Global debugw1:Int,debugh1:Int

' Our gfx
Global shipim:Image
Global shipcan:Canvas
Global rockim:Image
Global rockcan:Canvas
Global rockltim:Image
Global rockltcan:Canvas
Global rockrtim:Image
Global rockrtcan:Canvas
Global rocklbim:Image
Global rocklbcan:Canvas
Global rockrbim:Image
Global rockrbcan:Canvas
Global rockbackim:Image
Global rockbackcan:Canvas
Global rockore1im:Image
Global rockore1can:Canvas
Global rockore2im:Image
Global rockore2can:Canvas

Global iconore1im:Image
Global iconore1can:Canvas
Global iconore2im:Image
Global iconore2can:Canvas
Global iconore3im:Image
Global iconore3can:Canvas
Global iconscrapim:Image
Global iconscrapcan:Canvas
Global iconelecim:Image
Global iconeleccan:Canvas

Global explosionframe1im:Image
Global explosionframe1can:Canvas
Global explosionframe2im:Image
Global explosionframe2can:Canvas
Global explosionframe3im:Image
Global explosionframe3can:Canvas

Global missileim:Image
Global missilecan:Canvas

Global spacestationltim:Image
Global spacestationrtim:Image
Global spacestationlbim:Image
Global spacestationrbim:Image
Global spacestationltcan:Canvas
Global spacestationrtcan:Canvas
Global spacestationlbcan:Canvas
Global spacestationrbcan:Canvas

Class spacestation
	Field tilex:Int,tiley:Int	
	Method New(x:Int,y:Int)
		tilex = x
		tiley = y
	End Method
	Method update()
	End Method
End Class

Class minimap
	Field infotexttime:Int=200
	Field minimapim:Image
	Field minimapcan:Canvas
	Field x:Int,y:Int
	Field entityim:Image
	Field entitycan:Canvas
	Method New()
		entityim = New Image(myship.map.GetSize(0),myship.map.GetSize(1))
		entitycan = New Canvas(entityim)
		entitycan.Flush()
		createmap()
	End Method
	Method createmap()
		minimapim = New Image(myship.map.GetSize(0),myship.map.GetSize(1))
		minimapcan = New Canvas(minimapim)
		For Local _y:Int=0 Until minimapim.Height
		For Local _x:Int=0 Until minimapim.Width
			If solid(_x,_y)
				minimapcan.Color = Color.Grey
				minimapcan.DrawPoint(_x,_y)
			End If
			If myship.map[_x,_y] = 6 Then 
				minimapcan.Color = Color.Grey.Blend(Color.Black,.7)
				minimapcan.DrawPoint(_x,_y)
			End If
		Next
		Next
		minimapcan.Flush()
	End Method
	Method update()
		
		If Keyboard.KeyDown(Key.Right) Then x-=10
		If Keyboard.KeyDown(Key.Left) Then x+=10
		If Keyboard.KeyDown(Key.Down) Then y-=10
		If Keyboard.KeyDown(Key.Up) Then y+=10
		
	End Method
	Method addentities()
		entitycan.Clear(New Color(0,0,0,.5))
		entitycan.Flush()
		infotexttime = 100
		x = -(myship.x/myship.tilew)*4+320
		y = -(myship.y/myship.tileh)*4+240
		entitycan.Color = Color.Yellow
		entitycan.DrawPoint(myship.x/myship.tilew+((320/myship.tilew)),myship.y/myship.tileh+((240/myship.tileh)))
		'add missiles
		For Local i:=Eachin mymissiles
			entitycan.Color = Color.Red
			entitycan.DrawPoint(myship.x/myship.tilew+i.x/myship.tilew,myship.y/myship.tileh+i.y/myship.tileh)			
		Next
		'add spacestations
		For Local i:Int=0 Until myspacestation.Length
			entitycan.Color = Color.Blue
			entitycan.DrawRect(myspacestation.Get(i).tilex,myspacestation.Get(i).tiley,4,4)					
		Next
		entitycan.Flush()

	End Method
	Method draw(canvas:Canvas)
				
		canvas.Color = Color.White		
		canvas.DrawImage(minimapim,x,y,0,4,4)
		
		canvas.DrawImage(entityim,x,y,0,4,4)
		If infotexttime>0 Then
			infotexttime-=1
			canvas.Color = Color.Black
			canvas.DrawRect(200,0,640-200,30)
			canvas.Color = Color.White		
			canvas.DrawText("Use Cursor Keys to move map around.. M - exit",210,0)
		End If

	End Method
	
	Method solid:Bool(_x:Int,_y:Int)
		Select myship.map[_x,_y]
			Case 0 'nothing
				Return False
			Case 1'rock
				Return True
			Case 2'left top 
				Return True
			Case 3'right top
				Return True
			Case 4'left bottom
				Return True
			Case 5'right bottom
				Return True
			Case 6'background
				Return False
			Case 7'ore1(crystal)
				Return True
			Case 8'ore2(metal)
				Return True
		End Select
		Return False
	End Method
End Class

Class explosion
	Field x:Int,y:Int
	Field tp:Int,delay:Int,delaymax:Int=Rnd(1,6)
	Field startcount:Int,startdelay:Int
	Field anim:Int[],animpointer:Int=0
	Field deleteme:Bool	
	Field rotation:Float
	Method New(x:Int,y:Int,tp:Int,startdelay:Int)
		Self.x = x
		Self.y = y
		Self.tp = tp
		Self.startdelay = startdelay
		Select tp
			Case 1
			anim = New Int[5]
			anim[0] = 0
			anim[1] = 1
			anim[2] = 2
			anim[3] = 1
			anim[4] = 0
		End Select
	End Method
	Method update()		
		delay += 1
		startcount+=1
		If startcount<startdelay Then Return
		rotation+=.1
		If rotation > TwoPi Then rotation = 0
		If delay > delaymax
			delay = 0
			animpointer+=1
			Select tp
				Case 1
				If animpointer >4 Then deleteme = True ; Return
			End Select			
		End If
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		Select tp
			Case 1
				Select anim[animpointer]
					Case 0
					canvas.DrawImage(explosionframe1im,x,y,rotation)
					Case 1
					canvas.DrawImage(explosionframe2im,x,y,rotation)
					Case 2
					canvas.DrawImage(explosionframe3im,x,y,rotation)
				End Select
		End Select
	End Method
End Class

Class shipinventory
	Field x:Int=96,y:Int=96,w:Int=640-96*2,h:Int=480-96*2
	Field inv:Int[]
	Field invnum:Int[]
	Method New()
		inv = New Int[23]
		invnum = New Int[23]
		For Local i:Int=0 Until 5
			Local num:Int=8
			If Rnd()<.2 Then num=1
			If Rnd()<.2 Then num=7			 
			If Rnd()<.2 Then num=9
			If Rnd()<.2 Then num=10
			inv[i] = num
			invnum[i] = Rnd(1,99)
			If Rnd()<.3 Then invnum[i] = 99
			If Rnd()<.4 Then invnum[i] = 1
		Next
	End Method
	Method update()
		
	End Method
	Method draw(canvas:Canvas)
		winboxoutside(canvas,x,y,w,h)
		'winboxinside(canvas,x+32,y+12,w-64,128+8)
		maininventoryslots(canvas,x+32,y+12,w-64,128+8,inv)
	End Method
	Method maininventoryslots(canvas:Canvas,_x:Int,_y:Int,_w:Int,_h:Int,inv:Int[])
		Local num:Int
		For Local y:Int=0 Until _h Step 48
		For Local x:Int=0 Until _w Step 48
			winboxinside(canvas,_x+x,_y+y,48,48)
			If num<inv.Length
				'draw icon
				drawicon(canvas,_x+x,_y+y,inv[num])
				
				'draw amount
				If invnum[num]>1 Then 
					canvas.Color = Color.Black
					canvas.Alpha = 0.3
					canvas.DrawRect(_x+x+48-30,_y+y+48-20,28,16)
					canvas.Alpha=1
					canvas.Color = Color.Black
					canvas.DrawText(invnum[num],_x+x+48-24,_y+y+48-20)
					canvas.Color = Color.Black
					canvas.DrawText(invnum[num],_x+x+48-23,_y+y+48-18)
	
					canvas.Color = Color.White
					canvas.DrawText(invnum[num],_x+x+48-25,_y+y+48-22)
					canvas.Color = Color.White
					canvas.DrawText(invnum[num],_x+x+48-24,_y+y+48-21)
				End If
			End If
			num+=1
		Next
		Next
	End Method
	Method winboxoutside(canvas:Canvas,_x:Int,_y:Int,_w:Int,_h:Int)
		'black outline
		canvas.Color = c64color[0]
		canvas.DrawRect(_x,_y,_w,_h)
		' medium grey inside
		canvas.Color = c64color[15]
		canvas.DrawRect(_x+1,_y+1,_w-2,_h-2)
		' dark grey bottom hor and right
		canvas.Color = c64color[11]
		canvas.DrawRect(_x+1,_y+_h-4,_w-2,4)
		canvas.DrawRect(_x+_w-5,_y+1,4,_h-2)
		' dark top right and bottom
		canvas.Color = c64color[1]
		canvas.DrawRect(_x+1,_y+1,_w-2,4)
		canvas.DrawRect(_x+1,_y+1,4,_h-2)
	End Method
	Method winboxinside(canvas:Canvas,_x:Int,_y:Int,_w:Int,_h:Int)
		'black outline
		canvas.Color = c64color[0]
		canvas.DrawRect(_x,_y,_w,_h)
		' dark grey inside
		canvas.Color = c64color[11]
		canvas.DrawRect(_x+1,_y+1,_w-2,_h-2)
		' white bottom hor and right
		canvas.Color = c64color[1]
		canvas.DrawRect(_x+1,_y+_h-2,_w-1,1)
		canvas.DrawRect(_x+_w-2,_y+1,1,_h-1)
		' black top right and bottom
		canvas.Color = c64color[0]
		canvas.DrawRect(_x+1,_y+1,_w-1,1)
		canvas.DrawRect(_x+1,_y+1,1,_h-1)
	End Method
	Method drawicon(canvas:Canvas,_x:Int,_y:Int,num:Int)
		canvas.Color = Color.White
		Select num
			Case 1 'rock icon
			canvas.DrawImage(iconore3im,_x+24,_y+24,0)	
			Case 7 'crystal blue
			canvas.DrawImage(iconore1im,_x+24,_y+24,0)
			Case 8 'metal
			canvas.DrawImage(iconore2im,_x+24,_y+24,0)
			Case 9 'scrap
			canvas.DrawImage(iconscrapim,_x+24,_y+24,0)
			Case 10 'electronics
			canvas.DrawImage(iconelecim,_x+24,_y+24,0)

		End Select
	End Method
End Class

Class missiles
	Field x:Float,y:Float,angle:Float,incx:Float,incy:Float	
	Field deleteme:Bool=False
	Field home:Bool
	Field launchtime:Int=60
	Field launchangle:Float
	'Field currentangle:float
	Method New(x:Int,y:Int,angle:Float)
		Self.x = x
		Self.y = y
		Self.angle = angle
		Self.launchangle=angle		
	End Method
	Method update()
		
		If edistance(x,y,320,240)<200
			home=True
		End If
		If edistance(x,y,320,240)<32
			home=False
			deleteme = True
			If Rnd()<.8 Then mypickups.Add(New pickups(x*myship.tilew-myship.x+myship.tilew/2,y*myship.tileh-myship.y+myship.tileh/2,9))
			If Rnd()<.8 Then mypickups.Add(New pickups(x*myship.tilew-myship.x+myship.tilew/2,y*myship.tileh-myship.y+myship.tileh/2,10))
			For Local i:Int=0 Until 10
				myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
			Next
			'myship.dienow()
			myship.respawn = True
		End If
		If home=False Then Return
		launchtime-=1
		If launchtime>0 Then 
			Local vx:Float,vy:Float
			vx = Cos(launchangle)*Float(100-launchtime)/70.0
			vy = Sin(launchangle)*Float(100-launchtime)/70.0
			x+=vx
			y+=vy
			'Local tan:Float=-ATan2(vy,vx)+TwoPi
			Local tan:Float=-getangle(x,y,320,240)
    		Local difference:Float = angledifference(tan,angle)
			'Print "x:"+x+" y:+"+y+" dif:"+difference+"---"+angle+" tan:"+getangle(x,y,320,240)
        	'angle=-tan
        	If difference<0 Then angle-=.15 Else angle+=.15
			'Print getangle(x,y,320,240)+" tan:"+angle+ "diff:"+difference
			Return
		End if
		'Home the missile
        Local targetx:Double = 320 - x
        Local targety:Double = 240 - y
        angle = ATan2(targety, targetx) * 180 / Pi
        '2 here below is the movement speed
        Local vx:Double = 2 * (90 - Abs(angle)) / 90
	    local vy:Double
	    if (angle < 0)
	        vy = -2 + Abs(vx)
	    Else
	        vy = 2 - Abs(vx)
		End if		     
	    x += vx
	    y += vy		
	    angle = -ATan2(vy,vx)+TwoPi'-getangle(320,240,x,y)+Pi
	
	
		'collision with walls
		' get map position
		Local rx:Int=x+myship.x
		Local ry:Int=y+myship.y
		Local tx:Int=rx/myship.tilew
		Local ty:Int=ry/myship.tileh
		For Local y2:Int=-1 To 1
		For Local x2:Int=-1 To 1
			Local ax:Int=(tx+x2)*myship.tilew
			Local ay:Int=(ty+y2)*myship.tileh
			
			If isore(myship.map[tx+x2,ty+y2]) Or myship.map[tx+x2,ty+y2] = 1
				If rectsoverlap(ax,ay,myship.tilew,myship.tileh,rx,ry,3,3)
					deleteme = True
					For Local i:Int=0 Until 10
						myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
					Next						
					If Rnd()<.8 Then mypickups.Add(New pickups(x*myship.tilew-myship.x+myship.tilew/2,y*myship.tileh-myship.y+myship.tileh/2,9))
					If Rnd()<.8 Then mypickups.Add(New pickups(x*myship.tilew-myship.x+myship.tilew/2,y*myship.tileh-myship.y+myship.tileh/2,10))

				End If
			End If
			If myship.map[tx+x2,ty+y2] = 2 'left top
			
				Local x1:Float=ax
				Local y1:Float=ay+myship.tileh
				Local x2:Float=ax+myship.tilew
				Local y2:Float=ay+myship.tileh
				Local x3:Float=ax+myship.tilew
				Local y3:Float=ay
				For Local an:Float=0 To TwoPi Step .5
				Local x4:Float=Cos(an)*16
				Local y4:Float=Sin(an)*16
				If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
					incx=-incx
					incy=-incy
					deleteme = True
					For Local i:Int=0 Until 10
						myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
					Next						
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,9))
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,10))

					Return
				End If
				Next		
			End if
			If myship.map[tx+x2,ty+y2] = 3 'right top
				Local x1:Float=ax
				Local y1:Float=ay
				Local x2:Float=ax+myship.tilew
				Local y2:Float=ay+myship.tileh
				Local x3:Float=ax
				Local y3:Float=ay+myship.tileh
				For Local an:Float=0 To TwoPi Step .5
				Local x4:Float=Cos(an)*16
				Local y4:Float=Sin(an)*16
				If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
					incx=-incx
					incy=-incy
					deleteme = True
					For Local i:Int=0 Until 10
						myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
					Next						
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,9))
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,10))

					Return
				End If
				Next
			End If			
			If myship.map[tx+x2,ty+y2] = 4 'left bottom
			
				Local x1:Float=ax
				Local y1:Float=ay
				Local x2:Float=ax+myship.tilew
				Local y2:Float=ay+myship.tileh
				Local x3:Float=ax+myship.tilew
				Local y3:Float=ay
	'
				For Local an:Float=0 To TwoPi Step .5
				Local x4:Float=Cos(an)*16
				Local y4:Float=Sin(an)*16
				If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
					incx=-incx
					incy=-incy
					deleteme = True
					For Local i:Int=0 Until 10
						myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
					Next						
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,9))
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,10))

					Return
				End If
				Next		
			End if
			If myship.map[tx+x2,ty+y2] = 5 'right bottom
			
				Local x1:Float=ax
				Local y1:Float=ay
				Local x2:Float=ax
				Local y2:Float=ay+myship.tileh
				Local x3:Float=ax+myship.tilew
				Local y3:Float=ay+myship.tileh
				For Local an:Float=0 To TwoPi Step .5
				Local x4:Float=Cos(an)*16
				Local y4:Float=Sin(an)*16
				If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
					incx=-incx
					incy=-incy
					deleteme = True
					For Local i:Int=0 Until 10
						myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
					Next						
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,9))
					If Rnd()<.8 Then mypickups.Add(New pickups(x+myship.tilew/2,y+myship.tileh/2,10))

					Return
				End If
				Next		
			End if
			
		Next
		Next		
	
	
	
	
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawImage(missileim,x,y,angle)
	End Method
End Class

Class pickups
	Field deleteme:Bool=False
	Field x:Float,y:Float
	Field angle:Float,incx:Float,incy:Float
	Field s:Int=8
	Field rotation:Float=0
	Field tp:Int 'type of icon (uses tile numbering)
	Method New(x:Int,y:Int,tp:Int)
		Self.x = x
		Self.y = y
		Self.tp = tp
	End Method
	Method update()
		rotation += .05
		If rotation>TwoPi Then rotation-=TwoPi
		x+=incx
		y+=incy
		' check distance to ship 
		' and if close move it quickly to ship position
		If edistance(x,y,320,240)<50
			Local a:Float = getangle(x,y,320,240)
			incx = Cos(a)*10
			incy = Sin(a)*10			
		End If
		' if closer to ship remove (add to inventory!)
		If edistance(x,y,320,240)<10
			deleteme = True
			addtoplayerinventory()
		End If
	End Method
	Method addtoplayerinventory()
		' first check for almost filled stacks
		For Local i:Int=0 Until myshipinventory.inv.GetSize(0)
			If myshipinventory.inv[i] = tp And myshipinventory.invnum[i] < 99
				myshipinventory.invnum[i] += 1
				Return
			End If
		Next
		' check for empty inventory space
		For Local i:Int=0 Until myshipinventory.inv.GetSize(0)
			If myshipinventory.inv[i] = 0 And myshipinventory.invnum[i] < 99
				myshipinventory.inv[i] = tp
				myshipinventory.invnum[i] += 1
				Return
			End If
		Next	
	End Method
	Method draw(canvas:Canvas)
'		canvas.Color = Color.Yellow
'		canvas.DrawCircle(x,y,s)
'		canvas.Color = Color.Black
'		canvas.DrawText("O",x,y)
'		canvas.Color = Color.White
'		canvas.DrawText("O",x-1,y-1)		
		canvas.Color = Color.White
		If tp = 1 'rock
		canvas.DrawImage(iconore3im,x,y,rotation)
		Endif
		If tp = 7 'crystal blue
		canvas.DrawImage(iconore1im,x,y,rotation)
		End If
		If tp = 8 'metal
		canvas.DrawImage(iconore2im,x,y,rotation)
		Endif
		If tp = 9 'scrap
		canvas.DrawImage(iconscrapim,x,y,rotation)
		End if
		If tp = 10'elec
		canvas.DrawImage(iconelecim,x,y,rotation)
		End If

	End Method
End Class

Class laser
	Field x:Float,y:Float,s:Float=3
	Field incx:Float,incy:Float
	Field time:Int,timeout:Int=320
	Field deleteme:Bool=False
	Method New(x:Float,y:Float,incx:Float,incy:Float)
		Self.x = x
		Self.y = y
		Self.incx = incx
		Self.incy = incy
	End Method
	Method update()
		' increase life
		time+=1
		' if to old then mark for delete
		If time>timeout Then deleteme=True
		x += incx
		y += incy
		'
		' get map position
		Local rx:Int=x+myship.x
		Local ry:Int=y+myship.y
		Local tx:Int=rx/myship.tilew
		Local ty:Int=ry/myship.tileh
		For Local y2:Int=-1 To 1
		For Local x2:Int=-1 To 1
			Local ax:Int=tx+x2*myship.tilew
			Local ay:Int=ty+y2*myship.tileh
			
		If isore(myship.map[ax,ay]) Or myship.map[ax,ay] = 1
			If rectsoverlap(ax*myship.tilew,ay*myship.tileh,myship.tilew,myship.tileh,rx,ry,3,3)
				deleteme = True
				myship.mapdamage[ax,ay]+=1
				If myship.mapdamage[ax,ay] < 4 Then Exit
			
				If myship.map[ax,ay] = 7 Then 'drop pickup (crystal)
					mypickups.Add(New pickups(ax*myship.tilew-myship.x+myship.tilew/2,ay*myship.tileh-myship.y+myship.tileh/2,7))
				End if
				If myship.map[ax,ay] = 8 Then 'drop pickup (metal)
					mypickups.Add(New pickups(ax*myship.tilew-myship.x+myship.tilew/2,ay*myship.tileh-myship.y+myship.tileh/2,8))
				End if
				If myship.map[ax,ay] = 1 Then 'drop pickup (rock)
					mypickups.Add(New pickups(ax*myship.tilew-myship.x+myship.tilew/2,ay*myship.tileh-myship.y+myship.tileh/2,1))
				End if
			
				myship.map[ax,ay] = 6
				
				
				' remove any edges
				For Local bx:Int=-1 To 1
				For Local by:Int=-1 To 1
					If myship.map[ax+bx,ay+by] >1 And myship.map[ax+bx,ay+by]<6 Then myship.map[ax+bx,ay+by] = 6
				Next
				Next
				'recreate any edges
				For Local by:Int=ay-2 Until ay+2
				For Local bx:Int=ax-2 Until ax+2
					If myship.map[bx,by] = 1 And myship.map[bx-1,by+1] = 1 And myship.map[bx-1,by]=6 Then myship.map[bx-1,by] = 2 ;myship.mapdamage[bx-1,by]=0'left top rock
					If myship.map[bx,by] = 1 And myship.map[bx+1,by+1] = 1 And myship.map[bx+1,by]=6 Then myship.map[bx+1,by] = 3 ;myship.mapdamage[bx+1,by]=0'right top rock
					If myship.map[bx,by] = 1 And myship.map[bx-1,by-1] = 1 And myship.map[bx-1,by]=6 Then myship.map[bx-1,by] = 4 ;myship.mapdamage[bx-1,by]=0'left bottom rock
					If myship.map[bx,by] = 1 And myship.map[bx+1,by-1] = 1 And myship.map[bx+1,by]=6 Then myship.map[bx+1,by] = 5 ;myship.mapdamage[bx+1,by]=0'right bottom rock
				Next
				Next
				'remove any missiles on the rocks
				For Local i:=Eachin mymissiles
					'Print ax*myship.tilew+ ","+ay*myship.tileh
					'Exit
					If edistance(ax*myship.tilew-myship.x+myship.tilew/2,ay*myship.tileh-myship.y+myship.tileh/2,i.x,i.y)<64 Then 
						i.deleteme = True
						If Rnd()<.8 Then mypickups.Add(New pickups(i.x+Rnd(-8,8),i.y+Rnd(-8,8),9))
						If Rnd()<.8 Then mypickups.Add(New pickups(i.x+Rnd(-8,8),i.y+Rnd(-8,8),10))
						For Local i2:Int=0 Until 10
							myexplosions.Add(New explosion(i.x+Rnd(-32,32),i.y+Rnd(-32,32),1,Rnd(30)))
						Next					
					End If
				Next

				Exit
			End If
		End If
		Next
		Next
		'
		' collision with missiles
		' 
		For Local i:=Eachin mymissiles
			If rectsoverlap(i.x,i.y,6,6,x,y,4,4)
				i.deleteme = True
				If Rnd()<.8 Then mypickups.Add(New pickups(x,y,9))
				If Rnd()<.8 Then mypickups.Add(New pickups(x,y,10))
			
				For Local i:Int=0 Until 10
					myexplosions.Add(New explosion(x+Rnd(-32,32),y+Rnd(-32,32),1,Rnd(30)))
				Next	
			End If
		Next
	End Method

	Method draw(canvas:Canvas)
		canvas.Color = Color.Red
		canvas.DrawCircle(x,y,s)
	End Method
End Class

Class ship
	'
	Field respawn:Bool
	Field respawntime:Int=0
	' tilemap
	Field map:Int[,]
	Field mapdamage:Int[,]
	Field tilew:Int=48
	Field tileh:Int=48
	'ship
    Field x:Float,y:Float
	Field incx:Float,incy:Float
	Field thrust:Float,thrustmax:Float=2
	Field angle:Float
	Field maxspeed:Float=2
   	Method New(x:Float,y:Float,angle:Float)
	   	map = New Int[512,512]
	   	mapdamage = New Int[512,512]
	   	generatemap()
		Self.x = x
		Self.y = y
		For Local i:=Eachin mymissiles
			i.x-=x
			i.y-=y
		Next
		Self.angle = angle
	End Method
	
	Method update()		
		If respawn = True Then 
			incx = 0
			incy = 0
			respawntime+=1			
			If respawntime>100 Then
				respawntime = 0
				' realign anything on the map
				For Local i:=Eachin mymissiles
					i.x += x-startx
					i.y += y-starty
					If i.home Then i.deleteme=True
				Next
				For Local i:=Eachin mypickups
					i.x += x-startx
					i.y += y-starty
				Next
				mylaser.Clear()				
				' set to original position
				x = startx
				y = starty
				incx = 0
				incy = 0
				angle = 0

				respawn = False
			End if
			Return
		End if
		If thrust>0 Then thrust-=.01


		' collision with tiles
		' get map position
		
		Local rx:Int=320+x
		Local ry:Int=240+y
		Local tx:Int=rx/tilew
		Local ty:Int=ry/tileh
		For Local y2:Int=-1 To 1
		For Local x2:Int=-1 To 1
			Local ax:Int=(tx+x2)*tilew
			Local ay:Int=(ty+y2)*tileh

			
			
		If map[tx+x2,ty+y2] = 1 Or isore(map[tx+x2,ty+y2])			
			'rect
			If circlerectcollide(rx,ry,16,ax,ay,tilew,tileh)=True				
				incx=-incx
				incy=-incy
				dienow()
				Return
			End If
		End If
		If map[tx+x2,ty+y2] = 2 'left top
		
			Local x1:Float=ax
			Local y1:Float=ay+tileh
			Local x2:Float=ax+tilew
			Local y2:Float=ay+tileh
			Local x3:Float=ax+tilew
			Local y3:Float=ay
			For Local an:Float=0 To TwoPi Step .5
			Local x4:Float=Cos(an)*16
			Local y4:Float=Sin(an)*16
			If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
				incx=-incx
				incy=-incy
				dienow()
				Return
			End If
			Next		
		End if
		If map[tx+x2,ty+y2] = 3 'right top
			Local x1:Float=ax
			Local y1:Float=ay
			Local x2:Float=ax+tilew
			Local y2:Float=ay+tileh
			Local x3:Float=ax
			Local y3:Float=ay+tileh
			For Local an:Float=0 To TwoPi Step .5
			Local x4:Float=Cos(an)*16
			Local y4:Float=Sin(an)*16
			If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
				incx=-incx
				incy=-incy
				dienow()
				Return
			End If
			Next
		End If			
		If map[tx+x2,ty+y2] = 4 'left bottom
		
			Local x1:Float=ax
			Local y1:Float=ay
			Local x2:Float=ax+tilew
			Local y2:Float=ay+tileh
			Local x3:Float=ax+tilew
			Local y3:Float=ay
'
			For Local an:Float=0 To TwoPi Step .5
			Local x4:Float=Cos(an)*16
			Local y4:Float=Sin(an)*16
			If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
				incx=-incx
				incy=-incy
				dienow()
				Return
			End If
			Next		
		End if
		If map[tx+x2,ty+y2] = 5 'right bottom
		
			Local x1:Float=ax
			Local y1:Float=ay
			Local x2:Float=ax
			Local y2:Float=ay+tileh
			Local x3:Float=ax+tilew
			Local y3:Float=ay+tileh
			For Local an:Float=0 To TwoPi Step .5
			Local x4:Float=Cos(an)*16
			Local y4:Float=Sin(an)*16
			If pointintriangle2d(rx+x4,ry+y4,x1,y1,x2,y2,x3,y3)
				incx=-incx
				incy=-incy
				dienow()
				Return
			End If
			Next		
		End if

		Next
		Next
	End Method
	Method controls()
		If respawn Then Return
		'mine
		If Keyboard.KeyReleased(Key.Space) Then
			mylaser.Add(New laser(320+24-16,200+24+16,Cos(angle)*4,-Sin(angle)*4))
		End If

		' turn
		If Keyboard.KeyDown(Key.Right) Then angle-=.1
		If Keyboard.KeyDown(Key.Left) Then angle+=.1
		If angle<0 Then angle+=TwoPi
		If angle>TwoPi Then angle-=TwoPi
		' thrust (inc)
		If Keyboard.KeyDown(Key.Up) Then 
			thrust+=.015
			If thrust>thrustmax Then thrust=thrustmax
			Local nvx:Float = incx+Cos(angle)*thrust
			Local nvy:Float = incy+Sin(angle)*thrust
			'get the angle of the new nvx and nvy
			Local nangle:Float = ATan2(nvy,nvx) 'get the angle from the movement variables
			'get the distance traveled from location of ship and the location with the movement added
			Local dist:Float = edistance(x,y,x+nvx,y+nvy)
			' If the movement is larger than max then limit
			If Abs(dist) > maxspeed	Then
				incx = Cos(nangle)*maxspeed
				incy = Sin(nangle)*maxspeed
				Else
				'if the movement is within bounds then update the inc variables
				incx = nvx
				incy = nvy
			End If			
		End If
        x+=incx
        y-=incy
        For Local i:=Eachin mypickups
	        i.x -=incx
	        i.y +=incy
	    Next
        For Local i:=Eachin mymissiles
	        i.x -=incx
	        i.y +=incy
	    Next
        For Local i:=Eachin myexplosions
	        i.x -=incx
	        i.y +=incy
	    Next

	End Method
	Method generatemap()	
		' center of map set to 256,256
		
		'create asteroid by growing pixels
		map[256,256] = 1
		For Local i:Int=0 Until 2000*2000
			Local x:Int=256+Rnd(-150,150)
			Local y:Int=256+Rnd(-150,150)
			If map[x,y] = 1 Then 
				For Local y2:Int=-1 To 1
				For Local x2:Int=-1 To 1
					If Rnd()<.5 Then map[x+x2,y+y2] = 1
				Next
				Next
			End If
		Next
		
		Local point:Stack<Vec2i> = New Stack<Vec2i>
		Local numpoints:Int=100
		For Local i:Int=0 Until numpoints
			Local exitloop:Bool=False
			Local x:Int
			Local y:Int
			While exitloop = False			
				x = 256+Rnd(-170,170)
				y = 256+Rnd(-170,170)
				If map[x,y] = 1 Then exitloop = True
			Wend
			point.Push(New Vec2i(x,y))
		Next
		For Local i:Int=1 Until point.Length
			'carve
			Local x1:Int=point.Get(i-1).x
			Local y1:Int=point.Get(i-1).y
			Local x2:Int=point.Get(i).x
			Local y2:Int=point.Get(i).y
			While x1<>x2 And y1<>y2
				If x1<x2 Then x1+=1
				If x1>x2 Then x1-=1
				If y1<y2 Then y1+=1
				If y1>y2 Then y1-=1
				Local s:Int=1
				If Rnd()<.1 Then s=Rnd(2,3)
				For Local y:Int=-s To s
				For Local x:Int=-s To s
				map[x1+x,y1+y] = 6
				Next
				Next
			Wend
			
		Next
		

		'find edges and create those tile values
		For Local y:Int=1 Until 511
		For Local x:Int=1 Until 511
			If map[x,y] = 1 And map[x-1,y+1] = 1 And map[x-1,y]=6 Then map[x-1,y] = 2 'left top rock
			If map[x,y] = 1 And map[x+1,y+1] = 1 And map[x+1,y]=6 Then map[x+1,y] = 3 'right top rock
			If map[x,y] = 1 And map[x-1,y-1] = 1 And map[x-1,y]=6 Then map[x-1,y] = 4 'left bottom rock
			If map[x,y] = 1 And map[x+1,y-1] = 1 And map[x+1,y]=6 Then map[x+1,y] = 5 'right bottom rock

			If map[x,y] = 1 And map[x-1,y+1] = 1 And map[x-1,y]=0 Then map[x-1,y] = 2 'left top rock
			If map[x,y] = 1 And map[x+1,y+1] = 1 And map[x+1,y]=0 Then map[x+1,y] = 3 'right top rock
			If map[x,y] = 1 And map[x-1,y-1] = 1 And map[x-1,y]=0 Then map[x-1,y] = 4 'left bottom rock
			If map[x,y] = 1 And map[x+1,y-1] = 1 And map[x+1,y]=0 Then map[x+1,y] = 5 'right bottom rock
		Next
		Next
		
		'add ore 1
		For Local i:Int=0 Until 900
			Local x:Int=256+Rnd(-100,100)
			Local y:Int=256+Rnd(-100,100)
			If map[x,y] = 1 Then map[x,y] = 7
			'grow
			If Rnd()<.8
				Local s:Int=Rnd(2,80)
				For Local i2:Int=0 Until s
					Local x2:Int=x+Rnd(-25,25)
					Local y2:Int=y+Rnd(-25,25)
					If map[x2,y2] = 7 Then
						
						For Local x3:Int=-1 To 1
						For Local y3:Int=-1 To 1
							If map[x2+x3,y2+y3] = 1 And Rnd()<.3
								map[x2+x3,y2+y3] = 7
							End If 
						Next
						Next
					End if
				Next
			End If
		Next
		'add ore 2
		For Local i:Int=0 Until 900
			Local x:Int=256+Rnd(-100,100)
			Local y:Int=256+Rnd(-100,100)
			If map[x,y] = 1 Then map[x,y] = 8
			'grow
			If Rnd()<.8
				Local s:Int=Rnd(2,180)
				For Local i2:Int=0 Until s
					Local x2:Int=x+Rnd(-25,25)
					Local y2:Int=y+Rnd(-25,25)
					If map[x2,y2] = 8 Then
						
						For Local x3:Int=-1 To 1
						For Local y3:Int=-1 To 1
							If map[x2+x3,y2+y3] = 1 And Rnd()<.3
								map[x2+x3,y2+y3] = 8
							End If 
						Next
						Next
					End if
				Next
			End If
		Next
		
		' add some missiles
		For Local i:Int=0 Until 50000
			Local nx:Int=Rnd(100,400)
			Local ny:Int=Rnd(100,400)
			If map[nx,ny] = 1 And map[nx+1,ny] = 6
				'Print nx+"."+ny
				mymissiles.Add(New missiles(((nx+1)*tilew)+32/2,ny*tileh+tileh/2,0))
			End If
			If map[nx,ny] = 1 And map[nx-1,ny] = 6
				'Print nx+"."+ny
				mymissiles.Add(New missiles(((nx)*tilew)-32/2,ny*tileh+tileh/2,Pi))
			End If
		Next

		' add space station
		myspacestation.Push(New spacestation(350,350))
		map[350,350] = 9
		map[351,350] = 10
		map[350,351] = 11
		map[351,351] = 12

	End Method
	Method drawmap(canvas:Canvas)
		Local offx:Int=x/tilew
		Local offy:Int=y/tileh
		Local poffx:Int = (offx*tilew)-x
		Local poffy:Int = (offy*tileh)-y
		For Local my:Int=0 Until 16
		For Local mx:Int=0 Until 24
			canvas.Color = Color.White
			Local damage:Float=mapdamage[offx+mx,offy+my]
			If damage > 0 Then 
				canvas.Color = Color.White.Blend(Color.Black,1.0/10*damage)
			End If
			If map[offx+mx,offy+my] = 1 'rock
				'canvas.DrawRect(0+mx*tilew+poffx,0+my*tileh+poffy,tilew,tileh)
				canvas.DrawImage(rockim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End If
			If map[offx+mx,offy+my] = 2 'left top rock
				canvas.DrawImage(rockltim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 3 'right top rock
				canvas.DrawImage(rockrtim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 4 'left bottom rock
				canvas.DrawImage(rocklbim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 5 'right bottom rock
				canvas.DrawImage(rockrbim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 6 'background rock				
				canvas.DrawImage(rockbackim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 7 'rock ore 1 (blue crystal)
				canvas.DrawImage(rockore1im,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 8 'rock ore 2 (metal)
				canvas.DrawImage(rockore2im,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 9 'space station left top
				canvas.DrawImage(spacestationltim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 10 'space station right top
				canvas.DrawImage(spacestationrtim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 11 'space station left bottom
				canvas.DrawImage(spacestationlbim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 12 'space station right bottom
				canvas.DrawImage(spacestationrbim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if

		Next
		Next
	End Method
	Method dienow()		
		If Sqrt(incx*incx+incy*incy) > 1 Then 
			For Local i:Int=0 Until 10
				myexplosions.Add(New explosion(320+Rnd(-32,32),240+Rnd(-32,32),1,Rnd(30)))
			Next						
			respawn = True
		End If		
	End Method	
End Class

Global mylaser:List<laser> = New List<laser>
	' Our classes
Global myship:ship
Global mypickups:List<pickups> = New List<pickups>
Global mymissiles:List<missiles> = New List<missiles>
Global myshipinventory:shipinventory
Global myexplosions:List<explosion> = New List<explosion>
Global myminimap:minimap
Global myspacestation:Stack<spacestation> = New Stack<spacestation>

Class MyWindow Extends Window
	Field introinfotime:Int=200	
	Method New()
		'Setup our images so they can be drawn
		setupim()
		myship = New ship(349*48,349*48+20,0)
		startx = 349*48
		starty = 349*48+20
		myshipinventory = New shipinventory
		myminimap = New minimap
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If gamestate = "minimap"
			myminimap.draw(canvas)
			If Keyboard.KeyReleased(Key.M) Then 
				gamestate = "world"				
			End If
			myminimap.update()
		End If
		If gamestate = "shipinventory"
			If Keyboard.KeyReleased(Key.I) Then gamestate = "world"
			myshipinventory.update()
			myshipinventory.draw(canvas)
			
		End If
		If gamestate = "world"
			If Keyboard.KeyReleased(Key.M) Then 
				gamestate = "minimap"
				myminimap.addentities()
			End if
			If Keyboard.KeyReleased(Key.I) Then gamestate = "shipinventory"
			myship.update()
			myship.controls()
			' update the lasers
			For Local i:=Eachin mylaser
				i.update()
			Next
			' remove any dead ones
			For Local i:=Eachin mylaser
				If i.deleteme Then mylaser.Remove(i)
			Next
			' update the pickups
			For Local i:=Eachin mypickups
				i.update()
			Next
			' remove any dead pickups
			For Local i:=Eachin mypickups
				If i.deleteme Then mypickups.Remove(i)
			Next
			' update the missiles		
			For Local i:=Eachin mymissiles
				i.update()
			Next
			' remove any dead missiles
			For Local i:=Eachin mymissiles
				If i.deleteme Then mymissiles.Remove(i)
			Next
			' explosions
			For Local i:=Eachin myexplosions
				i.update()
			Next
			' remove any dead explosions
			For Local i:=Eachin myexplosions
				If i.deleteme Then myexplosions.Remove(i)
			Next
			
			
			'
			myship.drawmap(canvas)
			canvas.Color = Color.White
			canvas.DrawImage(shipim,320,240,myship.angle)
	
			' draw the lasers
			For Local i:=Eachin mylaser
				i.draw(canvas)
			Next
			' draw the pickups
			For Local i:=Eachin mypickups
				i.draw(canvas)
			Next
			' draw the missiles
			For Local i:=Eachin mymissiles
				i.draw(canvas)
			Next
			' draw the explosions
			For Local i:=Eachin myexplosions
				i.draw(canvas)
			Next
		
	
	
			canvas.DrawText("angle : "+myship.angle,0,0)
			canvas.DrawText("thrust : "+myship.thrust,0,15)
			canvas.DrawText("incx and incy : "+myship.incx+","+myship.incy,0,25)
			If introinfotime>0 Then 
				introinfotime-=1
				Local x:Int=310
				If introinfotime<50 Then x+=320-introinfotime*6
				canvas.Color = Color.Black
				canvas.DrawRect(x,0,330,40)
				canvas.Color = Color.White
				canvas.DrawText("Press i toggle inventory.",x,0)
				canvas.DrawText("Press m toggle map.",x,20)
				
			End If
		End if
		
'
'
'		Local rx:Int=Mouse.X+myship.x
'		Local ry:Int=Mouse.Y+myship.y
'		Local tx:Int=rx/myship.tilew
'		Local ty:Int=ry/myship.tileh
'		For Local y2:Int=-1 To 1
'		For Local x2:Int=-1 To 1
'			Local ax:Int=(tx+x2)*myship.tilew
'			Local ay:Int=(ty+y2)*myship.tileh
'		If myship.map[tx+x2,ty+y2] = 1 'Or isore(myship.map[tx+x2,ty+y2])			
'			
'		'rect
'		debugx1 = rx-myship.x ; debugy1 = ry-myship.y
'		debugr1 = 32
'		debugx2 = ax-myship.x
'		debugy2 = ay-myship.y
'		debugw1 = myship.tilew
'		debugh1 = myship.tileh
'		canvas.Alpha = 0.5
'		canvas.Color=Color.White
'		canvas.DrawCircle(debugx1,debugy1,debugr1)
'		canvas.Color=Color.Yellow
'		canvas.DrawRect(debugx2,debugy2,debugw1,debugh1)
'		canvas.Alpha = 1
'
'		If circlerectcollide(rx,ry,32,ax,ay,myship.tilew,myship.tileh)=True				
'			'Return
'			Print Microsecs()
'		End If
'		End If
'
'		Next
'		Next
'
'		canvas.Alpha = 0.5
'		canvas.Color=Color.White
'		canvas.DrawCircle(debugx1,debugy1,debugr1)
'		canvas.Color=Color.Yellow
'		canvas.DrawRect(debugx2,debugy2,debugw1,debugh1)
'		canvas.Alpha = 1
''		canvas.DrawRect(250,250,50,50)
'		canvas.DrawCircle(Mouse.X,Mouse.Y,50)
'		If circlerectcollide(Mouse.X,Mouse.Y,50,250,250,50,50) Then Print Microsecs()


		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	
	
	'
	' Holds and set up the gfx data.
	Method setupim()
		inic64colors()
		shipim = New Image(32,32)
		shipcan = New Canvas(shipim)
		shipim.Handle = New Vec2f(0.5,0.5)
		missileim = New Image(32,32)
		missilecan = New Canvas(missileim)
		missileim.Handle = New Vec2f(0.5,0.5)		
		rockim = New Image(48,48)
		rockcan = New Canvas(rockim)
		rockltim = New Image(48,48)
		rockltcan = New Canvas(rockltim)
		rockrtim = New Image(48,48)
		rockrtcan = New Canvas(rockrtim)
		rocklbim = New Image(48,48)
		rocklbcan = New Canvas(rocklbim)
		rockrbim = New Image(48,48)
		rockrbcan = New Canvas(rockrbim)
		rockbackim = New Image(48,48)
		rockbackcan = New Canvas(rockbackim)
		rockore1im = New Image(48,48)
		rockore1can = New Canvas(rockore1im)
		rockore2im = New Image(48,48)
		rockore2can = New Canvas(rockore2im)
		iconore1im = New Image(32,32)
		iconore1can = New Canvas(iconore1im)
		iconore1im.Handle = New Vec2f(0.5,0.5)
		iconore2im = New Image(32,32)
		iconore2can = New Canvas(iconore2im)
		iconore2im.Handle = New Vec2f(0.5,0.5)
		iconore3im = New Image(32,32)
		iconore3can = New Canvas(iconore3im)
		iconore3im.Handle = New Vec2f(0.5,0.5)
		iconscrapim = New Image(32,32)
		iconscrapcan = New Canvas(iconscrapim)
		iconscrapim.Handle = New Vec2f(0.5,0.5)
		iconelecim = New Image(32,32)
		iconeleccan = New Canvas(iconelecim)
		iconelecim.Handle = New Vec2f(0.5,0.5)

		explosionframe1im = New Image(32,32)
		explosionframe1can = New Canvas(explosionframe1im)
		explosionframe1im.Handle = New Vec2f(0.5,0.5)
		explosionframe2im = New Image(32,32)
		explosionframe2can = New Canvas(explosionframe2im)
		explosionframe2im.Handle = New Vec2f(0.5,0.5)
		explosionframe3im = New Image(32,32)
		explosionframe3can = New Canvas(explosionframe3im)
		explosionframe3im.Handle = New Vec2f(0.5,0.5)

		spacestationltim = New Image(48,48)
		spacestationltcan = New Canvas(spacestationltim)
		spacestationrtim = New Image(48,48)
		spacestationrtcan = New Canvas(spacestationrtim)
		spacestationlbim = New Image(48,48)
		spacestationlbcan = New Canvas(spacestationlbim)
		spacestationrbim = New Image(48,48)
		spacestationrbcan = New Canvas(spacestationrbim)

'ship
Local map := New Int[][] (

'New Int[](1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,1,12,1,1,1,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,1,12,1,1,1,1,1,1,0,0,0,0,0,0,0),
'New Int[](0,1,12,11,1,1,1,1,1,1,1,0,0,0,0,0),
'New Int[](0,1,1,1,1,12,1,1,1,1,1,1,1,0,0,0),
'New Int[](0,11,1,1,1,11,1,1,1,1,1,1,1,1,1,0),
'New Int[](0,11,1,1,1,1,1,11,1,1,1,1,11,12,1,1),
'New Int[](0,11,1,1,1,1,1,11,1,1,1,1,11,12,1,1),
'New Int[](0,11,1,1,1,11,1,1,1,1,1,1,1,1,1,0),
'New Int[](0,1,1,1,1,12,1,1,1,1,1,1,1,0,0,0),
'New Int[](0,1,12,11,1,1,1,1,1,1,1,0,0,0,0,0),
'New Int[](0,1,12,1,1,1,1,1,1,0,0,0,0,0,0,0),
'New Int[](0,1,12,1,1,1,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0))		
New Int[](0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4),
New Int[](0,11,11,11,11,11,11,12,0,4,4,4,4,4,4,4),
New Int[](4,0,12,12,12,12,12,12,0,4,4,4,4,4,4,4),
New Int[](4,0,12,15,1,1,15,12,12,0,4,4,4,4,4,4),
New Int[](4,0,12,12,11,11,12,12,12,12,0,4,4,4,4,4),
New Int[](4,0,12,11,0,0,11,12,11,12,12,0,0,0,4,4),
New Int[](0,0,12,12,11,11,12,12,12,12,0,11,11,0,0,4),
New Int[](0,0,15,1,1,1,12,15,12,15,1,1,1,1,12,0),
New Int[](0,0,15,1,1,1,12,15,12,15,1,1,1,1,12,0),
New Int[](0,0,12,12,11,11,12,12,12,12,0,11,11,0,0,4),
New Int[](4,0,12,11,0,0,11,12,11,12,12,0,0,0,4,4),
New Int[](4,0,12,12,11,11,12,12,12,12,0,4,4,4,4,4),
New Int[](4,0,12,15,1,1,15,12,12,0,4,4,4,4,4,4),
New Int[](4,0,12,12,12,12,12,12,0,4,4,4,4,4,4,4),
New Int[](0,11,11,11,11,11,11,12,0,4,4,4,4,4,4,4),
New Int[](0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			shipcan.Color = c64color[map[y][x]].Blend(Color.Yellow,.2)
			If map[y][x] = 4 Then shipcan.Alpha = 0 Else shipcan.Alpha=1
			shipcan.DrawRect(x*2,y*2,2,2)
		Next
		Next
		shipcan.Flush()

'rock
map = New Int[][] (
New Int[](12,11,12,12,15,15,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,15,15,1,12,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,12,12,15,15,15),
New Int[](15,15,15,12,1,15,15,15,15,1,12,11,15,15,15,15),
New Int[](15,15,15,15,12,1,15,15,15,15,12,15,15,15,15,15),
New Int[](15,15,15,15,15,12,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,11,12,15,15,15,15,15,15,15,15,12),
New Int[](12,15,15,15,15,15,15,12,15,15,15,15,15,12,15,15),
New Int[](15,15,15,15,15,15,15,11,12,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,1,15,15,15,15,15,15,15,1,15,15),
New Int[](15,15,15,11,12,12,15,15,15,15,15,15,12,12,1,15),
New Int[](15,15,15,12,15,15,15,15,15,15,15,15,15,12,12,15),
New Int[](15,15,11,12,1,15,15,15,15,15,15,15,12,11,12,15),
New Int[](12,11,15,15,1,15,15,15,15,15,15,15,12,11,12,15),
New Int[](12,15,15,12,15,15,15,15,15,15,15,15,15,15,12,12))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockcan.Color = c64color[map[y][x]]
			rockcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockcan.Flush()

'lefttop rock
map = New Int[][] (
New Int[](11,12,15,0,0,0,0,0,0,0,0,0,11,11,0,15),
New Int[](0,11,15,0,0,11,11,0,11,0,0,0,0,0,11,15),
New Int[](11,0,0,0,11,0,0,0,0,11,0,11,0,15,11,15),
New Int[](0,0,0,0,11,12,15,12,11,0,11,0,15,15,15,15),
New Int[](0,11,11,0,11,11,11,0,0,0,0,11,15,15,15,15),
New Int[](0,11,12,11,0,11,0,0,0,11,11,11,15,11,12,15),
New Int[](11,0,12,0,0,11,0,11,0,15,11,11,15,11,12,15),
New Int[](0,12,15,11,0,0,11,0,0,15,15,15,15,12,1,15),
New Int[](11,11,11,0,0,11,11,15,15,1,15,15,15,12,12,1),
New Int[](11,0,0,11,0,11,15,15,15,15,12,12,15,15,15,15),
New Int[](11,0,11,0,0,15,15,15,15,15,12,15,15,15,15,15),
New Int[](12,15,0,0,15,11,15,15,15,15,15,15,15,15,15,15),
New Int[](11,0,11,0,0,0,15,15,15,15,15,15,15,15,15,15),
New Int[](0,11,15,11,15,15,15,12,11,15,15,15,15,15,15,15),
New Int[](11,15,1,15,15,15,12,1,15,15,15,15,1,15,15,15),
New Int[](15,15,12,15,15,11,15,15,15,15,15,15,12,12,11,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockltcan.Color = c64color[map[y][x]]
			rockltcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockltcan.Flush()

'right top rock
map = New Int[][] (
New Int[](15,11,0,11,0,0,0,12,11,0,0,0,11,0,0,0),
New Int[](15,15,11,0,0,11,15,11,11,11,0,0,11,0,0,11),
New Int[](15,15,11,11,11,0,0,11,0,0,0,0,11,0,0,12),
New Int[](11,15,11,15,0,0,0,11,0,0,0,11,0,11,15,12),
New Int[](15,15,11,15,15,11,0,0,0,0,0,0,11,11,12,11),
New Int[](15,15,15,15,15,15,11,11,0,11,11,11,0,11,0,11),
New Int[](15,15,1,12,12,15,15,11,11,11,12,11,0,0,11,0),
New Int[](15,15,15,12,11,15,0,11,0,12,12,15,11,0,0,0),
New Int[](15,15,12,15,15,15,0,0,11,11,11,15,11,0,11,0),
New Int[](15,15,15,15,15,15,15,15,15,15,11,0,0,0,0,12),
New Int[](15,15,15,15,15,15,15,12,12,15,15,11,0,11,15,12),
New Int[](15,15,15,15,15,15,1,1,11,15,15,15,0,0,0,11),
New Int[](15,15,15,15,15,12,12,12,15,11,15,15,15,11,0,0),
New Int[](15,12,1,15,15,12,15,15,15,15,15,11,11,0,11,0),
New Int[](15,11,12,12,15,15,15,15,12,12,1,15,11,11,15,11),
New Int[](15,15,15,15,15,15,15,15,11,12,15,15,15,15,15,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockrtcan.Color = c64color[map[y][x]]
			rockrtcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockrtcan.Flush()


'left bottom rock
map = New Int[][] (
New Int[](15,15,15,15,15,15,1,15,12,11,15,15,15,15,15,15),
New Int[](11,15,15,12,12,12,12,15,15,15,15,15,15,15,15,15),
New Int[](11,11,15,15,15,15,12,11,15,15,15,15,12,1,12,15),
New Int[](0,0,11,15,11,11,15,15,15,15,15,15,15,15,11,15),
New Int[](11,0,11,0,0,11,15,15,15,15,15,15,15,15,15,15),
New Int[](12,12,0,11,0,11,15,15,15,12,1,15,15,12,15,15),
New Int[](11,0,15,11,0,0,15,15,11,12,12,15,15,15,15,15),
New Int[](0,11,11,0,11,0,0,15,15,11,12,15,15,15,15,15),
New Int[](0,0,0,11,0,12,0,0,15,12,15,15,15,12,1,15),
New Int[](0,0,0,0,15,12,11,11,11,15,15,15,15,12,12,15),
New Int[](0,0,0,0,11,11,0,0,11,11,11,11,15,15,12,15),
New Int[](11,11,11,0,0,11,11,0,0,0,11,0,11,15,12,11),
New Int[](15,12,11,0,11,0,11,0,0,0,0,11,15,15,15,11),
New Int[](11,0,0,0,0,11,0,0,11,11,0,11,0,11,15,15),
New Int[](0,0,0,0,0,0,0,15,12,11,0,0,11,0,15,15),
New Int[](11,0,0,11,11,0,0,11,12,0,0,0,0,11,11,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rocklbcan.Color = c64color[map[y][x]]
			rocklbcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rocklbcan.Flush()


'right bottom rock
map = New Int[][] (
New Int[](1,12,12,15,15,15,15,12,1,11,12,15,15,15,15,15),
New Int[](15,12,11,15,15,15,15,15,1,15,15,15,15,11,15,11),
New Int[](15,12,15,15,15,15,15,15,12,15,15,11,0,15,11,11),
New Int[](15,15,15,15,15,15,1,12,11,15,15,15,0,11,0,0),
New Int[](15,15,15,15,12,12,12,11,15,15,15,0,11,11,0,11),
New Int[](15,15,15,15,15,15,15,15,15,15,15,0,0,11,15,0),
New Int[](15,15,15,15,15,1,12,15,11,15,11,11,11,12,12,0),
New Int[](15,15,15,15,15,12,15,15,11,11,0,0,11,11,0,11),
New Int[](15,15,15,15,12,15,15,15,11,0,0,11,0,0,11,0),
New Int[](15,1,15,15,15,11,15,0,11,11,12,11,0,0,0,0),
New Int[](15,1,12,15,11,15,11,11,0,11,11,11,0,0,0,11),
New Int[](15,12,11,11,11,11,11,0,0,11,0,0,0,0,0,0),
New Int[](15,15,15,15,11,11,0,11,11,0,0,0,0,0,0,0),
New Int[](15,15,15,12,12,15,11,0,0,0,0,0,0,11,0,0),
New Int[](15,15,11,0,11,12,12,12,11,0,11,15,12,11,0,11),
New Int[](15,11,0,11,0,0,0,0,11,0,0,11,12,11,0,11))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockrbcan.Color = c64color[map[y][x]]
			rockrbcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockrbcan.Flush()

' background dark
map = New Int[][] (


New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,11,0,11,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,11,0,11,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0))

'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0),
'New Int[](0,0,11,0,0,0,0,0,0,0,12,15,0,0,0,0),
'New Int[](11,11,0,0,0,0,0,0,0,11,0,11,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,11,12,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0),
'New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
'New Int[](15,12,0,0,0,0,0,0,0,0,0,11,0,0,0,0),
'New Int[](11,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockbackcan.Color = c64color[map[y][x]]
			rockbackcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockbackcan.Flush()

map = New Int[][] (

New Int[](12,15,12,11,12,15,12,12,15,15,15,15,12,15,15,12),
New Int[](15,15,15,1,15,15,11,12,11,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,12,12,1,14,14,11,15,15,15,15,15),
New Int[](15,15,15,15,15,11,3,14,6,0,11,15,12,12,15,15),
New Int[](15,11,15,15,12,11,3,14,0,11,15,15,15,15,15,15),
New Int[](15,12,1,15,15,15,14,6,11,11,15,15,15,15,15,15),
New Int[](15,12,15,11,12,12,15,0,15,12,12,15,15,15,15,15),
New Int[](15,15,12,12,1,3,14,11,15,15,12,15,12,15,15,15),
New Int[](15,15,12,11,3,14,14,6,11,12,11,11,14,0,15,15),
New Int[](15,15,15,15,14,14,6,0,12,1,3,14,14,11,15,15),
New Int[](15,15,15,15,0,0,0,12,11,14,6,14,6,0,15,15),
New Int[](15,15,15,15,15,11,12,15,11,14,15,0,0,11,15,15),
New Int[](15,15,15,15,15,15,1,12,15,0,11,11,15,15,15,15),
New Int[](15,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15),
New Int[](12,12,15,15,15,15,15,15,15,15,15,15,12,1,15,15),
New Int[](11,12,15,15,15,15,15,15,15,15,15,15,11,12,12,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockore1can.Color = c64color[map[y][x]]			
			rockore1can.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockore1can.Flush()

'rock icon
map = New Int[][] (
New Int[](15,15,15,15,0,0,0,0,0,15,15,15,15,15,15,15),
New Int[](15,15,15,0,14,14,14,14,6,0,15,15,15,15,15,15),
New Int[](15,15,0,14,3,3,14,6,6,0,0,0,0,15,15,15),
New Int[](15,15,0,14,1,3,14,6,6,6,6,6,6,0,15,15),
New Int[](15,15,0,14,1,14,6,6,14,3,3,14,6,6,0,15),
New Int[](15,15,0,14,1,14,14,6,14,1,14,14,6,0,15,15),
New Int[](15,15,0,14,3,14,6,6,14,3,14,14,6,0,15,15),
New Int[](15,15,0,14,3,14,6,6,6,6,14,14,6,0,15,15),
New Int[](15,15,0,14,3,14,6,6,6,14,14,6,6,0,15,15),
New Int[](15,0,14,3,14,3,14,6,6,3,14,6,6,0,15,15),
New Int[](15,0,14,1,14,3,14,6,14,3,14,6,6,0,15,15),
New Int[](15,0,14,3,14,14,6,6,14,3,14,14,6,0,15,15),
New Int[](15,0,14,3,14,6,6,6,14,3,14,6,6,0,15,15),
New Int[](15,0,14,3,6,14,14,6,6,3,6,6,6,0,15,15),
New Int[](15,0,14,6,6,6,6,6,0,6,6,6,0,15,15,15),
New Int[](15,15,0,0,0,0,0,0,15,0,0,0,15,15,15,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			iconore1can.Color = c64color[map[y][x]]
			If map[y][x] = 15 Then iconore1can.Alpha = 0 Else iconore1can.Alpha=1
			iconore1can.DrawRect(x*2,y*2,2,2)
		Next
		Next
		iconore1can.Flush()

'ore 2 (metal)
map = New Int[][] (
New Int[](15,15,15,15,15,15,15,15,15,12,12,15,15,15,15,15),
New Int[](15,15,15,15,12,15,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,11,11,15,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,12,15,12,12,11,0,15,15,15,15,1,15,15),
New Int[](15,15,15,15,15,12,1,1,15,0,11,15,12,12,15,15),
New Int[](15,15,15,15,15,11,15,15,11,0,0,12,11,15,15,15),
New Int[](15,15,12,15,0,15,11,12,11,11,15,0,11,15,15,15),
New Int[](15,12,11,15,0,11,12,1,0,1,15,11,0,15,15,15),
New Int[](1,12,15,15,15,0,1,15,11,0,11,11,0,15,15,15),
New Int[](15,15,15,15,0,15,15,15,11,0,0,0,11,15,15,15),
New Int[](15,15,15,15,0,11,15,11,0,11,15,15,15,1,15,15),
New Int[](15,15,11,15,15,0,0,0,11,15,15,15,12,11,15,15),
New Int[](15,15,12,11,15,11,11,11,15,15,15,15,15,12,15,15),
New Int[](15,15,15,11,12,15,15,15,15,15,11,11,15,15,15,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,12,11,15,15,15),
New Int[](15,15,15,15,15,15,15,15,12,15,15,15,12,15,15,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockore2can.Color = c64color[map[y][x]]			
			rockore2can.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockore2can.Flush()

' metal icon
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,15,12,12,4,4,4,4,4,4),
New Int[](4,4,4,4,4,15,15,1,15,15,12,4,4,4,4,4),
New Int[](4,4,4,4,15,1,1,15,0,15,12,11,4,4,4,4),
New Int[](4,4,4,12,15,15,15,12,11,12,12,12,0,4,4,4),
New Int[](4,4,4,12,15,15,11,15,0,12,11,0,4,4,4,4),
New Int[](4,4,4,12,15,12,11,0,11,11,11,4,4,4,4,4),
New Int[](4,4,4,11,15,12,12,11,0,1,15,0,4,4,4,4),
New Int[](4,4,4,4,12,11,11,0,1,15,11,0,4,4,4,4),
New Int[](4,4,4,4,4,0,11,15,15,12,11,0,4,4,4,4),
New Int[](4,4,4,4,4,4,0,12,0,11,0,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,0,4,0,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			iconore2can.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then iconore2can.Alpha = 0 Else iconore2can.Alpha=1
			iconore2can.DrawRect(x*2,y*2,2,2)
		Next
		Next
		iconore2can.Flush()

' icon ore 3 (rock)
map = New Int[][] (

New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,12,12,11,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,12,1,11,4,4,4,4),
New Int[](4,4,4,4,4,4,4,12,4,11,15,15,0,4,4,4),
New Int[](4,4,4,4,4,4,12,15,4,4,11,11,0,4,4,4),
New Int[](4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,12,4,4,4,4,4,12,4,4,4,4,4),
New Int[](4,4,4,12,15,0,4,4,4,12,15,11,11,4,4,4),
New Int[](4,4,4,4,0,0,4,4,4,12,1,15,11,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,0,15,15,0,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,0,0,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
'New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
'New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
'New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
'New Int[](4,4,4,4,4,4,4,15,12,12,4,4,4,4,4,4),
'New Int[](4,4,4,4,4,4,15,1,15,15,11,4,4,4,4,4),
'New Int[](4,4,4,4,4,15,1,15,15,15,15,11,4,4,4,4),
'New Int[](4,4,4,4,4,12,15,15,1,12,15,0,4,4,4,4),
'New Int[](4,4,4,4,4,12,15,12,15,15,11,0,4,4,4,4),
'New Int[](4,4,4,4,15,11,15,15,15,11,0,4,4,4,4,4),
'New Int[](4,4,4,12,1,15,0,11,0,11,0,4,4,4,4,4),
'New Int[](4,4,4,11,15,15,0,15,1,15,15,11,0,4,4,4),
'New Int[](4,4,4,0,15,11,0,1,15,15,15,11,0,4,4,4),
'New Int[](4,4,4,4,0,0,0,0,15,11,0,0,4,4,4,4),
'New Int[](4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4),
'New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
'New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			iconore3can.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then iconore3can.Alpha = 0 Else iconore3can.Alpha=1
			iconore3can.DrawRect(x*2,y*2,2,2)
		Next
		Next
		iconore3can.Flush()


'missile
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](0,4,4,4,4,4,4,4,4,4,0,4,4,4,4,4),
New Int[](0,0,0,4,4,4,4,4,4,4,0,0,4,4,4,4),
New Int[](0,11,11,0,0,0,0,0,0,0,0,0,11,11,11,11),
New Int[](0,12,12,15,15,15,15,15,10,10,15,15,1,1,1,0),
New Int[](0,0,0,12,12,12,12,12,2,2,12,12,15,7,7,0),
New Int[](0,11,11,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,4,4,4,4,4,4,4,0,0,4,4,4,4),
New Int[](0,4,4,4,4,4,4,4,4,4,0,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			missilecan.Color = c64color[map[y][x]].Blend(Color.Red,.2)
			If map[y][x] = 4 Then missilecan.Alpha = 0 Else missilecan.Alpha=1
			missilecan.DrawRect(x*2,y*2,2,2)
		Next
		Next
		missilecan.Flush()

'electronic icon
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,5,5,5,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,5,5,5,1,5,4,4,4,4,4,4,4,4),
New Int[](4,4,5,5,5,5,5,5,5,4,4,4,4,4,4,4),
New Int[](4,4,4,5,1,5,5,5,11,12,4,4,4,4,4,4),
New Int[](4,4,4,4,5,5,11,5,12,15,5,4,4,4,4,4),
New Int[](4,4,4,4,7,11,0,5,5,5,5,0,4,4,4,4),
New Int[](4,4,4,4,4,7,5,5,5,5,5,5,5,4,1,4),
New Int[](4,4,4,4,4,4,7,5,11,0,5,5,5,1,4,4),
New Int[](4,4,4,4,4,4,4,4,0,0,5,5,11,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,5,5,11,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,1,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,1,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			iconscrapcan.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then iconscrapcan.Alpha = 0 Else iconscrapcan.Alpha=1
			iconscrapcan.DrawRect(x*2,y*2,2,2)
		Next
		Next
		iconscrapcan.Flush()


'scrap icon
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,1,1,1,1,15,15,11,4,4,4,4),
New Int[](4,4,4,4,4,1,1,12,12,12,15,11,4,4,4,4),
New Int[](4,4,4,4,4,1,12,12,12,15,12,4,4,4,4,4),
New Int[](4,4,4,4,4,1,12,12,15,12,11,4,4,4,4,4),
New Int[](4,4,4,4,4,1,12,15,15,12,11,4,4,15,4,4),
New Int[](4,4,4,4,4,1,15,15,12,11,4,4,12,4,4,4),
New Int[](4,4,4,4,4,15,15,12,12,11,4,11,4,4,4,4),
New Int[](4,4,4,4,4,15,12,12,12,0,11,4,4,4,4,4),
New Int[](4,4,4,4,4,15,12,12,0,11,4,4,4,4,4,4),
New Int[](4,4,4,4,4,15,12,15,0,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,12,11,11,0,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,11,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,12,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			iconeleccan.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then iconeleccan.Alpha = 0 Else iconeleccan.Alpha=1
			iconeleccan.DrawRect(x*2,y*2,2,2)
		Next
		Next
		iconeleccan.Flush()

'explosion frame 1 (4)
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,2,4,4,4,4,2,4,4,4,4,4),
New Int[](4,4,4,4,4,4,2,4,4,2,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,7,7,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,7,7,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,2,4,4,2,4,4,4,4,4,4),
New Int[](4,4,4,4,4,2,4,4,4,4,2,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			explosionframe1can.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then explosionframe1can.Alpha = 0 Else explosionframe1can.Alpha=1
			explosionframe1can.DrawRect(x*2,y*2,2,2)
		Next
		Next
		explosionframe1can.Flush()


'explosion frame 2 (4)
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,2,4,4,4,4,4,4,4,4,4,4,2,4,4),
New Int[](4,4,4,2,4,4,4,4,4,4,4,4,2,4,4,4),
New Int[](4,4,4,4,7,4,4,2,2,4,4,7,4,4,4,4),
New Int[](4,4,4,4,4,7,4,7,7,4,7,4,4,4,4,4),
New Int[](4,4,4,4,4,4,7,1,1,7,4,4,4,4,4,4),
New Int[](4,4,4,2,2,7,1,1,1,1,7,2,2,4,4,4),
New Int[](4,4,4,2,2,7,1,1,1,1,7,2,2,4,4,4),
New Int[](4,4,4,4,4,4,7,1,1,7,4,4,4,4,4,4),
New Int[](4,4,4,4,4,7,4,7,7,4,7,4,4,4,4,4),
New Int[](4,4,4,4,7,4,4,2,2,4,4,7,4,4,4,4),
New Int[](4,4,4,2,4,4,4,4,4,4,4,4,2,4,4,4),
New Int[](4,4,2,4,4,4,4,4,4,4,4,4,4,2,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			explosionframe2can.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then explosionframe2can.Alpha = 0 Else explosionframe2can.Alpha=1
			explosionframe2can.DrawRect(x*2,y*2,2,2)
		Next
		Next
		explosionframe2can.Flush()

'explosion frame 3 (4)
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](4,7,4,4,4,4,2,2,2,2,4,4,4,4,7,4),
New Int[](4,4,7,7,4,2,2,2,2,2,2,4,7,7,4,4),
New Int[](4,4,7,7,7,2,2,7,7,2,2,7,7,7,4,4),
New Int[](4,4,4,7,7,7,7,7,7,7,7,7,7,4,4,4),
New Int[](4,4,2,2,7,7,7,1,1,7,7,7,2,2,4,4),
New Int[](4,2,2,2,7,7,1,1,1,1,7,7,2,2,2,4),
New Int[](4,2,2,7,7,1,1,1,1,1,1,7,7,2,2,4),
New Int[](4,2,2,7,7,1,1,1,1,1,1,7,7,2,2,4),
New Int[](4,2,2,2,7,7,1,1,1,1,7,7,2,2,2,4),
New Int[](4,4,2,2,7,7,7,1,1,7,7,7,2,2,4,4),
New Int[](4,4,4,7,7,7,7,7,7,7,7,7,7,4,4,4),
New Int[](4,4,7,7,7,2,2,7,7,2,2,7,7,7,4,4),
New Int[](4,4,7,7,4,2,2,2,2,2,2,4,7,7,4,4),
New Int[](4,7,4,4,4,4,2,2,2,2,4,4,4,4,7,4),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			explosionframe3can.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then explosionframe3can.Alpha = 0 Else explosionframe3can.Alpha=1
			explosionframe3can.DrawRect(x*2,y*2,2,2)
		Next
		Next
		explosionframe3can.Flush()

'space station left top
map = New Int[][] (
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,1),
New Int[](4,4,4,4,4,4,4,4,4,4,0,0,12,15,12,1),
New Int[](4,4,4,4,4,4,4,0,0,0,12,15,15,15,12,1),
New Int[](4,4,4,4,4,0,0,12,15,15,15,15,15,15,12,1),
New Int[](4,4,4,0,0,12,15,15,15,1,1,15,15,15,12,1),
New Int[](4,0,0,12,15,15,15,1,1,12,15,15,15,15,12,1),
New Int[](0,12,15,15,15,1,1,12,15,15,15,15,15,15,11,12),
New Int[](0,15,15,1,1,12,15,15,15,15,15,15,15,12,11,12),
New Int[](0,15,15,15,15,15,15,15,15,15,15,15,12,11,11,12),
New Int[](0,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
New Int[](0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
New Int[](0,11,0,11,0,11,0,11,0,11,0,11,0,11,0,11),
New Int[](0,11,7,11,7,11,7,11,7,11,7,11,7,11,7,11))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			spacestationltcan.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then spacestationltcan.Alpha = 0 Else spacestationltcan.Alpha=1
			spacestationltcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		spacestationltcan.Flush()

'space station right top
map = New Int[][] (
New Int[](0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](1,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](1,12,12,0,0,0,4,4,4,4,4,4,4,4,4,4),
New Int[](1,12,15,15,15,12,0,0,0,4,4,4,4,4,4,4),
New Int[](1,12,15,15,15,15,15,15,12,0,0,4,4,4,4,4),
New Int[](1,12,15,15,15,1,1,15,15,15,12,0,0,4,4,4),
New Int[](1,12,15,15,15,15,12,1,1,15,15,15,12,0,0,4),
New Int[](12,11,15,15,15,15,15,15,12,1,1,15,15,15,12,0),
New Int[](12,11,12,15,15,15,15,15,15,15,12,1,1,15,15,0),
New Int[](12,11,11,12,15,15,15,15,15,15,15,15,15,15,15,0),
New Int[](11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,0),
New Int[](1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
New Int[](0,11,0,11,0,11,0,11,0,11,0,11,0,11,11,0),
New Int[](7,11,7,11,7,11,7,11,7,11,7,11,7,11,11,0))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			spacestationrtcan.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then spacestationrtcan.Alpha = 0 Else spacestationrtcan.Alpha=1
			spacestationrtcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		spacestationrtcan.Flush()

'space station left bottom
map = New Int[][] (
New Int[](0,11,7,11,7,11,7,11,7,11,7,11,7,11,7,11),
New Int[](0,11,0,11,0,11,0,11,0,11,0,11,0,11,0,11),
New Int[](0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
New Int[](0,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11),
New Int[](0,15,15,15,15,15,15,15,15,15,15,12,11,11,11,12),
New Int[](4,0,12,15,15,15,15,15,15,15,15,15,12,11,11,12),
New Int[](4,4,0,0,12,15,15,15,15,15,15,15,15,11,11,12),
New Int[](4,4,4,4,0,0,12,15,15,15,15,15,15,15,11,12),
New Int[](4,4,4,4,4,4,0,12,15,15,15,15,15,15,12,1),
New Int[](4,4,4,4,4,4,4,0,0,0,0,12,15,15,12,1),
New Int[](4,4,4,4,4,4,4,4,4,0,0,0,0,0,12,1),
New Int[](4,4,4,4,4,4,4,4,4,4,4,0,0,0,12,1),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,1),
New Int[](4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			spacestationlbcan.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then spacestationlbcan.Alpha = 0 Else spacestationlbcan.Alpha=1
			spacestationlbcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		spacestationlbcan.Flush()

'space station right bottom
map = New Int[][] (
New Int[](7,11,7,11,7,11,7,11,7,11,7,11,7,11,11,0),
New Int[](0,11,0,11,0,11,0,11,0,11,0,11,0,11,11,0),
New Int[](1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,0),
New Int[](12,11,11,11,12,15,15,15,15,15,15,15,15,15,15,0),
New Int[](12,11,11,12,15,15,15,15,15,15,15,15,15,12,0,4),
New Int[](12,11,11,15,15,15,15,15,15,15,15,12,0,0,4,4),
New Int[](12,11,15,15,15,15,15,15,15,12,0,0,4,4,4,4),
New Int[](1,12,15,15,15,15,15,15,12,0,4,4,4,4,4,4),
New Int[](1,12,15,15,12,0,0,0,0,4,4,4,4,4,4,4),
New Int[](1,12,0,0,0,0,0,4,4,4,4,4,4,4,4,4),
New Int[](1,12,0,0,0,4,4,4,4,4,4,4,4,4,4,4),
New Int[](1,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4),
New Int[](0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			spacestationrbcan.Color = c64color[map[y][x]]
			If map[y][x] = 4 Then spacestationrbcan.Alpha = 0 Else spacestationrbcan.Alpha=1
			spacestationrbcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		spacestationrbcan.Flush()

End Method
	'
	' This is the palette used for the graphics... 
	Method inic64colors()
		c64color = New Color[16]
		c64color[0 ] = New Color(intof(0)  ,intof(0)  ,intof(0)  )'Black
		c64color[1 ] = New Color(intof(255),intof(255),intof(255))'White
		c64color[2 ] = New Color(intof(136),intof(0)  ,intof(0)  )'Red
		c64color[3 ] = New Color(intof(170),intof(255),intof(238))'Cyan
		c64color[4 ] = New Color(intof(204),intof(68) ,intof(204))'Violet / Purple
		c64color[5 ] = New Color(intof(0)  ,intof(204),intof(85) )'Green
		c64color[6 ] = New Color(intof(0)  ,intof(0)  ,intof(170))'Blue
		c64color[7 ] = New Color(intof(238),intof(238),intof(119))'Yellow
		c64color[8 ] = New Color(intof(221),intof(136),intof(85) )'Orange
		c64color[9 ] = New Color(intof(102),intof(68) ,intof(0)  )'Brown
		c64color[10] = New Color(intof(255),intof(119),intof(119))'Light red
		c64color[11] = New Color(intof(51) ,intof(51) ,intof(51) )'Dark grey / Grey 1
		c64color[12] = New Color(intof(119),intof(119),intof(119))'Grey 2
		c64color[13] = New Color(intof(170),intof(255),intof(102))'Light green
		c64color[14] = New Color(intof(0)  ,intof(136),intof(255))'Light blue
		c64color[15] = New Color(intof(187),intof(187),intof(187))'Light grey / grey 3
	End Method
	' convert int(0.255) to float(0.1)
	Function intof:Float(a:Int)
		Return 1.0/255.0*a
	End Function
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function


Function edistance:Float(x1:Float,y1:Float,x2:Float,y2:Float) 
	Return Sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) )
End Function
Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    Return True
End

'
' Return the angle from - to in float
Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
	Return ATan2(y2-y1, x2-x1)
End Function

' Return a float value which is negative if the distance between the angle
' and target angle is shorter. Positive value if the right turn is shorter.
' Uses for homing missiles and turrets etc.
' returns - distance float
Function angledifference:Float(target:Float,angle:Float)
	' Our difference (Negative if left target angle is shorter or positive if right turn is closer)
	Local difference:Float = target - angle
	While (difference < -Pi) 
		difference += TwoPi
	Wend
	While (difference > Pi) 
		difference -= TwoPi
	Wend	
	Return difference
End Function

' Here is the circle vs rectangle collide function
' input :
' circlex,circley,circleradius
' rectx,recty,rectwidth,rectheight
' Returns : True or False
Function circlerectcollide:Bool(cx:Float,cy:Float,cr:Float, rx:Float,ry:Float,rw:Float,rh:Float)	
    Local closestx:Float = Clamp(cx, rx, rx+rw)
    Local closesty:Float = Clamp(cy, ry, ry+rh)
    Local distancex :Float = cx - closestx
    Local distancey:Float = cy - closesty
    Local distancesquared:Float = (distancex * distancex) + (distancey * distancey)
    Return distancesquared < (cr * cr)
End Function

Function isore:Bool(val:Int)
	If val = 7 Then Return True
	If val = 8 Then Return True
	Return False
End Function

' by RaGR (Ralph G. Roeske). from blitzbasic.com
Function pointintriangle2d:Bool(px:Float,pz:Float, x1:Float,y1:Float,x2:Float,y2:Float,x3:Float,y3:Float) 
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
