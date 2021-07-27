'Every file we make for including with our main source needs to make sure
'that it's in the correct namespace.
Namespace spacecraft

'The game object class will be the main class that handles all of our game objects
'We will be extending this class to create our different object classes, for example "Player"
Class GameObject
	
	'Store the object XY coordinates in the game world
	Field XY:Vec2f = New Vec2f(0, 0)
	'The color of the object
	Field Color:Color = New Color(1, 1, 1, 1)
	'The angle that the object is drawn at
	Field Rotation:Float
	'The scale of the object
	Field Scale:Vec2f = New Vec2f(1, 1)
	'The offset that the object is drawn at. We set it to the centre by default
	Field Handle:Vec2f = New Vec2f(0.5, 0.5)
	'Store the image of the object
	Field Image:Image
	'The components of the objects. In order to give our gameobjects different funcitonality depending on what they are
	'we will be using a components based system, where we can make each component make the object do different things.
	'Those things could be player control system, physics, collsions etc.
	Field Components:Stack<Component> = New Stack<Component>
	
	'Store a reference to the game which will be useful to have acces to
	Field Game:SpaceCraft
	
	Method New(game:SpaceCraft)
		Game = game
	End
	
	Method Update()
		'update all of the components in the object
		For Local c:=Eachin Components
			c.Update()
		Next	
	End
	
	'Draw the object
	Method Draw(canvas:Canvas)
		Image.Handle = Handle
		canvas.DrawImage(Image, XY, Rotation, Scale)
	End
	
	'Add a component to the object
	Method AddComponent:Component(c:Component)
		c.Parent = Self
		Components.Add(c)
		Return c
	End
	
End

'The abstract component class designed to be overridden 
Class Component Abstract
	'Store the game object the component belongs to
	Field Parent:GameObject
	'A name field for reference
	Field Name:String
	
	Method New(name:String)
		Name = name
	End
	
	'All components we create will have an update method that we override to give it whatever functionality that we need 
	Method Update() Abstract
	
	
End