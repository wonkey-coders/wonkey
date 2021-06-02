#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class unit
	Class pathnode
	    Field x:Int
	    Field y:Int
	    Method New(x:Int,y:Int)
	        Self.x = x
	        Self.y = y
	    End Method
	End Class
	Field path:Stack<pathnode>	
	Field px:Float,py:Float 'position x and y
	Field speed:Float=1 ' movement speed
	Field w:Int=10,h:Int=10 'width and height of units
	Field selected:Bool=False
	'
	' Pathpos is the unit his current position in the path
	'
	Field pathpos:Int
	Method New(x:Int,y:Int)
		Self.px = x
		Self.py = y
	End Method
	Method findpath:Bool(destx:Int,desty:Int)
		If mypath.findpath(px/mypath.tilewidth,py/mypath.tileheight,destx,desty) = True
			path = New Stack<pathnode>
			For Local i:=Eachin mypath.path				
				path.Push(New pathnode(i.x,i.y))
			Next
			pathpos = 0
			Return True
		End If
		Return False
	End Method
	Method move()
		If Not path Then Return
		' If the current position in the path = not valid
		' then do not move
		If pathpos >= path.Length Then Return
		' dx and dy = the destination (pixels) of the next
		' location to move to in the path.
		Local dx:Int,dy:Int
		dx = path.Get(pathpos).x*mypath.tilewidth
		dy = path.Get(pathpos).y*mypath.tileheight
		' Move the unit
		If px < dx Then px +=1 Else px-=1
		If py < dy Then py +=1 Else py-=1
		'If the unit is close enough to the next position
		' in the path then go to the next position
		If distance(px,py,dx,dy) < 5
			pathpos+=1
			' If we are at the end then erase
			' the path
			If pathpos = path.Length Then 
				path = New Stack<pathnode>
			End If
		End If
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = New Color(1,.1,.1,.5)
		
		If path		
		For Local i:=Eachin path
			canvas.DrawOval(i.x*mypath.tilewidth,i.y*mypath.tileheight,6,6)
			'canvas.DrawText(i.x+","+i.y,i.x*mypath.tilewidth,i.y*mypath.tileheight)
		Next
		End If
		'Draw the unit
		canvas.Color = Color.White
		canvas.DrawOval(px,py,w,h)
		'If unit selected then draw this
		If selected
			canvas.Color = New Color(1,1,.5,.5)
			canvas.DrawRect(px,py,w,h)
		End If
	End Method
	Method cx:Int()
		Return px+w/2
	End Method
	Method cy:Int()
		Return py+h/2
	End Method
	Method distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x2-x1)+Abs(y2-y1)
	End Method		
End Class

