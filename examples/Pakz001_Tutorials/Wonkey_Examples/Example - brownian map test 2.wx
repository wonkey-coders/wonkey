#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Field range:Int=6
	Field len:Int=300

	Class node
		Field x:Int
		Field y:Int
		Method New(x:Int,y:Int)
			Self.x = x
			Self.y = y
		End Method
	End Class

	Field brownian:Stack<node>

	Method New()
		make()		
	End method
	
	Method make()
		brownian = New Stack<node>
		brownian.Push(New node(100,100))
		For Local i:Int=0 Until len
			Local nx:Int=brownian.Get(i).x
			Local ny:Int=brownian.Get(i).y
			SeedRnd(Microsecs())
			nx += Rnd(-range,range)
			ny += Rnd(-range,range)
 			nx = Clamp(nx,0,200)
			ny = Clamp(ny,0,200)
			brownian.Push(New node(nx,ny))			
		Next
		'make the coordinates gridlike
		For Local i:Int=0 Until brownian.Length
			Local x:Int=brownian.Get(i).x
			Local y:Int=brownian.Get(i).y
			brownian.Get(i).x = (x/10)*10
			brownian.Get(i).y = (y/10)*10
		Next		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		For Local i:Int=0 Until brownian.Length-1
			Local x1:Int=brownian.Get(i).x
			Local y1:Int=brownian.Get(i).y
			Local x2:Int=brownian.Get(i+1).x
			Local y2:Int=brownian.Get(i+1).y
			x1*=2
			y1*=2
			x2*=2
			y2*=2
			SeedRnd(100)
			Local l:Float=4
			For Local y:Int=Rnd(-l,-1) To Rnd(1,l)
			For Local x:Int=Rnd(-l,-1) To Rnd(1,l)
				canvas.DrawLine(x1+x+100,y1+y+100,x2+x+100,y2+y+100)
				l+=Rnd(1)
				If l>10 Then l=4
			Next
			Next
		Next
		' If key pace then new map
		If Keyboard.KeyReleased(Key.Space) Then make()		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
