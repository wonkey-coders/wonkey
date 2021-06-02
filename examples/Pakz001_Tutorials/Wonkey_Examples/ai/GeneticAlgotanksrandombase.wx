#Import "<std>"
#Import "<mojo>"

' Tanks destroying a random base defended by turrets. Using the Genetic Algorithm.
'
' I want to run 1 or a group of tanks on one simulation at a time.
' I run a simulation a x amount of times and store the genes
' Then I select a new fittest brain and do some mutations and repeat.
'
' step 1 ; create x brains
' step 2 ; run brains
' step 3 ; find fittest and if completed end
' step 4 ; erase every brain except fittest
' step 5 ; create x brains from fittest 
' step 6 ; add instructions to brain
' step 7 ; mutate instructions in brains
' step 8 ; goto step 2

Using std..
Using mojo..

Global numtiles:Int=13

Enum tiles
	ground=0,wallver=1,wallhor=2
	wallverdestroyed=3,wallhordestroyed=4
	turret=5,turretdestroyed=6
	tree=7,treedestroyed=8
	capturepoint=9,startpoint=10,
	groundvariation=11,
	rockfloor=12
End Enum

Enum geneinst
	turnleft=1,turnright=2,moveforward=3,movebackward=4,
	stop=5
End Enum


Class ai
	Field tankimage:Image
	Field tankcanvas:Canvas
	'
	' Here we store a x amount of runs that we use
	' to select the fittest for a new run.
	Class brainhistory
		Field numbrains:Int
		Field deathstep:Int[] ' how close to target were we
		Field damagedone:Int[]
		Field damagetaken:Int[]
		Field genescom:Stack<Int>[]
		Field genesval:Stack<Int>[]
		Method New(numbrains:Int)
			Self.numbrains = numbrains
			'set up the genes
			genescom = New Stack<Int>[numbrains]
			genesval = New Stack<Int>[numbrains]
			For Local i:Int=0 Until numbrains
				genescom[i] = New Stack<Int>
				genesval[i] = New Stack<Int>
			Next
			' genetic algorithm variables
			damagedone = New Int[numbrains]
			deathstep = New Int[numbrains]			
			damagetaken = New Int[numbrains]
		End Method
		Method mutate()			
			For Local i:Int=0 Until numbrains
				Local st:Int=deathstep[i]-10
				If st<0 Then st=0
				For Local ii:Int=0 Until deathstep[i]
					If Rnd() < .1 Then 
						genescom[i].Set(ii,Rnd(0,6))
						genesval[i].Set(ii,10)
					End If
				Next
			Next
		End Method
		' Insert 5 random instructions
		Method insertrandominstructions()
			For Local ii:Int=0 Until 5
				For Local i:Int=0 Until numbrains
					genescom[i].Push(Rnd(0,6))
					genesval[i].Push(10)
				Next
			Next
		End Method		
	End Class
	Field mybrainhistory:Stack<brainhistory>
	
	
	Class brain
		'Global a:List<test>[] = New List<test>[10]
		Field numbrains:Int
		Field deathstep:Int[] ' how close to target were we
		Field damagedone:Int[]
		Field damagetaken:Int[]
		Field position:Int[]
		Field angle:Float[]
		Field kx:Float[],ky:Float[],kw:Float[],kh:Float[] 'xywidhtheight
		Field genescom:Stack<Int>[]
		Field genesval:Stack<Int>[]
		Method New(numbrains:Int,x:Int,y:Int)
			Self.numbrains = numbrains
			'set up the genes
			genescom = New Stack<Int>[numbrains]
			genesval = New Stack<Int>[numbrains]
			For Local i:Int=0 Until numbrains
				genescom[i] = New Stack<Int>
				genesval[i] = New Stack<Int>
			Next
			' position and width and height of 'tank' 
			kx = New Float[numbrains]
			ky = New float[numbrains]
			kw = New float[numbrains]
			kh = New float[numbrains]
			' genetic algorithm variables
			damagedone = New Int[numbrains]
			deathstep = New Int[numbrains]			
			damagetaken = New Int[numbrains]
			' position in the gene
			position = New Int[numbrains]
			' angle of the tank
			angle = New Float[numbrains]			
			' put the tanks on the map
			For Local i:Int=0 Until numbrains
				Self.kx[i] = x+(i*(myworld.tw*2))
				Self.ky[i] = y
				Self.kw[i] = myworld.tw / 3
				Self.kh[i] = myworld.th / 2
				angle[i] = 0
			Next									
		End Method
		' Insert 5 random instructions
		Method insertrandominstructions()
			For Local ii:Int=0 Until 5
				For Local i:Int=0 Until numbrains
					genescom[i].Push(Rnd(0,6))
					genesval[i].Push(10)
				Next
			Next
		End Method

		' Insert a instruction
		Method insertinstruction(in1:Int,in2:Int)
			'in1 is a command
			'in2 is the time/steps
			For Local i:Int=0 Until numbrains
				genescom[i].Push(in1)
				genesval[i].Push(in2)
			Next
		End Method
		'
		' Here we execute 1 step at position from the genes
		' start at 0 and at every step update the world
		' check collision with bullets(damage)
		' check collision with obstacles(collision)
		Method rungene(position:Int)
			Local i:Int=position
			For Local ii:Int=0 Until numbrains
			Select genescom[ii].Get(i)
				Case geneinst.stop
					Local val:Int=genesval[ii].Get(i)
					For Local i2:Int=0 Until val

					Next				
				Case geneinst.moveforward						
					Local val:Int=genesval[ii].Get(i)
					For Local i2:Int=0 Until val
						kx[ii] += Cos(-angle[ii])*1
						ky[ii] += Sin(-angle[ii])*1
					Next				
				Case geneinst.movebackward
					Local val:Int=genesval[ii].Get(i)
					For Local i2:Int=0 Until val
						kx[ii] -= Cos(-angle[ii])*1
						ky[ii] -= Sin(-angle[ii])*1
					Next				
				Case geneinst.turnleft
					Local val:Int=genesval[ii].Get(i)
					For Local i2:Int=0 Until val
						angle[ii]-=.05
					Next
				Case geneinst.turnright
					Local val:Int=genesval[ii].Get(i)
					For Local i2:Int=0 Until val
						angle[ii]+=.05
					Next
			End Select
			Next
		End Method
		Method draw(canvas:Canvas)			
			For Local i:Int=0 Until numbrains
				canvas.Color = Color.White
				canvas.DrawImage(myai.tankimage,kx[i],ky[i],angle[i])
			Next
		End Method
	End Class
	Field mybrain:brain
	Field numhistory:Int=200
	Field sx:Int=50,sy:Int=20,ex:Int,ey:Int 'start position and end position	
	Field numtanks:Int=5
	Method New()
		mybrain = New brain(numtanks,50,120)
		mybrainhistory = New Stack<brainhistory>
		createtankimage()
	End Method
	Method updateturrets()
		For Local i:Int=0 Until myworld.myturret.Length
			myworld.myturret.Get(i).update()
		Next
	End Method
	' create x amount of brains (copy from mybrain)
	Method createsetofbrains()
		mybrainhistory.Clear()
		For Local i:Int=0 Until numhistory
			' Copy the contents of the current brain into the 
			' brain history
			mybrainhistory.Push(New brainhistory(numtanks))
			For Local ii:Int=0 Until numtanks 
				mybrainhistory.Top.damagedone[ii] = mybrain.damagedone[ii]
				mybrainhistory.Top.damagetaken[ii] = mybrain.damagetaken[ii]
				mybrainhistory.Top.deathstep[ii] = mybrain.deathstep[ii]
				mybrainhistory.Top.numbrains = mybrain.numbrains
				For Local iii:Int= 0 Until mybrain.genescom[ii].Length
					mybrainhistory.Top.genescom[ii] = mybrain.genescom[ii]
					mybrainhistory.Top.genesval[ii] = mybrain.genesval[ii]
				Next
			Next
			' add a series of new random instructions
			mybrainhistory.Top.mutate()
			mybrainhistory.Top.insertrandominstructions()
		Next
	End Method
	Method createtankimage()
		tankimage = New Image(myworld.tw,myworld.th)
		tankimage.Handle = New Vec2f(0.5,0.5)
		tankcanvas = New Canvas(tankimage)
		tankcanvas.Clear(New Color(0,0,0,0))
		tankcanvas.Flush()
		tankcanvas.Color = Color.Red
		tankcanvas.DrawQuad(tankimage.Width,tankimage.Height/2+5,
							tankimage.Width,tankimage.Height/2-5,
							4,4,
							4,tankimage.Height-4)
		tankcanvas.Color = Color.Silver.Blend(Color.Grey,.5)
		tankcanvas.DrawOval(tankimage.Width/2-tankimage.Width/6,
							tankimage.Height/2-tankimage.Height/6,
							tankimage.Width/3,
							tankimage.Height/3)
		tankcanvas.Color = Color.Gold.Blend(Color.Grey,.5)
		tankcanvas.DrawRect(tankimage.Width/2,tankimage.Height/2,
							tankimage.Width/2,tankimage.Height/10)
		tankcanvas.Color = Color.White
		tankcanvas.DrawRect(tankimage.Width/1.1,tankimage.Height/2,
							tankimage.Width/1.5,tankimage.Height/10)

		tankcanvas.Color = Color.Brown.Blend(Color.Black,.5)
		tankcanvas.DrawLine(tankimage.Width,tankimage.Height/2-5,							
							4,4)
		tankcanvas.DrawLine(tankimage.Width,tankimage.Height/2+5,							
							4,tankimage.Height-5)
		tankcanvas.Flush()
	End Method
