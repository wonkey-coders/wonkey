#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
Class dungeon	
	Field map:Int[,]
	Field screenwidth:Int,screenheight:Int
	Field mapwidth:Int,mapheight:Int
	Field tilewidth:Int,tileheight:Int
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		If mapwidth < 10 Or mapheight < 10 Then RuntimeError("Map size to small. in dungeon class.")
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		tilewidth = Float(screenwidth) / Float(mapwidth)
		tileheight = Float(screenheight) / Float(mapheight)
		generatedungeon()
	End Method
	Method generatedungeon()
		map = New Int[mapwidth,mapheight]
		Local maxroomwidth:Int=mapwidth/4
		Local maxroomheight:Int=mapheight/4
		Local minroomwidth:Int=4
		Local minroomheight:Int=4
		' center of the room coordinates
		Local currentroomx:Int
		Local currentroomy:Int
		Local prevroomx:Int=-1
		Local prevroomy:Int
		' We create a number of rooms based on the width and 
		' height of the map.
		
		For Local i:Int=0 Until (mapwidth+mapheight)/10
			Local newroomwidth:Int = Rnd(minroomwidth,maxroomwidth)
			Local newroomheight:Int = Rnd(minroomheight,maxroomheight)
			Local count:Int=0
			currentroomx = Rnd(minroomwidth/2,mapwidth)
			currentroomy = Rnd(minroomheight/2,mapheight)			
			' Here we keep looping until we have a valid room position
			While overlap(currentroomx,currentroomy,newroomwidth,newroomheight) = True
				' We exit the method if it takes to long.
				count += 1
				If count>99 Then Return
				' Try to get new valid room
				currentroomx = Rnd(minroomwidth,mapwidth)
				currentroomy = Rnd(minroomheight,mapheight)
				newroomwidth = Rnd(minroomwidth,maxroomwidth)
				newroomheight = Rnd(minroomheight,maxroomheight)				
			Wend			
			' Place the room
			For Local y1:Int=currentroomy-newroomheight/2 Until currentroomy+newroomheight/2
			For Local x1:Int=currentroomx-newroomwidth/2 Until currentroomx+newroomwidth/2
				map[x1,y1] = 1
			Next
			Next
			' Can we connect two room yet?
			If prevroomx > -1 
				' Here we start to tunnel between the current room
				' center to the previous rooms center.
				Local x1:Int=currentroomx,x2:Int=prevroomx
				Local y1:Int=currentroomy,y2:Int=prevroomy
				' Randomly decide if x or y goes first
				If Rnd() < .5
					' Make a tunnel
					While x1<>x2
						If x1<x2 Then x1+=1 Else x1-=1					
						map[x1,y1] = 1
					Wend
					While y1<>y2
						If y1<y2 Then y1+=1 Else y1-=1
						map[x1,y1] = 1
					Wend
				Else
					' Make a tunnel
					While y1<>y2
						If y1<y2 Then y1+=1 Else y1-=1
						map[x1,y1] = 1
					Wend
					While x1<>x2
						If x1<x2 Then x1+=1 Else x1-=1					
						map[x1,y1] = 1
					Wend				
				End If
	
			End If
			prevroomx = currentroomx
			prevroomy = currentroomy
			
		Next
	End Method
	' Does the inputted area touch a value in the map
	' or does it go outside of the screen.
	' returns true if so.
	Method overlap:Bool(x:Int,y:Int,w:Int,h:Int)
		x-=1
		y-=1
		w+=1
		h+=1
		If x-w/2<3 Or y-h/2<3 Or x+w/2>=mapwidth-3 Or y+h/2>=mapheight-3 Then Return True
		For Local y1:Int=y-h/2 Until y+h/2
		For Local x1:Int=x-w/2 Until x+w/2
			If map[x1,y1] = 1 Then Return True
		Next
		Next			
		Return False
	End Method
	Method drawmap(canvas:Canvas)
		canvas.Color = Color.White
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If map[x,y] > 0
				canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth+1,tileheight+1)
			End If
		Next
		Next
	End Method
End Class


