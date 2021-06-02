#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		'Create a new int list
		Local mylist:List<Int>
		mylist = New List<Int>
		' add some values to the list
		mylist.AddLast(10)
		mylist.AddLast(20)
		mylist.AddLast(30)
		' increase the ints using this function
		mylist = inclist(mylist)
		' print the output to the console
		For Local i:=Eachin mylist
			Print i
		Next
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

'
' Here we create a function that returns a list and takes in 
' a list.
'
Function inclist:List<Int>(in:List<Int>)
	' Create a local list
	Local out:List<Int> = New List<Int>
	'loop through the inputted list
	For Local i:=Eachin in		
		' add new value based on old value to the out list
		out.AddLast(i+1)
	Next
	' return the out list from the function
	Return out
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