End Class

Class world
	' this is the turret class
	Class turret
		'turret x and y and width and height - in pixels
		Field kx:Int,ky:Int,kw:Int,kh:Int
		Field dist:Int=7 'what is their range
		Field angle:Float,targetangle:Float
		Field targettime:Int
		Field targetfound:Bool=False
		Method New(x:Int,y:Int,w:Int,h:Int)
			kx = x
			ky = y
			kw = w
			kh = h
			angle=0
		End Method
		Method update()
			' if no target then find target
			findtarget()
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
		End Method
		'
		' Find the closest target
		' Every 100 clicks check for change of position
		' or new closest target.
		Method findtarget()
			targettime-=1
			
			If targettime>0 Then Return
			targettime = 100
			targetfound=False
			' closest target angle.			
			Local closest:Int=999999
			For Local i:Int=0 Until myai.mybrain.numbrains
				Local x2:Int=myai.mybrain.kx[i]
				Local y2:Int=myai.mybrain.ky[i]
				Local d:Int=distance(kx,ky,x2,y2)
				If d<closest Then
					closest = d
					targetangle=getangle(kx,ky,x2,y2)					
					targetfound=True
				End If
			next
			
		End Method
		Method draw(canvas:Canvas)
			' Draw a circle around the turret which shows
			' his firing range .
			Local cx:Int=kx + kw/2
			Local cy:Int=ky + kh/2
			canvas.Color = New Color(0,0,0,0)
			canvas.OutlineMode = OutlineMode.Smooth
			canvas.OutlineWidth = 1
			canvas.OutlineColor = Color.Yellow
			canvas.DrawOval(cx-kw*dist,cy-kh*dist,kw*dist*2,kh*dist*2)
			' Draw the barrel
			' get the turret barrel angle
			' turret center x and y 
			Local tcx:Int=kx+kw/2
			Local tcy:Int=ky+kh/2			
			Local tx:Float,ty:Float
			tx = tcx+Cos(angle)*kw/1.5
			ty = tcy+Sin(angle)*kh/1.5

			canvas.Color = Color.Black
			canvas.LineWidth = 5
			canvas.DrawLine(tcx,tcy,tx,ty)

			canvas.Color = Color.DarkGrey
			canvas.LineWidth = 3
			canvas.DrawLine(tcx,tcy,tx,ty)

			canvas.Color = Color.White
			canvas.LineWidth = 1
			canvas.DrawLine(tcx,tcy,tx,ty)





