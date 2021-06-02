#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Field tmp:=New Image[10,7]
	
	Method New()
		SeedRnd(Microsecs())
		For Local i:Int=0 Until 10
		For Local ii:Int=0 Until 7
		tmp[i,ii] = New Image(48,64)
		tmp[i,ii] = createtree()
		Next
		Next
	End Method
	Method createtree:Image()
		SeedRnd(Microsecs())
		Local im:Image = New Image(48,64)
		Local can:Canvas = New Canvas(im)
		can.Clear(Color.Green.Blend(Color.Brown,.9))
		can.Flush()
		Local maxcol:Int=0
		Local m:Int[,] = New Int[48,64]
		Local cnt:Float=0
		Local cnt2:Int
		Local f:Int=1
		For Local y:Int=63 Until 0 Step -1			
			For Local x:Int=0+cnt Until 48-cnt
				If x<0 Or x>=48 Then Exit
				m[x,y] = f
			Next
			cnt+=.4
			cnt2+=1
			If cnt2>7 Then f+=1 ;maxcol=f; cnt2=0
			
		Next
		
		For Local i:Int=0 Until 2200
			Local x:Int=Rnd(2,48-2)
			Local y:Int=Rnd(2,64-2)
			Local a:Int=m[x,y]
			If a>0 And m[x,y+1] <> a Then
				Local angle:Float=Rnd(Pi)
				Local x2:Float=x
				Local y2:Float=y
				For Local ii:Int=0 To Rnd(2,5)
					x2+=Cos(angle)
					y2+=Sin(angle)
					If x2<0 Or y2<0 Or x2>=48 Or y2>=64 Or m[x2,y2]=0 Then Continue
					m[x2,y2]=a					
					If a+1<=maxcol And ii<2 Then m[x2,y2]=a+1
				Next
			End If
		Next		

		'spiker left side
		For Local y:Int=0 Until 64
			For Local z:Int=0 Until 180
			Local x:Int=Rnd(1,47)
			If m[x,y]>0 And m[x-1,y]=0
				Local angle:Float=Rnd(-Pi)
				Local x2:Float=x,y2:Float=y
				For Local i:Int=0 Until 3
					x2+=Cos(angle)
					y2+=Sin(angle)
					If x2<0 Or y2<0 Or x2>=48 Or y2>=64 Then Continue
					m[x2,y2]=m[x,y]
				Next
				z=180
			End If
			Next
		Next

		'spiker right side
		For Local y:Int=0 Until 64
			For Local z:Int=0 Until 180
			Local x:Int=Rnd(1,47)
			If m[x,y]>0 And m[x+1,y]=0
				Local angle:Float=Rnd(-Pi,Pi)
				Local x2:Float=x,y2:Float=y
				For Local i:Int=0 Until 3
					x2+=Cos(angle)
					y2+=Sin(angle)
					If x2<0 Or y2<0 Or x2>=48 Or y2>=64 Then Continue
					m[x2,y2]=m[x,y]
				Next
				z=180
			End If
			Next
		Next
		
		'Outline black
		Local tm:Int[,] = New Int[48,64]
		For Local y1:Int=0 Until 64
		For Local x1:Int=0 Until 48
			If m[x1,y1]>0
				Local doit:Bool=True
				For Local x2:Int=-1 To 1
				For Local y2:Int=-1 To 1
					Local x3:Int=x1+x2
					Local y3:Int=y1+y2
					If x3<0 Or y3<0 Or x3>=48 Or y3>=64 Then Continue
					If m[x3,y3]=0 Then tm[x3,y3]=99
				Next
				Next
			End If
		Next
		next
		For Local y1:Int=0 Until 64
		For Local x1:Int=0 Until 48
			If tm[x1,y1] = 99 Then m[x1,y1]=99
		Next
		Next		
				
		For Local y:Int=0 Until 64
		For Local x:Int=0 Until 48
			If m[x,y] = 0 Then Continue			
			If m[x,y]<99
			can.Color = Color.Black.Blend(Color.Green,(1.0/Float(maxcol)*Float(m[x,y])))
			can.DrawPoint(x,y)
			End If
			If m[x,y]=99
				can.Color = Color.Black.Blend(Color.White,Rnd(.0,.4))
				can.DrawPoint(x,y)
			End If
'			Select m[x,y]
'				Case 1
'					can.Color = Color.Green
'					can.DrawPoint(x,y)
'				Default
'					'can.Color = Color.Black
'					'can.DrawPoint(x,y)
'			End Select
		Next
		Next
		can.Flush()
		Return im
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		canvas.Clear(Color.Green.Blend(Color.Brown,.9))
		For Local i:Int=0 Until 10
		For Local ii:Int=0 Until 7
		canvas.DrawImage(tmp[i,ii],40+48*i,10+ii*64)
		Next
		Next		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
