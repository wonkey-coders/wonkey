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
		' If visible or invisible draw the text
		If Mouse.PointerVisible = True
			canvas.DrawText("Mouse Pointer is Visible",0,0)
		Else
			canvas.DrawText("Mouse Pointer is not Visible",0,0)
		End If
		'
		' With space pressed hide or show mouse cursor
		If Keyboard.KeyReleased(Key.Space) 
			If Mouse.PointerVisible = True Then
				Mouse.PointerVisible = False
			Else
				Mouse.PointerVisible = True
			End If
		End If
		' 
		canvas.DrawText("Press Space to hide/Show MouseCursor",Width*.5,Height-10,.5,.5)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
