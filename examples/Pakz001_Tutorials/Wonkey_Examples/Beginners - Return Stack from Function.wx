#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		'Create a new int list
		Local mystack:Stack<Int>
		mystack = New Stack<Int>
		' add some values to the list
		mystack.Add(10)
		mystack.Add(20)
		mystack.Add(30)
		' increase the ints using this function
		mystack = incstack(mystack)
		' print the output to the console
		For Local i:=Eachin mystack
			Print i
		Next		
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Here we create a function that returns a list and takes in 
' a list. (it increases the ints in the in list bu 1)
'
Function incstack:Stack<Int>(in:Stack<Int>)
	' Create a local list
	Local out:Stack<Int> = New Stack<Int>
	'loop through the inputted list
	For Local i:=Eachin in		
		' add new value based on old value to the out list
		out.Add(i+1)
	Next
	' return the out list from the function
	Return out
End Function


Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
