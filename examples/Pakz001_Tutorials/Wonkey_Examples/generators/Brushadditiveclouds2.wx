#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..



Class MyWindow Extends Window
	Field im:Image
	Field can:Canvas
	Field map:Float[,] 
	
	Method New()
		SeedRnd(Microsecs())
		makenew()

	End method
	Method makenew()	
		Local met:Int=Rnd(2)
		im = New Image(640,480)
		can = New Canvas(im)
		map = New Float[im.Width,im.Height]
		
		' Here we move a paintbrush(additive) in a array and then make
		' a image out of it.
		Local amount:Int=Rnd(100,700)
		For Local i:Int=0 To amount
			movebrush(can,Rnd(0,640),Rnd(0,480))
		Next
		
		' turn the array into a image.
		For Local y:Int=0 Until im.Height
		For Local x:Int=0 Until im.Width
			Local c:Color = New Color(map[x,y],map[x,y],map[x,y])
			can.Color = c
			If met = 1
				If map[x,y] < 0.4 Then can.Color = Color.Blue Else can.Color=Color.Green
			End If
			can.DrawRect(x,y,1,1)
		Next
		Next
		can.Flush()
	End Method	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.DrawImage(im,0,0)
		' create new image
		If Keyboard.KeyReleased(Key.Space) Then makenew()		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Method movebrush(canvas:Canvas,dx:Int,dy:Int)
		Local a:Float = Rnd(TwoPi) ' angle of brush
		Local am:Float= Rnd(-.2,.2) ' angle of brush modifier
		Local x:Float = dx
		Local y:Float = dy
		Local len:Int=Rnd(150,360) ' length of line to draw
		Local rad:Int=Rnd(2,10) ' radius of brush
		Local radmod:Int=Rnd(-2,2) ' grow or shrink brush
		Local inversion:Bool=True
		If Rnd()<.5 Then inversion=False
		For Local i:Int=0 Until len
			x += Cos(a)
			y += Sin(a)
			a+=am
			If Rnd()<.1 Then am = Rnd(-.2,.2) ' change brush angle
			If Rnd()<.02 Then ' every now and then change size of brush
			rad+=radmod
			If rad<2 Then radmod=-radmod
			If rad>20 Then radmod=-radmod
			End If
			If Rnd()<.01
				If inversion = True Then inversion = False Else inversion = True
			End If
			' draw the brush
			For Local y2:Int=-rad To rad
			For Local x2:Int=-rad To rad
				Local x3:Int=x+x2
				Local y3:Int=y+y2
				Local t:Float = 1.0-(1.0 / Float(rad*2) * Float(distance(x3,y3,x,y)))
				If x3<0 Or y3<0 Or x3>=im.Width Or y3>=im.Height Then Continue
				'Print t
				If inversion Then
					map[x3,y3] += Abs(t)/30
				Else
					map[x3,y3] -= Abs(t)/30
				End If
				
				If map[x3,y3] > 1.0 Then map[x3,y3] = 1.0
				If map[x3,y3] < 0 Then map[x3,y3] = 0
				'canvas.Color = Color.White.Blend(Color.Black,t)
				'canvas.DrawRect(x3,y3,1,1)
			Next
			Next
		Next
		
	End Method
    ' Manhattan Distance (less precise)
    Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
	    Return Abs(x2-x1)+Abs(y2-y1)   
    End Function	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
