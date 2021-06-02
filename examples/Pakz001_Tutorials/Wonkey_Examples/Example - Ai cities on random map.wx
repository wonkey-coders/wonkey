#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field map:Int[,]
	Field tw:Float,th:Float
	Field mw:Int=32,mh:Int=32
	Class city
		Field x:Int,y:Int
		Method New(x:Int,y:Int)
			Self.x = x
			Self.y = y
		End Method
	End Class
	Field mycity:List<city>
	Method New()
		tw = Float(Width)/Float(mw)
		th = Float(Height)/Float(mh)
		map = New Int[mw,mh]
		makemap()
		mycity = New List<city>
		makecountry(3)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		drawmap(canvas) 
		' If we press the mouse on the map then execute 
		' the method. (print the returnvale to the console)
		If Mouse.ButtonReleased(MouseButton.Left) Or Keyboard.KeyReleased(Key.Space)
			SeedRnd(Millisecs())
			map = New Int[mw,mh]
			makemap()
			mycity = New List<city>
			makecountry(Rnd(1,10))
		End If
		' 
		canvas.Color = Color.Black
		canvas.DrawText("Press the lmb or space for new country.",0,0)
		'
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	'
	' For the first ai player.
	' does not check other cities
	Method makecountry(numberofcities:Int)
		Local citiesmade:Int=0
		Local currentx:Int,currenty:Int
		'
		' Find starting position
		Local exitloop:Bool=False
		While exitloop = False
			Local x:Int=Rnd(mw)
			Local y:Int=Rnd(mh)
			If map[x,y] > 5
				currentx = x
				currenty = y				
				exitloop = True	
			End If
		Wend
		' Add the first city to the list
		mycity.Add(New city(currentx,currenty))
		citiesmade = 1
		exitloop=False
		Local failcount:Int
		Repeat
			' find next city position
			exitloop=False
			While exitloop=False
				' get a random coordinate
				Local nx:Int=Rnd(mw),ny:Int=Rnd(mh)
				'first check if the new position is not to close to a excisting city
				Local check1:Bool=True
				For Local i:=Eachin mycity
					If distance(i.x,i.y,nx,ny)<5 Then check1 = False
				Next
				'check if the new position is near a existing city
				Local check2:Bool=True
				For Local i:=Eachin mycity
					If distance(i.x,i.y,nx,ny) > 10 Then check2 = False
				Next
				If check1 = True And check2 = True
				If map[nx,ny] > 5 'if the current tile is land
					citiesmade += 1
					mycity.Add(New city(nx,ny))
					exitloop = True
				End If
				End If
				failcount+=1
				If failcount>1000 Then Return
			Wend
			'
			If citiesmade = numberofcities Then Exit
		Forever		
	End Method
	' function that returns the distance between 2 2d points.
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function 	
	' Create a random map (hill algorithm)
	Method makemap()
		Local exitloop:Bool=False
		While exitloop=False
			Local x1:Int=Rnd(-10,mw)
			Local y1:Int=Rnd(-10,mh)
			Local w:Int=Rnd(1,12)
			Local h:Int=Rnd(1,10)
			For Local y2:=y1 To y1+h
			For Local x2:=x1 To x1+w
				If x2>=0 And x2<mw And y2>=0 And y2<mh
					map[x2,y2] = map[x2,y2] + 1
					If map[x2,y2] > 46 Then exitloop = True
				End If
			Next
			Next		
		Wend
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			map[x,y] = (10.0/46)*map[x,y]
		Next
		Next
	End Method
	' Draw the map on the canvas
	Method drawmap(canvas:Canvas)
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			Local col:Float=0
			col = Float(map[x,y])/20
			If map[x,y]>5
				canvas.Color = New Color(col,1,col)
				Else
				canvas.Color = New Color(col,col,1)
			End If
			canvas.DrawRect(x*tw,y*th,tw,th)
		Next
		Next
		'draw the cities
		For Local i:=Eachin mycity
			canvas.Color = Color.Black
			canvas.DrawRect(i.x*tw-1,i.y*th-1,tw+2,th+2)
			canvas.Color = Color.White
			canvas.DrawRect(i.x*tw,i.y*th,tw,th)
		Next
	End Method
End	Class
	
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