Class world
	Class kagent
		Field kpx:Int,kpy:Int,kw:Int,kh:Int
		Field genetic:Stack<Int> = New Stack<Int>
		Field currentpos:Int
		Field time:Int,timeend:Int=10
		Field die:Bool=False
		Field winner:Bool=False		
		Field dis:Int 'last distance to target
		Field closest:Int 'flood distance
		Field origx:Int,origy:Int
		Field deathstep:Int=-1
		Method New(x:Int,y:Int)
			kpx = x
			kpy = y
			origx = x
			origy = y
			kw = 10
			kh = 10
		End Method
		Method updatewinner()
			time+=1
			move()

			If time>timeend Then 
				time = 0
				currentpos += 1
				'If int(kpx/myworld.tw) = myworld.endx And int(kpy/myworld.th) = myworld.endy Then 
				If distance((kpx/myworld.tw)-1,(kpy/myworld.th)-1,myworld.endx,myworld.endy) < 3 Or currentpos = deathstep
					currentpos = 0
					kpx = origx
					kpy = origy
					myworld.setmap1()					
				End If
			End If

		End Method
		Method move()
			Select genetic.Get(currentpos)
				Case 0
					kpx-=1
					kpy-=1
				Case 1
					kpy-=1
				Case 2
					kpx+=1
					kpy-=1
				Case 3
					kpx-=1
				Case 4
				Case 5
					kpx+=1
				Case 6
					kpx-=1
					kpy+=1
				Case 7
					kpy+=1
				Case 8
					kpx+=1
					kpy+=1
			End Select

		End Method
		Method update()
			If die=True Then Return
			move()
			If Int(kpx/myworld.tw) = myworld.endx And Int(kpy/myworld.th) = myworld.endy
				For Local i:Int=0 Until myworld.myagent.Length
					myworld.myagent.Get(i).winner = false
				Next
				deathstep = currentpos
				winner = True
				currentpos = 0
				kpx = origx
				kpy = origy				
				myworld.completed = True
				myworld.setmap1()
				Return
			End If
			time+=1
			If time>timeend Then 
				time = 0
				currentpos += 1
				If currentpos = genetic.Length Then die = True
			End If
			If collidemap()
				die = True
				deathstep = currentpos
			End If
			If collideobstacle()
				die = True
				deathstep = currentpos
			End If
		End Method
		Method growgenetic()
			For Local i:Int=0 Until 5
				genetic.Push(Rnd(0,9))
			Next
		End Method
		Method draw(canvas:Canvas)
			canvas.Color = Color.Red
			canvas.DrawOval(kpx,kpy,kw,kh)
		End Method
		Method collideobstacle:Bool()
			For Local i:Int=0 Until myworld.myobstacle.Length
				Local x2:Int=myworld.myobstacle.Get(i).kx
				Local y2:Int=myworld.myobstacle.Get(i).ky
				Local w2:Int=myworld.myobstacle.Get(i).kw
				Local h2:Int=myworld.myobstacle.Get(i).kh
				x2+=w2/2
				y2+=h2/2
				If rectsoverlap(kpx+kw/2,kpy+kh/2,kw,kh,x2,y2,w2*2,h2*2)
					Return True
				End if
			Next
			Return False
		End Method
		Method collidemap:Bool()
			Local cx:Int=(kpx+kw/2)/myworld.tw
			Local cy:Int=(kpy+kh/2)/myworld.th
			For Local y1:Int=cy-3 To cy+3
			For Local x1:Int=cx-3 To cx+3
				If x1<0 Or y1<0 Or x1>=myworld.mapw Or y1>=myworld.maph Then Continue
				If myworld.map[x1,y1] = 1
					Local x2:Int=x1*myworld.tw
					Local y2:Int=y1*myworld.th					
					If rectsoverlap(kpx,kpy,kw,kh,x2,y2,myworld.tw,myworld.th) Then Return True
				End if
			Next
			Next
			Return False
		End Method
		Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
			Return Abs(x2-x1)+Abs(y2-y1)
		End Function
		Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
		    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
		    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
		    Return True
		End Function
	End Class
	Class kobstacle
		Field kx:Int,ky:Int
		Field incx:Int,incy:Int
		Field kw:Int,kh:Int
		Field kd:String
		Method New(x:Int,y:Int,w:Int,h:Int,d:String)
			Self.kx = x
			Self.ky = y
			Self.kw = w
			Self.kh = h
			If d = "u" Then incy = -1
			If d = "d" Then incy = 1
			If d = "l" Then incx = -1
			If d = "r" Then incx = 1			
			Self.kd = d
		End Method
		Method update()			
			kx += incx
			ky += incy
			If collidemap() Then
				If kd = "u" Then 
					kd = "d"
					incy = 1					
				Elseif kd = "d"
					kd = "u"
					incy = -1
				End If
				If kd = "l" Then 
					kd = "r"
					incx = 1					
				Elseif kd = "r"
					kd = "l"
					incx = -1
				End If

			End If 
		End Method
		Method draw(canvas:Canvas)
			canvas.Color = Color.Blue
			canvas.DrawOval(kx+kw/2,ky+kh/2,kw,kh)
		End Method
		Method collidemap:Bool()
			Local cx:Int=(kx+kw/2)/myworld.tw
			Local cy:Int=(ky+kh/2)/myworld.th
			For Local y1:Int=cy-2 To cy+2
			For Local x1:Int=cx-2 To cx+2
				If x1<0 Or y1<0 Or x1>=myworld.mapw Or y1>=myworld.maph Then Continue
				If myworld.map[x1,y1] = 1
					Local x2:Int=x1*myworld.tw
					Local y2:Int=y1*myworld.th					
					If rectsoverlap(kx+kw/2,ky+kh/2,kw,kh,x2,y2,myworld.tw,myworld.th) Then Return True
				End if
			Next
			Next
			Return False
		End Method
		Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
		    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
		    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
		    Return True
		End Function
	End Class
	'
	Field sw:Int,sh:Int
	Field tw:Float,th:Float
	Field mapw:Int,maph:Int
	Field map:Int[,]
	Field dmap:Int[,] 'contains distances from end to start
	Field myagent:Stack<kagent> = New Stack<kagent>
	Field myobstacle:Stack<kobstacle> = New Stack<kobstacle>
	Field startx:Int,starty:Int,endx:Int,endy:Int
	Field completed:Bool=False
	Field currentlevel:Int
	
	Method New(sw:Int,sh:Int,level:Int)
		Self.sw = sw
		Self.sh = sh
		currentlevel = level
		setmap1()
		

		For Local i:Int=0 Until 200
			myagent.Push(New kagent(startx*tw,starty*th))
			myagent.Get(i).growgenetic()
		Next
	End Method
	Method update()
		If completed
			For Local i:Int=0 Until myobstacle.Length
				myobstacle.Get(i).update()
			Next
			For Local i:Int=0 Until myagent.Length				
				If myagent.Get(i).winner = True
					myagent.Get(i).updatewinner()					
				End If
			Next
			Return
		End If
		
		
		For Local ii:Int=0 Until 20
		' update the obstacles
		'While completed=False
		For Local i:Int=0 Until myobstacle.Length
			myobstacle.Get(i).update()
		Next

