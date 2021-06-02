#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		Title="Select Case Example"
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		Local out1:String="this is a test to see if it works."
		Local numspaces:Int=0
		For Local i:=Eachin out1.Split(" ")
			numspaces+=1
		Next
		canvas.DrawText("Counting the spaces resulted in : "+numspaces+" spaces.",0,50)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
