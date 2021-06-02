#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class map
	Field map:= New Int[50,50] 
	Field floodx:=New Stack<Int>
	Field floody:=New Stack<Int>
	Field drainx:=New Stack<Int>
	Field drainy:=New Stack<Int>
	Field olx:=New Stack<Int>
	Field oly:=New Stack<Int>
	Field clx:=New Stack<Int>
	Field cly:=New Stack<Int>
	Field cmap:=New Bool[50,50]
	Method New()
	For Local y:=22 Until 50
	For Local x:=0 Until 50
		map[x,y] = 1
	Next
	Next
	For Local y:=0 Until 50
		map[0,y] = 1
		map[49,y] = 1
	Next
	makewater(20,15,10,10)
	End Method 
	Method update()
		If Mouse.ButtonDown(MouseButton.Left)
			Local x:Int= Mouse.X/16
			Local y:Int = Mouse.Y/16
			If x>0 And x<50 And y>0 And y<50 
				map[x,y] = 2
			End if
		End if
		For Local i := 0 Until 60
		updatewater(Rnd()*49,Rnd()*49)
		next
	End Method 
	Method updatewater(x:Int,y:Int)
		If map[x,y] <> 2 Then Return
		Print "map value is :"+map[x,y]
		clx.Clear()
		cly.Clear()
		olx.Clear()
		oly.Clear()
		floodx.Clear()
		floody.Clear()
		drainx.Clear()
		drainy.Clear()
		For Local y:=0 Until 50
		For Local x:=0 Until 50
			cmap[x,y] = False
		Next
		Next		
		olx.Push(x)
		oly.Push(y)		
		While olx.Empty = False
			Local ax:Int=olx.Get(0)
			Local ay:Int=oly.Get(0)			
			olx.Erase(0)
			oly.Erase(0)			
			clx.Push(ax)
			cly.Push(ay)
			cmap[ax,ay] = True
			For Local bx:=-1 To 1
			For Local by:=-1 To 1
				If ax+bx>0 And ax+bx<50 And ay+by>0 And ay+by<50
				If cmap[ax+bx,ay+by] = False
				If map[ax+bx,ay+by] = 2
					olx.Push(ax+bx)
					oly.Push(ay+by)
					cmap[ax+bx,ay+by] = True
				End If 
				End If 
				End If
			Next
			Next
		Wend

		For Local y:=0 Until 50
		For Local x:=0 Until 50
			cmap[x,y] = False
		Next
		Next		

		For Local i:=0 Until clx.Length
			Local ax:Int=clx.Get(i)
			Local ay:Int=cly.Get(i)
			If ax>1 And ax<49 And ay>2 And ay<49				
				'left
				If map[ax-1,ay] = 0
				If map[ax+1,ay] = 2
				If map[ax,ay+1] = 2
					floodx.Push(ax-1)
					floody.Push(ay)
				End If
				End If
				End If
				If map[ax,ay+1] = 0
					floodx.Push(ax)
					floody.Push(ay+1)
				End If 
				If map[ax-1,ay+1] = 0					
					floodx.Push(ax-1)
					floody.Push(ay+1)
				End If
				If map[ax-1,ay] = 0
				If map[ax-1,ay+1] = 2
				If map[ax+1,ay] = 0
					floodx.Push(ax-1)
					floody.Push(ay)
				End If 
				End If 
				End If 
				'right
				If map[ax+1,ay] = 0
				If map[ax-1,ay] = 2
				If map[ax,ay+1] = 2
					floodx.Push(ax+1)
					floody.Push(ay)
				End If
				End If
				End If
				If map[ax+1,ay+1] = 0					
					floodx.Push(ax+1)
					floody.Push(ay+1)
				End If

				'drain			
				If map[ax,ay-1] = 0
				If map[ax,ay+1] = 0
					drainx.Push(ax)
					drainy.Push(ay)
				End If 
				End if					
				If map[ax,ay-1] = 0				
					drainx.Push(ax)
					drainy.Push(ay)
				End If
			End If
		Next
		Local cnt:Int=0
		For Local i:=0 Until floodx.Length
			map[floodx.Get(i),floody.Get(i)] = 2
			cnt+=1
		Next	
		Local cnt2:Int=0
		For Local i:=0 Until drainx.Length
			If i<(cnt-4)
				
				map[drainx.Get(i),drainy.Get(i)] = 0
			End If			
		Next
	End Method 
	Method makewater(x:Int,y:Int,w:Int,h:Int)
		For Local y1:=y Until y+h
		For Local x1:=x Until x+w
			map[x1,y1] = 2
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:=0 Until 50
		For Local x:=0 Until 50
			If map[x,y] = 0
				canvas.Color = Color.Black
				canvas.DrawRect(x*16,y*16,16,16)
			End If 
			If map[x,y] = 1
				canvas.Color = Color.Grey
				canvas.DrawRect(x*16,y*16,16,16)
			End If 
			If map[x,y] = 2
				canvas.Color = Color.Blue
				canvas.DrawRect(x*16,y*16,16,16)
			End If 
		Next
		Next
	End Method 
End Class 

Global mymap:map

Class MyWindow Extends Window

	Method New()
		mymap = New map()
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
