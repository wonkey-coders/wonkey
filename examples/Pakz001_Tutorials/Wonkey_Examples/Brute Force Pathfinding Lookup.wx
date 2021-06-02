#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
' Large maps require super CPU!! (2020)
Global mapwidth:Int=8
Global mapheight:Int=8
Global tilewidth:Int,tileheight:Int
Global maxpathlen:Int=12
Global path:Int[] = New Int[maxpathlen]
Global map:Int[,]

Class p
	Field path:Int[] = New Int[maxpathlen]
	Method New(p:Int[])
		For Local i:Int=0 Until maxpathlen
			path[i] = p[i]
		Next
	End Method
End Class

Class MyWindow Extends Window
	Field lupath:List<p> = New List<p>
	Field sx:Int,sy:Int
	Field ex:Int,ey:Int
	Field ms:Int
	Field pathed:Bool=False
	Method New()
		Title="Lookup Table Brute Force Pathfinding"
		tilewidth=Width/mapwidth
		tileheight=Height/mapheight
		sx = 2
		sy = 2
		ex = 7
		ey = 7		
		map = New int[mapwidth,mapheight]
		Local cnt:Int=0
			path = New Int[maxpathlen]	
			For Local i:Int=0 Until maxpathlen
				path[i]=-1
			Next
		Local exitloop:Bool=False
		While exitloop=False
			lupath.Add(New p(path))
			exitloop = True
			For Local i:Int=1 Until maxpathlen-1
				If path[i] = -1 Then 
				exitloop=False				
				Exit
				End If
			Next
			incpath()
			'cnt+=1
			If Rnd(15000)<1 Then Print Millisecs()
		Wend
		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		drawgrid(canvas)
		If pathed = True Then drawpath(canvas)

		If Keyboard.KeyReleased(Key.Space)
		
			ms = Millisecs()
			Local cnt:Int=0
			For Local i:=Eachin lupath
				For Local ii:Int=0 Until maxpathlen
					path[ii] = i.path[ii]
				Next
				Local s:Bool=pathfound()
				If s=True Then
					Print "Milliseconds taken : "+(Millisecs()-ms)
					pathed = True					
					Exit
				End If
					
				cnt+=1
				' timeout after xxxxx millisecs
				If ms+10000<Millisecs() Then 
					Print "failed - timeout"
					pathed=False
					Exit
				End If
			Next
			
		End If

		Local tx:Int=Mouse.X/tilewidth
		Local ty:Int=Mouse.Y/tileheight
				
		If Mouse.ButtonReleased(MouseButton.Middle)
			If (tx=sx And ty=sy) Or (tx=ex And ty=ey)
			Else
			If map[tx,ty] = 1
				map[tx,ty] = 0
				Else
				map[tx,ty] = 1
			End If
			End if
		End If

		If Mouse.ButtonReleased(MouseButton.Left) 
			If map[tx,ty] = 0
				sx = tx
				sy = ty
				pathed=False
			End If
		End If
		If Mouse.ButtonReleased(MouseButton.Right) 
			If map[tx,ty] = 0
				ex = tx
				ey = ty
				pathed=False
			End If
		End If
		
		canvas.Color = Color.Black
		canvas.DrawText("LMB(start)/RMB(end)/SPACE(findpath)MMB(wall)",0,0)

		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	Method pathfound:Bool()
		Local cx:Int=sx
		Local cy:Int=sy
		For Local i:Int=maxpathlen-1 Until 0 Step -1			
			Select path[i]
				Case 0'up
					cy-=1
				Case 1'right
					cx+=1
				Case 2'down
					cy+=1
				Case 3'left
					cx-=1					
				Default'exit
					Return False
			End Select
			If cx<0 Then Return False
			If cx>=mapwidth Then Return False
			If cy<0 Then Return False
			If cy>=mapheight Then Return False
			If map[cx,cy] = 1 Then Return False
			If ex = cx And ey = cy Then 
				Print "found"
				Return True
			Endif
		Next
		Return False
	End Method
	
	Method incpath()
		path[maxpathlen-1]+=1
		For Local i:Int=maxpathlen-1 Until 1 Step-1
			If path[i] > 3 Then 
				path[i] = 0				
				path[i-1] += 1				
			Endif
		Next
	End Method

	Method drawgrid(canvas:Canvas)		
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			canvas.Color = Color.Black
			canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
			canvas.Color = Color.White
			canvas.DrawRect(x*tilewidth+1,y*tileheight+1,tilewidth-1,tileheight-1)			
			If map[x,y] = 1 Then 
				canvas.Color = Color.Magenta
				canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
			End If
			If x=sx And y = sy Then
				canvas.Color = Color.Green
				canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
				canvas.Color = Color.Red
				canvas.DrawText("start LMB",x*tilewidth,y*tileheight)
			End If
			If x=ex And y = ey Then
				canvas.Color = Color.Yellow
				canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
				canvas.Color = Color.Red
				canvas.DrawText("end RMB",x*tilewidth,y*tileheight)
			End If
		Next
		Next				
	End Method
	Method drawpath(canvas:Canvas)
		canvas.Color = Color.Red
		Local cx:Int=sx
		Local cy:Int=sy
		For Local i:Int=maxpathlen-1 Until 0 Step -1
			Select path[i]
				Case 0'up
					cy-=1
				Case 1'right
					cx+=1
				Case 2'down
					cy+=1
				Case 3'left
					cx-=1					
			End Select			
			canvas.DrawCircle(cx*tilewidth+tilewidth/2,cy*tileheight+tileheight/2,10)
			If ex = cx And ey = cy Then 
				Return 
			Endif
		Next				
	End Method

End	Class



Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
