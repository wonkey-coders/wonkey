#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Global mylist := New List<Int>

Class MyWindow Extends Window

	Method New()
		For Local i:=0 Until 10
			mylist.AddLast(i)
		Next
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		Local y:=0
		For Local value:=Eachin mylist
			canvas.DrawText(value,0,y)
			y+=15
		Next
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
