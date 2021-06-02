#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global screenwidth:Int,screenheight:Int

Class astroidmapgen
	Field tw:Float,th:Float 'tile width and height
	Field map:Int[,]
	Field w:Int,h:Int ' map width and height
	Field posx:Float,posy:Float
	Method New(w:Int,h:Int)
		Self.w = w
		Self.h = h
		Self.tw = Float(screenwidth) / Float(w)
		Self.th = Float(screenheight) / Float(h)
		map = New Int[w,h]		
		createmap()
	End Method
	Method createmap()
		Print w+"."+h
		' we start the map from the center with a random angle to move to
		posx=w/2
		posy=h/2
		
		For Local i:Int=0 To w*h/500
			' here we tunnel out area		
			shootstone(posx,posy,Rnd(TwoPi))			
		Next
	End Method
	Method shootstone(x:Float,y:Float,angle:Float)
		Local shot:Bool=False
		
		Local depth:Int=Rnd(w/10,w/3)
		Local z:Float=3.0/Float(depth)
		map[x,y]=1
		For Local i:Int=0 Until depth
			x+=Cos(angle)
			y+=Sin(angle)
			'reset position to center if to close to edge
			If x<5 Or y<5 Or x>w-5 Or y>h-5 Then 
				posx = w/2
				posy = h/2				
				Return
			End If
			'bounce
			If Rnd()<.1 And i>depth/2 Then angle+=Rnd()		
			' here we brush the current position
			Local d:Float=Abs(3.0-(z*Float(i)))
			For Local y1:Int=y-d To y+d+1
			For Local x1:Int=x-d To x+d+1
				If x1<3 Or y1<3 Or x1>=w-3 Or y1>=h-3 Then Continue
				map[x1,y1] = 1				
			Next
			Next
			
		Next
		'store our current location
		posx = x
		posy = y
	End Method
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			Local dx:Int=x*tw
			Local dy:Int=y*th
			If map[x,y] > 0
				canvas.Color = Color.White
				canvas.DrawRect(dx,dy,tw+1,th+1)
			End If
		Next
		Next
			
	End Method
End Class

Class MyWindow Extends Window
	Field mymap:astroidmapgen
	Method New()
		SeedRnd(Microsecs())
		screenwidth = Width
		screenheight = Height
		mymap = New astroidmapgen(100,100)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mymap.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		If Keyboard.KeyReleased(Key.Space) Then mymap = New astroidmapgen(Rnd(50,200),Rnd(50,200))
	End Method	
	
End	Class

Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
	Return ATan2(y2-y1, x2-x1)
End Function 

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
