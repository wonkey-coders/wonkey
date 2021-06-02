#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class background
	Field w:Int,h:Int
	Field barwidth:Int=16
	Field col1:Color
	Field col2:Color
	Field col3:Color
	Field col4:Color
	Field bh:Float
	Method New(w:Int,h:int)
		Self.w = w
		Self.h = h
		col1 = New Color(Rnd(),Rnd(),Rnd())
		col2 = New Color(Rnd(),Rnd(),Rnd())
		col3 = New Color(Rnd(),Rnd(),Rnd())
		col4 = New Color(Rnd(),Rnd(),Rnd())
		bh = h/3
	End Method
	Method draw(canvas:Canvas)
		Local cnt:Float=0
		Local pos:Float=0
		Local r1:float,g1:Float,b1:Float
		Local r2:Float,g2:Float,b2:Float
		
		For Local y:=0 Until h
			Select pos
			Case 0
				Local r1:Float = col1.r
				Local g1:Float = col1.g
				Local b1:Float = col1.b
				Local r2:Float = col2.r
				Local g2:Float = col2.g
				Local b2:Float = col2.b
				Local cstepr:Float = (r2-r1)/bh
				Local cstepg:Float = (g2-g1)/bh
				Local cstepb:Float = (b2-b1)/bh			
				canvas.Color = New Color(r1+(cstepr*cnt),g1+(cstepg*cnt),b1+(cstepb*cnt))
			Case 1
				Local r1:Float = col2.r
				Local g1:Float = col2.g
				Local b1:Float = col2.b
				Local r2:Float = col3.r
				Local g2:Float = col3.g
				Local b2:Float = col3.b
				Local cstepr:Float = (r2-r1)/bh
				Local cstepg:Float = (g2-g1)/bh
				Local cstepb:Float = (b2-b1)/bh			
				canvas.Color = New Color(r1+(cstepr*cnt),g1+(cstepg*cnt),b1+(cstepb*cnt))
			Case 2
				Local r1:Float = col3.r
				Local g1:Float = col3.g
				Local b1:Float = col3.b
				Local r2:Float = col4.r
				Local g2:Float = col4.g
				Local b2:Float = col4.b
				Local cstepr:Float = (r2-r1)/bh
				Local cstepg:Float = (g2-g1)/bh
				Local cstepb:Float = (b2-b1)/bh			
				canvas.Color = New Color(r1+(cstepr*cnt),g1+(cstepg*cnt),b1+(cstepb*cnt))
			End Select
			canvas.DrawLine(0,y,w,y)
			cnt+=1
			If cnt>= bh Then pos+=1 ; cnt=0
		Next
	End Method
end Class

Global mybackground:background

Class MyWindow Extends Window

	Method New()
		Title = "Tinted Gradient background Example.."
		mybackground = New background(Width,Height)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Keyboard.KeyReleased(Key.Space)
			mybackground = New background(Width,Height)
		End If
		'
		mybackground.draw(canvas)
		' if key escape then quit
		canvas.Color = Color.White
		canvas.DrawText("Press space for new screen..",0,0)
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
