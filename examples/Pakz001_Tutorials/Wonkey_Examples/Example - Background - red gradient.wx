#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class background
	Field w:Int,h:Int
	Field barwidth:Int=16
	Method New(w:Int,h:int)
		Self.w = w
		Self.h = h
	End Method
	Method draw(canvas:Canvas)
		Local cnt:Float=0.0
		Local cd:Int=0		
		For Local x:=0 Until w*2
			canvas.Color = New Color(cnt,0,0)
			If cd = 1 Then cnt+=1.0/barwidth
			If cd = 0 Then cnt-=1.0/barwidth
			If cnt>1 Then cd=0;cnt=1
			If cnt<0 Then cd=1;cnt=0
			canvas.DrawLine(x,0,x-w,h)
		Next
	End Method
end Class

Global mybackground:background

Class MyWindow Extends Window

	Method New()
		Title = "Red Gradient background Example.."
		mybackground = New background(Width,Height)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		mybackground.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
