#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)

		' Create a screen filled with random
		' text.
		SeedRnd(0)
		' Here the font height is used.
		For Local y:Int=0 To Height Step canvas.Font.Height
			Local x:Int=0
			While x<Width-120
				Local a:String=""
				Local b:Int=Rnd(5,10)				
				For Local c:int=0 To b
						a+=String.FromChar(Rnd(65,65+26))						
				Next
				a+=" "
				canvas.DrawText(a,x,y)
				' here we add the width of the text to x					
				x+=canvas.Font.TextWidth(a)
				
			Wend
		Next		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
