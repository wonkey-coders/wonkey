#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class tilegen
	Field map:Int[,]
	Field imw:Int,imh:Int
	Field im:Image
	Field imcan:Canvas
	Field col:Color
	Method New(w:Int,h:Int,col:Color)
		Self.imw = w
		Self.imh = h
		Self.col = col
		im = New Image(w,h)
		imcan = New Canvas(im)
		imcan.Clear(Color.Yellow)
		imcan.Flush()
		map = New Int[w,h]
		generateim()
		createim()
	End Method 
	Method generateim()
		Local bh:Int=imh/3
		Local bw:Int=Rnd(imw/4,imw/2)
		'mapblock(0,0,32,32)
		Local x:Int=0
		Local y:Int=0
		Repeat
		Repeat 
			mapblock(x,y,bw,bh)	
			x+=bw
			bw=Rnd(imw/4,imw/2)
			If (x+9)+bw>=imw Then 
				mapblock(x,y,(imw-x-1),bh)	
				Exit
			End If
		Forever
		x=0
		bw=Rnd(imw/4,imw/2)
		y+=bh
		Until y>=imh
	End Method
	Method mapblock(x:Int,y:Int,w:Int,h:Int)
		If w<3 Or h<3 Then Return
		If x+w >= imw Or y+h >= imh Then Return
		'light edges
		For Local x2:Int=x Until x+w
			map[x2,y] = 1
			
			If x2+1<x+w-1 Then map[x2+1,y+1] = 4
			If x2+2<x+w-1 Then map[x2+2,y+2] = 4
		Next
		For Local y2:Int=y To y+h
			map[x+w,y2] = 1
			If y2+1<y+h Then map[x+w-1,y2+1] = 4
			If y2+2<y+h Then map[x+w-2,y2+1] = 4
		Next
		'dark edges
		For Local y2:Int=y+1 Until y+h
			map[x,y2] = 1
			If y2+2<y+h Then map[x+1,y2+1] = 2
			If y2+3<y+h Then map[x+2,y2+1] = 2
		Next
		For Local x2:Int=x Until x+w
			map[x2,y+h] = 1
			If x2+2<x+w Then map[x2+1,y+h-1] = 2
			If x2+3<x+w Then map[x2+1,y+h-2] = 2
		Next
		' Fill remaining
		For Local y2:Int=y Until y+h
		For Local x2:Int=x Until x+w
			If map[x2,y2] = 0 Then map[x2,y2] = 3
		Next
		Next

		' edge smear TOP
		For Local x2:Int=x+1 Until x+w
			If x2<x+w/2 And Rnd()<.2
				Local d:Int=Rnd(1,5)
				Local d2:Int=0
				While d2<d
					If x2+d2<x+w Then map[x2+d2,y] = 2
					d2+=1
				Wend				
			End If			
			If Rnd()<.1 Then map[x2,y+1] = 2
			If Rnd()<.1 Then 
				map[x2,y+3] = 4
				If Rnd()<.3
					map[x2,y+4] = 4
				End If
			End If
		Next		
'		' edge smear LEFT
		For Local y2:Int=y+1 Until y+(h-1)
			If y2<y+h/2 And Rnd()<.2
				Local d:Int=Rnd(1,5)
				Local d2:Int=0
				While d2<d
					If y2+d2<y+h Then map[x,y2+d2] = 2
					d2+=1
				Wend				
			End If
			If Rnd() < .2 Then 
				map[x+1,y2] = 1
				Local d:Int=Rnd(1,3)
				Local y3:Int=y2
				While y3<y+h And y3<y2+d
					map[x+1,y3] = 1
					y3+=1
				Wend
			End If
			If Rnd() < .2
				If x+3 < imw Then map[x+3,y2] = 2
			End If
		Next
		' edge smear RIGHT
		For Local y2:Int=y+1 Until y+(h-1)
			If y2<y+h/2 And Rnd()<.2
				Local d:Int=Rnd(1,5)
				Local d2:Int=0
				While d2<d
					If y2+d2<y+h Then map[x+w,y2+d2] = 4
					d2+=1
				Wend				
			End If
			If Rnd() < .2 Then 
				map[x+w-1,y2] = 3
				Local d:Int=Rnd(1,3)
				Local y3:Int=y2
				While y3<y+h And y3<y2+d
					map[x+w-3,y3] = 4
					y3+=1
				Wend
			End If			
		Next
		' edge smear BOTTOM
		For Local x2:Int=x Until x+w-1
			If x2>x+x+w/2 And Rnd()<.2 Then 
				Local d:Int=Rnd(1,5)
				Local d2:Int=0
				While d2<d
					If x2+d2<x+w Then map[x2+d2,y+h] = 2
					d2+=1
				Wend
			End If
			If Rnd()<.2 Then map[x2,y+h-1] = 1
			If Rnd()<.3 Then 
				map[x2,y+h-2] = 2
				If Rnd()<.5
					map[x2,y+h-3] = 2
				End If
			End If
		Next		
		' crack bottom to up
		If Rnd()<.6
		Local num:Int=Rnd(0,2)
		If Rnd()<.5 Then num=0
		For Local z:Int=0 To num
		Local dx:Float=Rnd(-1,1)
		Local y2:Float=y+h
		Local x2:Float=Rnd(x+3,x+(w-3))
		Local d:Int=Rnd(4,h/1.5)
		Local d2:Int=0
		Local light:Bool=False
		While d2<d 
			y2-=1
			x2+=dx
			If Rnd()<.2 Then dx=Rnd(-1,1)
			If Rnd()<.1 Then x2+=dx
			If x2<x Or x2>=x+w Then Exit
			d2+=1
			Local c:Int=1
			If d2>4 Then c = 2
			If Rnd()<.1
			Else
				map[x2,y2] = c
				If light=False And Rnd()<.1 And d2>2 Then map[x2-1,y2] = 4 ; map[x2-1,y2-1]=1;light=True
			End If
		Wend
		Next
		End If
		' crack top to down
		If Rnd()<.6
		Local num:Int=Rnd(0,2)
		If Rnd()<.5 Then num=0
		For Local z:Int=0 To num
		Local dx:Float=Rnd(-1,1)
		Local y2:Float=y
		Local x2:Float=Rnd(x+3,x+(w-3))
		Local d:Int=Rnd(4,h/1.5)
		Local d2:Int=0
		Local light:Bool=False
		While d2<d 
			y2+=1
			x2+=dx
			If Rnd()<.2 Then dx=Rnd(-1,1)
			If Rnd()<.1 Then x2+=dx
			If x2<x Or x2>=x+w Then Exit
			d2+=1
			Local c:Int=1
			If d2>4 Then c = 2
			If Rnd()<.1
			Else
				map[x2,y2] = c
				If light=False And Rnd()<.1 And d2>2 Then map[x2-1,y2] = 4 ; map[x2-1,y2-1]=1;light=True
			End If
		Wend
		Next
		End If
		' crack left to right
		If Rnd()<.6
		Local num:Int=Rnd(0,2)
