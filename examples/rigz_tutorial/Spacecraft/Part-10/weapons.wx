Namespace spacecraft

'The BluePrints class is and abstract class we can use as a basis for all of the weapons
'in the Game
Class Weapon Abstract
	'The name of the weapon
	Field Name:String
	
	'The amount of damage the weapon does
	Field Damage:Float

	'Effect that the weapon uses, this is the reference effect
	Field Effect:tlEffect
	'When the weapon is in use, the Effect will be cloned into the active weapon
	Field ActiveEffect:tlEffect
	
	'A link to the User which the weapon belongs to
	Field User:Player
	
	'A flag to keep track of whether the weapon is active or not
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
	
	'Each weapon will have a method to active and deactivate the weapon
	Method Activate() Abstract
	
	Method DeActivate() Abstract
End

Class MiningLaser Extends Weapon
	'Maximum length of the laser
	Field Length:Float
	
	'Constructor for mining laser
	Method New(name:String, damage:Float, user:Player)
		'Call the new method in the class we're extending with Super
		Super.New(name, damage, user)
		Init()
	End

	'Override the init method and set up the laser ready for use
	Method Init() Override
		'Set the range or length of the laser to 350 pixels
		Length = 350
		'Get the effect for the laser from the effects library
		Effect = User.Game.Effects.GetEffect("Laser")
	End Method
	
	'When the weapon is fired this method is called where we create effects and other things for the weapon
	Method Activate() Override
		If Not Active
			'If the laser is not currently active then get a copy of the effect and add it to the weapons particle manager
			'Set Active to true so this isn't called again while the mouse button is held down
			Active = True
			ActiveEffect = CopyEffect(Effect, User.Game.WeaponPM)
			User.Game.WeaponPM.AddEffect(ActiveEffect)
		End If
		
		'Set the effect angle to that which the User is facing. We add 90degrees (or 1.5708 in radians) and
		'reverse the angle so that it all syncs up (angles in TimelineFX work a little differently
		ActiveEffect.SetEffectAngle(-User.Rotation + 1.5708)
		'Match the position of the laser to that of the User
		ActiveEffect.SetPosition(User.XY.x, User.XY.y)
		
		'Get the end of the laser coordinates based on the player location and direction that it's facing
		Local laser:=User.Facing*Length+User.XY
		'Create a chipmunk filter that looks for maptiles only as that's all we want the laser to collide with
		Local spacefilter:=cpShapeFilterNew(ULong(0), MapTiles, MapTiles)
		'We need a variable to store the result of the chipmunk segment query (or raycast)
		Local out:cpSegmentQueryInfo
		
		'cpSpaceSegmentQueryFirst gets the first object in the space that the line hits - in this case our laser beam.
		'We're interested in the data that gets put into the "out" variable as it will contain data such as the point of impact
		Local tileshape_ptr:=cpSpaceSegmentQueryFirst(User.Game.Space, cpv(User.XY.x, User.XY.y), cpv(laser.x, laser.y), -1, spacefilter, Varptr(out))
			
		If Not out.shape
			'If out doesn't have a shape then that means nothing was hit, so set the lenght of the laser to the default length
			ActiveEffect.SetLineLength(Length)
		Else
			'There is a shape that was hit so call MiningLaserCallBack to handle that 
			MiningLaserCallBack(out)
		End If
	End Method
	
	'If the mouse button is not being pressed then the deactive method is called
	Method DeActivate() Override
		If Active
			Active = False
			'Kill the effect immediately to stop it from rendering. The particle manager will deal with that for us
			ActiveEffect.HardKill()
			'Set the ActiveEffect to null as we don't need it for now.
			ActiveEffect = Null
		End If
	End Method
	
	'Handle what happens when a map tile is hit with the mining laser
	Method MiningLaserCallBack(info:cpSegmentQueryInfo)
		'Get the laser vector so that we can calculate the distance from the player to the tile that was hit
		Local laser:= New Vec2f(info.point.x, info.point.y) - User.XY
		
		'creat the flare (or spark) effect, grab the effect from the library
		Local flare:tlEffect = CopyEffect(User.Game.Effects.GetEffect("flare1"), User.Game.WeaponPM)
		'Set the location of the flare to the point of impact
		flare.SetPosition(info.point.x, info.point.y)
		'Set the emission angle to point back towards the player
		flare.SetEmissionAngle( -ATan2(User.Facing.x, User.Facing.y) )
		
		'Set the length of the laser effect to the distance between the player and the point of impact
		ActiveEffect.SetLineLength(laser.Length)
		
		'Add the flare effect to the particle manager. Note that the flare effect is a short effect that lasts only
		'a brief time but as this method will be called every update while the laser is hitting, a new flare effect
		'will be continuously created and added to the particle manager. The particle manager will automatically remove
		'all the flare effects as they die out.
		User.Game.WeaponPM.AddEffect(flare)
	End
End