''			canvas.LineWidth = 2
'			canvas.DrawLine(tcx,tcy,dx,dy)
		End Method
	   	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)   
	    	Return Abs(x2-x1)+Abs(y2-y1)   
	    End Function
		Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
			Return ATan2(y2-y1, x2-x1)
		End Function 	    
	End Class
	
	Field sw:Int,sh:Int,mw:Int,mh:Int,tw:Float,th:Float
	Field map:Int[,]
	Field dmap:Int[,]
	Field capturexy:Vec2i,startxy:Vec2i
	Field tileim:Image[] = New Image[numtiles]
	Field tilecan:Canvas[] = New Canvas[numtiles]
	Field myturret:Stack<turret> = New Stack<turret>
	Method New(sw:Int,sh:Int,mw:Int,mh:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		tw = Float(sw) / Float(mw)
		th = Float(sh) / Float(mh)
		map = New Int[mw,mh]
		dmap = New Int[mw,mh]
		createtiles()
		generatemap()
	End Method
	Method generatemap()
		SeedRnd(1)
		For Local i:Int=0 Until 20
			map[Rnd(mw),Rnd(mh)] = tiles.groundvariation
		next
		
		
		For Local y:Int= 10 To 20
		For Local x:Int=10 To 20
			map[x,y] = tiles.rockfloor
		Next
		Next
		For Local i:Int=0 Until 29
			map[15+Rnd(-6,7),15+Rnd(-6,7)]=tiles.rockfloor
		Next		
		
		For Local x:Int=0 Until 10
			map[10+x,10] = tiles.wallhor
		Next
		For Local y:Int=0 Until 10
			If Rnd()<.8
				map[20,10+y] = tiles.wallverdestroyed								
			Else
				map[20,10+y] = tiles.wallver
			End If
		Next
		map[20,10] = tiles.turret
		
		For Local i:Int=0 Until 20
			If Rnd()<.5 Then 
			map[Rnd(mw),Rnd(mh)] = tiles.tree
			Else
			map[Rnd(mw),Rnd(mh)] = tiles.treedestroyed
			End If
		Next



		
		map[10,10] = tiles.wallhor
		map[11,10] = tiles.wallhordestroyed
		map[10,10] = tiles.turretdestroyed
		map[10,11] = tiles.wallverdestroyed
		map[10,12] = tiles.wallver
		map[5,5] = tiles.treedestroyed
		map[4,5] = tiles.tree
		map[5,6] = tiles.tree
		map[10,13] = tiles.turret
		map[4,4] = tiles.tree
		'flooddistance(mw/2,mh/2,0,0)
		
		' initiate the turrets
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If map[x,y] = tiles.turret
				myturret.Push(New turret(x*tw,y*th,tw,th))
			End If
		Next
		Next
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
				If x1<0 Or y1<0 Or x1>=mw Or y1>=mh Then Continue
				If map[x1,y1] = tiles.ground And dmap[x1,y1] = 0
					dx.Push(x1)
					dy.Push(y1)
					dmap[x1,y1] = dmap[x,y]+1
				End If
			Next
		Wend
	End Method	
	Method createtiles()		
		For Local i:Int=0 Until numtiles			
			tileim[i] = New Image(tw+1,th+1)
			tilecan[i] = New Canvas(tileim[i])
			tilecan[i].Clear(Color.Black)
			tilecan[i].Flush()
			createtile(tilecan[i],0,0,i)
			tilecan[i].Flush()
		Next	
	End Method
	Method drawtile(canvas:Canvas,x:Float,y:Float,tile:Int)
		canvas.Color = Color.White
		canvas.DrawImage(tileim[tile],x,y)
	End Method
	Method createtile(canvas:Canvas,x:Int,y:Int,tile:Int)		
		Select tile
			Case tiles.ground
				canvas.Color = New Color(.78,.47,.23)
				canvas.DrawRect(x,y,tw+1,th+1)
				SeedRnd(1)
				For Local i:Int=0 Until tw*th/20
					If Rnd()<.5
					canvas.Color = New Color(.78,.47,.23).Blend(Color.Black,Rnd(0.1,.3))
					Else
					canvas.Color = New Color(.78,.47,.23).Blend(Color.White,Rnd(0.1,.3))
					Endif
					canvas.DrawPoint(x+Rnd(tw),y+Rnd(th))
					For Local y2:Int=-2 To 2
					For Local x2:Int=-2 To 2
					If Rnd()<.1
						canvas.DrawPoint(x+Rnd(tw)+x2,y+Rnd(th)+y2)
					End	if
					Next
					Next
					If Rnd()<.2
						canvas.DrawPoint(x+Rnd(tw)+1,y+Rnd(th)+1)
						canvas.DrawPoint(x+Rnd(tw),y+Rnd(th)+2)
					End if
				Next				
			Case tiles.groundvariation
				'canvas.Color = Color.Yellow.Blend(Color.Red,.5)
				'canvas.DrawRect(x,y,tw+1,th+1)
				'SeedRnd(1)
				drawtile(canvas,x,y,tiles.ground)
				SeedRnd(1)
				For Local i:Int=0 Until tw*th/20
					canvas.Color = Color.Yellow.Blend(Color.Brown,Rnd(0.1,.8))
					canvas.DrawPoint(x+Rnd(tw),y+Rnd(th))
				Next
			Case tiles.turret
				canvas.Color = Color.Grey.Blend(Color.White,.5)
				canvas.DrawRect(x,y,tw+1,th+1)
				canvas.Color = Color.Grey.Blend(Color.White,.8)
				canvas.DrawRect(x,y,tw/8,th)
				canvas.Color = Color.Grey.Blend(Color.Black,.5)
				canvas.DrawOval(x+tw/4-2,y+th/4-2,tw/2.5+4,th/2.5+4)
				canvas.Color = Color.Grey.Blend(Color.Yellow,.5)
				canvas.DrawOval(x+tw/4,y+th/4,tw/2.5,th/2.5)
			Case tiles.wallver
				
				createtile(canvas,x,y,tiles.rockfloor)
				
				canvas.Color = Color.Grey.Blend(Color.White,.5)
				canvas.DrawRect(x+tw/4,y,tw/2,th+1)		
				canvas.Color = Color.Grey.Blend(Color.White,.8)		
				canvas.DrawRect(x+tw/4,y,2,th+1)		
			Case tiles.wallhor
				createtile(canvas,x,y,tiles.rockfloor)
				canvas.Color = Color.Grey.Blend(Color.White,.5)
				canvas.DrawRect(x,y+th/4,tw+1,th/2)
				canvas.Color = Color.Grey.Blend(Color.White,.8)		
				canvas.DrawRect(x,y+th/4,tw+1,2)
				canvas.Color = Color.Grey.Blend(Color.White,.1)		
				canvas.DrawRect(x,y+th/1.5,tw+1,th/4)
			Case tiles.treedestroyed
				createtile(canvas,x,y,tiles.ground)
				SeedRnd(1)
				For Local i:Int=0 Until 14
					If Rnd()<.6
						canvas.Color = Color.Green.Blend(Color.Brown,Rnd(0.1,0.3))
					Else
						If Rnd()<.5
							canvas.Color = Color.Brown.Blend(Color.Black,Rnd(0.1,1))
						Else
							canvas.Color = Color.Green.Blend(Color.Black,Rnd(0.1,1))
						End If
					End If
					canvas.DrawRect(x+Rnd(tw-tw/5),y+Rnd(th-th/5),Rnd(2,tw/5),Rnd(2,th/5))
					If Rnd()<.4 Then
						Local ax:Float=x+Rnd(tw-tw/5)
						Local ay:Float=y+Rnd(th-th/5)
						canvas.DrawQuad(ax,ay,ax+Rnd(10),ay+Rnd(10),ax+Rnd(10),ay+Rnd(10),ax+Rnd(10),ay+Rnd(10))
					End If
				Next
								

			Case tiles.turretdestroyed
				createtile(canvas,x,y,tiles.rockfloor)
				SeedRnd(1)
				For Local i:Int=0 Until 14
					If Rnd()<.5
						canvas.Color = Color.Grey.Blend(Color.Brown,Rnd(0.1,0.3))
					Else
						If Rnd()<.5
							canvas.Color = Color.Grey.Blend(Color.Black,Rnd(0.1,1))
						Else
							canvas.Color = Color.Grey.Blend(Color.Yellow,Rnd(0.1,1))
						End If
					End If
					canvas.DrawRect(x+Rnd(tw-tw/5),y+Rnd(th-th/5),Rnd(2,tw/5),Rnd(2,th/5))
					If Rnd()<.4 Then
						Local ax:Float=x+Rnd(tw-tw/5)
						Local ay:Float=y+Rnd(th-th/5)
						canvas.DrawQuad(ax,ay,ax+Rnd(10),ay+Rnd(10),ax+Rnd(10),ay+Rnd(10),ax+Rnd(10),ay+Rnd(10))
					End If
				Next
								
			Case tiles.wallhordestroyed
				createtile(canvas,x,y,tiles.rockfloor)
				SeedRnd(1)
				For Local i:Int=0 Until 19
					If Rnd()<.5
						canvas.Color = Color.Grey.Blend(Color.Brown,Rnd(0.3,0.6))
					Else
						If Rnd()<.5
							canvas.Color = Color.Grey.Blend(Color.Black,Rnd(0.3,1))
						Else
							canvas.Color = Color.Grey.Blend(Color.White,Rnd(0.3,1))
						End If
					End If
					canvas.DrawRect(x+Rnd(tw-tw/3),y+Rnd(th/5,th-th/3),Rnd(2,tw/6),Rnd(2,th/6))		
				Next
			Case tiles.wallverdestroyed
				createtile(canvas,x,y,tiles.rockfloor)
				SeedRnd(1)
				For Local i:Int=0 Until 19
					If Rnd()<.5
						canvas.Color = Color.Grey.Blend(Color.Brown,Rnd(0.3,0.3))
					Else
						If Rnd()<.5
							canvas.Color = Color.Grey.Blend(Color.Black,Rnd(0.3,1))
						Else
							canvas.Color = Color.Grey.Blend(Color.White,Rnd(0.3,1))
						End If
					End If
					canvas.DrawRect(x+Rnd(tw/3,tw-tw/3),y+Rnd(0,th-th/3),Rnd(2,tw/6),Rnd(2,th/6))		
				Next

			Case tiles.tree
				createtile(canvas,x,y,tiles.ground)
				canvas.Color = Color.Green.Blend(Color.Black,.7)
				canvas.DrawOval(x+tw/5,y+th/5,tw/1.25,th/1.25)				
				canvas.Color = Color.Green.Blend(Color.Red,.2)
				canvas.DrawOval(x+tw/7,y+th/7,tw/1.25,th/1.25)
				canvas.Color = Color.Green.Blend(Color.White,.2)
				canvas.DrawOval(x+tw/4,y+th/4,tw/2,th/3.25)
			Case tiles.rockfloor
				canvas.Color = New Color(.5,.5,.4)'main
				canvas.DrawRect(x,y,tw+1,th+1)
				canvas.Color = New Color(.8,.8,.55)'light
				SeedRnd(1)
				Local x1:Float=x+tw/3
				Local y1:Float=y+th/1.24
				Local angle:Float=0
				For Local i:Int=0 Until th
					x1-=Cos(angle)*1
					y1-=Sin(angle)*1
					If i<th/2 Then 
						angle+=Rnd(0.1,.3)
					Else
						angle-=Rnd(0.1,.3)
					End if
					If Rnd()<.7 Then canvas.DrawPoint(x1,y1)
					If Rnd()<.2 Then 
						canvas.Color = New Color(.8,.8,.55).Blend(Color.Black,Rnd(.5,.71))'light
						canvas.DrawPoint(x1+Rnd(-2,2),y1+Rnd(-2,2))
						If Rnd()<.5
							canvas.DrawPoint(x1+Rnd(-2,2),y1+Rnd(-2,2))
						Endif
						canvas.Color = New Color(.8,.8,.55).Blend(Color.Black,Rnd(.5,.71))'light
					End If
				Next				
				
				canvas.Color = New Color(.3,.3,.25)'dark
				x1=x+tw/2
				y1=y
				angle=0
				For Local i:Int=0 Until th
					x1+=Cos(angle)*1
					y1+=Sin(angle)*1
					If i<th/2
						angle+=Rnd(0.1,.3)
					Else
						angle-=Rnd(0.1,.3)
					End If
					canvas.DrawPoint(x1,y1)
					If Rnd()<.5 Then canvas.DrawPoint(x1+Rnd(-2,2),y1)
				Next

				canvas.Color = New Color(.6,.43,.43)'brownish
				For Local i:Int=0 Until 6
					canvas.DrawRect(x+Rnd(tw),y+Rnd(th),Rnd(4),Rnd(4))
				Next

				'random spots
				canvas.Color = New Color(.3,.3,.25)'dark
				For Local i:Int=0 Until 2
				x1=x+Rnd(tw/3,tw-tw/3)
				y1=y+Rnd(th/3,th-th/3)
				'dark rock spots
				For Local ii:Int = 0 Until 5
					canvas.DrawRect(x1+Rnd(-6,6),y1+Rnd(-4,4),Rnd(3),Rnd(3))
				Next
				Next
				
				canvas.Color = New Color(.8,.8,.55)'light
				For Local i:Int=0 Until 1
				x1=x+Rnd(tw/3,tw-tw/3)
				y1=y+Rnd(th/5,th-th/4)
				'dark rock spots
				For Local ii:Int = 0 Until 3
					canvas.DrawRect(x1+Rnd(-6,6),y1+Rnd(-4,4),Rnd(3),Rnd(3))
				Next
				Next
				
				'noise
				For Local i:Int=0 Until tw+th
					canvas.Color = New Color(.8,.8,.55).Blend(Color.Black,Rnd(.3,.8))'light
					canvas.DrawPoint(Rnd(x,x+tw),Rnd(y,y+th))
				Next
		End Select
		SeedRnd(Microsecs())
	End Method
	Method drawmap(canvas:Canvas)
		' draw the tiles 
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			drawtile(canvas,x*tw,y*th,map[x,y])
			canvas.Color = Color.Black
			' draw the distance map
			If Keyboard.KeyDown(Key.LeftShift)
				canvas.DrawText(dmap[x,y],x*tw,y*th)
			End If
		Next
		Next
		' draw the turrets
		For Local i:Int=0 Until myturret.Length
			myturret.Get(i).draw(canvas)
		Next
	End Method
End Class

Global myworld:world
Global myai:ai


Class MyWindow Extends Window
	Field mapwidth:Int=25,mapheight:Int=25
	Field pos:Int=0
	Method New()
		
		myworld = New world(Width,Height,mapwidth,mapheight)
		myai = New ai()
		
		
		myai.mybrain.insertrandominstructions()
		myai.mybrain.insertrandominstructions()
		myai.mybrain.insertrandominstructions()		
		SeedRnd(Microsecs())
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		myworld.drawmap(canvas)

		myai.mybrain.draw(canvas)

		myai.updateturrets()		
			
		'If Keyboard.KeyReleased(Key.Space)
						
			If Rnd()<.3
			If pos < myai.mybrain.genescom[0].Length Then 
				myai.mybrain.rungene(pos)
			Else
				pos=0
			End If
			pos+=1
			End If
		'End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
