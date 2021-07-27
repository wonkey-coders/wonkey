Namespace spacecraft

'The BluePrints class is and abstract class we can use as a basis for all of the weapons
'in the Game
Class Weapon Abstract
	'The name of the weapon
	Field Name:String

	'The amount of damage the weapon does
	Field Damage:Float

	'Effect that the weapon uses, this is the reference Effect
	Field Effect:tlEffect
	'When the weapon is in use, the Effect will be cloned into the Active weapon
	Field ActiveEffect:tlEffect

	'A link to the User which the weapon belongs to
	Field User:Player

	'A flag to keep track of whether the weapon is Active or not
	Field Active:Int

	'Default constructor
	Method New()
	End

	'Contructor
	Method New(name:String, damage:Float, user:Player)
		Name = name
		Damage = damage
		User = user
		Init()
	End

	'Weapon can be initialised here
	Method Init() Virtual

	End

	'Each weapon will have a method to Active and deactivate the weapon
	Method Activate() Abstract

	Method DeActivate() Abstract
End

Class MiningLaser Extends Weapon
	'Maximum Length of the laser
	Field Length:Float

	'The Effect for mining a map tile
	Field MineGlow:tlEffect

	'The coords of the maptile currently being mined
	Field MinedNode:Vec2i = New Vec2i(-1, -1)

	'Constructor for mining laser
	Method New(name:String, damage:Float, user:Player)
		'Call the new method in the class we're extending with Super
		Super.New(name, damage, user)
		Init()
	End

	'Override the init method and set up the laser ready for use
	Method Init() Override
		'Set the range or Length of the laser to 350 pixels
		Length = 350
		'Get the Effect for the laser from the Effects library
		Effect = User.Game.Effects.GetEffect("Laser")
	End Method

	'When the weapon is fired this method is called where we create Effects and other things for the weapon
	Method Activate() Override
		If Not Active
			'If the laser is not currently Active then get a copy of the Effect and add it to the weapons particle manager
			'Set Active to true so this isn't called again while the mouse button is held down
			Active = True
			ActiveEffect = CopyEffect(Effect, User.Game.WeaponPM)
			User.Game.WeaponPM.AddEffect(ActiveEffect)
		End If

		'Set the Effect angle to that which the User is Facing. We add 90degrees (or 1.5708 in radians) and
		'reverse the angle so that it all syncs up (angles in TimelineFX work a little differently
		ActiveEffect.SetEffectAngle(-User.Rotation + 1.5708)
		'In order to make sure that the laser starts from a point on the player ship that is located at the tip of the ships nose
		'We call the GetRotatedPoint function that we created to calclate where that should be based on the rotation of the player
		Local laservec:=GetRotatedPoint(User.Rotation, New Vec2f(0, 20)) + User.XY
		'Match the position of the laser to that of the User
		ActiveEffect.SetPosition(laservec.x, laservec.y)

		'Get the end of the laser coordinates based on the player location and direction that it's Facing
		Local laser:=User.Facing*Length+laservec
		'Create a chipmunk filter that looks for maptiles only as that's all we want the laser to collide with
		Local spacefilter:=cpShapeFilterNew(ULong(0), MapTiles, MapTiles)
		'We need a variable to store the result of the chipmunk segment query (or raycast)
		Local out:cpSegmentQueryInfo

		'cpSpaceSegmentQueryFirst gets the first object in the space that the line hits - in this case our laser beam.
		'We're interested in the data that gets put into the "out" variable as it will contain data such as the point of impact
		Local tileshape_ptr:=cpSpaceSegmentQueryFirst(User.Game.Space, cpv(User.XY.x, User.XY.y), cpv(laser.x, laser.y), -1, spacefilter, Varptr(out))

		If Not out.shape
			'If out doesn't have a shape then that means nothing was hit, so set the lenght of the laser to the default Length
			'minus 20 to compensate for the position that we set for the starting point of the laser on the ship
			ActiveEffect.SetLineLength(Length)
			'Stop the glow Effect
			StopGlow()
		Else
			'There is a shape that was hit so call MiningLaserCallBack to handle that
			MiningLaserCallBack(out)
		End If
	End Method

	'If the mouse button is not being pressed then the deActive method is called
	Method DeActivate() Override
		If Active
			Active = False
			'Kill the Effect immediately to stop it from rendering. The particle manager will deal with that for us
			ActiveEffect.HardKill()
			'Set the ActiveEffect to null as we don't need it for now.
			ActiveEffect = Null
			StopGlow()
		End If
	End Method

	'There's a few cases where we need to be able to stop the glow Effect when a player is mining. So best to
	'put it in a method and just call that whenever we need to
	Method StopGlow()
		'Make sure MineGlow isn't null
		If MineGlow
			'Use SoftKill to make the Effect stop spawning particles. Remaining particles in the Effect will continue
			'their animation until they're gone at which point the particle manager will tidy up the Effect.
			MineGlow.SoftKill()
			MineGlow = Null
			'Reset the current mined node coordinates
			MinedNode = New Vec2i(-1, -1)
		End If
	End Method

	'Handle what happens when a map tile is hit with the mining laser
	Method MiningLaserCallBack(info:cpSegmentQueryInfo)
		'Get the laser vector so that we can calculate the distance from the player to the tile that was hit
		Local laser:= New Vec2f(info.point.x, info.point.y) - User.XY

		'creat the flare (or spark) Effect, grab the Effect from the library
		Local flare:tlEffect = CopyEffect(User.Game.Effects.GetEffect("flare1"), User.Game.WeaponPM)
		'Set the location of the flare to the point of impact
		flare.SetPosition(info.point.x, info.point.y)
		'Set the emission angle to point back towards the player
		flare.SetEmissionAngle( -ATan2(User.Facing.x, User.Facing.y) )

		'Set the Length of the laser Effect to the distance between the player and the point of impact
		ActiveEffect.SetLineLength(laser.Length - 20)

		'Add the flare Effect to the particle manager. Note that the flare Effect is a short Effect that lasts only
		'a brief time but as this method will be called every update while the laser is hitting, a new flare Effect
		'will be continuously created and added to the particle manager. The particle manager will automatically remove
		'all the flare Effects as they die out.
		User.Game.WeaponPM.AddEffect(flare)

		'Use the UserData in the shape to get to the tile that has been collided with
		Local tile:=Cast<Tile Ptr>(info.shape.UserData)[0]

		If tile
			'Use our GetNearestNodeToTile to get the nearest node to the point of impact
			Local node:=User.Game.Map.GetNearestNodeToTile(New Vec2f(info.point.x, info.point.y), tile.Location)
			'If for some reason a nearest node wasn't found the node.Layer will equal -1, but in theory this should never
			'be the case
			If node.Layer <> -1
				'Get the properties of the node
				Local properties:=User.Game.Map.Layers[node.Layer].Nodes[node.XY.x, node.XY.y]
				'Check if this is a new node being mined, and if so set up the Glow Effect
				If MinedNode.x <> node.XY.x Or MinedNode.y <> node.XY.y
					'Stop any previous glows
					StopGlow()
					'Grab the Effect from the library
					MineGlow = CopyEffect(User.Game.Effects.GetEffect("minesparks"), User.Game.WeaponPM)
					'Position it at the node point in the world
					MineGlow.SetPosition(User.Game.Map.NodeXToWorld(node.XY.x), User.Game.Map.NodeYToWorld(node.XY.y))
					'Add it to the particle manager
					User.Game.WeaponPM.AddEffect(MineGlow)
					'Set the MindedNode to the node coordinates so we know what node is currently being mined
					MinedNode = node.XY
					'Reset the Damage of this node to 0, so that if you stop mining a node it's damage will reset.
					'This is a gameplay choice so can be tweaked however you want.
					properties.Damage = 0
				End If
				'Increase the damage taken of the current node being mined
				properties.Damage += Damage
				If properties.Damage >= properties.Health
					'if the damage taken is more then the health of the node then erase it from the map
					User.Game.Map.Erase(node.XY.x, node.XY.y, node.Layer)
					'And stop the glow Effect
					StopGlow()
					'Grab the explosion Effect from the library
					Local explosion:tlEffect = CopyEffect(User.Game.Effects.GetEffect("Toon Smoke Puff Ring"), User.Game.WeaponPM)
					'Position it at the node coordinates
					explosion.SetPosition(User.Game.Map.NodeXToWorld(node.XY.x), User.Game.Map.NodeYToWorld(node.XY.y))
					'Scale the size of it down a bit using the Zoom property
					explosion.Zoom = 0.75
					'Add the Effect to the particle manager
					User.Game.WeaponPM.AddEffect(explosion)

					'Create some rock objects
					For Local c:=0 To 5
						'We don't have to assign the rock to a variable because the constructor will add it to the chipmunk
						'space for us. Give them a lifetime of 200-210 seconds
						New RockObject(User.Game, User.Game.Map.NodeXToWorld(node.XY.x) + Rnd(-10, 10), User.Game.Map.NodeYToWorld(node.XY.y) + Rnd(-10, 10), Rnd(200000) + 10000, 0)
					Next
				End If
			End If
		End If
	End
