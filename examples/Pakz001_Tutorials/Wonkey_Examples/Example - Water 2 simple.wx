'What it does is rndomly find a pos on the map (thousand times per second)
'if that map pos is water then see if you can move it down
'see if it can move left
'see if it can move right
'see if it can move left down
'replace the old position with no water and the place where to go with water value


' lmb = pour water - mmb = erase tile - rmb = make tile

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class map
	Field freq:Int 'how many updates per cycle
	Field tw:Float,th:Float
	Field w:Int,h:Int
	Field map:= New Int[1,1] 

	Method New(sw:float,sh:float,w:float,h:Float,freq:int)
		Self.freq = freq
		tw = sw/w
		th = sh/h
		map = New Int[w,h]
		Self.w = w
		Self.h = h
		For Local y:=(h/1.5) Until h
		For Local x:=0 Until w
			map[x,y] = 1
		Next
		Next
		For Local y:=0 Until h
			map[0,y] = 1
			map[w-1,y] = 1
		Next
		makewater(20,15,10,10)
	End Method 
	Method update()
		If Mouse.ButtonDown(MouseButton.Left)
			Local x:Int= Mouse.X/tw
			Local y:Int = Mouse.Y/th
			If x>0 And x<w And y>0 And y<h 
				map[x,y] = 2
			End If
		End If
		If Mouse.ButtonDown(MouseButton.Right)
			Local x:Int= Mouse.X/tw
			Local y:Int = Mouse.Y/th
			If x>0 And x<w And y>0 And y<h 
				map[x,y] = 1
			End If
		End If
		If Mouse.ButtonDown(MouseButton.Middle)
			Local x:Int= Mouse.X/tw
			Local y:Int = Mouse.Y/th
			If x>0 And x<w And y>0 And y<h 
				map[x,y] = 0
			End If
		End If

		For Local i := 0 Until freq
			updatewater(Rnd(1,w-1),Rnd(1,h-1))
		Next
	End Method 
	Method updatewater(x:Int,y:Int)
		Local s:Int=Rnd(0,4)
		If map[x,y] = 2 Then
		Select s
			Case 0
			If map[x-1,y] = 0
			If map[x+1,y] = 2
			map[x-1,y] = 2
			map[x,y] = 0				
			End If
			Endif
			Case 1
			If map[x-1,y] = 2
			If map[x+1,y] = 0
				map[x+1,y] = 2
				map[x,y] = 0				
			End If
			End If
			Case 2
			If map[x,y+1] = 0
				map[x,y+1] = 2
				map[x,y] = 0
			End If				
			Case 3
			If map[x-1,y] = 0
			If map[x-1,y+1] = 0
			If map[x,y+1] = 2
				map[x,y] = 0
				map[x-1,y+1] = 2
			End If	
			End If 
			End If 
			End Select
		End If
	End Method 
	Method makewater(x:Int,y:Int,w:Int,h:Int)
		For Local y1:=y Until y+h
		For Local x1:=x Until x+w
			map[x1,y1] = 2
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:=0 Until h
		For Local x:=0 Until w
			If map[x,y] = 0
				canvas.Color = Color.Black
				canvas.DrawRect(x*tw,y*th,tw,th)
			End If 
			If map[x,y] = 1
				canvas.Color = Color.Grey
				canvas.DrawRect(x*tw,y*th,tw,th)
			End If 
			If map[x,y] = 2
				canvas.Color = Color.Blue
				canvas.DrawRect(x*tw,y*th,tw,th)
			End If 
		Next
		Next
	End Method 
End Class 

Global mymap:map

Class MyWindow Extends Window

	Method New()
		mymap = New map(Width,Height,70,30,2000)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mymap.update()
		mymap.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
