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
			' same seed same rnd result
			SeedRnd(1)
			r=Rnd()
		End If
		canvas.DrawText("Last value was :"+r,0,60)
		canvas.DrawText("Press F1 for Seed 1 rnd()",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
