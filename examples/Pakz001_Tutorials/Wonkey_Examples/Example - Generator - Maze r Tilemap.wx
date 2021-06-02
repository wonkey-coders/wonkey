#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class maze
	Field sw:Int,sh:Int
	Field mw:Int,mh:Int
	Field tmw:Int,tmh:Int
	Field tw:Float,th:Float
	Field mazex:Stack<Int> = New Stack<Int>
	Field mazey:Stack<Int> = New Stack<Int>	
	Field tilemap:Int[,] = New Int[1,1]
	Field map:Int[,] = New Int[1,1]
	Field map2:Int[,,] = New Int[1,1,1]
	Enum wall
		up=1,
		right=2,
		down=3,
		left=4
	End Enum
	Method New(sw:int,sh:Int,mw:Int,mh:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh	
		tmw = (mw*2)+1
		tmh = (mh*2)+1
		tw = Float(sw)/((Float(tmw)))
		th = Float(sh)/((Float(tmh)))
		tilemap = New Int[mw*3,mh*3]
		map = New Int[mw,mh]
		map2 = New Int[mw,mh,4]
		makemaze()
	End Method 
	Method makemaze()
		Local ax:Int[] = New Int[](0,1,0,-1)
		Local ay:Int[] = New Int[](-1,0,1,0)
		mazex.Push(Rnd(mw))
		mazey.Push(Rnd(mh))								
		While mazex.Empty = False			
			Local x:Int=mazex.Top
			Local y:Int=mazey.Top
			Local d:Int[] = New Int[4]
			Local deadend:Bool=True
			For Local i:=0 Until ax.Length
				Local x2:Int=x+ax[i]
				Local y2:Int=y+ay[i]
				If x2>=0 And x2<mw And y2>=0 And y2<mh
					If map[x2,y2] = 0 
						d[i] = 1
						deadend=False
					End If
				End If
			Next
			
			If deadend = False				
				Local eloop:Bool=False
				While eloop = False
					Local r:Int=Rnd(0,4)
					If d[r] = 1 Then						
						eloop = True
						Local nx:Int=x+ax[r]
						Local ny:Int=y+ay[r]
						map2[x,y,r] = 1																		
						mazex.Push(nx)
						mazey.Push(ny)						
						map[x,y] = 1
						map[nx,ny] = 1
					End If
				Wend
			Else	' if nothing happened than backtrace
				mazex.Pop()
				mazey.Pop()
			End If
		Wend		
		' convert the map into a tilemap
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			Local x2:Int=x*2
			Local y2:Int=y*2
			If map[x,y] = 1 Then tilemap[x2+1,y2+1] = 1
			If map2[x,y,0] = 1 Then tilemap[x2+1,y2] = 1
			If map2[x,y,1] = 1 Then tilemap[x2+2,y2+1] = 1
			If map2[x,y,2] = 1 Then tilemap[x2+1,y2+2] = 1
			If map2[x,y,3] = 1 Then tilemap[x2,y2+1] = 1			
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Clear(Color.Black)
		canvas.Color = Color.Brown
		For Local y:Float=0 Until tmh Step 1
		For Local x:float=0 Until tmw Step 1
			Local x2:Float=(x*tw)
			Local y2:Float=(y*th)
			If tilemap[x,y] = 1 Then 
				canvas.DrawRect(x2,y2,tw,th)
			End If
		Next
		Next	
	End Method	
End Class

Global mymaze:maze

Class MyWindow Extends Window
	Field cnt:Int=0
	Method New()
		Title="Maze - Recursive backtracker."
		mymaze = New maze(Width,Height,10,10)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		cnt+=1
		'
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Or cnt>200 Then
			cnt=0
			SeedRnd(Millisecs())
			Local s:Int=Rnd(10,64)				
			mymaze = New maze(Width,Height,s,s)
		End If
		'
		mymaze.draw(canvas)
		'
		canvas.Color = Color.White
		canvas.DrawText("Press space or tap for new maze",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
