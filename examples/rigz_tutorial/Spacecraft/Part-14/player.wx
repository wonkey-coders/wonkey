Namespace spacecraft

'A player class which extends the GameObject class. this means that it will inherit all of the functionality
'contained in the GameObject class.
Class Player Extends GameObject

	'We will need to know which way the player is facing, so lets store that in a vec2f
	Field Facing:Vec2f = New Vec2f

	'An array to hold a number of weapons that might be available to the player
	Field Weapons:Weapon[]

	'An index for the currently selected weapon
	Field SelectedWeapon:Int
	Field SelectedWeaponAlt:Int

	'The glow effect for the player
	Field Glow:tlEffect

	'The effect used for thrusters
	Field Thrusters:tlEffect

	'A shape for the player sensor what will detect when the player touches a rock
	Field Collector:cpShape

	Method New(game:SpaceCraft, x:Float, y:Float)
		Super.New(game)

		'Set the initial position of the player
		XY = New Vec2f(x, y)

		'Initialise the physics
		InitPhysics(100, 10, 1, 1, Players, MapTiles|Players)

		'We also need a way to detect if the player is touching a rock so that it can be "absorbed".
		'So here we create a Sensor and set it to the PlayerSensors mask and collision type the same as the player
		'In the game class we create a collision handler for when the rock hits the player.
		Collector = cpCircleShapeNew(Body, 10, cpvzero)
		Collector.Sensor = True
		Collector.CollisionType = PlayerCT
		Collector.UserData = Varptr Me
		cpShapeSetFilter(Collector, cpShapeFilterNew(ULong(0), PlayerSensors, PlayerSensors|Rocks))
		cpSpaceAddShape(Game.Space, Collector)

		'Add a control Component to the player
		AddComponent(New Controls("Controls", Self))

		'Initialise the weapons array
		Weapons = New Weapon[9]

		'And give the player a mining laser to start with
		Weapons[0] = New MiningLaser("Mining Laser", 1, Self)
		Weapons[1] = New TractorBeam("Tractor Beam", 0, Self)

		'Set the mining laser as the currently selected weapon
		SelectedWeapon = 0
		SelectedWeaponAlt = 1

		Glow = CopyEffect(game.Effects.GetEffect("Player glow"), Game.WeaponPM)
		Glow.SetZ(0.35)
		Game.WeaponPM.AddEffect(Glow)
	End

	'Override the update method in the GameObject to do our own unique player stuff
	Method Update() Override
		'We still want to do the things in the GameObject update method so call it here with Super
		Super.Update()

		'Position the glow effect so that it follows the player about
		Glow.SetPosition(XY.x, XY.y)
		'And set it to the right angle to align it with the player
		Glow.SetEffectAngle(-Rotation + 3.14159)

		'If there is a thrusters effect (which there will be as soon as the player starts moving
		If Thrusters
			'Set the emission angle of the effect to align with the player
			Thrusters.SetEmissionAngle(-Rotation)
			'Call the GetRotatedPoint function that we created to calcute the correct point on the player ship to draw the
			'Thruster effect at.
			Local thrustervec:=GetRotatedPoint(Rotation, New Vec2f(0, -15))
			'And set the position of the thrusters to the player coordinates
			Thrusters.SetPosition(XY.x + thrustervec.x, XY.y + thrustervec.y)
		End If
	End

End

