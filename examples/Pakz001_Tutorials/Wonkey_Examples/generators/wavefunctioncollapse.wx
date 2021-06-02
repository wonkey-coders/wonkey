
'
' This kind of failed - I need to learn more about this ...
'''

'

#Import "<std>"
#Import "<mojo>"
'

Using std..
Using mojo..
Global instance:AppInstance
Class wfc
	'wave function setup
	Class wavenode		
		Field tile:int
		'Global a:List<test>[] = New List<test>[10]
		Field beside:Stack<Int>[]
		Method New(t:Int)
			Self.tile = t			
			beside = New Stack<Int>[9]
			For Local i:Int=0 Until 9
				beside[i] = New Stack<Int>
			Next
		End Method
		Method addtile(location:Int,tile:Int)
			For Local i:Int=0 Until beside[location].Length
				If beside[location].Get(i) = tile Then Return
			Next
			beside[location].Push(tile)			
		End Method
	End Class
	'map setup
	Field map:Int[,]
	Field mw:Int,mh:Int,sw:Int,sh:Int
	Field tw:Float,th:Float
	Field leftmousetile:Int,rightmousetile:Int
	Enum tiles
		nothing = 0,
		sand = 1,
		sandgrasstop = 2,
		rock = 3,
		rocklightleft = 4,
		rocklightright = 5,
		rocklighttop = 6
		
	End Enum
	Field tused:Stack<wavenode>
	Method New(sw:Int,sh:Int,mw:Int,mh:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		tw = Float(sw) / Float(mw)
		th = Float(sh) / Float(mh)
		map = New Int[mw,mh]
		tused = New Stack<wavenode>
	End Method
	Method printinfo(tile:Int)
		For Local i:Int=0 Until tused.Length
			If tused.Get(i).tile = tile
				Print "tile :"+tile
				For Local ii:Int=0 Until 9
					Print " side :" + ii
					For Local n:Int=0 Until tused.Get(i).beside[ii].Length
					Print tused.Get(i).beside[ii].Get(n)
					Next
				Next
			End If
		Next
		
	End Method
	Method dofunction()
		'find tiles used
		tused = New Stack<wavenode>
		
		Local exsists := Lambda:Bool(in:Int)
			For Local i:Int=0 Until tused.Length
				If tused.Get(i).tile = in Then Return True
			Next
			Return False
		End Lambda

		Local stindex := Lambda:Int(in:Int)
			For Local i:Int=0 Until tused.Length
				If tused.Get(i).tile = in Then Return i
			Next
			Return -1
		End Lambda


		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw			
			'add tile and add surroundings
			If exsists(map[x,y]) = False
				tused.Push(New wavenode(map[x,y]))
			End If			
				Print "added:"+map[x,y]
				Local zz:Int=stindex(map[x,y])
				If zz=-1 Then RuntimeError("ere")
				Local location:Int=0
				For Local y2:Int=y-1 To y+1
				For Local x2:Int=x-1 To x+1
					If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then 
						location +=1
						Continue
					End If
					tused.Get(zz).addtile(location,map[x2,y2])	
					location +=1
				Next
				Next
			
		Next
		Next		
	
		If tused.Length = 0 Then Return
		
		' Get a random tile from the tiles used stack
		Local randomtile := Lambda:Int()			
			Repeat			
				For Local i:Int=0 Until tused.Length
					If Rnd() <.01 Then Return tused.Get(i).tile 
				Next
			Forever
			Return False
		End Lambda

		

		'get legal tile
		Local getlegaltile := Lambda:Int(x:Int,y:Int)			
			
			Local l:Int[] = New Int[999]
			For Local i:Int=0 Until 999
				l[i]=-1
			Next
			'get what is allowed here by inserting
			'all legal tiles from around
			'add beside(0) 
			Local cnt:Int=0
		
			For Local y1:Int=y-1 To y+1
			For Local x1:Int=x-1 To x+1
				If x1<0 Or y1<0 Or x1>=mw Or y1>=mh
					cnt+=1
					Continue
				End If
	
				If cnt=4
					Else
				For Local i:Int=0 Until tused.Length
					If tused.Get(i).tile = map[x1,y1]
					For Local ii:Int=0 Until tused.Get(i).beside[8-cnt].Length
						l[tused.Get(i).beside[8-cnt].Get(ii)]+=1
					Next
					End If
				Next
				End If
				cnt+=1
			Next
			Next
			' count all that are 
			Local z:Int=4
			For Local ii:Int=0 Until 150
			For Local i:Int=0 Until 15
				If l[i] > z And Rnd()<.1 Then 
				If i<>0 Then Return i
				End If
			Next
			If Rnd()<.2 Then z-=1
			Next
			Return -1
		End Lambda
		

		' Create new map
		map = New Int[mw,mh]
		map[Rnd(0,mw),Rnd(0,mh)] = randomtile()		
		For Local i:Int=0 Until mw*mh/2
			
			Local x:Int=Rnd(mw)
			Local y:Int=Rnd(mh)
			
			If map[x,y] <> 0 Then Continue
			map[x,y]=getlegaltile(x,y)
			
		Next
		Print "done"
	End Method
	Method edit()
		Local x:Int=Mouse.X / tw
		Local y:Int=Mouse.Y / th
		If Mouse.ButtonDown(MouseButton.Left)
			map[x,y] = leftmousetile
		Elseif Mouse.ButtonDown(MouseButton.Right)
			leftmousetile = map[x,y]
		End If
	End Method
 	Method drawtile(canvas:Canvas,tile:Int,x:Float,y:Float)
		If tile = 0 ' air/nothing
			canvas.Color = Color.Blue
			canvas.DrawRect(x,y,tw+1,th+1)
		End If
		If tile = 1 ' sand
			canvas.Color = Color.Brown
			canvas.DrawRect(x,y,tw+1,th+1)
		End If
		If tile = 2 'sand and grass at top
			canvas.Color = Color.Brown
			canvas.DrawRect(x,y,tw+1,th+1)
			canvas.Color = Color.Green
			canvas.DrawRect(x,y,tw+1,th/5)
		End If
		If tile = 3 ' rock
			canvas.Color = Color.Grey
			canvas.DrawRect(x,y,tw+1,th+1)
		End If
		If tile = 4 'rock light side left
			canvas.Color = Color.Grey
			canvas.DrawRect(x,y,tw+1,th+1)
			canvas.Color = Color.LightGrey
			canvas.DrawRect(x,y,tw/5,th+1)
		End If
		If tile = 5 'rock light right left
			canvas.Color = Color.Grey
			canvas.DrawRect(x,y,tw+1,th+1)
			canvas.Color = Color.LightGrey
			canvas.DrawRect(x+tw-(tw/5),y,tw/5,th+1)
		End If
		If tile = 6 'rock light top side
			canvas.Color = Color.Grey
			canvas.DrawRect(x,y,tw+1,th+1)
			canvas.Color = Color.LightGrey
			canvas.DrawRect(x,y,tw+1,th/5)
		End If
		If tile = 7 'rock ramp left bottom to up
			canvas.Color = Color.Grey
			canvas.DrawTriangle(x+tw,y,x,y+th,x+tw,y+th)
			canvas.Color = Color.LightGrey
			canvas.DrawQuad(x+tw,y,x,y+th,x+tw/5,y+th,x+tw,y+th/5)
		End If
		If tile = 8  'rock ramp right bottom up
			canvas.Color = Color.Grey
			canvas.DrawTriangle(x,y,x,y+th,x+tw,y+th)
			canvas.Color = Color.LightGrey
			canvas.DrawQuad(x,y,x+tw,y+th,x+tw-tw/5,y+th,x,y+th/5)
		End If
		If tile = 9 ' rock left and top highlighted
			canvas.Color = Color.Grey
			canvas.DrawRect(x,y,tw+1,th+1)
			canvas.Color = Color.LightGrey
			canvas.DrawRect(x,y,tw+1,th/5)
			canvas.DrawRect(x,y,tw/5,th+1)
		End If
		If tile = 10 ' rock Right and top highlighted
			canvas.Color = Color.Grey
			canvas.DrawRect(x,y,tw+1,th+1)
			canvas.Color = Color.LightGrey
			canvas.DrawRect(x,y,tw+1,th/5)
			canvas.DrawRect(x+tw-tw/5,y,tw/5,th+1)
		End If

	End Method
	Method tileselect(canvas:Canvas)		
		canvas.Clear(Color.Black)
		Local cnt:Int=0
		Local highlight:Int
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			
			drawtile(canvas,cnt,x*(tw),y*(th))
			If rectsoverlap(x*(tw),y*(th),tw,th,Mouse.X,Mouse.Y,1,1)
				canvas.Color = Color.Yellow.Blend(New Color(.1,.1,.1,.2),.5)
				canvas.DrawRect(x*(tw),y*(th),tw,th)
				If Mouse.ButtonReleased(MouseButton.Left)				
						leftmousetile = cnt
						Print leftmousetile
				Elseif Mouse.ButtonReleased(MouseButton.Right)
						rightmousetile = cnt
						Print rightmousetile
				End If
	
			End If
			
			cnt+=1
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			drawtile(canvas,map[x,y],x*tw,y*th)
		Next
		Next
	End Method
	Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
    	If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    	If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    	Return True
	End Function	
End Class

Class MyWindow Extends Window
	Field mywfc:wfc
	Field delay:Int=20,maxdelay:Int=20
	Method New()
		mywfc = New wfc(Width,Height,16,16)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		delay+=1
		App.RequestRender() ' Activate this method 
		
		mywfc.draw(canvas)
		If delay>maxdelay Then mywfc.edit()
		If Keyboard.KeyDown(Key.LeftShift) Then mywfc.tileselect(canvas) ; delay=0
		
		If Keyboard.KeyReleased(Key.Space)
			mywfc.dofunction()
		End If
		
		If Keyboard.KeyReleased(Key.I)
			Local x:Int=Mouse.X/mywfc.tw
			Local y:Int=Mouse.Y/mywfc.th
			mywfc.printinfo(mywfc.map[x,y])
		End If
		
		
		If Keyboard.KeyReleased(Key.Key1) Then pastemap()
		If Keyboard.KeyReleased(Key.Key0) Then pastetoclip()
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()				
	End Method	
	Method pastetoclip()
		Local d:String=""
		Local cnt:Int=0
		For Local y:Int=0 Until mywfc.mh
			d+="m["+cnt+"]=~q"
		For Local x:Int=0 Until mywfc.mw			
			d+=translatetoabc(mywfc.map[x,y])
		Next
		cnt+=1
			d+="~q~n"
		Next
		instance.ClipboardText = d
	End Method
	Method pastemap()
		Local m:String[] = New String[16]
m[0]="aaaaaaaaaaaaaaaa"
m[1]="aaaaaaaaaaaaaaaa"
m[2]="aajggkaaaaaajkaa"
m[3]="aaeddfaaaaaaefaa"
m[4]="aaeddfaaaaaaefaa"
m[5]="aaeddfaaaaaaefaa"
m[6]="aaeddfaaaaaaefaa"
m[7]="aaeddfaaaaaaefaa"
m[8]="aaeddfaaaaaaefaa"
m[9]="aaeddfaaaaaaefaa"
m[10]="aaeddfaaaaaaefaa"
m[11]="aaeddfaahiaaefaa"
m[12]="cccccccccccccccc"
m[13]="bbbbbbbbbbbbbbbb"
m[14]="bbbbbbbbbbbbbbbb"
m[15]="bbbbbbbbbbbbbbbb"
	
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			mywfc.map[x,y] = translateto0(m[y].Mid(x,1))
			'mywfc.map[x,y] = Int(m[y].Mid(x,1))
		Next
		Next	
	End Method
	Method translateto0:Int(in:String)
		Select in
			Case "a"
				Return 0
			Case "b"
				Return 1
			Case "c"
				Return 2
			Case "d"
				Return 3
			Case "e"
				Return 4
			Case "f"
				Return 5
			Case "g"
				Return 6
			Case "h"
				Return 7
			Case "i"
				Return 8
			Case "j"
				Return 9
			Case "k"
				Return 10
			Case "l"
				Return 11
			Case "m"
				Return 12
			Case "n"
				Return 13
			Case "o"
				Return 14
			Case "p"
				Return 15
			Case "q"
				Return 16
			Case "r"	
				Return 17				
		End Select
		Return 0
	End Method
	Method translatetoabc:String(in:Int)
		Select in
			Case 0
				Return "a"
			Case 1
				Return "b"
			Case 2
				Return "c"
			Case 3
				Return "d"
			Case 4
				Return "e"
			Case 5
				Return "f"
			Case 6
				Return "g"
			Case 7
				Return "h"
			Case 8
				Return "i"
			Case 9
				Return "j"
			Case 10
				Return "k"
			Case 11
				Return "l"
			Case 12
				Return "m"
			Case 13
				Return "n"

		End Select
		Return "a"
	End Method
End	Class

Function Main()
	'New AppInstance		
	instance = New AppInstance
	New MyWindow
	App.Run()
End Function
