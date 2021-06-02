#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Global myi:=10

Class MyWindow Extends Window


	Field myf:=0.10
	Field mys:="hello"
	
	Method New()
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Integer : "+myi,0,0)	
		canvas.DrawText("Float : "+myf,0,15)
		canvas.DrawText("String : "+mys,0,30)
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