'		' update the agents
		If alldead() = False		
			For Local i:Int=0 Until myagent.Length
				myagent.Get(i).update()
			Next
		Else
			newagents()
			Exit
		End If
		'Wend
		If completed = True Then Exit
		Next
	End Method
	Method distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x2-x1)+Abs(y2-y1)
	End Method
	Method newagents()
		If completed = True Then Return
		'If Rnd()<.05 Then Print Microsecs()
		SeedRnd(Millisecs())
		' find the agent closest to the destination
		Local closest:Int=9999999
		Local dis:Int=99999999
		Local closestid:Int=-1
		For Local i:Int=0 Until myagent.Length
			Local ax:Int=myagent.Get(i).kpx/tw
			Local ay:Int=myagent.Get(i).kpy/th
			If dmap[ax,ay]<closest And dmap[ax,ay]>0'distance(ax,ay,endx,endy)<dis Then
				closest = dmap[ax,ay]
				closestid = i
				'dis = distance(ax,ay,endx,endy)
			End If
		Next

		

		'If dis<5 Then
		'	 Print "made it...."
		'	 myagent.Get(closestid).winner = True			 
		'	 completed=True
		'End If

		' cut off 1 of length
'		For Local i:Int = 0 Until myagent.Length
'			For Local ii:Int=0 To 3
'			myagent.Get(i).genetic.Pop			
'			Next
'		Next
''
'Print "a"
		For Local i:Int=0 Until myagent.Length
			If i <> closestid
				myagent.Get(i).genetic.Clear()	
			End If
		Next
		' copy the genetic of the closest into every other
		Local maxd:Int=myagent.Get(closestid).genetic.Length
		If myagent.Get(closestid).deathstep+20 < myagent.Get(closestid).genetic.Length
			maxd = myagent.Get(closestid).deathstep+20
		Endif
		For Local i:Int=0 Until myagent.Length
			If i <> closestid
				Local ax:Int=myagent.Get(i).kpx/tw
				Local ay:Int=myagent.Get(i).kpy/th
				'myagent.Get(i).genetic.Clear()				
				'If dmap[ax,ay] <>0 And dmap[ax,ay]+2 < closest Then Continue
				For Local ii:Int=0 Until maxd'myagent.Get(closestid).genetic.Length
					'myagent.Get(i).genetic.Clear()
					myagent.Get(i).genetic.Push(myagent.Get(closestid).genetic.Get(ii))
				Next
			End If
		Next
		'Print "b"
		'Mutate some
		Local l:Int=1.0/Float(myagent.Get(0).genetic.Length)
		For Local i:Int=0 Until myagent.Length	
			If i<>closestid 'And Rnd()<.1
				
			For Local ii:Int=0 Until myagent.Get(i).genetic.Length
				'If ii>myagent.Get(i).genetic.Length/3 Or Rnd()<.2
				If Rnd()<.2 And ii>myagent.Get(i).deathstep-10 Then myagent.Get(i).genetic.Set(ii,Rnd(0,9))
				'End If
			Next
			
			End If
			'myagent.Get(i).genetic.Set(myagent.Get(i).genetic.Length,Rnd(0,9))
		Next		
		'add length of 5
		For Local i:Int=0 Until myagent.Length	
			For Local ii:Int=0 Until 5
				Local nd:Int=Rnd(0,9)
				myagent.Get(i).genetic.Push(nd)
			Next
		Next
		'Print "c"
		'reset agents
		For Local i:Int=0 Until myagent.Length
			myagent.Get(i).kpx = startx*tw
			myagent.Get(i).kpy = starty*th
			myagent.Get(i).currentpos = 0
			myagent.Get(i).die = False
			myagent.Get(i).time = 0
			'myagent.Get(i).winner = False
		Next		
		setmap1()
	End Method
	Method alldead:Bool()
		For Local i:Int=0 Until myagent.Length
			If myagent.Get(i).die = False Then Return False
		Next
		Return True
	End Method
	Method setmap1()
		myobstacle = New Stack<kobstacle>
		Local l:String[] 
		
		If currentlevel >= 4  And currentlevel<=9999 'random one
			Local sx:Int,sy:Int,ex:Int,ey:Int
			SeedRnd(currentlevel)
			Local dw:Int=25,dh:Int=25
			Local mydun:dungeon = New dungeon(640,480,dw,dh)
			'grow width and height by 1 (blocks)
			For Local y:Int=1 Until dh-1
			For Local x:Int=1 Until dw-1
				If mydun.map[x,y] = 1 Then mydun.map[x-1,y] = 1
				If mydun.map[x,y] = 1 Then mydun.map[x,y-1] = 1
			Next
			Next
			'add walls
			For Local y:Int=0 Until dh
			For Local x:Int=0 Until dw
				If mydun.map[x,y] = 0
					For Local y1:Int=y-1 To y+1
					For Local x1:Int=x-1 To x+1
						If x1<0 Or y1<0 Or x1>=dw Or y1>=dh Then Continue
						If mydun.map[x1,y1] = 1
							mydun.map[x,y] = 2							
						End If
					Next
					Next
				End If
			Next
			Next	
			' insert the dungeon into the l string array		
			l = New String[dw]
			For Local y:Int=0 Until dh
			For Local x:Int=0 Until dw
				Local t:Int=mydun.map[x,y]
				If t=1 Then l[y]+="0" 
				If t=0 Then l[y]+="q"
				If t=2 Then l[y]+="1"
			Next
			Next
			'left most position at random x is start pos
			Local set:Bool=False
			For Local x:Int=0 Until dw
			For Local y:Int=0 Until dh
				If set=False
				If l[y].Mid(x,1) = 1 And l[y].Mid(x+1,1) = 0
					l[y]=l[y].Mid(0,x+1)+"a"+l[y].Mid(x+2,l[y].Length-x-1)
					set=True
					sx = x
					sy = y
				End If
				End If
			Next
			If set=True Then Exit
			Next		
			'Right bottom most position at random x is end pos
			set=False
			For Local x:Int=dw-1 Until 1 Step -1
			For Local y:Int=dh-1 Until 1 Step -1
				If set=False
				If l[y].Mid(x,1) = 1 And l[y].Mid(x-1,1) = 0
					l[y]=l[y].Mid(0,x-1)+"z"+l[y].Mid(x,l[y].Length-x-1)
					set=True
					ex = x
					ey = y
				End If
				End If
			Next
			If set=True Then Exit
			Next		
			' Add a UPMOVING obstacle (u)
			Local isplaced:Bool=False
			For Local y:Int=dh-1 Until 1 Step -1
			For Local x:Int=dw-1 Until 1 Step -1
				If x<1 Or y<1 Or x>=dw-1 Or y>=dh-1 Then Continue
				Local y2:Int=0
				If l[y].Mid(x,1) = 1 And l[y-1].Mid(x,1) = 0
					y-=1
				Repeat
					If l[y-y2].Mid(x,1) = 0 Then
						y2+=1
						If y2=5 Then 
							l[y]=l[y].Mid(0,x-1)+"u"+l[y].Mid(x,l[y].Length-x)
							isplaced = True
							Exit
						End If
					Else
						Exit
					End If
					
				Forever
				End If
				If isplaced = True Then Exit
			Next
			If isplaced = True Then Exit
			Next
			' Add a RIGHTMOVING obstacle (r)
			For Local i:Int=0 Until 200
				Local x:Int=Rnd(2,dw-2)
				Local y:Int=Rnd(dh/5,dh-dh/5)
				'see if spot is wall
				If l[y].Mid(x,1) = 1 And l[y].Mid(x+1,1) = 0
					' see if there is another wall at the end
					Local step1:Bool=True
					Local d:Int=0
					For Local z:Int=x+1 Until dw-2
						If l[y].Mid(z,1) = 1 And d<5 Then 
							step1=false  
							Exit
						End If
						d+=1
					Next
					If step1 = True
						l[y] = l[y].Mid(0,x+1) + "r" + l[y].Mid(x+2,l[y].Length-x-2)
						Exit
					End If
				End If
			Next
			' Add a downmoving obstacle
			For Local i:Int=0 Until 200
				Local x:Int=Rnd(dw/3,dw-dw/5)
				Local y:Int=Rnd(dh/5,dh-dh/3)
				If l[y].Mid(x,1) = 1 And l[y+1].Mid(x,1) = 0 'And l[y+2].Mid(x,1) = 0 And l[y+3].Mid(x,1) = 0
					'see If there is another wall at the end
					Local step1:Bool=True
					Local d:Int=0
					For Local z:Int=y+1 Until dh-2
						
						If l[z].Mid(x,1) = 1 And d<5 
							step1=False  						
							Exit
						End If
						d+=1
					Next
					
					If step1 = True
						l[y+1] = l[y+1].Mid(0,x) + "d" + l[y+1].Mid(x+1,l[y+1].Length-x-2)
						Exit
					End If

				End If
			Next
		End If
		If currentlevel = 2
			l = New String[10]
			' 0 - floor
			' 1 - wall
			' a - start position
			' z - end position
			' u - move up obstacle
			' d - move down obstacle
			l[0]="11111111111111111111"
			l[1]="1a000011000111111111"
			l[2]="10000011000000d00001"
			l[3]="10000011000000000001"
			l[4]="10000011000110000001"
			l[5]="10000l11r00110000001"
			l[6]="10000011000111111001"
			l[7]="10000011000110d00001"
			l[8]="100u000000011z000001"
			l[9]="11111111111111111111"
		End If

		If currentlevel = 3
			l = New String[10]
			' 0 - floor
			' 1 - wall
			' a - start position
			' z - end position
			' u - move up obstacle
			' d - move down obstacle
			l[0]="00000011111111100000"
			l[1]="000000100a1111100000"
			l[2]="01111110001111111111"
			l[3]="010d0000000000000001"
			l[4]="010000000000u0000001"
			l[5]="01000011111111111111"
			l[6]="01000l100d0001000011"
			l[7]="010000100000000000z1"
			l[8]="0100000000000100u001"
			l[9]="01111111111111111111"
		End If
		If currentlevel = 1
			l = New String[10]
			' 0 - floor
			' 1 - wall
			' a - start position
			' z - end position
			' u - move up obstacle
			' d - move down obstacle
			l[0]="00000011111111000000"
			l[1]="000000101010d1000000"
			l[2]="00000010101001000000"
			l[3]="11111010d0d001011111"
			l[4]="10001110000001110001"
			l[5]="10a000000000000000z1"
			l[6]="10001110000001110001"
			l[7]="11111010101001011111"
			l[8]="0000001u1u1u01000000"
			l[9]="00000011111111000000"
		End If

		map = New Int[l[0].Length,l.GetSize(0)]
		dmap = New Int[l[0].Length,l.GetSize(0)]
		mapw = map.GetSize(0)
		maph = map.GetSize(1)
		tw = Float(sw)/Float(map.GetSize(0))
		th = Float(sh)/Float(map.GetSize(1))
		For Local y:Int=0 Until map.GetSize(1)
		For Local x:Int=0 Until map.GetSize(0)
			Local t:String=l[y].Mid(x,1)
			Select t
				Case "0"
					map[x,y] = 0
				Case "1"
					map[x,y] = 1
				Case "u","d","l","r"
					myobstacle.Push(New kobstacle(x*tw,y*th,tw/2,th/2,t))
				Case "a"
					startx = x
					starty = y
				Case "z"
					endx = x
					endy = y					
			End Select
		Next
		Next
		flooddistance(endx,endy,startx,starty)
	End Method
	Method flooddistance(sx:Int,sy:Int,ex:Int,ey:Int)
		Local dx:Stack<Int> = New Stack<Int>
		Local dy:Stack<Int> = New Stack<Int>
		Local dd:Stack<Int> = New Stack<Int>
		dx.Push(sx)
		dy.Push(sy)
		dmap[sx,sy] = 1
		Local x:Int,y:Int,d:Int
		Local mx:Int[]=New Int[](-1,0,1,0)
		Local my:Int[]=New Int[](0,-1,0,1)
		While dx.Length>0
			x = dx.Get(0)
			y = dy.Get(0)
			dx.Erase(0)
			dy.Erase(0)
			For Local i:Int=0 Until mx.Length
				Local x1:Int=x+mx[i]
				Local y1:Int=y+my[i]
				If x1<0 Or y1<0 Or x1>=mapw Or y1>=maph Then Continue
				If map[x1,y1] = 0 And dmap[x1,y1] = 0
					dx.Push(x1)
					dy.Push(y1)
					dmap[x1,y1] = dmap[x,y]+1
				End If
			Next
		Wend
	End Method
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until map.GetSize(1)
		For Local x:Int=0 Until map.GetSize(0)
			Select map[x,y]
				Case 0
					canvas.Color = Color.DarkGrey
				Case 1
					canvas.Color = Color.Grey
			End Select
			canvas.DrawRect(x*tw,y*th,tw+1,th+1)
		Next
		Next
		' draw the obstacles
		For Local i:Int=0 Until myobstacle.Length
			myobstacle.Get(i).draw(canvas)
		Next
