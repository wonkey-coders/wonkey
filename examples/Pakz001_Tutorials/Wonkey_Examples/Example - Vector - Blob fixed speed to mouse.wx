#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field blob:= New Vec2f(50,50)
	Field velocity:=New Vec2f(0,-2)
	Field acc:=New Vec2f()
Method New()
		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Create a vector that holds the desired velocity
		Local desired:= New Vec2f()
		' Get the angle between blob and mouse and multiply it by 0.1
		desired = (blob-Mouse.Location)*0.1				
		desired.Normalize()
		' Substract the desired from blob to move blob
		' towards the mouse
		
		
		Local steer:= New Vec2f()
		steer= desired-velocity
		
		' set the movement speed to 1
		steer = vectorlimit(steer,1)
		
		blob-=steer
		'draw the blob
		canvas.DrawCircle(blob.x,blob.y,10)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function vectorlimit:Vec2f(myvec:Vec2f,max:float)
	Local out:= New Vec2f()
	out = myvec
	Local lengthSquared:Float = out.x * out.x + out.y * out.y
	    
	   if( ( lengthSquared > max * max ) and ( lengthSquared > 0 ) ) 
	        Local ratio:Float = max / Sqrt( lengthSquared )
	        out.x *= ratio
	        out.y *= ratio
	   End If
	Return out	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
