#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class tile
	Field tw:Int,th:Int
	Field map:Int[,]
	Field im:Image
	Field imcan:Canvas
	Field col:Color
	Field noise:Bool=False
	Method New(tw:Int,th:Int,col:Color,noise:Bool=True)
		Self.tw = tw
		Self.th = th
		Self.col = col
		Self.noise = noise
		im = New Image(tw,th)
		imcan = New Canvas(im)
		imcan.Clear(Color.Blue)
		imcan.Flush()
		map = New Int[tw,th]
		generatetile()
		createtile()
	End Method
	Method generatetile()
		If Rnd()<.5
		drawblock(0,0,tw,th/4)
		drawblock(0,th/4,tw/2,th/4)
		drawblock(tw/2,th/4,tw/2,th/4)
		drawblock(0,th/4*2,tw,th/4*2)
		Return
		End If
		If Rnd()<.5
		drawblock(0,0,tw/2,th/3)
		drawblock(0,th/3,tw/2,th/1.5)
		drawblock(tw/2,0,tw/2,th)
		Return
		End If
		For Local x:Int = 0 Until tw Step tw/2
		For Local y:Int = 0 Until th Step th/2
		drawblock(x,y,tw/2,th/2)
		Next
		Next

	End Method
	Method drawblock(x:Int,y:Int,w:Int,h:Int)
'		If x<0 Or y<0 Or x+w>=tw Or y+h>=th Then Return
'		w=w+1
'		h=h+1
		For Local y1:Int=y Until y+h
		For Local x1:Int=x Until x+w
			map[x1,y1] = 1
		Next
		Next
		' left top to right top lighter bar
		For Local x1:Int=x Until x+(w-1)
			map[x1,y] = 3
		Next
		' left top to left bottom light bar
		For Local y1:Int=y Until y+(h-1)
			map[x,y1] = 3
		Next
		' left bottom to right bottom dark bar
		For Local x1:Int=x+1 Until x+(w-1)
			map[x1,y+h-1] = 2
		Next
		' right top to right bottom dark color
		For Local y1:Int=y+1 Until y+(h)
			map[x+w-1,y1] = 2
		Next
		' noise light top left to top right
		For Local x1:Int=x+1 Until x+(w-4)
			If Rnd() < .2 Or x1=x+1
				Local d:Int=Rnd(1,4)
				If x1 < x+(w/3) Then d = 6
				For Local x2:Int=x1 Until x1+d
					If x2>x+(w-3) Then Exit
					If y+1>=th Then Continue
					map[x2,y+1] = 3
				Next
			End if
		Next
		' noise light top left to bottom left
		For Local y1:Int=y+1 Until y+(h-4)
			If Rnd() < .2 Or y1=y+1
				Local d:Int=Rnd(1,4)
				If y1 < y + (h/3) Then d = 5
				For Local y2:Int=y1 Until y1+d
					If y2>y+(h-3) Then Exit
					map[x+1,y2] = 3
				Next
			End if
		Next
		'
		' Inner Lighting left top
		'		
		If w>7 And h > 5
			' noise light top left to top right
			For Local x1:Int=x+2 Until x+(w/3)
				If Rnd() < .2 Or x1=x+2
					Local d:Int=Rnd(1,4)
					If x1 < x+(w/3) Then d = 4
					For Local x2:Int=x1 Until x1+d
						If x2>x+(w-4) Then Exit
						map[x2,y+2] = 3
					Next
				End if
			Next
			' noise light top left to bottom left
			For Local y1:Int=y+2 Until y+(h/3)
				If Rnd() < .2 Or y1=y+2
					Local d:Int=Rnd(1,4)
					If y1 < y + (h/3) Then d = 4
					For Local y2:Int=y1 Until y1+d
						If y2>y+(h-4) Then Exit
						map[x+2,y2] = 3
					Next
				End if
			Next							
		End If
		
		
		' noise right bottom to left bottom
		For Local x1:Int=x+(w-1) Until x+4 Step -1
			If Rnd() < .2 Or x1=x+(w-1)
				Local d:Int=Rnd(1,4)
				If x1 > x+(w/4) Then d = 4
				For Local x2:Int=x1 Until x1-d Step -1
					If x2<x+4 Then Exit
					map[x2,y+h-2] = 2
				Next
			End if
		Next
		' noise right b ottom to right top
		For Local y1:Int=y+(h-1) Until y+4 Step -1
			If Rnd() < .2 Or y1=y+(h-1)
				Local d:Int=Rnd(1,4)
				If y1 > y + (h/4) Then d = 4
				For Local y2:Int=y1 Until y1-d Step -1
					If y2<y-4 Then Exit
					map[x+w-2,y2] = 2
				Next
			End if
		Next
		'
		' Random dots(BROWN) in the right bottom quadrant
		'
		For Local i:Int=0 Until w*h/30
			Local x1:Int=x+w/2+Rnd(w/2)
			Local y1:Int=y+h/4+Rnd(h)
			If x1>=x+w Or x1<0 Or y1>=y+h Or y1<0 Then Continue
			If map[x1,y1] = 1 Then map[x1,y1] = 4
		Next
		'
		' Random dots(BLACK) in the right bottom quadrant
		'
		If Rnd()<.2
		For Local i:Int=0 Until w*h/50
			Local x1:Int=x+Rnd(w/2)
			Local y1:Int=y+h/4+Rnd(h)
			If x1>=x+w Or x1<0 Or y1>=y+h Or y1<0 Then Continue
			If map[x1,y1] = 1 Then map[x1,y1] = 5
		Next
		End If
	End Method
	Method createtile()
		Local noiselevel:Float=Rnd(0.05,0.20)
		For Local y:Int=0 Until th
		For Local x:Int=0 Until tw
			If map[x,y] = 0 Then Continue
			Select map[x,y]
				Case 1
					imcan.Color = col
				Case 2
					imcan.Color = col.Blend(Color.Black,.3)					
				Case 3
					imcan.Color = col.Blend(Color.White,.5)
				Case 4
					imcan.Color = col.Blend(Color.Brown,.8)
				Case 5
					imcan.Color = Color.Black
			End Select			
			If noise
				Local c:Color = imcan.Color
				If Rnd()<.5
					imcan.Color = c.Blend(col.White,Rnd(noiselevel))
				Else
					imcan.Color = c.Blend(col.Black,Rnd(noiselevel))
				End If
			End If
			imcan.DrawRect(x,y,2,2)
		Next
		Next
		imcan.Flush()
	End Method
End Class

Class MyWindow Extends Window
	Field mytile:tile[,] = New tile[10,10]
	Method New()
		SeedRnd(Microsecs())
		newtiles()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Red)
		'canvas.DrawImage(mytile.im,100,100,0,6,6)
		For Local y:Int=0 Until 10
		For Local x:Int=0 Until 10
			canvas.DrawImage(mytile[x,y].im,x*64,y*64)
		Next
		Next		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		If Keyboard.KeyReleased(Key.Space) Then newtiles()		
		canvas.Color = Color.Red
		canvas.DrawText("Press <Space> for new tiles..",0,0)
	End Method	

	Method newtiles()		
		For Local y:Int=0 Until 10
		For Local x:Int=0 Until 10
			mytile[x,y] = New tile(64,64,Color.Grey.Blend(Color.White,Rnd(0.3,0.7)))
		Next
		next
	End Method
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
