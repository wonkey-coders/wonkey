#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	Field mystack:= New Stack<String>

	Method New()
		For Local i:=0 To 10
			mystack.Push(i)
		Next
		mystack.Add(500) ' add is like push
		mystack.Insert(0,1000) ' insert at any point (0) = at starting point of list
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		If Keyboard.KeyReleased(Key.Space)
			mystack.Erase(0)
			Print mystack.Length
		End if
		For Local i:=0 until mystack.Length
			canvas.DrawText(mystack.Get(i),10,i*20)
		Next
		
		'
		' top reads the last value added
		canvas.DrawText("Stack.Top value :"+mystack.Top,320,40)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
