Namespace spacecraft

'The BluePrints class is and abstract class we can use as a basis for all of the weapons
'in the game
Class Weapon Abstract
	'The name of the weapon
	Field Name:String
	
	'The amount of damage the weapon does
	Field Damage:Float

	'Effect that the weapon uses, this is the reference effect
	Field Effect:tlEffect
	'When the weapon is in use, the Effect will be cloned into the active weapon
	Field ActiveEffect:tlEffect
	
	'A link to the player which the weapon belongs to
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
		
		'Set the effect angle to that which the player is facing. We add 90degrees (or 1.5708 in radians) and
		'reverse the angle so that it all syncs up (angles in TimelineFX work a little differently
		ActiveEffect.SetEffectAngle(-User.Rotation + 1.5708)
		'Match the position of the laser to that of the player
		ActiveEffect.SetPosition(User.XY.x, User.XY.y)
			
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
End