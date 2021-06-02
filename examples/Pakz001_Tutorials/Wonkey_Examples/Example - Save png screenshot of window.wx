#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Press space to make screenshot.....
		If Keyboard.KeyReleased(Key.Space)
			Local filename:String=DesktopDir()+"screenshot.png"
			Local screenshot:Pixmap = canvas.CopyPixmap(New Recti(0, 0, Width, Height))
			SavePixmap(screenshot, filename)
			Print "Screenshot saved as : "+filename
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
