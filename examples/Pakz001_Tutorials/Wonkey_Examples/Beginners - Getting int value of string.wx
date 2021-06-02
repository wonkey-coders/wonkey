#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
		'
		canvas.DrawText("Alphabet/Characters integer value example",0,0)
		canvas.DrawText("int value of letter a="+"a"[0],0,20)
		canvas.DrawText("int value of letter A="+"A"[0],0,40)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
