' Class inside Class Example

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class master
	' The s variable is used to create the slave with
	Field s:slave
	' This is a class inside a class
	Class slave
			' Fields
			Field x:Int,y:Int
			' New method
			Method New(x:Int,y:Int)
				' Assign self x and y with new x'es and y'es
				Self.x = x
				Self.y = y				
			End Method
			' Draw method which draws on canvas
			Method draw(canvas:Canvas)
				canvas.DrawCircle(x,y,100)
			End Method			
	End Class	
	' new method for main class
	Method New(x:Int,y:Int)	
		' Assign into s from class inside the main
		' class.
		s = New slave(x,y)
	End Method
	' update class in main class which passes
	' the canvas(draw)
	Method update(canvas:Canvas)
			s.draw(canvas)
	End Method
End Class

' make a global variable which we put the master
' class into. We create it here also.
Global mymaster:master = New master(200,200)


Class MyWindow Extends Window

	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Here we call the mymaster update method
		' canvas which we draw on is passed into the call
		mymaster.update(canvas)
		' We can modify variables from classes in classes
		' also.
		' mymaster is the variable we created the master class
		' with.
		' s is the variable inside the mymaster class we created
		' the slave class with.
		mymaster.s.x = Rnd(Width)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
