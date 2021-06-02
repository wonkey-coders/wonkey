#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global screenwidth:Int,screenheight:Int

'
' This effect creates a grey stone like texture
' 
Class effect	
	Field w:Int,h:Int ' map array width and height
	Field tw:Float,th:Float 'tile width and height
	Field map:Float[,] 'our map that holds the texture (greyscale)
	Method New(w:Int,h:Int)
		Self.w = w
		Self.h = h
		Self.tw = float(screenwidth)/float(w)
		Self.th = Float(screenheight)/Float(h)
		' Here we create our texture array
		map = New Float[w,h]
		' Here we call the brush stroking method that creates the texture.
		' we call it 20000 times in this setting. It takes a random position
		' on the map and a random direction.
		For Local i:Int=0 Until w+h*20
			shootproj(Rnd(w),Rnd(h),Rnd(TwoPi))
		Next

	End Method
	' This is the painters brush. It takes a position 
	' and angle and strokes the brush for a certain distance.
	' While it moves it increases the color value under the tip.
	Method shootproj(x:Float,y:Float,angle:Float)		
		For Local i:Int=0 Until w+h
			x+=Cos(angle)/Rnd(1,10)
			y+=Sin(angle)/Rnd(1,10)		
			If x<0 Or y<0 Or x>=w Or y>=h Then Exit
			map[x,y]+=1
			If map[x,y]>255 Then map[x,y] = 255
			If map[x,y]<0 Then map[x,y] = 0
		Next
	End Method
	' This draws the texture
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			Local dx:Int=x*tw
			Local dy:Int=y*th
			Local a:Float=(1.0/255.0)*Float(map[x,y])
			canvas.Color = New Color(a,a,a)
			canvas.DrawRect(dx,dy,tw+1,th+1)
		Next
		Next
	End Method
End Class

Class MyWindow Extends Window

	Field myeffect:effect
	Method New()
		SeedRnd(Microsecs())
		screenwidth = Width
		screenheight = Height
		myeffect = New effect(640,480)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		myeffect.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
