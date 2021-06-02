#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class maze
	Field sw:Int,sh:Int
	Field mw:Int,mh:Int
	Field tw:Float,th:Float
	Field mazex:Stack<Int> = New Stack<Int>
	Field mazey:Stack<Int> = New Stack<Int>	
	Field map:Int[,] = New Int[1,1]
	Field map2:Int[,,] = New Int[1,1,1]
	Enum wall
		up=1,
		right=2,
		down=3,
		left=4
	End Enum
	Method New(sw:Int,sh:Int,mw:Int,mh:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		tw = sw/mw
		th = sh/mh
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
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Black
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			Local x2:Int=(x*tw)+tw/2
			Local y2:Int=(y*th)+th/2
			For Local i:=0 Until 4
				If map2[x,y,i] > 0
				Select i
					Case 0
					canvas.DrawLine(x2,y2,x2,y2-th)
					Case 1
					canvas.DrawLine(x2,y2,x2+tw,y2)
					Case 2
					canvas.DrawLine(x2,y2,x2,y2+th)
					Case 3
					canvas.DrawLine(x2,y2,x2-tw,y2)
				End Select
				End If
			Next
		Next
		Next
	End Method
End Class

Global mymaze:maze


Class MyWindow Extends Window

	Method New()
		Title="Maze - Recursive backtracker."
		mymaze = New maze(Width,Height,10,10)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		'
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Then
			SeedRnd(Millisecs())				
			mymaze = New maze(Width,Height,10,10)
		End If
		'
		mymaze.draw(canvas)
		'
		canvas.Color = Color.Black
		canvas.DrawText("Press space for new maze",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
