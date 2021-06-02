'
' https://gamedevelopment.tutsplus.com/tutorials/create-a-procedurally-generated-dungeon-cave-system--gamedev-10099
'
'
' Dungeon generator.
'
' The trick here is to take find a valid spot for a rectangle
' and remember the previous rectangles center location. We build
' a tunnel between the new and the previous rectangle. This
' ensures that every spot in the map is reachable.
'
' Code is commented lightly
 

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
		If x-w/2<0 Or y-h/2<0 Or x+w/2>=mapwidth Or y+h/2>=mapheight Then Return True
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

Class MyWindow Extends Window

	Field mydun:dungeon
		
	Method New()
		mydun = New dungeon(Width,Height,50,50)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		If Keyboard.KeyReleased(Key.Space) Then
			Local s:Int=Rnd(30,100)
			mydun = New dungeon(Width,Height,s,s)
		End if
		
		mydun.drawmap(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
