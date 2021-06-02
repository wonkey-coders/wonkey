#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class overworld
	'map layers
	'dirt, grass, stone etc
	Field background:Int[,]
	'buildings, mountains, trees, villages
	Field ground:Int[,]
	'rocks, weeds, flowers, skulls etc
	Field decoration:Int[,]
	'shapes where player can and can not move to
	Field collision:Int[,]
	'player and non player character spawns
	Field spawn:Int[,]
	'trigger events (move from one map to another)
	Field portal:Int[,]
	
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
