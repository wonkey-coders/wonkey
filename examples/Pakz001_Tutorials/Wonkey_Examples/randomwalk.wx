#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class randomwalk
	Field map:Int[,] ' array
	Field w:Int,h:Int ' width and height of the map
	Field sw:Int,sh:Int 'screenwidth and screenheight
	Field tw:Float,th:Float ' tile width and height
	Field sx:Int,sy:Int,ex:Int,ey:Int 'start x and y and end x and y
	Field cx:Int,cy:Int 'current x and y
	Method New(sw:Int,sh:Int,w:Int,h:Int)
		Self.w = w
		Self.h = h
		Self.sw = sw
		Self.sh = sh
		Self.tw = Float(sw) / Float(w)
		Self.th = Float(sh) / Float(h)
		map = New Int[w,h] ' create our map array
		' Set a random start and end
		SeedRnd(Microsecs())
		sx = Rnd(w)
		sy = Rnd(h)
		ex = Rnd(w)
		ey = Rnd(h)
		' If start is same as end then change value
		While sx = ex And sy = ey
			ex = Rnd(w)
			ey = Rnd(h)
		Wend
		cx = sx
		cy = sy
	End Method
	
	' Here we are going to execute the walker
	Method randomwalk()
		' First we are going to read the area around the agents
		' position. -1 if the position is blocked.
		Local cnt:Int=0
		Local tx:Stack<Int> = New Stack<Int>
		Local ty:Stack<Int> = New Stack<Int>
		For Local y:Int=-1 To 1
		For Local x:Int=-1 To 1
			Local ax:Int=cx+x
			Local ay:Int=cy+y
			
			If ax>=0 And ax<w And ay>=0 And ay<h And map[cx+x,cy+y] = 0 Then 
				tx.Push(x)
				ty.Push(y)
			Else
				tx.Push(-1)
				ty.Push(-1)
			End If
			cnt+=1
		Next
		Next
		' Here we are going to see if we have a straight path to the destination
		Local nnx:Int=cx,nny:Int=cy
		If cx<ex Then nnx+=1
		If cx>ex Then nnx-=1
		If cy<ey Then nny+=1
		If cy>ey Then nny-=1
		If map[nnx,nny] = 1
			Local c:Int=0
			Local rx:Int=Rnd(tx.Length)
			Local ry:Int=Rnd(ty.Length)
			While map[cx+tx.Get(rx),cy+ty.Get(ry)] = 1
				rx = Rnd(tx.Length)
				ry = Rnd(ty.Length)
				c+=1
				If c>50 Then Return
			Wend
			cx += tx.Get(rx)
			cy += ty.Get(ry)
		Else
			cx = nnx
			cy = nny
		End If
		
		' If we are at the destination then shuffle start and end
		If cx = ex And cy = ey
			Local xx:Int=Rnd(w)
			Local yy:Int=Rnd(h)
			sx = xx
			sy = yy
			xx=Rnd(w)
			yy=Rnd(h)
			ex = xx
			ey = yy
			While sx = ex And sy = ey
			sx=Rnd(w)
			sy=Rnd(h)
			Wend			
		End If
	End Method
	
	' here we edit the map (blocked/open)
	Method editmap()
		If Mouse.ButtonPressed(MouseButton.Left) = True
			Local x:Int=Mouse.X/tw
			Local y:Int=Mouse.Y/th
			If x<0 Or y<0 Or x>=w Or y>=h Then Return
			' Do not put block on start or end position
			If Not (x = sx And y = sy)
			If Not (x = ex And y = ey)
				If map[x,y] = 0 Then map[x,y] = 1 Else map[x,y] = 0
			End If
			End If
		End If
	End Method
	' Here we draw the map
	Method drawmap(canvas:Canvas)
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			If x = sx And y = sy
				canvas.Color = Color.Green
				canvas.DrawRect(x*tw,y*th,tw,th)
				canvas.Color = Color.Yellow
				canvas.DrawText("Start",x*tw,y*th)
			Endif
			If x = ex And y = ey
				canvas.Color = Color.Red
				canvas.DrawRect(x*tw,y*th,tw,th)
				canvas.Color = Color.Yellow
				canvas.DrawText("End",x*tw,y*th)
			Endif
			If map[x,y] > 0 Then 
				canvas.Color = Color.White
				canvas.DrawRect(x*tw,y*th,tw+1,th+1)
			End If
		Next
		Next
		' Draw the agent
		canvas.Color = Color.Red
		canvas.DrawOval(cx*tw,cy*th,tw,th)
	End Method
End Class

Class MyWindow Extends Window
	Field myrw:randomwalk

	Method New()
		myrw = New randomwalk(Width,Height,30,30)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Update the randomwalk
		myrw.editmap()
		'
		If Rnd()<.1 Then myrw.randomwalk()
		' Draw the map
		myrw.drawmap(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
