#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class enemy
	Field x:Int,y:Int
	Method New(x:int,y:Int)
		Self.x = x
		Self.y = y 
	End Method
End Class

Class MyWindow Extends Window
	field mystack:Stack<enemy>
	Method New()
		'Create a new int Stack<enemy>
		
		mystack = New Stack<enemy>
		' Create some data in the stack class
		mystack.Add(New enemy(Rnd(Width),Rnd(Height)))
		mystack.Add(New enemy(Rnd(Width),Rnd(Height)))
		mystack.Add(New enemy(Rnd(Width),Rnd(Height)))
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)
		' create a new stack<class> (change the x variable)
		mystack = modifystack(mystack)

		canvas.Color = Color.White
		For Local i:=Eachin mystack
			canvas.DrawOval(i.x,i.y,10,10)
		Next

		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Here we create a function that returns a stack and takes in 
' a stack<class> 
'
Function modifystack:Stack<enemy>(in:Stack<enemy>)
	' Create a local stack<class>
	Local out:Stack<enemy> = New Stack<enemy>
	'loop through the inputted stack
	For Local i:=Eachin in				
		Local x:Int=i.x+Rnd(-100,100)
		Local y:Int=i.y+Rnd(-100,100)
		If x<0 Or x>640 Then x=320
		If y<0 Or y>480 Then y=240
		out.Add(New enemy(x,y))		
	Next
	' return the out stack<class> from the function
	Return out
End Function


Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
