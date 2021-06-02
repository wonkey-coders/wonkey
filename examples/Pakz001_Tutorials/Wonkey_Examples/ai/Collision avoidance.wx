#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class entity
	Field id:Int
	Field ex:Float,ey:Float
	Field speed:Float
	Field angle:Float
	Field state:String="forward"
	Field statecountdown:Int
	Method New(id:Int,x:Int,y:Int)
		Self.id = id
		ex = x
		ey = y
	End Method
	Method update()		
		If speed<0.2 Then speed=.2
		ex+=Cos(-angle)*speed
		ey+=Sin(-angle)*speed
		If ex>640 Then ex=0
		If ex<0 Then ex=640
		If ey<0 Then ey=480
		If ey>480 Then ey=0
		statecountdown-=1
		If statecountdown<0
		Local n:Float=Rnd()
		If n<.1 Then 
		state = "left"
		statecountdown=Rnd(10,20)
		speed = 1
		Elseif n>.1 And n<.2
		state = "right"
		statecountdown=Rnd(10,20)
		speed = 1
		Else
		state = "forward"
		statecountdown=Rnd(40,200)
		speed = 1
		End If
		End If
		'
		For Local i:Int=0 Until myentity.Length
			If id <> myentity.Get(i).id
				If circleoverlap(ex,ey,32,myentity.Get(i).ex,myentity.Get(i).ey,32)
					If orientation(ex,ey,ex+Cos(-angle)*10,ey+Sin(-angle)*10,myentity.Get(i).ex,myentity.Get(i).ey) = -1 Then state="right" Else state="left"
					speed-=.012
					If circleoverlap(ex,ey,20,myentity.Get(i).ex,myentity.Get(i).ey,20) Then speed=0
					If speed<0 Then speed=0
					statecountdown = Rnd(0,20)
					'Print "coll"+Microsecs()+"+++"+id+","+myentity.Get(i).id
				End If
			End If
		Next
		'
		Select state
			Case "left"
				angle+=.03
			Case "right"
				angle-=.03
			Case "forward"
		End Select
	End Method
End Class

Global myentity:Stack<entity>

Class MyWindow Extends Window
	Field db32color:Color[] ' our colors	
	Field image:Image
	Field imagecan:Canvas
	Method New()
		inidb32colors()
		image = New Image(32,32)
		image.Handle = New Vec2f(0.5,0.5)
		imagecan = New Canvas(image)
		imagecan.Clear(Color.None)
		imagecan.Flush()
		createsprite()
		myentity = New Stack<entity>
		For Local i:Int=0 Until 16
			myentity.Push(New entity(i,Rnd(640),Rnd(480)))
		Next
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		For Local i:Int=0 Until myentity.Length
			myentity.Get(i).update()
		Next

		For Local i:Int=0 Until myentity.Length
			canvas.DrawImage(image,myentity.Get(i).ex,myentity.Get(i).ey,myentity.Get(i).angle)
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	Method createsprite()
		Local map := New Int[][] (
		New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,1,1,27,27,28,1,0,0,0,0,0,0,0),
		New Int[](0,0,0,0,1,27,27,27,28,1,0,0,0,0,0,0),
		New Int[](0,0,0,27,1,28,28,27,27,28,1,0,0,0,0,0),
		New Int[](0,0,0,27,8,21,27,27,29,8,29,21,21,1,1,0),
		New Int[](0,0,0,27,8,21,27,27,29,8,29,21,21,1,1,0),
		New Int[](0,0,0,27,1,28,28,27,27,28,1,0,0,0,0,0),
		New Int[](0,0,0,0,1,27,27,27,28,1,0,0,0,0,0,0),
		New Int[](0,0,0,1,1,27,27,28,1,0,0,0,0,0,0,0),
		New Int[](0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0))		
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			imagecan.Color = db32color[map[y][x]]
			If map[y][x] = 0 Then imagecan.Alpha=0 Else imagecan.Alpha=1
			imagecan.DrawRect(x*2,y*2,2,2)
		Next
		Next		
		imagecan.Flush()
		
	End Method
	Method inidb32colors()
		db32color = New Color[32]
		db32color[0 ] = New Color(intof(0),intof(0),intof(0))
		db32color[1 ] = New Color(intof(34),intof(32),intof(52))
		db32color[2 ] = New Color(intof(69),intof(40),intof(60))
		db32color[3 ] = New Color(intof(102),intof(57),intof(49))
		db32color[4 ] = New Color(intof(143),intof(86),intof(59))
		db32color[5 ] = New Color(intof(223),intof(113),intof(38))
		db32color[6 ] = New Color(intof(217),intof(160),intof(102))
		db32color[7 ] = New Color(intof(238),intof(195),intof(154))
		db32color[8 ] = New Color(intof(251),intof(242),intof(54))
		db32color[9 ] = New Color(intof(153),intof(229),intof(80))
		db32color[10] = New Color(intof(106),intof(190),intof(48))
		db32color[11] = New Color(intof(55),intof(148),intof(110))
		db32color[12] = New Color(intof(75),intof(105),intof(47))
		db32color[13] = New Color(intof(82),intof(75),intof(36))
		db32color[14] = New Color(intof(50),intof(60),intof(57))
		db32color[15] = New Color(intof(63),intof(63),intof(116))
		db32color[16] = New Color(intof(48),intof(96),intof(130))
		db32color[17] = New Color(intof(91),intof(110),intof(225))
		db32color[18] = New Color(intof(99),intof(155),intof(225))
		db32color[19] = New Color(intof(95),intof(205),intof(228))
		db32color[20] = New Color(intof(203),intof(219),intof(252))
		db32color[21] = New Color(intof(255),intof(255),intof(255))
		db32color[22] = New Color(intof(155),intof(173),intof(183))
		db32color[23] = New Color(intof(132),intof(126),intof(135))
		db32color[24] = New Color(intof(105),intof(106),intof(106))
		db32color[25] = New Color(intof(89),intof(86),intof(82))
		db32color[26] = New Color(intof(118),intof(66),intof(138))
		db32color[27] = New Color(intof(172),intof(50),intof(50))
		db32color[28] = New Color(intof(217),intof(87),intof(99))
		db32color[29] = New Color(intof(215),intof(123),intof(186))
		db32color[30] = New Color(intof(143),intof(151),intof(74))
		db32color[31] = New Color(intof(138),intof(111),intof(48))
	End Method
	
End	Class
	Function intof:Float(a:Int)
		Return 1.0/255.0*a
	End Function
Function circleoverlap:Bool(x1:Int,y1:Int,r1:Int,x2:Int,y2:Int,r2:Int)
    Local dx:Int = x1-x2
    Local dy:Int = y1-y2
    Local r:Int = r1+r2
    If dx*dx+dy*dy <= r*r Then Return True Else Return False
End Function
Function orientation:Int(ax:Int,ay:Int,bx:Int,by:Int,cx:Int,cy:Int)
	Return Sgn((bx-ax)*(cy-ay)-(by-ay)*(cx-ax))	
End Function
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
