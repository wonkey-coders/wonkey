#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field r:Double
	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Keyboard.KeyReleased(Key.F1)
			r=Rnd()
		End If
		If Keyboard.KeyReleased(Key.F2)
			r=Rnd(5)
		End If
		If Keyboard.KeyReleased(Key.F3)
			r=Rnd(2,5)
		End If
		canvas.DrawText("Last value was :"+r,0,60)
		canvas.DrawText("Press F1 for rnd 0/1",0,0)
		canvas.DrawText("Press F2 for rnd 0<5",0,20)
		canvas.DrawText("Press F3 for rnd 2><5",0,40)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
