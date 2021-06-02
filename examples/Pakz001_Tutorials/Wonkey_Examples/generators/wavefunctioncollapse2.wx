'
' Wave Function Collapse (2d tilemap)
'

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class wfc
	Field mapwidth:Int,mapheight:Int
	Field screenwidth:Int,screenheight:Int
	Field tilewidth:Float,tileheight:Float
	Field map:Int[,]
	Method New(sw:Int,sh:Int)
		'Print "1"[0]
		map = New Int[5,5]
		map = mapinit()
		mapwidth = map.GetSize(0)
		mapheight = map.GetSize(1)
		screenwidth = sw
		screenheight = sh
		tilewidth = Float(screenwidth)/Float(mapwidth)
		tileheight = Float(screenheight)/Float(mapheight)
		collapse()
	End Method
	Method collapse()
		Local numtiles:Int=9
		Local tile:Stack<Stack<Stack<Int>>> = New Stack<Stack<Stack<Int>>>
		
		For Local i:Int=0 Until numtiles
			tile.Add(New Stack<Stack<Int>>)
			For Local ii:Int=0 Until 9
				tile.Get(i).Add(New Stack<Int>)
			Next
		Next

		'
		' here we are going to read each position on the map. We have a number
		' of unique tiles. Each tile has 8 neighbours. For each tile based on the
		' input map has a number of valid neighbour tiles.
		'
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Local ctile:Int=map[x,y]
			Local cnt:Int=0
			For Local y2:Int=-1 To 1
			For Local x2:Int=-1 To 1
				If x+x2<0 Or x+x2>=mapwidth Or y+y2<0 Or y+y2>=mapheight Then 
					cnt+=1
					Continue
				End If
				If (x+x2 = 0 And y+y2=0)
					cnt+=1
					Continue
				End If
				Local btile:Int=map[x+x2,y+y2]
				tile.Get(ctile).Get(cnt).Push(btile)
				cnt+=1
			Next
			Next
		Next
		Next

		' generate new map
		map = New Int[mapwidth,mapheight]
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			map[x,y] = -1
		Next
		Next		

		map[7,7] = 4
		
		' loop until we have a map (4)
		For Local i:Int=0 Until 4
		For Local y:Int=7-i Until 7+i
		For Local x:Int=7-i Until 7+i
			If map[x,y] <> -1
				Local ctile:Int=map[x,y]
				Local cnt:Int=0
				For Local y2:Int=-1 To 1
				For Local x2:Int=-1 To 1
					Local x3:Int=x+x2
					Local y3:Int=y+y2
					If x3<0 Or x3>=mapwidth Or y3<0 Or y3>=mapheight Then 
						cnt+=1
						Continue
					End If
					If (x2=0 And y2=0)
						cnt+=1
						Continue
					End If

					If map[x3,y3] = -1 ' if the current position is a none
						' Here we pick a number to place
						Local num:Int=tile.Get(ctile).Get(cnt).Length
						Local newt:Int=tile.Get(ctile).Get(cnt).Get(Rnd(num))
						
						map[x3,y3] = newt
									
					End if
					cnt+=1
				Next
				Next
			End If
			
		Next
		Next
		Next		


		'remove illegal tiles
		Local damned:Bool=True
		Local xit:Int=0
		While damned=True
			xit+=1
			
			damned=False
			For Local y1:Int=0 Until mapheight
			For Local x1:Int=0 Until mapwidth
				If map[x1,y1] = -1 Then Continue
				Local cnt:Int=0
				Local t:Int=map[x1,y1]
				Local valids:Int
				For Local y2:Int=-1 To 1
				For Local x2:Int=-1 To 1
					Local x3:Int=x1+x2
					Local y3:Int=y1+y2
					If x3<0 Or y3<0 Or x3>=mapwidth Or y3>=mapheight
						cnt+=1
						Continue
					End If
					If (x2=0 And y2=0)
						cnt+=1
						Continue
					End If
					Local isin:Bool=False
					If map[x3,y3] <> -1				
					For Local i:Int=0 Until tile.Get(map[x3,y3]).Get(cnt).Length
						If tile.Get(map[x3,y3]).Get(cnt).Get(i) = t Then isin=True ; Exit
					Next
					Else
						isin=True
					End If
					If isin=False						
						'map[x1,y1] = Rnd(numtiles)
						'damned=True
					Else
						valids+=1
					End If
					cnt+=1
				Next
				Next				
				
				If valids<8 Then 
					Local v:Int=Rnd(numtiles)
					If Rnd()<.3 Then v=0
					map[x1,y1] = v
					damned=True					
				End If
			Next
			Next
			If xit>100 Then damned=False			
		Wend

	End Method
	Method mapinit:Int[,]()
		Local s:String[] = New String[15]		
		s[0] ="000000000000000"
		s[1] ="000000000000000"
		s[2] ="000000000000000"
		s[3] ="000000000000000"
		s[4] ="000000000000000"
		s[5] ="000074600000000"
		s[6] ="000081500000000"
		s[7] ="000081500000000"
		s[8] ="000081500000000"
		s[9] ="000081500000000"
		s[10]="000081500000000"
		s[11]="007444444446000"
		s[12]="338111111115333"
		s[13]="228111111115222"
		s[14]="441111111111444"
		Local m:Int[,] = New Int[15,15]
		For Local y:Int=0 Until s.GetSize(0)
		For Local x:Int=0 Until s[0].Length
			Select s[y][x]
				Case 48
					m[x,y] = 0
				Case 49
					m[x,y] = 1
				Case 50
					m[x,y] = 2
				Case 51
					m[x,y] = 3
				Case 52
					m[x,y] = 4
				Case 53
					m[x,y] = 5
				Case 54
					m[x,y] = 6
				Case 55
					m[x,y] = 7
				Case 56
					m[x,y] = 8
			End Select
		Next
		Next
		Return m
	End Method
	Method drawmap(canvas:Canvas)
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Local x1:Int=x*tilewidth
			Local y1:Int=y*tileheight
			Select map[x,y]
				Case 0 'air
					canvas.Color = Color.Blue.Blend(Color.White,.5)
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
				Case 1 'sand
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
				Case 2 'water
					canvas.Color = Color.Blue
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
				Case 3 'water top
					canvas.Color = Color.Blue
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Blue.Blend(Color.White,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
				Case 4 'sand top
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.White,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
				Case 5 'sand right
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1+tilewidth-3,y1,3,tileheight+1)
				Case 6 'sand right top
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
					canvas.DrawRect(x1+tilewidth-3,y1,3,tileheight+1)					
				Case 7 'sand left top
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
					canvas.DrawRect(x1,y1,0,tileheight+1)					
				Case 8 ' sand left
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1,y1,3,tileheight+1)
					
			End Select
		Next
		Next
	End Method
End Class

Global mywfc:wfc

Class MyWindow Extends Window

	Method New()
		mywfc = New wfc(Width,Height)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mywfc.drawmap(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