'		If Rnd()<.5 Then num=0
		For Local z:Int=0 To num
		Local dy:Float=Rnd(-1,1)
		Local y2:Float=Rnd(y+3,y+(h-3))
		Local x2:Float=x
		Local d:Int=Rnd(4,w/1.5)
		Local d2:Int=0
		Local light:Bool=False
		While d2<d 
			x2+=1
			y2+=dy
			If Rnd()<.2 Then dy=Rnd(-1,1)
			If Rnd()<.1 Then y2+=dy
			If y2<y Or y2>=y+h Then Exit
			d2+=1
			Local c:Int=1
			If d2>4 Then c = 2
			If Rnd()<.2 Then 
			Else
				If light=False And x2>1 And Rnd()<.1 And d2>2 Then map[x2-1,y2] = 1 ; map[x2-1,y2-1]=1;light=True
				map[x2,y2] = c
			End If
			
		Wend
		Next
		End If

		' some spots
		Local d:Int=Rnd(10,40)
		For Local i:Int=0 Until (w+h)/d
			Local x1:Int=Rnd(x+2,x+w-2)
			Local y1:Int=Rnd(y+2,y+h-2)
			Local c:Int=Rnd(1,3)
			c=Rnd(1,4)
			map[x1,y1] = c
			c=Rnd(1,3)
			map[x1,y1+1] = c
			
			c=Rnd(1,3)
			If Rnd()<.4 map[x1-1,y1+1] = c
			c=Rnd(1,3)
			If Rnd()<.4 map[x1+1,y1+1] = c
		Next
		

	End Method
	Method createim()
		Local noiselevel:Float=Rnd(0.1,0.35)
		For Local y:Int=0 Until imh
		For Local x:Int=0 Until imw
			If map[x,y] = 0 Then Continue
			Select map[x,y]
				Case 0
					
				Case 1
					imcan.Color = col.Blend(Color.Black,.7)
				Case 2
					imcan.Color = col.Blend(Color.Black,.2)
				Case 3
					imcan.Color = col
				Case 4
					imcan.Color = col.Blend(Color.White,.4)
			End Select
			Local mc:Color 
			mc = imcan.Color
			If Rnd()<.5
			If Rnd()<.5
				mc = imcan.Color.Blend(Color.White,Rnd(noiselevel))
			Else
				mc = imcan.Color.Blend(Color.Black,Rnd(noiselevel))
			End If
			End If
			imcan.Color = mc			
			imcan.DrawPoint(x,y)	
		Next
		Next
		imcan.Flush()
	End Method
End Class 

Class MyWindow Extends Window
	Field mywall:tilegen
	Method New()
		mywall = New tilegen(64,64,Color.Grey.Blend(Color.Brown,.4))
	End method

	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		'
		
		If Keyboard.KeyReleased(Key.Key1) Then
			mywall = New tilegen(64,64,Color.Grey.Blend(New Color(Rnd(),Rnd(),Rnd()),.5))
		End If
		canvas.DrawImage(mywall.im,50,50,0,4,4)
		canvas.DrawImage(mywall.im,450,50,0,2,2)
		canvas.DrawImage(mywall.im,450,250,0,1,1)
		If Keyboard.KeyDown(Key.Space)
			canvas.Color = Color.White
			For Local y:Int=0 Until Height Step 128
			For Local x:Int=0 Until Width Step 128
				canvas.DrawImage(mywall.im,x,y,0,2,2)
			Next
			Next
		End If
		canvas.Color = Color.White
		canvas.DrawText("Press '1' and  space'",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
	End Method

End	Class

Function Main()
	New AppInstance
	New MyWindow
	App.Run()
End Function