Class pathfinder
	Class openlist
	    Field x:Int
	    Field y:Int
	    Field f:Int
	    Field g:Int
	    Field h:Int
	    Field px:Int
	    Field py:Int
	    Method New(    x:Int=0,y:Int=0,f:Int=0,
	                g:Int=0,h:Int=0,px:Int=0,py:Int=0)
	        Self.x=x
	        Self.y=y
	        Self.f=f
	        Self.g=g
	        Self.h=h
	        Self.px=px
	        Self.py=py
	    End Method
	End Class
	Class closedlist
	    Field x:Int
	    Field y:Int
	    Field px:Int
	    Field py:Int 
	    Method New(x:Int,y:Int,px:Int,py:Int)
	        Self.x = x
	        Self.y = y
	        Self.px = px
	        Self.py = py
	    End Method
	End Class
	Class pathnode
	    Field x:Int
	    Field y:Int
	    Method New(x:Int,y:Int)
	        Self.x = x
	        Self.y = y
	    End Method
	End Class
	Field cl:List<closedlist>
	Field path:List<pathnode>
	Field ol:List<openlist>
	' -1 is impassable
	Field map:Int[,]
	Field olmap:Int[,]
	Field clmap:Int[,]
	Field mapwidth:Int
	Field mapheight:Int
	' these are the start and end coordinates
	Field sx:Int,sy:Int,ex:Int,ey:int
	'for debugging
	Field tilewidth:Float,tileheight:Float

	Method New(newmap:Int[,])
		' If the inputted array is at zero and zero then return
		If newmap.GetSize(0) = 0 Or newmap.GetSize(1) = 0 Then 
			Print "array in pathfinder class width and or height at zero..."
			Return
		End If
		' get the mapwidth and mapheight
		Self.mapwidth = newmap.GetSize(0)
		Self.mapheight = newmap.GetSize(1)
		' copy the input array into this class its map array
		map = new Int[mapwidth,mapheight]
		For Local y:=0 Until mapheight
		For Local x:=0 Until mapwidth
			map[x,y] = newmap[x,y]
		Next
		Next
		' For debugging / testing
		' 
		tilewidth = 10
		tileheight = 10
		
	End Method

	' This is the a* pathfinder method.
	' sx and sy = start x and y	
	' ex and ey = end coordinates
	'
	Method findpath:Bool(sx:Int,sy:Int,ex:Int,ey:Int)
		' Store the start and end coordinates
		' locally in the class
		Self.ex = ex
		Self.ey = ey
		Self.ex = ex
		Self.ey = ey
		' if start and end is same then message that and return
	    If sx = ex And sy = ey Then 
		    Print "Start coordinates same as end coordinates in findpath method in pathfinder class"
	    	Return False
	    End If
	    ' Reset/Create this class its arrays and lists
	    olmap = New Int[mapwidth,mapheight]
	    clmap = New Int[mapwidth,mapheight]
		ol = New List<openlist>
		cl = New List<closedlist>
		path = New List<pathnode>
		' Start pathfinding
	    ol.AddFirst(New openlist(sx,sy))
	    Local tx:Int
	    Local ty:Int
	    Local tf:Int
	    Local tg:Int
	    Local th:Int
	    Local tpx:Int
	    Local tpy:Int
	    Local newx:Int
	    Local newy:Int
	    Local lowestf:Int
	    olmap[sx,sy] = 1
	    While ol.Empty = False
	        lowestf = 100000
	        For Local i:=Eachin ol
	            If i.f < lowestf
	                lowestf = i.f
	                tx = i.x
	                ty = i.y
	                tf = i.f
	                tg = i.g
	                th = i.h
	                tpx = i.px
	                tpy = i.py
	            End If
	        Next
	        If tx = ex And ty = ey
	            cl.AddLast(New closedlist(tx,ty,tpx,tpy))
	            findpathback()
	            Return True
	        Else
	            removefromopenlist(tx,ty)
	            olmap[tx,ty] = 0
	            clmap[tx,ty] = 1
	            cl.AddLast(New closedlist(tx,ty,tpx,tpy))
	            For Local y:=-1 To 1
	            For Local x:=-1 To 1		            
	                newx = tx+x
	                newy = ty+y	                
	                If newx>=0 And newy>=0 And newx<mapwidth And newy<mapheight
		            If map[newx,newy] >= 0
	                If olmap[newx,newy] = 0
	                If clmap[newx,newy] = 0
	                    olmap[newx,newy] = 1
	                    '
	                    ' gg is the go to cost. Modify the cost here.
	                    ' example: roads tile (5) in array cost 2
	                    ' while forrest tile (8) in array cost 8
	                    ' below it just adds the map int value and one (heightmap)
	                    Local gg:Int = map[newx,newy]+1
	                    Local hh:Int = distance(newx,newy,ex,ey)
	                    Local ff:Int = gg+hh
	                    ol.AddLast(New openlist(newx,newy,ff,gg,hh,tx,ty))
	                End If
	                End If
	                End If
	                End if
	            Next
	            Next
	        End If
	    Wend
	    Return False
	End Method

	
	Method findpathback:Bool()
	    Local x:Int=ex
	    Local y:Int=ey
	    path.AddFirst(New pathnode(x,y))
	    Repeat
	        For Local i:=Eachin cl
	            If i.x = x And i.y = y
	                x = i.px
	                y = i.py
	                path.AddFirst(New pathnode(x,y))
	            End If
	        Next
	        If x = sx And y = sy Then 
	        	path.RemoveFirst()
	        	Return True	        
	       	End if
	    Forever    
	    Return False
	End Method
	
	Method removefromopenlist:Void(x1:Int,y1:Int)
	    For Local i:=Eachin ol
	        If i.x = x1 And i.y = y1
	            ol.Remove(i)
	            Exit
	        End If
	    Next
	End Method
	
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	    Return Abs(x2-x1)+Abs(y2-y1)
	End Function	
	
	' Debug test function/methods
	' Draw the map to the screen
	Method drawmap:Void(canvas:Canvas)
		If mapwidth = 0 Or mapheight = 0 
			Print "Error in pathfinder class (drawmap) no width and height"
			Return
		End If
	    For Local y:=0 Until mapheight
	    For Local x:=0 Until mapwidth	        
	        If map[x,y]>=0
	       		canvas.Color = New Color(0,(Float(map[x,y])*10)/255,0)
	        	canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
	        End If
	    Next
	    Next
	End Method
	' draw the path to the screen
	Method drawpath:Void(canvas:Canvas)
		If path.Count() = 0 Then return
	    Local cnt:Int=1
	    For Local i:=Eachin path
	        canvas.Color = Color.Yellow
	        canvas.DrawOval(i.x*tilewidth,i.y*tileheight,4,4)
	        canvas.Color = Color.White
	        canvas.DrawText(cnt,i.x*tilewidth,i.y*tileheight)
	        cnt+=1
	    Next
	End Method
