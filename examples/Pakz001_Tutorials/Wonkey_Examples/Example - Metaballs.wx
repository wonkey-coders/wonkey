'Thanks to the coding train for showing how it's done

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class metaball
	Class blob
		Field x:Float,y:Float
		Field r:Float
		Field incx:Float,incy:Float
		Field screenwidth:Int,screenheight:Int
		Method New(x:Int,y:Int,sw:Int,sh:Int)
			Self.x = x
			Self.y = y
			r = Rnd(5,14)
			incx = Rnd(-2,2)
			incy = Rnd(-2,2)
			Self.screenwidth = sw
			Self.screenheight = sh
		End Method
		Method update()
			x += incx
			y += incy
			If x<0 Or x>screenwidth Then incx = -incx
			If y<0 Or y>screenheight Then incy = -incy		
		End Method
	End Class	
    Field image:Image
    Field pixels:Pixmap
    Field width:Int,height:Int
	Field ball:blob[] = New blob[4]
    Method New(w:Int,h:Int)
    	width = w
    	height = h
    	pixels = New Pixmap( width,height )
    	image = New Image(width,height)
        For Local i:Int=0 Until 4
	        ball[i] = New blob(Rnd(width),Rnd(height),width,height)
        Next
	End Method
	Method update()
       	For Local i:=Eachin ball
       		i.update()
       	Next
        For Local y:Int=0 Until height
        For Local x:Int=0 Until width
	        Local index:Int = x+y*width
        	Local sum:Float = 0
        	For Local b:=Eachin ball
        		Local d:Float = distance(x,y,b.x,b.y)
        		sum += b.r / d
        	Next
        	If sum<0 Then sum=0 
        	If sum>1 Then sum=1
        	If sum<.5 Then sum = 0 Else sum=1
       		pixels.SetPixel(x,y,New Color(sum,sum,sum))
       	Next
       	Next
		image.Texture.PastePixmap(pixels,0,0)
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawImage(image,0,0,0,(1.0/width)*640.0,(1.0/height)*480.0)
	End Method
    Function distance:Float(x1:Int,y1:Int,x2:Int,y2:Int)
    	Return Sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
    End Function
End Class


Class MyWindow Extends Window
	Field mymetaball:metaball
	Field time:Int=Millisecs()+3000
	Method New()
		mymetaball = New metaball(200,200)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Mouse.ButtonReleased(MouseButton.Left) Or Millisecs()>time
			time = Millisecs() + 3000
			mymetaball = New metaball(200,200)
		End If
		mymetaball.update()
		mymetaball.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
