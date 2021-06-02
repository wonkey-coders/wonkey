#Import "<std>"
#Import "<mojo>"
Using std..
Using mojo..

Class flowfield
	Field mapwidth:Int,mapheight:Int
	Field tilewidth:Float,tileheight:Float
	Field screenwidth:Int,screenheight:Int
	Field map:Int[,]
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		Self.tilewidth = Float(screenwidth)/Float(mapwidth)
		Self.tileheight = Float(screenheight)/Float(mapheight)
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		map = New Int[mapwidth,mapheight]
        pointtocenter()
	End Method
	'
	' In the flowfield array there are 8 directions. 
	' Here we point the directions towards the center
	'
	Method pointtocenter()
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Local x2:Int=mapwidth/2
			Local y2:Int=mapheight/2
			Local nd:Int=0
			If x<x2 Then nd=0
			If x>x2 Then nd=4
			If y<y2 Then nd=2
			If y>y2 Then nd=6
			
			If x<x2 And y<y2 Then nd=1
			If x>x2 And y<y2 Then nd=3
			If x<x2 And y>y2 Then nd=7
			If x>x2 And y>y2 Then nd=5

			map[x,y] = nd
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		For Local y:=0 Until mapheight
		For Local x:=0 Until mapwidth
			Local direction:Int = map[x,y]
			Local x1:Float=Float(x)*tilewidth+tilewidth/2
			Local y1:Float=Float(y)*tileheight+tileheight/2
			Local ang:Float= (TwoPi/8*direction)
			Local x2:Float=x1+(Cos(ang)*tilewidth/2)
			Local y2:Float=y1+(Sin(ang)*tileheight/2)		
			Local x3:Float=x1+(Cos(ang+Pi/90)*tilewidth*1.5)
			Local y3:Float=y1+(Sin(ang+Pi/90)*tileheight*1.5)		
			Local x4:Float=x1+(Cos(ang-Pi/90)*tilewidth*1.5)
			Local y4:Float=y1+(Sin(ang-Pi/90)*tileheight*1.5)		
			
			canvas.DrawPoly(New Float[](x2,y2,x3,y3,x4,y4))
		Next
		Next
	End Method
End Class

Class MyWindow Extends Window
	Field myflowfield:flowfield
	Field alienx:Int=200,alieny:Int=200
    Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )
        myflowfield = New flowfield(Width,Height,20,20)
    End Method
    Method update()        
    	Local d:Int=myflowfield.map[alienx/myflowfield.tilewidth,alieny/myflowfield.tileheight]
    	Select d
	    	Case 0
	    	alienx+=1
	    	Case 1
	    	alienx+=1;alieny+=1
	    	Case 2
	    	alieny+=1
	    	Case 3
	    	alienx-=1
	    	alieny+=1
	    	Case 4
	    	alienx-=1
	    	Case 5
	    	alienx-=1
	    	alieny-=1
	    	Case 6
	    	alieny-=1
	    	Case 7
	    	alieny-=1
	    	alienx+=1
    	End Select

		If rectsoverlap(alienx-10,alieny-10,20,20,Width/2-30,Height/2-30,60,60)
			alienx = Rnd(Width)
			alieny = Rnd(Height)
		End If

		If Mouse.ButtonReleased(MouseButton.Left) Then
			alienx = Mouse.X
			alieny = Mouse.Y
		End If

    End Method
    Method OnRender( canvas:Canvas ) Override
	    RequestRender()
	    update()
        canvas.Clear(Color.Black)
        canvas.Color = Color.White
        myflowfield.draw(canvas)
       	canvas.Color = Color.Red
        canvas.DrawCircle(alienx,alieny,20)
        canvas.Color = Color.White
        canvas.DrawText("Flow Fields - Press Left Mouse to place alien",0,0)
        If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
    End Method
    
End Class

Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    Return True
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
