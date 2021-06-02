#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' 
' The Linear Interpolation function lerp featured here is a function
' that takes 0.0 to 1.0 as its first value, this will tell the function
' to return a value between the second and third value. This on the percentage
' of the first. 0.0 is 0 percent and 1.0 is 100 percent.
'
' lerp(0,0,10) would return 0
' lerp(0.5,0.10) would return 5
' lerp(1,0,10) would return 10
' 
' You can use it for example moving a player from start to goal location
' x = lerp(percentage,x1,x2)
' y = lerp(percentage,y1,y2)

Class MyWindow Extends Window

	Field percentage:Float=0 'will go from 0.0 to 1.0
	Field stp:Float=.05 'step value smaller is smoother
	Field playerx:Int,playery:Int
	Field x1:Int=100,y1:Int=100 'our path start
	Field x2:Int=200,y2:Int=250 'our path end
	Method New()
		' set the player start location
		playerx = x1
		playery = y1
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)

		canvas.Color = Color.White
		canvas.DrawRect(playerx,playery,32,32)

		' move the player (ea:patrol)
		playerx = lerp(percentage,x1,x2)
		playery = lerp(percentage,y1,y2)
		
		percentage+=stp
		If percentage>=1 Or percentage<=0 Then stp=-stp


		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Function lerp:double(t:double , a:double, b:double) 
		return a + t * (b - a)
	End Function 	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
