#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		Super.New("test",1024,768,WindowFlags.Fullscreen)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
		'
		If Keyboard.KeyReleased(Key.F)
			If Fullscreen = True Then Fullscreen = False Else Fullscreen = True		
		End If				
		'
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Press Escape to End.",0,0)
		canvas.DrawText("Press key f to switch between fullscreen/Windowed",0,20)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow()
	App.Run()
End Function
