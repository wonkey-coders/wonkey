#Import "<pyro-framework>"																					' Import pyro framework.

Using pyro.framework..

Global bullets:=New ObjectPool<Bullet>

Class Bullet

	Field name:=""
	Field poolIndex:=0

	Method Free()
		bullets.Free( poolIndex )
	End

End

Function Main()

	' Create a pool of bullets
	For Local i:=0 Until 5
		Local bullet:=New Bullet()
		bullet.name="bullet "+i
		bullet.poolIndex=bullets.Add( bullet )					' Store the index for faster removal!
	Next

	' Get the first available bullet and free it
	Local bullet:=bullets.GetAvailable()
	If bullet
		Print bullet.name
		bullet.Free()
	Endif

End