'		' draw the agents
'		If myagent
		For Local i:Int=0 Until myagent.Length
			If completed = False
				myagent.Get(i).draw(canvas)
			Elseif completed = True				
				If myagent.Get(i).winner = True				
					myagent.Get(i).draw(canvas)
					
				End If
			End If
		Next
'		End If
		' Draw the distances
		If Keyboard.KeyDown(Key.Key1)
			canvas.Color=Color.Black
			For Local y:Int=0 Until dmap.GetSize(1)
			For Local x:Int=0 Until dmap.GetSize(0)
				canvas.DrawText(dmap[x,y],x*tw,y*th)
			Next
			Next	
		End If
	End Method
End Class

Global myworld:world

Class MyWindow Extends Window
	Field level:Int=4
	Method New()
		SeedRnd(Microsecs())
		myworld = New world(Width,Height,level)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		myworld.update()
		myworld.draw(canvas)
		
		'If myworld.completed
		If Keyboard.KeyReleased(Key.Space)
			'level+=1
			'If level>9999 Then level=1
			level = Rnd(1,9999)
			myworld = New world(Width,Height,level)
		End If
		'End If
		
		canvas.Color = Color.Red
		canvas.DrawText("Press space to Train new - (can take a while)",0,0)
		'canvas.DrawText(myworld.myagent.Length,0,20)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