End Class


Global mypath:pathfinder
Global myunit:Stack<unit>

Class MyWindow Extends Window
	Field testmap:Int[,]
	Field selection:Bool=False
	Field drag1:Vec2i = New Vec2i(0,0)
	Field drag2:Vec2i = New Vec2i(0,0)
	Field dragactive:Bool=False
	Field dragwait:Int
	Method New()
		' Here we create a map array
		testmap = New Int[50,50]
		testmap = makemap(50,50)			
		
		
		' Here we insert the map into the pathfinder
		' at the moment it works like this.
		' it goes in 8 direction.
		' high values in the map are higher movement cost.
		' 
		mypath = New pathfinder(testmap)

		myunit = New Stack<unit>
		myunit.Push(New unit(50,50))
		myunit.Push(New unit(60,50))

		'myunit.Top.findpath(10,10)

		' Here we find a path
		'mypath.findpath(0,0,40,40)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Display the map and path
		mypath.drawmap(canvas)
		
		Local bl:Bool
		Local br:Bool
		If Mouse.ButtonReleased(MouseButton.Left) Then bl=True
		If Mouse.ButtonReleased(MouseButton.Right) Then br=True
		
		
		dragselect()
		unitselect(bl)		
		unitselectdest(bl)
		unitdeselect(bl,br)
		
		
		' move the units
		For Local i:Int=0 Until myunit.Length
			myunit.Get(i).move()
		Next	

		' draw the units
		For Local i:Int=0 Until myunit.Length
			myunit.Get(i).draw(canvas)
		Next	
		' draw the drag selection rectangle
		drawdrag(canvas)
		
		
		'mypath.drawpath(canvas)
		' if key escape then quit		
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()	
		canvas.Color = Color.White
		If selection=True Then canvas.DrawText("selected",0,0)	
		If dragactive Then canvas.DrawText("drag",50,0)		
	End Method	
	
	'
	Method dragselect()
			
		' If there is currently no dragging going on
		If dragactive = False
			' if drag action then set drag flag and initial coords
		If Mouse.ButtonDown(MouseButton.Left)
			drag1.x = Mouse.X
			drag1.y = Mouse.Y
			drag2.x = Mouse.X
			drag2.y = Mouse.Y
			dragactive = True			
			Return
		End If
		End if
		' 
		' If we are currently dragging
		If dragactive
			' If still mouse down then update the drag zone
			If Mouse.ButtonDown(MouseButton.Left)
				drag2.x = Mouse.X
				drag2.y = Mouse.Y
				If distance(drag1.x,drag1.y,drag2.x,drag2.y)>10 Then dragwait = 10
			End If
			' If the drag is completed.

			If Mouse.ButtonDown(MouseButton.Left) = False
				Local a:Int,b:Int,w:Int,h:Int
				dragactive = False
				' Select every unit inside the drag zone
				' make sure we have a valid selection set of coords				
				If drag1.x < drag2.x Then 
					a = drag1.x
					w = drag2.x - drag1.x				
				Else
					a = drag2.x
					w = drag1.x - drag2.x
				End If
				If drag1.y < drag2.y Then
					b = drag1.y
					h = drag2.y - drag1.y
				Else
					b = drag2.y
					h = drag1.y - drag2.y
				End If
				' make sure the size of the rect is large enough
				If Abs(w)<5 Or Abs(h)<5 Then Return
				' Select flag every unit in the selection rectangle
				For Local i:Int=0 Until myunit.Length
					myunit.Get(i).selected =False
					If rectsoverlap(a,b,w,h,myunit.Get(i).px,myunit.Get(i).py,myunit.Get(i).w,myunit.Get(i).h)
						myunit.Get(i).selected =True
						selection = True
					End If
				Next
			End If
		End If
	End Method
	
	Method drawdrag(canvas:Canvas)
		' If there is no selection then return
		If dragactive=False Then Return
		' Set up a drawing mode with outline
		canvas.Color = Color.White
		canvas.OutlineMode=OutlineMode.Smooth
		canvas.OutlineColor = Color.Blue
		canvas.OutlineWidth = 4
		canvas.Color = Color.None
		' Get the coords for drawing the rectangle
		Local a:Int,b:Int,w:Int,h:Int
		a = drag1.x
		b = drag1.y
		w = drag2.x-drag1.x
		h = drag2.y-drag1.y
		' Draw the rectangle
		canvas.DrawRect(a,b,w,h)
	End Method

	Method unitdeselect(buttonleft:Bool,buttonright:Bool)
		If selection = False Then Return
		' 		
		' Here we deselect every unit
		If buttonright
			For Local i:Int=0 Until myunit.Length
				myunit.Get(i).selected = False
			Next
			selection = False
		End If				
	End Method
	
	Method unitselect(buttonleft:Bool)

		If buttonleft
			' If unit on this tile then set its selected flag
			' and all other units set selection flag to false			
			For Local i:Int=0 Until myunit.Length
				'myunit.Get(i).selected = False
				If distance(Mouse.X,Mouse.Y,myunit.Get(i).cx(),myunit.Get(i).cy()) < 8
					myunit.Get(i).selected = true
					Print Millisecs()+" selected unit"
					selection = True
					' deselect others
					For Local j:Int=0 Until myunit.Length
						If i <> j
							myunit.Get(j).selected = False
						Endif
					Next
					Return
				End If
			Next		
		End If
	End Method
	
	Method unitselectdest(buttonleft:Bool)
		If dragwait > 0 Then dragwait-=1
		' if nothing is selected then return
		If selection = False Then Return		
		If dragwait > 0 Then Return		
		'
		' Here we find a path for the selected unit(s)
		'
		If buttonleft
			' Return if we click on a unit
			For Local i:Int=0 Until myunit.Length
				If distance(Mouse.X,Mouse.Y,myunit.Get(i).cx(),myunit.Get(i).cy()) < 8
					Return
				Endif
			Next
			'	Find a path for the selected unit
			For Local i:Int=0 Until myunit.Length
				If myunit.Get(i).selected = True Then					
					myunit.Get(i).findpath(Mouse.X/mypath.tilewidth,Mouse.Y/mypath.tileheight)
				Endif
			Next
		End if
	End Method
	
	Method distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x2-x1)+Abs(y2-y1)
	End Method	
	Method rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	Method
End	Class

' Make a random map (hill algorithm)
Function makemap:Int[,](mapwidth:int,mapheight:Int)
	Local map:Int[,] = New int[mapwidth,mapheight]
    For Local y:=0 Until mapheight
    For Local x:=0 Until mapwidth
        map[x,y] = 0
    Next
    Next

    '
    Return map
End Function


Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
