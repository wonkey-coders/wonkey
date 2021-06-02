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
		' Outline mode. Draw a border around things.
		'
		canvas.Color = Color.Black
		' smooth outline
		canvas.OutlineMode=OutlineMode.Smooth
		canvas.OutlineColor = Color.Blue
		canvas.OutlineWidth = 4
		' Draw things with the new drawing settings
		canvas.DrawRect(50,50,100,100)
		canvas.DrawOval(50,50,20,20)
		canvas.DrawQuad(100,100,200,150,200,200,100,200)
		Local b:Float[] = New Float[](10,10,20,20,10,60)
		canvas.DrawPoly(b)
		' solid outline
		canvas.OutlineMode = OutlineMode.Solid
		canvas.DrawRect(200,50,100,100)
		'Set back the outline mode to none
		canvas.OutlineMode = OutlineMode.None
		canvas.DrawRect(350,50,100,100)
		

		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
