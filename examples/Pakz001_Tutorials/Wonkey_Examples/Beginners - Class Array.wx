#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' This the enemy class
Class enemy
	' position x and y
	Field px:Int,py:Int
	' This is called when the class is created
	Method New(x:Int,y:Int)
		' Set the position
		Self.px = x
		Self.py = y
	End Method
	' Method to modify the px and py
	Method move(x:Int,y:Int)
		px += x
		py += y
	End Method
End Class

Class MyWindow Extends Window
	' How many enemies are there
	Field numenemies:Int=10
	' The array class
	Field myenemy:enemy[]
	'
	Method New()
		' Create our class array
		myenemy = New enemy[numenemies]	
		' Create our enemies inside the class array
		For Local i:Int=0 Until numenemies
			myenemy[i] = New enemy(Rnd(Width),Rnd(Height))
		Next
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' We can read/modify/call anything inside the class array
		myenemy[0].move(5,0)
		If myenemy[0].px > Width Then myenemy[0].px = -32
		'
		' Draw the enemies to the screen
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		' Loop through everything inside the array
		For Local i:=Eachin myenemy
			' i is used to run/read/modify the class array
			canvas.DrawRect(i.px,i.py,32,32)
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
