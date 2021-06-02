#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Touch.FingerReleased(0) Then
			Print "Finger x and y : "+ Touch.FingerX(0)+","+Touch.FingerY(0)						
			Print "Finger x and y : "+ Touch.FingerX(0)/640+","+Touch.FingerY(0)/480
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
