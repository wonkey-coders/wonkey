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
		If IsHexDigit("F"[0])
			canvas.DrawText("F - is a hex digit",0,0)
		End If
		If IsHexDigit("G"[0]) = False
			canvas.DrawText("G - is not a hex digit",0,20)
		End If
		If IsSpace(" "[0])
			canvas.DrawText("' ' - is a space character",0,40)
		End If
		If IsSpace("-"[0]) = False
			canvas.DrawText("'-' - is not a space character",0,60)
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
