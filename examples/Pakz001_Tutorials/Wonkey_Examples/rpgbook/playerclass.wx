#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class player
	'weapon useage and attack damage
	Field strength:Int
	'magic useage and spell damage bonusses
	Field intelligence:Int
	'how much damage can the character take before dying
	Field hitpoints:Int
	'how much magic damage can character inflict before running out
	Field magicpoints:Int
	'every level you need a certain amount of points to level up
	Field experiencepoints:Int
	
End Class

Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