End

Class TractorBeam Extends Weapon

	'We need an area to detect if a rock object is being hit by the tractor beam
	Field BeamArea:cpShape

	'The lenght of the tractor beam
	Field Length:Float

	'The tractor beam will be made up of 2 effects so we need an extra one. ExtraEffect will contain the effect in the library
	'And ActiveExtraEffect will be a copy that we use to manipulate (change the length as it hits MapTiles).
	Field ExtraEffect:tlEffect
	Field ActiveExtraEffect:tlEffect

	Method New(name:String, damage:Float, user:Player)
		Super.New(name, damage, user)
		Init()
	End

	Method Init() Override
		'Set the size of the tractor beam to 250 pixels
		Length = 250
		'Grab the effects we want from the effect library
		Effect = User.Game.Effects.GetEffect("TractorBeam")
		ExtraEffect = User.Game.Effects.GetEffect("TractorBeamRays")

		'Create the chipmunk area for the tractor beam. It will be a poly so that we can make a triangle shape so the end of
		'the beam is wider then the start. Also note that we attach it to the Player's object, so that it will move and rotate
		'With the player automatically.
		
		'Prepare the verts for the tractor beam sensor
		Local verts:=New cpVect[3]
		verts[0] = cpv(0.0, 0.0)
		verts[1] = cpv(-15.0, -1.0)
		verts[2] = cpv(15.0, -1.0)
		BeamArea = cpPolyShapeNew(User.Body, 3, verts.Data, cpTransformScale(1, Length), 0.0)
		'Make it a chipmunk sensor. This means that it won't interact with other objects like it's a physical object, instead
		'it will just sense if other objects are overlapping.
		BeamArea.Sensor = True
		'Set the filter for the beam area.
		cpShapeSetFilter(BeamArea, cpShapeFilterNew(ULong(0), Utilities, Rocks|Utilities|MapTiles))
		'Add the beam area to the Space.
		User.Game.Space.AddShape(BeamArea)
	End Method

	'Handle what happens what the tractor beam is activated
	Method Activate() Override
		If Not Active
			'if it's not currently active then create the effects and add them to the particle manager
			Active = True
			ActiveEffect = CopyEffect(Effect, User.Game.WeaponPM, True)
			ActiveExtraEffect = CopyEffect(ExtraEffect, User.Game.WeaponPM, True)
			User.Game.WeaponPM.AddEffect(ActiveEffect)
			User.Game.WeaponPM.AddEffect(ActiveExtraEffect)
		End If

		'Set the effect angles to match up with the player. Depending on how they're set up in the TimelineFX editor
		'you might have to tweak things here.
		ActiveEffect.SetEffectAngle(-User.Rotation + 1.5708)
		ActiveExtraEffect.SetEffectAngle(-User.Rotation)

		'And set the positions to match the player as well
		ActiveEffect.SetPosition(User.XY.x, User.XY.y)
		ActiveExtraEffect.SetPosition(User.XY.x, User.XY.y)

		'Get the location of the end of the tractor beam which we can use to create the Chipmunk segment query
		Local tractor:=User.Facing*Length+User.XY
		'The query will just see if any maptiles are being hit and adjust the length as necessary
		Local spacefilter:=cpShapeFilterNew(ULong(0), MapTiles, MapTiles)
		'out will contain the result of the segmant query
		Local out:cpSegmentQueryInfo

		'Do the segment query and store the result
		Local tileshape_ptr:=cpSpaceSegmentQueryFirst(User.Game.Space, cpv(User.XY.x, User.XY.y), cpv(tractor.x, tractor.y), -1, spacefilter, Varptr(out))

		If Not out.shape
			'If no map tiles were hit then set the lenght of the tractor beam to it's original lenth
			ActiveEffect.GetEmitter("TractorBeam/Beam").SetBaseWidth(Length)
			ActiveExtraEffect.GetEmitter("TractorBeamRays/Rays").SetBaseHeight(Length * 0.75)
			ActiveExtraEffect.GetEmitter("TractorBeamRays/Rays").SetBaseHeightVariation(Length * 0.75)
		Else
			'Otherwise clal the TractorBeamCallBack to handle that collision
			TractorBeamCallBack(out)
		End If

		'Run a shape query to see if the tractor beam is touching any rocks
		cpSpaceShapeQuery(User.Game.Space, BeamArea, RockSuckedUpCallBack, Varptr(User))
	End Method

	'Handle the deactivation of the tractor beam
	Method DeActivate() Override
		If Active
			'if the beam was on then kill the effects
			Active = False
			ActiveEffect.SoftKill()
			ActiveExtraEffect.SoftKill()
		End If
	End Method

	'The method that handles what happens when the maptiles are hit by the beam
	Method TractorBeamCallBack:Void(info:cpSegmentQueryInfo)
		'Get the laser vector based on the player position and the impact point
		Local laser:= New Vec2f(info.point.x, info.point.y) - User.XY

		'Create a flare effect from the library
		Local flare:tlEffect = CopyEffect(User.Game.Effects.GetEffect("TractorBeamFlare"), User.Game.WeaponPM)

		'Put the flare effect into position (the impact point)
		flare.SetPosition(info.point.x, info.point.y)
		'Set the lenth of the effect to the distance between the player and the impact point
		ActiveEffect.SetLineLength(laser.Length)

		'In order to adjust all the parts of the effect to the correct lenght, we have to get at some specific emitters
		'with the effect and adjust to the laser length (with a little bit of tweaking until it looks right)
		ActiveEffect.GetEmitter("TractorBeam/Beam").SetBaseWidth(laser.Length)
		ActiveExtraEffect.GetEmitter("TractorBeamRays/Rays").SetBaseHeight(laser.Length * 0.75)
		ActiveExtraEffect.GetEmitter("TractorBeamRays/Rays").SetBaseHeightVariation(laser.Length * 0.75)

		'Add the flare effect to the particile manager
		User.Game.WeaponPM.AddEffect( flare )
	End

	'The function that handles what happens when the tractor beam touches a rock
	Function RockSuckedUpCallBack:Void(shape:cpShape, pointset:cpContactPointSet Ptr, p:Void Ptr)
		'Use casting to get at the RockObject stored in the shape userdata.
		Local r:= Cast<RockObject Ptr>(shape.UserData)[0]
		'Get the player too which was passed through to the function
		Local player:=Cast<Player Ptr>(p)[0]

		'In order to get the tractor beam to behave in a way that suits the gameplay we have to do some math. This all came
		'about after experimenting and trial and error

		'A force vector that points towards the player (the opposite way the player is facing)
		Local force:=-player.Facing*10
		'Get the normal of the player facing vector
		Local normal:= player.Facing.Normal
		'And then use that to get the dot product of the vector between the rock and the player. We want to know which side
		'of the beam relative to player the rock is so that we can push it more towards the centre of the beam
		Local dot:Float = cpvdot(cpv(normal.x, normal.y), cpvsub(player.Body.Position, cpv(r.XY.x,r.XY.y)))

		'Convert the player facing vector to a chipmunk vector
		Local tline:=cpv(player.Facing.x,player.Facing.y)
		'Project the position of the rock onto the centre of the tractor beam line (so we get the nearest point on the tractor
		'beam to the rock
		Local proj:=cpvadd(player.Body.Position, cpvmult(tline, cpvdot(cpvsub(r.Body.Position, player.Body.Position), tline)))
		'Get the distance of the rock to that projected point.
		Local d:=cpvdist(proj, r.Body.Position)

		Local v:cpVect

		'If the dot product is great than 0 then the rock is to the left of the beam, otherwise the right. We can then use this
		'information the push it in the right direction
		If dot > 0
			v = cpv(normal.x, normal.y)
		Else
			v = cpv(-normal.x, -normal.y)
		End If

		'Multiply the BeamVec of the rock by the distance towards the centre of the beam (this is the chipmunk vector we
		'set up in the rock object to create a velocity vector that pushes the rock towards the player.)
		r.BeamVec = cpvmult(v, d)

		'Add the force vector to the beamvector
		v = cpvadd(r.BeamVec, cpv(force.x, force.y))
		'This is one of the main things that makes this work ok. We cancel gravity on the rock object when it is touched by the beam
		'Gravity is 500 px/sec hence we divide by 60 (the update time of the game) This can be tweaked if you wanted gravity
		'to have a little bit of an effect and make it more of a challenge to pick the rocks up.
		v = cpvadd(v, cpv(0, -500/60))
		'Make the rock object angle itself toward the player for extra effect
		r.Body.Angle = ATan2(player.Facing.x, player.Facing.y)
		'Set the velocity of the rock to the velocity we have calculated
		cpBodySetVelocity(r.Body,cpvadd(cpBodyGetVelocity(r.Body), v))
		'Clamp the velocity to a sensible limit
		Local clamp:=cpBodyGetVelocity(r.Body)
		clamp = cpvclamp(clamp, 120)
		'Finally set the rock velocity to the clamped amount
		cpBodySetVelocity(r.Body, clamp)

		'Reset the timestamp of the rock so that it won't expire and give the player a chance to pick it up
		r.TimeStamp = Millisecs()
	End

End
