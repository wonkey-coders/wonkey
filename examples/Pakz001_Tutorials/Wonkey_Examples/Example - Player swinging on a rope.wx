'
'  Thanks to Daniel SHiffman (book - nature of code)
'
' This example might be usable in platformer games (rope and swing)
' 

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	' player x and y and width and height
	Field px:Float=100,py:Float=200
	Field pw:Int=32,ph:Int=32
	
	'our anchor x and y
	Field ax:Int=320,ay:Int=0

	Field angle:Float 'our angle between anchor and player	
	Field dist:Float 'distance between anchor and player
	Field acc:Float,vel:Float 'acceleration and velocity
	Field gravity:Float=0.4 ' 
	Field damping:Float=0.995 'slowdown
	Field r:Float 'distance between anchor and player
	Method New()
		' Get the angle betweem the player and the anchor
		angle = getangle(px,py,ax,ay)		
		' Get the distgance between the player and anchor
		r = distance(px,py,ax,ay)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' swing harder
		If Keyboard.KeyReleased(Key.Right) Then vel+=.005
		If Keyboard.KeyReleased(Key.Left) Then vel-=.005
		' CLimb up or down..
		If Keyboard.KeyDown(Key.Up) Then r-=2
		If Keyboard.KeyDown(Key.Down) Then r+=2
		
		' Do the swing math
		acc=(-1*gravity/r)*Sin(angle)
		vel+=acc
		angle+=vel		
		vel*=damping
		
		' update our position
		px = r*Sin(angle)		
		py = r*Cos(angle)
		px+=ax
		py+=ay

		' Draw our player
		canvas.DrawRect(px,py,pw,ph)
		canvas.DrawLine(px+pw/2,py,ax,ay)
		
		canvas.DrawText("Press cursor left and right to apply force..",0,0)
		canvas.DrawText("Hold cursor Up Down to climb or Lower yourself..",0,20)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Return the angle from - to in float
Function getangle:Float(x1:Int,y1:Int,x2:Int,y2:Int)
	Return ATan2(y2-y1, x2-x1)
End Function

' Manhattan Distance (less precise)
Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
	Return Abs(x2-x1)+Abs(y2-y1)   
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
