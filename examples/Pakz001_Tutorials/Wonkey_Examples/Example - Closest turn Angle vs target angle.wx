#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		'Our target angle
		Local target:Float=Pi+0.5
		'Our angle
		Local angle:Float=TwoPi-0.2

        Print angledifference(target,angle)
		
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Return a float value which is negative if the distance between the angle
' and target angle is shorter. Positive value if the right turn is shorter.
' Uses for homing missiles and turrets etc.
' returns - distance float
Function angledifference:Float(target:Float,angle:Float)
	' Our difference (Negative if left target angle is shorter or positive if right turn is closer)
	Local difference:Float = target - angle
	While (difference < -Pi) 
		difference += TwoPi
	Wend
	While (difference > Pi) 
		difference -= TwoPi
	Wend	
	Return difference
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
