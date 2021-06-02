#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance



Class MyWindow Extends Window
	
	Field mydata:="Nothing"
	
	Method New()
	End Method
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit		
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		' Put the clipboardtext into the string variable
		If Keyboard.KeyReleased(Key.Space) Then
			mydata = instance.ClipboardText
		End If
		'Put string into the clipboard text
		If Keyboard.KeyReleased(Key.P) Then
			instance.ClipboardText = mydata
		End If
		
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Space to Paste Current Clipboardtext..",0,0)
		canvas.DrawText("P to copy data into the clipboardtext..",0,15)
		canvas.DrawText(mydata,0,30)
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
