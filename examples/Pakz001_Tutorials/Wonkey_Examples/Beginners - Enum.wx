#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

' Here we create the enum
' it gives a number to each variable in the enum section
Enum test
	a,b,c
End Enum 

Enum test2
	a = 10
	b = 20
	c = 30
End Enum

Class MyWindow Extends Window

	Method New()		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()				
		'
		if test.a = 0 then canvas.DrawText("Enum a = 0",0,0)
		If test.b = 1 then canvas.DrawText("Enum b = 1",0,15)
		If test.c = 2 then canvas.DrawText("Enum c = 2",0,30)
		if test2.a = 10 then canvas.DrawText("Enum 2 a = 10",110,0)
		If test2.b = 20 then canvas.DrawText("Enum 2 b = 20",110,15)
		If test2.c = 30 then canvas.DrawText("Enum 2 c = 30",110,30)

	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
