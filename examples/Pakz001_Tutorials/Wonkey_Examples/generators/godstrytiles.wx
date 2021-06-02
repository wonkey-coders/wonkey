#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class godstile
	Field palette:Color[]
	Field w:Int,h:Int
	Field map:Int[,]
	Method New(w:Int,h:Int)
		Self.w = w
		Self.h = h
		map = New Int[w,h]
		palette = New Color[7]
		makepalette()
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			map[x,y] = 3
		Next
		Next
		
		' make the cracks
		Local d:Int=w*h/100+Rnd(w*h/70)
		For Local i:Int=0 Until d
		makestone(0,0,w,h)
		Next
		' make the camouflage
		camou("light",0,0,w,h)
		camou("dark",0,0,w,h)
		' make the edges
		makeedge(0,0,w,h)
	End Method
	Method makeedge(sx:Int,sy:Int,sw:Int,sh:Int)
		' left top to right top - LIGHT
		For Local x:Int=sx Until sx+sw
			map[x,0] = 6
			If Rnd()<.1 Then 
				map[x,0] = 5
			End If
			If Rnd()<.09 Then 
				map[x,0] = 4
				Local l:Int=Rnd(3,12)
				For Local x2:Int=x+1 Until x+l-1
					If x2< sx+sw
						map[x2,0] = 0 
					End If
				Next
				If x+l-1<sx+sw Then map[x+l-1,0] = 5
				x+=l
			End If
		Next
		' left top to left bottom - LIGHT
		For Local y:Int=sy Until sy+sh
			map[0,y] = 6
			If Rnd()<.1 Then 
				map[0,y] = 5
			End If
			If Rnd()<.09 Then 
				map[0,y] = 4
				Local l:Int=Rnd(3,12)
				For Local y2:Int=y+1 Until y+l-1
					If y2< sy+sh
						map[0,y2] = 0 
					End If
				Next
				If y+l-1<sy+sh Then map[0,y+l-1] = 5
				y+=l
			End If
		Next

		' left bottom to right bottom - DARK
		For Local x:Int=sx Until sx+sw
			map[x,sy+sh-1] = 1
			If Rnd()<.1 Then 
				map[x,sy+sh-1] = 0
			End If
			If Rnd()<.09 Then 
				map[x,sy+sh-1] = 1
				Local l:Int=Rnd(3,12)
				For Local x2:Int=x+1 Until x+l-1
					If x2< sx+sw
						map[x2,sy+sh-1] = 0 
					End If
				Next
				If x+l-1<sx+sw Then map[x+l-1,sy+sh-1] = 1
				x+=l
			End If
		Next

		' Right top to right bottom- DARK
		For Local y:Int=sy Until sy+sh
			map[sx+sw-1,y] = 1
			If Rnd()<.1 Then 
				map[sx+sw-1,y] = 2
			End If
			If Rnd()<.09 Then 
				map[sx+sw-1,y] = 2
				Local l:Int=Rnd(3,12)
				For Local y2:Int=y+1 Until y+l-1
					If y2< sy+sh
						map[sx+sw-1,y2] = 0 
					End If
				Next
				If y+l-1<sy+sh Then map[sx+sw-1,y+l-1] = 1
				y+=l
			End If
		Next


	End Method
	Method camou(mode:String,sx:Int,sy:Int,sw:Int,sh:Int)
		' Overwrite 3 and nothing else		
		'
		Local tmap:Int[,] =  New Int[sw,sh]
		For Local i:Int=0 Until 15	
			Local x:Float=Rnd(sw)
			Local y:Float=Rnd(sh)
			tmap[x,y] = 1
			If Rnd()<.5 Then 
				Local a:Float=Rnd(-.5,.5)
				For Local i:Int=0 Until 20
					x+=Cos(a)
					y+=Sin(a)					
					If x<sx Or y<sy Or x>sw Or y>sh Then Exit
					tmap[x,y] = 1
				Next
			End If
		Next
		For Local i:Int=0 Until sw*sh*5
			Local x:Int=Rnd(sw)
			Local y:Int=Rnd(sh)			
			If tmap[x,y] = 1
				Local mx:Int=Rnd(-2,2)
				Local my:Int=Rnd(-2,2)
				If x+mx>=0 And x+mx<sw And y+my>=0 And y+my<sh
					tmap[x+mx,y+my] = 1
				Endif
			End If
		Next
		' copy camou on thing
		For Local y:Int=sy Until sy+sh
		For Local x:Int=sx Until sx+sw
			If mode="light"
				If map[x,y] = 3 And tmap[x,y] = 1 Then map[x,y] = 4
			Elseif mode="dark"
				If map[x,y] = 3 And tmap[x,y] = 1 Then map[x,y] = 2
			End if
		Next
		Next
	End Method
	Method makestone(sx:Int,sy:Int,sw:Int,sh:Int)
		' draw crack every now and then left to right
		Local x1:Float=Rnd(sw)
		Local y1:Float=Rnd(sh)
		Local a:Float=Rnd(TwoPi)
		Local as:Float=Rnd(-.2,.2)
		Local lastx:Float,lasty:Float
		For Local i:Int=0 Until 30
			x1+=Cos(a)
			y1+=Sin(a)
			a+=as
			For Local zx:Int=-1 To 1
			For Local zy:Int=-1 To 1
				Local nx:Int=x1+sx
				Local ny:Int=y1+sy
				If nx+zx>=0 And nx+zx<sw And ny+zy>=0 And ny+zy<sh
					If zx<0 
					If map[nx+zx,ny+zy]>0 Then map[nx+zx,ny+zy] -=1					
					End If
					If zx>0
					If map[nx+zx,ny+zy]<6 Then map[nx+zx,ny+zy] +=1					
					End If
				End If
			Next
			Next
			lastx = x1
			lasty = y1
			If Rnd()<.05 Then Exit
		Next
	End Method
	Method makepalette()
		Local rp:Color = New Color(Rnd(1),Rnd(1),Rnd(1)).Blend(Color.Grey,.7)
		Local r:Float=0.0
		Local s:Int=palette.GetSize(0)
		palette[0] = Color.Black
		For Local i:Int=1 Until s
			r+=1.0/(Float(s)-1)
			palette[i] = New Color(r,r,r).Blend(rp,.1)
		Next
	End Method
	Method mapdraw(canvas:Canvas,dx:Int,dy:Int)
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			canvas.Color = palette[map[x,y]]'.Blend(Color.Black,Rnd(.2))
			canvas.DrawRect((x)+dx,(y)+dy,1,1)
		Next
		Next
	End Method
End Class


Class MyWindow Extends Window
	Field im:Image
	Field can:Canvas
	Field yea:godstile
	Method New()
		SeedRnd(Microsecs())
		im = New Image(640,480)
		can = New Canvas(im)
		Local sw:Int=0
		For Local y:Int=0 Until 480/32
		For Local x:Int=0 Until 640/64
			Local tw:Int=64		
			If sw=1 Then tw=96
			yea = New godstile(tw,32)
			yea.mapdraw(can,(tw+1)*x,33*y)
		Next
			If sw=0 Then sw=1 Else sw=0
		Next
		can.Flush()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.DrawImage(im,0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
