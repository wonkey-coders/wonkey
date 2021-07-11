Namespace spacecraft

'Rocks are created what a map tile is destroyed
Class RockObject Extends GameObject
	
	'The life is how many milliseconds the rock object will hang around for before expiring
	Field Life:Int
	'Timestamp will be the internal clock (in millisecs) for when the rock was created. We can then use this
	'to make the rock expire after a certain amount of time
	Field TimeStamp:Int
	'The map layer that this rock belongs to
	Field MapLayer:Int
	'A chipmunk vector that we will need to implement the tractor beam weapon
	Field BeamVec:cpVect = cpvzero
	
	'Constructor for the rock
	Method New(game:SpaceCraft, x:Float, y:Float, life:Int, layer:Int)
		Super.New(game)
	
		XY = New Vec2f(x, y)
		Life = life
		TimeStamp = Millisecs()
		MapLayer = layer
		'Grab the image to use from the map tile layer (we set that when creating the map)
		Image = Game.Map.Layers[layer].RockImage
		
		'Scale the rock to the size that we want. A little variation can be used as well.
		Scale = New Vec2f(0.2, 0.2)
		
		'Initialise the physics
		InitPhysics(1, 4.25, RocksCT, 1, Rocks, MapTiles|PlayerSensors|Rocks|Utilities)
	
	End Method 
	
	'Over ride the update method in GameObject so that we can rotate and adjust the velocity
	Method Update() Override
		Super.Update()
		
		'Match the rotation of the rock to the Chipmunk Body
		Rotation = -cpBodyGetAngle(Body)
		'In chipmunk objects that roll do not lose energy so this will fix that so that rocks will slow to a halt
		cpBodySetVelocity(Body, cpvmult(cpBodyGetVelocity(Body), 0.98))
		
		'If the rock as been around for longer then we want then remove it from the world
		If Millisecs() - TimeStamp > Life
			Game.RemoveObjectFromSpace(Self)
		End If
	End
	
End