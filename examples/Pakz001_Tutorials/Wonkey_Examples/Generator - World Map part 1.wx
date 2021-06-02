#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class world
	Field mapwidth:Int,mapheight:Int
	Field map:Int[,]
	Field tilewidth:Float,tileheight:Float
	Field tileim:Image[] = New Image[100]
	Field tilecan:Canvas[] = New Canvas[100]
	Method New(mapwidth:Int,mapheight:Int,tilewidth:Float,tileheight:Float)
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		map = New Int[mapwidth,mapheight]
		Self.tilewidth = tilewidth
		Self.tileheight = tileheight
		generatetiles()
	End Method
	Method draw(canvas:Canvas)
		'0 grass tile
		'1 coast left side
		'2 coast right side
		'3 coast bottom side
		'4 coast top side
		'  coast corners
		'9 snow tile
		'10 snow coast left
		'11 snow coast right
		'12 snow coast bottom
		'13 snow coast top
		'14  snow coast corners
		'15
		'16
		'17
		'18 snow edge grass left
		'19 snow edge grass right
		'20 snow edge grass bottom
		'21 snow edge grass top
		'22
		'23
		'24
		'25
		'26 grass edge snow left
		'27 grass edge snow right
		'28 grass edge snow bottom
		'29 grass edge snow top
		
		'grass and shores
		canvas.DrawImage(tileim[0],320,64,0,2,2)
		canvas.DrawImage(tileim[1],320+tilewidth*2,64,0,2,2)
		canvas.DrawImage(tileim[2],320-tilewidth*2,64,0,2,2)
		canvas.DrawImage(tileim[3],320,64-tileheight*2,0,2,2)
		canvas.DrawImage(tileim[4],320,64+tileheight*2,0,2,2)

		'snow and shores
		canvas.DrawImage(tileim[9],320,264,0,2,2)
		canvas.DrawImage(tileim[10],320+tilewidth*2,264,0,2,2)
		canvas.DrawImage(tileim[11],320-tilewidth*2,264,0,2,2)
		canvas.DrawImage(tileim[12],320,264-tileheight*2,0,2,2)
		canvas.DrawImage(tileim[13],320,264+tileheight*2,0,2,2)
		

		For Local y:Int=0 To 2
		For Local x:Int=0 To 2
			canvas.DrawImage(tileim[0],0+x*tilewidth*2,0+y*tileheight*2,0,2,2)
			canvas.DrawImage(tileim[9],0+x*tilewidth*2,200+y*tileheight*2,0,2,2)
		Next
		Next
		
		'snow edges
		canvas.DrawImage(tileim[9],tilewidth*2,64,0,2,2)
		canvas.DrawImage(tileim[18],tilewidth*2+tilewidth*2,64,0,2,2)
		canvas.DrawImage(tileim[19],tilewidth*2-tilewidth*2,64,0,2,2)
		canvas.DrawImage(tileim[20],tilewidth*2,64-tilewidth*2,0,2,2)
		canvas.DrawImage(tileim[21],tilewidth*2,64+tilewidth*2,0,2,2)
		
		'grass inside snow edges
		canvas.DrawImage(tileim[0],tilewidth*2,264,0,2,2)
		canvas.DrawImage(tileim[26],tilewidth*2+tilewidth*2,264,0,2,2)
		canvas.DrawImage(tileim[27],tilewidth*2-tilewidth*2,264,0,2,2)
		canvas.DrawImage(tileim[28],tilewidth*2,264-tilewidth*2,0,2,2)
		canvas.DrawImage(tileim[29],tilewidth*2,264+tilewidth*2,0,2,2)

	End Method
	Method generatetiles()
		For Local i:Int=0 Until 100
			tileim[i] = New Image(tilewidth,tileheight)
			tileim[i].Handle = New Vec2f(0,0)
			tilecan[i] = New Canvas(tileim[i])
			tilecan[i].Clear(Color.Blue)
			tilecan[i].Flush()
		Next
		tilecan[0].Clear(Color.Green.Blend(Color.Black,.5))
		generateshores()
		generategrass()
		generatesnow()
		generatesnowshores()
		generatesnowedgegrass()
		generategrassedgesnow()
	End Method
	Method generategrassedgesnow()
		'26
		'copy grass tiles into snow edge grass tiles
		For Local i:Int=26 Until 26+8
			tilecan[i].DrawImage(tileim[9],0,0)
			tilecan[i].Flush()
		Next


		' grass left side of snow
	
		Local m:Int[,] = New Int[tilewidth,tileheight]
		Local t:Int=26
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/4
			m[0,Rnd(tileheight)] = 1
		Next		
	
		' Grow the snow
		For Local i:Int=0 Until tilewidth*tileheight*4
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
	
		' create the shade
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth-1
			If m[x,y] = 1 And m[x+1,y] = 0
				m[x,y] = 2
				m[x+1,y] = 3
			End If
		Next
		Next		
	
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				If Rnd()<.2 Then
					tilecan[t].Color = Color.Green.Blend(Color.Black,.8)
				Else
					tilecan[t].Color = Color.Green.Blend(Color.Black,.4)
				End If
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If
	
				tilecan[t].DrawPoint(x,y)
		Next
		Next
	
		tilecan[t].Flush()


		' grass right side of snow
	
		m= New Int[tilewidth,tileheight]
		t=27
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/4
			m[tilewidth-1,Rnd(tileheight)] = 1
		Next		
	
		' Grow the grass
		For Local i:Int=0 Until tilewidth*tileheight*4
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
	
		' create the shade
		For Local y:Int=0 Until tileheight
		For Local x:Int=1 Until tilewidth
			If m[x,y] = 1 And m[x-1,y] = 0
				m[x,y] = 2
				m[x-1,y] = 3
			End If
		Next
		Next		
	
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				If Rnd()<.2 Then
					tilecan[t].Color = Color.Green.Blend(Color.Black,.8)
				Else
					tilecan[t].Color = Color.Green.Blend(Color.Black,.4)
				End If
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If
	
				tilecan[t].DrawPoint(x,y)
		Next
		Next
	
		tilecan[t].Flush()


		' grass bottom side of snow
	
		m= New Int[tilewidth,tileheight]
		t=28
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/4
			m[Rnd(tilewidth),tileheight-1] = 1
		Next		
	
		' Grow the grass
		For Local i:Int=0 Until tilewidth*tileheight*4
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
	
		' create the shade
		For Local y:Int=1 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 1 And m[x,y-1] = 0
				m[x,y] = 2
				m[x,y-1] = 3
			End If
		Next
		Next		
	
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				If Rnd()<.2 Then
					tilecan[t].Color = Color.Green.Blend(Color.Black,.8)
				Else
					tilecan[t].Color = Color.Green.Blend(Color.Black,.4)
				End If
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If
	
				tilecan[t].DrawPoint(x,y)
		Next
		Next
	
		tilecan[t].Flush()



		' grass top side of snow
	
		m= New Int[tilewidth,tileheight]
		t=29
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/4
			m[Rnd(tilewidth),0] = 1
		Next		
	
		' Grow the grass
		For Local i:Int=0 Until tilewidth*tileheight*4
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
	
		' create the shade
		For Local y:Int=0 Until tileheight-1
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 1 And m[x,y+1] = 0
				m[x,y] = 2
				m[x,y+1] = 3
			End If
		Next
		Next		
	
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				If Rnd()<.2 Then
					tilecan[t].Color = Color.Green.Blend(Color.Black,.8)
				Else
					tilecan[t].Color = Color.Green.Blend(Color.Black,.4)
				End If
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If
	
				tilecan[t].DrawPoint(x,y)
		Next
		Next
	
		tilecan[t].Flush()


	End Method
	Method generatesnowedgegrass()
		'18
		'copy grass tiles into snow edge grass tiles
		For Local i:Int=18 Until 18+8
			tilecan[i].DrawImage(tileim[0],0,0)
			tilecan[i].Flush()
		Next
		'
		
		' SNow left side of
		
		Local m:Int[,] = New Int[tilewidth,tileheight]
		Local t:Int=18
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/5
			m[0,Rnd(tileheight)] = 1
		Next		
		
		' Grow the snow
		For Local i:Int=0 Until tilewidth*tileheight*5
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
		
		' create the shade
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth-1
			If m[x,y] = 1 And m[x+1,y] = 0
				m[x,y] = 2
				m[x+1,y] = 3
			End If
		Next
		Next		
		
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				tilecan[t].Color = Color.White
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.White.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If

				tilecan[t].DrawPoint(x,y)
		Next
		Next
		
		tilecan[t].Flush()




		' SNow Right side of
		
		m = New Int[tilewidth,tileheight]
		t=19
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/5
			m[tilewidth-1,Rnd(tileheight)] = 1
		Next		
		
		' Grow the snow
		For Local i:Int=0 Until tilewidth*tileheight*5
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-1,2)
			Local ny:Int=y+Rnd(-1,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
		
		' create the shade
		For Local y:Int=0 Until tileheight-1
		For Local x:Int=tilewidth-1 To 1 Step -1
			If m[x,y] = 1 And m[x-1,y] = 0
				m[x,y] = 2
				m[x-1,y] = 3
			End If
		Next
		Next		
		
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				tilecan[t].Color = Color.White
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.White.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If

				tilecan[t].DrawPoint(x,y)
		Next
		Next
		
		tilecan[t].Flush()



		' SNow Bottom side of
		
		m = New Int[tilewidth,tileheight]
		t=20
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/5
			m[Rnd(tilewidth),tileheight-1] = 1
		Next		
		
		' Grow the snow
		For Local i:Int=0 Until tilewidth*tileheight*5
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-1,2)
			Local ny:Int=y+Rnd(-1,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
		
		' create the shade
		For Local y:Int=0 Until tileheight-1
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 1 And m[x,y+1] = 0
				m[x,y] = 2
				m[x,y+1] = 3
			End If
		Next
		Next		
		
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				tilecan[t].Color = Color.White
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.White.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If

				tilecan[t].DrawPoint(x,y)
		Next
		Next
		
		tilecan[t].Flush()


		' SNow top side of
		
		m = New Int[tilewidth,tileheight]
		t=21
		' Create initial snow grows
		For Local i:Int=0 Until tilewidth+tileheight/5
			m[Rnd(tilewidth),0] = 1
		Next		
		
		' Grow the snow
		For Local i:Int=0 Until tilewidth*tileheight*5
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			If m[x,y] = 1
				If nx<0 Or ny<0 Or nx>=tilewidth Or ny>=tileheight Then Continue
					m[nx,ny] = 1
			End If
		Next
		
		' create the shade
		For Local y:Int=tileheight-1 Until 1 Step -1
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 1 And m[x,y-1] = 0
				m[x,y] = 2
				m[x,y-1] = 3
			End If
		Next
		Next		
		
		' create the image		
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1 Then 
				tilecan[t].Color = Color.White
			End If
			If m[x,y] = 2 Then 				
				tilecan[t].Color = Color.White.Blend(Color.Black,.5)
			End If
			If m[x,y] = 3 Then 				
				tilecan[t].Color = New Color(0,.5,0,.5)
			End If
			
			tilecan[t].DrawPoint(x,y)
		Next
		Next
		
		tilecan[t].Flush()



	End Method
	Method generatesnowshores()
		Local left:Int=0
		Local right:Int=tilewidth
		Local top:Int=0
		Local bottom:Int=tileheight
		Local y:Float=0
		Local x:Float=0
		Local a:Float=Pi/2
		Local c:Float=0
		Local t:Int=10'tile
		While y<bottom
			' draw the shore
			For Local z:Int=0 To x
				tilecan[t].Color = Color.White
				tilecan[t].DrawPoint(z,y)
			Next
			'Left to right sand up not including sea
			tilecan[t].Color = Color.White.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.1,.4))
			tilecan[t].DrawPoint(x+1,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.6,1))
			tilecan[t].DrawPoint(x+2,y)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x+3,y)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x+4,y)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x+5,y)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If y<7 Or y>bottom-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If y<7 Or y>bottom-7
				If x<left Then x+=1
				If x>left Then x-=1
			endif
			If x<0 Then x=0
		Wend
		tilecan[t].Flush()

		'shore on the right side 		
		left=0
		right=tilewidth
		top=0
		bottom=tileheight
		y=0
		x=right
		a=Pi/2
		c=0
		t=11'tile
		While y<bottom
			' draw the shore
			For Local z:Int=right To x Step -1
				tilecan[t].Color = Color.White
				tilecan[t].DrawPoint(z,y)
			Next
			'right to left
			tilecan[t].Color = Color.White.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.1,.4))
			tilecan[t].DrawPoint(x-1,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.6,1))
			tilecan[t].DrawPoint(x-2,y)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x-3,y)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x-4,y)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x-5,y)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If y<7 Or y>bottom-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If y<7 Or y>bottom-7
				If x<right Then x+=1
				If x>right Then x-=1
			endif
			If x>right Then x=right
		Wend
		tilecan[t].Flush()

		'shore on the bottom side 		
		left=0
		right=tilewidth
		top=0
		bottom=tileheight
		y=bottom
		x=0
		a=0
		c=0
		t=12'tile
		Local cnt:Int=0
		While x<right
			cnt+=1
			If cnt>10000 Then Exit
			' draw the shore
			For Local z:Int=bottom To y Step -1
				tilecan[t].Color = Color.White
				tilecan[t].DrawPoint(x,z)
			Next
			'bottom to top
			tilecan[t].Color = Color.White.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.1,.4))
			tilecan[t].DrawPoint(x,y-1)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.6,1))
			tilecan[t].DrawPoint(x,y-2)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x,y-3)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x,y-4)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x,y-5)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If x<7 Or x>right-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If x<7 Or x>right-7
				If y>bottom Then y-=1
				If y<bottom Then y+=1
			endif
			If y>bottom Then y=bottom
		Wend
		tilecan[t].Flush()


		'shore on the top side 		
		left=0
		right=tilewidth
		top=0
		bottom=tileheight
		y=top
		x=0
		a=0
		c=0
		t=13'tile
		cnt=0
		While x<right
			cnt+=1
			If cnt>10000 Then Exit
			' draw the shore
			For Local z:Int=0 To y
				tilecan[t].Color = Color.White
				tilecan[t].DrawPoint(x,z)
			Next
			'Top to bottom
			tilecan[t].Color = Color.White.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.1,.4))
			tilecan[t].DrawPoint(x,y+1)
			tilecan[t].Color = Color.Brown.Blend(Color.White,Rnd(.6,1))
			tilecan[t].DrawPoint(x,y+2)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x,y+3)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x,y+4)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x,y+5)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If x<7 Or x>right-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If x<7 Or x>right-7
				If y>top Then y-=1
				If y<top Then y+=1
			endif
			If y<0 Then y=0
		Wend
		tilecan[t].Flush()




	End Method
	Method generatesnow()
		tilecan[9].Clear(Color.White)
		tilecan[9].Flush()
	End Method
	Method generategrass()
		Local m:Int[,] = New Int[tilewidth,tileheight]
		Local maxgrow:Int=tilewidth*tileheight/1.5
		Local cg:Int=0
		For Local i:Int=0 Until tilewidth+tileheight/10
			m[Rnd(1,tilewidth-1),Rnd(1,tileheight-1)]=Rnd(1,3)
		Next
		m[0,Rnd(1,tileheight-2)] = 1
		m[tilewidth-1,Rnd(1,tileheight-2)] = 1
		m[Rnd(1,tilewidth-2),0] = 1
		m[Rnd(1,tilewidth-2),tileheight-1] = 1

		While cg<maxgrow
			' add grow
			Local x:Int=Rnd(1,tilewidth-1)
			Local y:Int=Rnd(1,tileheight-1)
			If m[x,y] > 0
				m[x+Rnd(-2,2),y+Rnd(-2,2)] = m[x,y]
			End If
			' how much grow is there
			cg=0
			For Local a:Int=0 Until tileheight
			For Local b:Int=0 Until tilewidth
				If m[a,b] <> 0 Then cg+=1
			Next
			Next
		Wend
		
		'make seamless
		'
		' Loop the edges and on random copy pixels to the other side
		'
		'
		For Local x:Int=0 Until tilewidth
		For Local y:Int=0 Until 5
			If m[x,y] >= 0
				If Rnd()<.3
					m[x,tileheight-y-1] = m[x,y]
				End If
			End if
			If m[tilewidth-1-x,y] > 0
				If Rnd()<.3
					m[tilewidth-1-x,tileheight-y-1] = m[tilewidth-1-x,y]
				End If
			End if			
		Next
		Next
		For Local x:Int=0 Until 5
		For Local y:Int=0 Until tileheight
			If m[x,y] >= 0
				If Rnd()<.3					
					m[tilewidth-x-1,y] = m[x,y]
				End If
			End If
			If m[x,tileheight-1-y] > 0
				If Rnd()<.3
					m[tilewidth-x-1,y] = m[x,tileheight-1-y]
				End If
			End If
		Next
		Next		
		
		
		For Local a:Int=0 Until tileheight
		For Local b:Int=0 Until tilewidth			
			If m[a,b] = 1 Then 
				tilecan[0].Color = Color.Green.Blend(Color.Black,.4)
			Else
				tilecan[0].Color = Color.Green.Blend(Color.Black,.6)
			Endif
			If m[a,b] <> 0 Then tilecan[0].DrawPoint(a,b)
		Next
		Next
		tilecan[0].Flush()
	End Method
	'tile 
	'1-shore on left side of tile
	'2-shore of right side of tile
	'3-
	'4-
	Method generateshores()
		'shore on the right side 		
		Local left:Int=0
		Local right:Int=tilewidth
		Local top:Int=0
		Local bottom:Int=tileheight
		Local y:Float=0
		Local x:Float=0
		Local a:Float=Pi/2
		Local c:Float=0
		Local t:Int=1'tile
		While y<bottom
			' draw the shore
			For Local z:Int=0 To x
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
				tilecan[t].DrawPoint(z,y)
			Next
			'Left to right sand up not including sea
			tilecan[t].Color = Color.Brown.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.1)
			tilecan[t].DrawPoint(x+1,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.8)
			tilecan[t].DrawPoint(x+2,y)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x+3,y)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x+4,y)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x+5,y)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If y<7 Or y>bottom-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If y<7 Or y>bottom-7
				If x<left Then x+=1
				If x>left Then x-=1
			endif
			If x<0 Then x=0
		Wend
		tilecan[t].Flush()

		'shore on the right side 		
		left=0
		right=tilewidth
		top=0
		bottom=tileheight
		y=0
		x=right
		a=Pi/2
		c=0
		t=2'tile
		While y<bottom
			' draw the shore
			For Local z:Int=right To x Step -1
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
				tilecan[t].DrawPoint(z,y)
			Next
			'Left to right sand up not including sea
			tilecan[t].Color = Color.Brown.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.1)
			tilecan[t].DrawPoint(x-1,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.8)
			tilecan[t].DrawPoint(x-2,y)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x-3,y)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x-4,y)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x-5,y)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If y<7 Or y>bottom-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If y<7 Or y>bottom-7
				If x<right Then x+=1
				If x>right Then x-=1
			endif
			If x>right Then x=right
		Wend
		tilecan[t].Flush()

		'shore on the bottom side 		
		left=0
		right=tilewidth
		top=0
		bottom=tileheight
		y=bottom
		x=0
		a=0
		c=0
		t=3'tile
		Local cnt:Int=0
		While x<right
			cnt+=1
			If cnt>10000 Then Exit
			' draw the shore
			For Local z:Int=bottom To y Step -1
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
				tilecan[t].DrawPoint(x,z)
			Next
			'Left to right sand up not including sea
			tilecan[t].Color = Color.Brown.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.1)
			tilecan[t].DrawPoint(x,y-1)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.8)
			tilecan[t].DrawPoint(x,y-2)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x,y-3)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x,y-4)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x,y-5)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If x<7 Or x>right-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If x<7 Or x>right-7
				If y>bottom Then y-=1
				If y<bottom Then y+=1
			endif
			If y>bottom Then y=bottom
		Wend
		tilecan[t].Flush()


		'shore on the top side 		
		left=0
		right=tilewidth
		top=0
		bottom=tileheight
		y=top
		x=0
		a=0
		c=0
		t=4'tile
		cnt=0
		While x<right
			cnt+=1
			If cnt>10000 Then Exit
			' draw the shore
			For Local z:Int=0 To y
				tilecan[t].Color = Color.Green.Blend(Color.Black,.5)
				tilecan[t].DrawPoint(x,z)
			Next
			'Left to right sand up not including sea
			tilecan[t].Color = Color.Brown.Blend(Color.Black,.3)
			tilecan[t].DrawPoint(x,y)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.1)
			tilecan[t].DrawPoint(x,y+1)
			tilecan[t].Color = Color.Brown.Blend(Color.White,.8)
			tilecan[t].DrawPoint(x,y+2)
			If Rnd()<.5 Then 
				tilecan[t].Color = Color.Brown.Blend(Color.Black,.5)
			Else 
				tilecan[t].Color = Color.Brown.Blend(Color.White,.5)
			End If
			tilecan[t].DrawPoint(x,y+3)
			'sea
			tilecan[t].Color = Color.Blue.Blend(Color.White,.6)
			tilecan[t].DrawPoint(x,y+4)
			tilecan[t].Color = Color.Blue.Blend(Color.White,.5)
			tilecan[t].DrawPoint(x,y+5)
			' move the point
			c+=Rnd(-2,2)
			If c<-Pi/2 Or c>Pi/2 Then c=0
			If x<7 Or x>right-7 Then c=0
			x+=Cos(a+c)
			y+=Sin(a+c)
			If x<7 Or x>right-7
				If y>top Then y-=1
				If y<top Then y+=1
			endif
			If y<0 Then y=0
		Wend
		tilecan[t].Flush()


	End Method
End Class

Global myworld:world

Class MyWindow Extends Window
		
	Method New()
		
		myworld = New world(100,100,32,32)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Keyboard.KeyReleased(Key.Space) Then 
			SeedRnd(Microsecs())
			myworld = New world(100,100,32,32)
		End If
		'
		myworld.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
