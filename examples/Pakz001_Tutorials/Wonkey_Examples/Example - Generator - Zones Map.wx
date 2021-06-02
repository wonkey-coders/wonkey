#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class themap
	Field map:Int[,] 
	Field mw:Int,mh:Int 'mapwidth and mapheight
	Field numzones:Int'number of zones(provinces ect)
	Field zonecol:Color[] 'color for drawing zones
	Method New(mw:Int,mh:Int,numzones:Int)
		Self.mw = mw
		Self.mh = mh
		Self.numzones = numzones
		map = New Int[mw,mh]
		'create colors
		zonecol = New Color[numzones+1]
		' Put numbers on the map at random locations
		For Local i:Int=1 To numzones
			Repeat 'make sure not to overwrite a number
				Local x:Int=Rnd(mw)
				Local y:Int=Rnd(mh)
				If map[x,y] = 0
					map[x,y] = i
					zonecol[i] = New Color(Rnd(1),Rnd(1),Rnd(1))
					Exit
				End If
			Forever			
		Next
		generatemap()
	End Method
	Method generatemap()		
		' Here we grow the numbers on the map thus creating zones
		' We pick a random position on the map and look if it is
		' a zone number. If so then try to grow it by putting that
		' same number around it. 
		Local exitloop:Bool=False
		While exitloop = False
			'create a random position
			Local x:Int=Rnd(mw)
			Local y:Int=Rnd(mh)
			' read the map at this position
			Local currentzone:Int=map[x,y]			
			' if it is a zone number
			If currentzone > 0		
				' find a place to grow it to. left top, top ect		
				Local x1:Int=Rnd(-2,2)
				Local y1:Int=Rnd(-2,2)
				' if in bounds
				If x+x1 >= 0 And y+y1 >=0 And x+x1<mw And y+y1<mh
					' if not a zone already
					If map[x+x1,y+y1] = 0
						'grow				
						map[x+x1,y+y1] = currentzone
					End If
				End If
			End If
			'every now and then see if we can exit the loop
			'no more free spaces to grow.
			If Rnd(mw*mh)<10 Then				
				exitloop = True			
				For Local x1:Int=0 Until mw
				For Local y1:Int=0 Until mh
					If map[x1,y1] = 0 Then exitloop = False
				Next
				Next
			End If
		Wend
	End Method
	'This method draws the map to the canvas
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			canvas.Color = zonecol[map[x,y]]
			canvas.DrawRect(x*6,y*6,6,6)
		Next
		Next		
	End Method
End Class

'create a variable to use/create the map
Global mymap:themap

Class MyWindow Extends Window

	Method New()
		Title = "Zones Map Generator"
		'create the map
		mymap = New themap(Width/6,Height/6,Rnd(2,20))
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' When the space is pressed generate a new map
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonHit(MouseButton.Left) Then 
			mymap = New themap(Width/6,Height/6,Rnd(2,20))
		End if
		' Draw the map
		mymap.draw(canvas)
		'
		canvas.Color = Color.White
		canvas.DrawText("Press Space or LMB to generate new map",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
