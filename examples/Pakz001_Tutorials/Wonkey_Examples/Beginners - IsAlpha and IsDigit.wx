#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If IsAlpha("a"[0])
			canvas.DrawText("a - Is a alpa",0,0)
		End If
		if IsAlpha("0"[0]) = False
			canvas.DrawText("0 - Is not a alpha",0,20)			
		End If
		If IsDigit("0"[0])
			canvas.DrawText("0 - is a Digit",0,40)
		End If
		If IsDigit("!"[0]) = False
			canvas.DrawText("! - is not a Digit",0,60)
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