'The player will need to be controlled, so we can use make a new Controls class that extends Component
Class Controls Extends Component
	'Store a reference to the player
	Field Player:Player

	'Define some player control keys
	Field MoveUp:= Key.W        'Thrust forwards
	Field MoveDown:= Key.S      'Straf Left
	Field MoveLeft:= Key.A      'Straf Right
	Field MoveRight:= Key.D     'Reverse

	'A vector to contain the current velocity of the player
	Field Velocity:Vec2f
	'A Float to contain how fast the player accellerates, note that values are in pixels per second
	Field Accelleration:Float = 25

	'A toggle field which is set if the player is strafing
	Field Strafing:Int
	'Strafing state is 1 or 2 depending on whether you're strafing left or right relative to the player.
	Field StrafingState:Int

	'Make our own New Method that lets us pass in the player that the component belongs to.
	Method New (name:String, player:Player)
		Super.New(name)
		Player = player
		'Set the velocity update function of the player body to our own custom function so that we can
		'cancel out the effect of gravity on the player.
		cpBodySetVelocityUpdateFunc(Player.Body, UpdateBodyPhysics)
	End

	'Override the abstract Update method where we can put in the functionality that we need to control the player
	Method Update() Override
		'Get the mouse coordinates and convert them to world coordinates so we can figure out where the player
		'needs to be facing
		Local target:=Player.Game.ScreenToWorld(New Vec2f(Mouse.X, Mouse.Y))
		'Subtract the player coords from the mouse coords
		Player.Facing = target - Player.XY
		'Normalize the Facing vector
		Player.Facing = Player.Facing.Normalize()
		'Use the facing vector calculate the angle of the player.
		'Note: The image you use should be facing downwards so that it lines up and faces in the correct direction.
		Player.Rotation = ATan2(Player.Facing.x, Player.Facing.y)

		Velocity = New Vec2f(0,0)

		'If the thust key is pressed
		If Keyboard.KeyDown(MoveUp)
			'Calculate the velocity of the player by multiplying the facing vector by the Accelleration
			Velocity = Player.Facing * Accelleration

			'If there's no thrusters effect yet then create one
			If Not Player.Thrusters
				'Grab the thrusters effect from the effects library
				Player.Thrusters = CopyEffect(Player.Game.Effects.GetEffect("thrusters1"), Player.Game.WeaponPM)
				'This tells the particle manager to not delete the effect if it's not spawning particles
				'This means that the effect will stay in existance while the player isn't moving, so we can
				'keep using the same effect
				Player.Thrusters.DoNotTimeOut = True
				'Add the effect to the particle manager
				Player.Game.WeaponPM.AddEffect(Player.Thrusters)
			Else
				'Set the amount of particles spawned by the effect to 100%
				Player.Thrusters.SetAmount(1)
			End If
		Else
			If Player.Thrusters
				'If the player has stopped thrusting forward then stop the thrusters effect from spawning anymore
				'particles for now by setting the amount to 0%
				Player.Thrusters.SetAmount(0)
			End If
		End If

		'Create a local so that we can toggle a strafing state.
		Local straftest:Int

		'Straf Left
		If Keyboard.KeyDown(MoveLeft)
			'We're strafing so set that to true.
			straftest = True
			Local leftvec:Vec2f
			'If we're not strafing then calculate the dot product to find out the directing we should be moving
			'depending on which way the player is facing
			If Not Strafing
				If Player.Facing.Dot(New Vec2f(0, -1)) <= 0
					'if the dot is less than 0 then straf towards the normal of the facing vector
					leftvec = Player.Facing.Normal
					'Set the strafing state so that we can continue to straf in that direction relative to where the
					'player is facing.
					StrafingState = 1
				Else
					'Straf in the opposite direction if the dot is >0
					leftvec = New Vec2f(Player.Facing.y, -Player.Facing.x)
					StrafingState = 2
				End If
			Else
				'if we're already strafing then keep on moving in the same direction relative to where
				'the player is facing. We use StrafingState which was set when we started strafing.
				Select StrafingState
					Case 1
						leftvec = Player.Facing.Normal
					Case 2
						leftvec = New Vec2f(Player.Facing.y, -Player.Facing.x)
				End Select
			End If
			'Add the leftvec to the Velocity
			Velocity += leftvec * Accelleration
		End If

		'Straf Left
		If Keyboard.KeyDown(MoveRight)
			'We're strafing so set that to true.
			straftest = True
			Local leftvec:Vec2f
			'If we're not strafing then calculate the dot product to find out the directing we should be moving
			'depending on which way the player is facing
			If Not Strafing
				If Player.Facing.Dot(New Vec2f(0, -1)) <= 0
					'if the dot is less than 0 then straf towards the left normal of the facing vector
					leftvec = New Vec2f(Player.Facing.y, -Player.Facing.x)
					'Set the strafing state so that we can continue to straf in that direction relative to where the
					'player is facing.
					StrafingState = 1
				Else
					'Straf in the opposite direction if the dot is >0
					leftvec = Player.Facing.Normal
					StrafingState = 2
				End If
			Else
				'if we're already strafing then keep on moving in the same direction relative to where
				'the player is facing. We use StrafingState which was set when we started strafing.
				Select StrafingState
					Case 1
						leftvec = New Vec2f(Player.Facing.y, -Player.Facing.x)
					Case 2
						leftvec = Player.Facing.Normal
				End Select
			End If
			'Add the leftvec to the Velocity
			Velocity += leftvec * Accelleration
		End If

		'Toggle the Strafing field depending on whether we're strafing or not.
		If straftest
			Strafing = True
		Else
			Strafing = False
		End If

		If Keyboard.KeyDown(MoveDown)
			Local reversevec:Vec2f = New Vec2f(-Player.Facing.x, -Player.Facing.y)
			Velocity+=reversevec * Accelleration
		End If

		'Now we apply the velocity to the Chipmunk body field of the player. Do do this we use a couple of chipmunk
		'functions: cpBodySetVelocity, and cpvadd which is basically a way of adding 2 chipmunk vectors together. In this
		'case we're adding the current velocity of the body (cpBodyGetVelocity), and the just recently calculated
		'accelleration velocity vector.
		cpBodySetVelocity( Player.Body, cpvadd(cpBodyGetVelocity(Player.Body), cpv(Velocity.x, Velocity.y) ) )

		'And we now align the chipmunk body with the current player angle
		cpBodySetAngle(Player.Body, -Player.Rotation + DegRad(180))

		'Next check if the mouse buttons are being pressed and fire the weapons if so. Check if the player
		'actually has a weapon to fire in the current slot
		If Player.Weapons[Player.SelectedWeapon]
			If Mouse.ButtonDown(MouseButton.Left)
				'Fire the weapon!
				Player.Weapons[Player.SelectedWeapon].Activate()
			Else
				'Stop firing
				Player.Weapons[Player.SelectedWeapon].DeActivate()
			End If
		End If

		If Player.Weapons[Player.SelectedWeaponAlt]
			If Mouse.ButtonDown(MouseButton.Right)
				'Fire the weapon!
				Player.Weapons[Player.SelectedWeaponAlt].Activate()
			Else
				'Stop firing
				Player.Weapons[Player.SelectedWeaponAlt].DeActivate()
			End If
		End If
	End

	'This is our own Update body physics which we're using to cancel out the effect of gravity on the player.
	'Chipmunk will pass in a few parameters such as the player body and the gravity. The other 2 (damping and delta)
	'we won't need to worry about.
	Function UpdateBodyPhysics(body:cpBody, gravity:cpVect, damping:cpFloat, dt:cpFloat)

		'Limit the speed of the player to 150 pixels per second
		body.Velocity = cpvclamp(body.Velocity, 150)
		'Multiply the velocity of the player body so that it will slow to a stop when you stop the thrusters. You can play
		'with this number depending on how much inertia you want.
		body.Velocity = cpvmult(body.Velocity, 0.95)

		'Now we've done that we can call the normal chipmunk update velocity function except we pass a 0 gravity vector
		'so that gravity won't have any affect.
		cpBodyUpdateVelocity(body, cpv(0, 0), damping, dt)
	End

End
