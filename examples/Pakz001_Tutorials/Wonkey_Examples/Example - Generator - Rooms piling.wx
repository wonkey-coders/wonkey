#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class mapgen
	Field sw:Int,sh:Int
	Field mw:Int,mh:Int
	Field tw:Float,th:Float
	Field map:Int[,]
	Method New(sw:Int,sh:Int,mw:Int,mh:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		Self.tw = Float(sw) / Float(mw)
		Self.th = Float(sh) / Float(mh)
		Self.tw += 1
		Self.th += 1
		map = New Int[mw,mh]
		generate()
	End Method
	Method generate()
		' Put the first floor on the map
		map[mw/2,mh/2] = 1
		' Insert the room there
		insertroom(mw/2,mh/2)
		' Create rooms until percentage of map is filled
		Repeat
			insertroom(Rnd(mw),Rnd(mh))
			Local cnt:Int=0
			For Local y:Int=0 Until mh
			For Local x:Int=0 Until mw
				If map[x,y] = 1 Then cnt+=1
			Next
			Next
			If cnt*3>mw*mh Then Exit
		Forever
	End Method
	Method insertroom(x:Int,y:Int)
		' Create the room sizes
		Local w:Int=Rnd(-mw/4,mw/4)
		Local h:Int=Rnd(-mh/4,mh/4)
		' if sizes are to small then cancel
		If w>-2 And w<2 Then Return
		If h>-2 And h<2 Then Return
		' If going outside of map then cancel
		If x+w+8 > mw Then Return
		If y+h+8 > mh Then Return
		If x+w < 0 Then Return
		If y+h < 0 Then Return
		
		' On the position where the room is going to be put
		' see if there is at least one room present. If not then 
		' cancel.
		Local go:Bool=False
		For Local y2:Int=y+1 To y+h-1
		For Local x2:Int=x+1 To x+w-1
			If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
			If map[x2,y2] = 1 Then go = True
		Next
		Next
		If go=False Then Return
		
		' On the new rooms position put the floor(1)
		For Local y2:Int=y+1 To y+h-1
		For Local x2:Int=x+1 To x+w-1
			If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
			map[x2,y2] = 1
		Next
		Next
		' On the new rooms position put the walls if there
		' is no floor on that place(only on 0)
		For Local y2:Int=y To y+h
			If y2<0 Or y2>=mh Then Continue			
			If map[x,y2] = 0 Then map[x,y2] = 2
			If x+h >= mh Then Continue
			If map[x+w,y2] = 0 Then map[x+w,y2] = 2
		Next
		For Local x2:Int=x To x+w
			If x2<0 Or x2>=mw Then continue
			If map[x2,y] = 0 Then map[x2,y] = 2
			If y+h >= mh Then Continue
			If map[x2,y+h] = 0 Then map[x2,y+h] = 2
		Next

	End Method
	' Draw the map on the canvas
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If map[x,y] = 0 Then Continue
			If map[x,y] = 1 Then canvas.Color = Color.White
			If map[x,y] = 2 Then canvas.Color = Color.Red
			canvas.DrawRect(x*tw,y*th,tw,th)
		Next
		Next
	End Method
End Class

Class MyWindow Extends Window

	Field mymapgen:mapgen 
	Method New()
		mymapgen = New mapgen(Width,Height,50,50)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		If Keyboard.KeyReleased(Key.Space) Then 
			mymapgen = New mapgen(Width,Height,50,50)
		End If
		mymapgen.draw(canvas)
		
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
