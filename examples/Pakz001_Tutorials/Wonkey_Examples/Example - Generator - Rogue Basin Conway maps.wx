#Import "<std>"
#Import "<mojo>"

' Based on code linked on Rogue Basin - Conways Game of Life

Using std..
Using mojo..

Class MyWindow Extends Window
	
	Field neighbours:Int
	Field iterations:Int
	Field mapx:Int
	Field mapy:Int
	Field closecellprob:Int
	Field probexceeded:Bool
	Field map:Int[,]	

	Method New()
		neighbours = 4
		iterations = 50000
		probexceeded = True
		mapx = 99
		mapy = 99
		closecellprob = 45
		go()
	End method
	'build a map
	Method go()
		map = New Int[mapx,mapy]
		' go through each cell and use the specified probability to determine if it's open
		For Local y:Int=0 Until map.GetSize(0)
		For Local x:Int=0 Until map.GetSize(1)
			If Rnd(100) < closecellprob
				map[x,y] = 1
			End If				
		Next
		Next	
		'pick cell at random
		For Local i:Int=0 Until iterations
			Local rx:Int=Rnd(map.GetSize(0))
			Local ry:Int=Rnd(map.GetSize(1))
			If probexceeded=True
				If examineneighbours(rx,ry)>neighbours
					map[rx,ry] = 1
				Else
					map[rx,ry] = 0
				End If
			Else
				If examineneighbours(rx,ry)>neighbours
					map[rx,ry] = 0
				Else
					map[rx,ry] = 1
				End If
			End If
		Next	
	End Method
	'Count all the closed cells around the specified cell and return that number
	Method examineneighbours:Int(xval:Int,yval:Int)
		Local count:Int=0
		For Local x:Int=-1 To 1
		For Local y:Int=-1 To 1
			If checkcell(xval+x,yval+y) = True
				count+=1
			End If
		Next
		Next
		Return count
	End Method
	'Check the examined cell is legal and closed
	Method checkcell:Bool(x:Int,y:Int)
		If (x>=0 And x<map.GetSize(0)) And (y>=0 And y<map.GetSize(1))
			If map[x,y]>0
				Return True
			Else
				Return False
			End If
		Else
			Return False			
		End If
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 		
		'Draw the map on the screen
		Local cw:Float=Float(Width)/Float(mapx)
		Local ch:Float=Float(Height)/Float(mapy)
		For Local y:Int=0 Until mapy
		For Local x:Int=0 Until mapx
			If map[x,y] = 1
				canvas.Color=Color.White
			Else
				canvas.Color=Color.Black
			End If
			canvas.DrawRect(x*cw,y*ch,cw,ch)
		Next
		Next
		'If pressed space then create new map
		If Keyboard.KeyReleased(Key.Space) Then 
			neighbours = 4
			iterations = 50000
			probexceeded = True
			If Rnd()<.5 Then 
				probexceeded=False
				If Rnd() <.5
					neighbours=2
				End if
			End If
			closecellprob = Rnd(30,60)'45
			go()
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		canvas.Color = Color.Blue
		canvas.DrawRect(0,0,Width,15)
		canvas.Color = Color.Red
		canvas.DrawText("Press space to generate new map",0,0)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
