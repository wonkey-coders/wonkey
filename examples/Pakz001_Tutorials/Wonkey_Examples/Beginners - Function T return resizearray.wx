#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	' create a integer 2 dimensional array sized 10x10
	Field myarray:Int[,] = New Int[10,10]
	Method New()
		' fill the array with random numbers
		' getSize returns the size of the array. (0-first collumn 1 is second ..)
		For Local y:=0 Until myarray.GetSize(1)
		For Local x:=0 Until myarray.GetSize(0)
			myarray[x,y] = Int(Rnd(10,1000))
		Next
		Next
		'resize the array to 5x5
		myarray = resize2darray(myarray,5,5)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'Draw the contents of the array to the screen.
		For Local y:=0 Until myarray.GetSize(1)
		For Local x:=0 Until myarray.GetSize(0)
			canvas.DrawText(myarray[x,y],x*50,y*20)
		Next
		Next


		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

'
' Here we create a function that returns a list and takes in 
' a list.
'
Function resize2darray<T>:T[,](a:T[,],x:int,y:Int)
	' Create a local array
	Local out:= New T[x,y]
	' Loop though the local array
	For Local i:=0 Until out.GetSize(0)
	For Local j:=0 Until out.GetSize(1)
		out[i,j] = a[i,j]
	Next
	Next
	'return the local array
	Return out
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
