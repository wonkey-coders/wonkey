#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global mapwidth:Int=200,mapheight:Int=200
Global numpoints:Int=20

Class MyWindow Extends Window
	
	Field nm:Int
	
	Field point:Vec2i[]
	Field pointvisited:Bool[]
	Field map:Int[,]

	Method New()
		newmap()
	End Method
			
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		nm+=1
		If nm>500 Then newmap() ; nm=0
		'
		drawmap(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	

	'
	' Here we find edges. We do this by looping through
	' the entire map and if we are at a walkable tile we check for unwalkables.
	' If so then we have a edge situation and can place the edge tile(2)
	Method blurmap()
		For Local y:Int=4 Until mapheight-4
		For Local x:Int=4 Until mapwidth-4
			If map[x,y] = 1	And Rnd()<.3
				For Local y2:Int=-1 To 1
				For Local x2:Int=-1 To 1
					If map[x+x2,y+y2] = 0 Then
						map[x,y] = 2
						Exit						
					End If
				Next
				Next				
			End If
		Next
		Next
	End Method

	'
	' Hre we create the map. We create a series of random points on the map.
	' We take one random point and then choose one unvisited other point. We then
	' tunnel towards this unvisited point. We make sure we have a brush point while
	' tunneling that can be of changing size. We sometimes wonder of the direction to 
	' create a bit of a wavy line.
	'
	Method newmap()
		SeedRnd(Microsecs())
		numpoints=Rnd(6,30)
		map = New Int[mapwidth,mapheight]
		point = New Vec2i[numpoints]
		For Local i:Int=0 Until point.GetSize(0)
			point[i].y = Rnd(8,mapheight-8)
			point[i].x = Rnd(8,mapwidth-8)
		Next
		pointvisited = New Bool[numpoints]
		'
		Local exitloop:Bool=False
		While exitloop=False			
			' pick a random point and connect it to 
			' a unconnected point
			Local p1:Int=Rnd(numpoints)
			Local p2:Int
			Local exitloop2:Bool=False
			While exitloop2=False
				p2 = Rnd(numpoints)
				If pointvisited[p2] = False Then 
					exitloop2 = True
					pointvisited[p2] = True
				End If
			Wend
			' Tunnel point1 to point 2
			'
			Local angle:Float=getangle(point[p1].x,point[p1].y,point[p2].x,point[p2].y)
			Local tx:Float=point[p1].x,ty:Float=point[p1].y
			Local cnt:Int,cnt2:Int
			Local m2:Float
			Local phase1:Bool=False
			Local s1:Int=1,s2:Int=1
			While distance(tx,ty,point[p2].x,point[p2].y) > 2
				
				cnt+=1
				If distance(tx,ty,point[p2].x,point[p2].y) > 20 And cnt>10 And phase1=False Then
					angle+=Rnd(-1,1)
					cnt=0		
					phase1=True	
					Elseif distance(tx,ty,point[p2].x,point[p2].y) < 20					
					phase1=False
				End If			
				If phase1=True Then cnt2+=1
				If cnt2>5 Then phase1=False;cnt2=0;cnt=0
				If phase1=False Then angle=getangle(tx,ty,point[p2].x,point[p2].y)
			
				
				tx+=Cos(angle)
				ty+=Sin(angle)
				
				If Rnd()<.05 Then s1=Rnd(1,4);s2=Rnd(1,4)
				For Local y:Int=-s1 To s2
				For Local x:Int=-s1 To s2
					If tx>8 And tx<mapwidth-8 And ty>8 And ty<mapheight-8
					map[tx+x,ty+y] = 1
					End If
				Next
				Next
			'Next
			Wend
			
			'
			exitloop=True
			For Local i:Int=0 Until pointvisited.GetSize(0)
				If pointvisited[i] = False Then
					exitloop=False
				End If
			Next
			
		Wend
		'
		blurmap()
	End Method
	
	'
	' Here we draw the map on the canvas. The tilewidth and height are
	' based on the canvas size and map width and height so everything fills
	' the sceen.
	'
	Method drawmap(canvas:Canvas)
		Local tw:Float=(Float(Width)/Float(mapwidth))
		Local th:Float=(Float(Height)/Float(mapheight))
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If map[x,y] = 1
				canvas.Color = Color.White
				canvas.DrawRect(Float(x)*tw,Float(y)*th,tw,th)
			End If
			If map[x,y] = 2
				canvas.Color = Color.Grey
				canvas.DrawRect(Float(x)*tw,Float(y)*th,tw,th)
			End If

		Next
		Next
	End Method
	
End	Class


'' Couple of helper functions. Manhattan distance and get angle between two points.
    Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
    Return Abs(x2-x1)+Abs(y2-y1)   
    End Function
	' Return the angle from - to in float
	Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function	    
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
