#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field tmpim:= New Image[10]
	Method New()
		SeedRnd(Microsecs())
		For Local i:Int=0 Until 4
			tmpim[i] = New Image(32,32)
			tmpim[i] = createwater()
		Next

	End method
	'Here we create a random topdown water tile
	Method createwater:Image()
		Local tw:Int=32,th:Int=32
		Local im:Image
		Local can:Canvas
		im = New Image(tw,th)
		can = New Canvas(im)
		can.Clear(Color.Blue.Blend(Color.White,.3))
		can.Flush()

		' Store the water layer
		Local tm:Int[,] = New Int[tw,th]
		' create our water layer
		tm = makelayer(tw,th,Rnd(100,800))
		For Local y:Int=0 Until th
		For Local x:Int=0 Until tw
			If tm[x,y] = 1 Then
				can.Color = Color.Blue.Blend(Color.White,.45)
				can.DrawPoint(x,y)
				' make tilable
				If Rnd()<.7
				If x=tw-1 Then 
					If Rnd()<.5
					can.DrawPoint(0,y)
					Else
					can.DrawPoint(tw-2,y)
					End If					
				End If
				If x=0 Then 
					If Rnd()<.5
					can.DrawPoint(tw-1,y)
					Else
					can.DrawPoint(1,y)
					End If					
				End If
				If y=th-1 Then 
					If Rnd()<.5
					can.DrawPoint(x,0)
					Else
						can.DrawPoint(x,th-2)						
					End If
				End If
				If y=0 Then 
					If Rnd()<.5
					can.DrawPoint(x,th-1)
					Else
					End If
				End If
				End If

			End If
		Next
		Next
'		' Create our top layer (lighter)
		tm = New Int[tw,th]
		tm = makelayer(tw,th,Rnd(100,800))
		For Local y:Int=0 Until th
		For Local x:Int=0 Until tw
			If tm[x,y] = 1 Then
				can.Color = Color.Blue.Blend(Color.White,.5)
				If Rnd()<.2 Then can.Color = Color.White
				' make tilable
				If Rnd()<.7
				If x=tw-1 Then 
					If Rnd()<.5
					can.DrawPoint(0,y)
					Else
					can.DrawPoint(tw-2,y)					
					End If
				End If
				If x=0 Then 
					If Rnd()<.5
					can.DrawPoint(tw-1,y)
					Else
					can.DrawPoint(1,y)
					End If
				End If
				If y=th-1 Then 
					If Rnd()<.5
					can.DrawPoint(x,0)
					Else
					can.DrawPoint(x,th-2)
					End If
				End If
				If y=0 Then 
					If Rnd()<.2
					can.DrawPoint(x,th-1)
					Else
					can.DrawPoint(x,1)
					End If
				End If
				End If
				can.DrawPoint(x,y)
			End If
		Next
		Next
		
		'finsih up
		can.Flush()
		'
		Return im
	End Method
	'
	' This creates a pattern of water reflection
	' depth is the blurry thickness (defaulted at making to 400)
	Method makelayer:Int[,](tw:Int,th:Int,deep:Int=500)	
		' We want to create points and connect those
		Local px:Stack<Int> = New Stack<Int>
		Local py:Stack<Int> = New Stack<Int>

		'create points in some kind of pattern
		Local lx:Int=0
		Local st:Int=6
		For Local ly:Int=0 Until th Step st
		For Local i:Int=0 Until 2
			lx+=Rnd(tw/2)
			If lx>=tw Then lx=Rnd(0,5)
			px.Push(lx)
			py.Push(ly)
		Next
		Next

		For Local z:Int=0 Until 16
		'fix - make sure no double y
		For Local i:Int =0 Until px.Length
		For Local j:Int=0 Until px.Length
			If i=j Then Continue
			If distance(py.Get(i),0,py.Get(j),0)<2				
				py.Set(i,Rnd(th))	
			End if
		Next
		Next
		'no double x
		For Local i:Int =0 Until px.Length
		For Local j:Int=0 Until px.Length
			If i=j Then Continue
			If distance(px.Get(i),0,px.Get(j),0)<2				
				px.Set(i,Rnd(tw))
			End if
		Next
		Next
		Next
		'
		' Here we pick one point and connect it to the nearest next point
		Local tm:Int[,] = New Int[tw,th]
		Local x:Float=px.Get(0)
		Local y:Float=py.Get(0)
		Local sx:Int=x,sy:Int=y
		Local numt:Int=px.Length
		Local numc:Int=0
		tm[x,y] = 1
		While numc<numt
			'find closest next point
			Local x2:Int,y2:Int
			Local d:Int=999
			For Local i:Int=0 Until px.Length
				If tm[px.Get(i),py.Get(i)] = 1 Then Continue				
				If distance(px.Get(i),py.Get(i),x,y) < d										
					x2 = px.Get(i)
					y2 = py.Get(i)
					d = distance(x2,y2,x,y)
				End If
			Next
			tm[x2,y2] = 1
			numc+=1
			'connect line
			While distance(x,y,x2,y2) > 1
				If x<x2 Then x+=1
				If x>x2 Then x-=1
				If y<y2 Then y+=1
				If y>y2 Then y-=1
				If Rnd()<.5 
					Local ox:Int=x,oy:Int=y
					x+=Rnd(-2,2)
					y+=Rnd(-2,2)
					If x<0 Or x>=tw Then x=ox
					If y<0 Or y>=th Then y=oy
				End If
				tm[x,y] = 1
			Wend
			x=x2
			y=y2
		Wend
		'connect start with end
		While distance(x,y,sx,sy) > 1
			If x<sx Then x+=1
			If x>sx Then x-=1
			If y<sy Then y+=1
			If y>sy Then y-=1
			If Rnd()<.3 
				Local ox:Int=x,oy:Int=y
				x+=Rnd(-2,2)
				y+=Rnd(-2,2)
				If x<0 Or x>=tw Then x=ox
				If y<0 Or y>=th Then y=oy
			End If
			
			tm[x,y] = 1
		Wend

		' tm holds the starting point of the back layer of the water
		' we now are going to grow them a little bit(edge grow)
		
		Local zi:Int
		For zi=0 To deep
			Local x1:Int=Rnd(tw)
			Local y1:Int=Rnd(th)
			If Not tm[x1,y1]=1 Then Continue
			Local x2:Int=x1+Int(Rnd(-2,2))
			Local y2:Int=y1+Int(Rnd(-2,2))
			If x2<0 Then x2=tw-1
			If x2>=tw Then x2=0
			If y2<0 Then y2=th-1
			If y2>=th Then y2=0
			tm[x2,y2] = 1
		Next
		
		Return tm
	End Method

	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		canvas.Color = Color.White
		Local cnt:Int=0
		For Local y1:Int=0 Until 2
		For Local x1:Int=0 Until 2			
			canvas.DrawImage(tmpim[cnt],x1*340,y1*200,0,4,4)
			For Local y:Int=0 Until 5
			For Local x:Int=0 Until 5
				canvas.DrawImage(tmpim[cnt],(x1*320)+x*32+160,(y1*200)+y*32)
			Next
			Next
			cnt+=1
		Next
		Next
		'generate new tiles
		If Keyboard.KeyReleased(Key.Space) Then 
			For Local i:Int=0 Until 4
				tmpim[i] = New Image(32,32)
				tmpim[i] = createwater()
			Next			
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class
    ' Manhattan Distance (less precise)
    Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
	    Return Abs(x2-x1)+Abs(y2-y1)   
    End Function
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
