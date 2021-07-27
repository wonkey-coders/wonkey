'Every file we make for including with our main source needs to make sure
'that it's in the correct namespace.
Namespace spacecraft

'The game object class will be the main class that handles all of our game objects
'We will be extending this class to create our different object classes, for example "Player" or "Rock"
Class GameObject
	
	'Store the object XY coordinates in the game world
	Field XY:Vec2f = New Vec2f(0, 0)
	'The color of the object. Note that colour values range from 0 to 1, not 0 to 255
	Field Color:Color = New Color(1, 1, 1, 1)
	'The angle that the object is drawn at
	Field Rotation:Float
	'The scale of the object
	Field Scale:Vec2f = New Vec2f(1, 1)
	'The offset that the object is drawn at. We set it to the centre by default
	Field Handle:Vec2f = New Vec2f(0.5, 0.5)
	'Store the image of the object
	Field Image:Image
	'The components of the objects. In order to give our gameobjects different functionality depending on what they are,
	'we will be using a components based system, where we can make each component make the object do different things.
	'Those things could be a player control system, physics, collsions etc.
	Field Components:Stack<Component> = New Stack<Component>
	'each gameobject will have a chipmunk body and shape for handling the physics and collisions
	Field Shape:cpShape
	Field Body:cpBody
	
	'We need to store a reference to the object in the chipmunk shape that represnents it. To do that a Me field is used
	'to reference itself which is then used as a data pointer in the chipmunk "UserData" field.
	Field Me:GameObject
	
	'Store a reference to the game which will be useful to have acces to
	Field Game:SpaceCraft
	
	'Default constructor. 
	Method New()
	End
	
	Method New(game:SpaceCraft)
		Game = game
		'Self reference the GameObject, this will be used to pass the object into chipmunk queries and collision checks
		Me = Self
	End
	
	Method Update()
		'update all of the components in the object
		For Local c:=Eachin Components
			c.Update()
		Next
		
		'update the position of the object so that it syncs up with the chipmunk body which chipmunk is changed the position of
		'based on the physics being performed on it.
		'Note: a Vec2f is a struct which means it goes on the stack and is pretty much free to overwrite the old position with a new one
		'(Structs don't need to be garbage collected). If you don't know what any of that means then just know that it's fine to do this :)
		XY = New Vec2f(Body.Position.x, Body.Position.y)
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
	
	'Let's initialise the physics for the object. By default we'll use circle shapes as they are fastest and
	'good enough for our needs. Parameters are:
	'@mass: How heavy the object is.
	'@radius: The size of the collision radius
	'@collisiontpye: this is where you can organise objects so that you can manage what you want to happen when 
					'certain objects collide with each other
	'@friction: How much the object slows down when sliding against another surface
	'@category: Similar to collision type, think of it like putting the object onto a specific group in the Space.
				'you can decide which groups are allowed to interact with each other
	'@mask: Here you can set which other groups in the space this object should be able to interact with
	Method InitPhysics(mass:Float, radius:Float, collisiontype:Int, friction:Float, category:UInt, mask:UInt)
  
		'The moment of inertia is like mass for rotation. i don't understand it much either but thankfully
		'this function knows what it's doing!
		'Note that cpvzero is a 0 vector which comes from chipmunk
		Local moment:=cpMomentForCircle( mass, 0, radius, cpvzero )
		
		'Create the body and position it.
		'Note that chipmunk has it's own vector object it uses to do all its math, "cpv" creates a new one of those for us.
		Body = cpBodyNew( mass, moment )
		Body.Position = cpv(XY.x, XY.y)

		'Create a cirlce shape and attach it to the body. Assign the friction, elasticity and collision type.
		Shape = cpCircleShapeNew( Body, radius, cpvzero )
		Shape.Friction = friction
		Shape.Elasticity = .2
		Shape.CollisionType = collisiontype
		'Use the Me field to store a pointer to this object in the shape's "UserData". We can use this later to 
		'grab this GameObject when we're detecting collisions between objects and also when we're using the Space
		'to query objects that fall within a certain area - for example the area of the screen.
		Shape.UserData = Varptr(Me)
		'A shape filter is used to determine which group of objects should collide with each other.
		cpShapeSetFilter(Shape, cpShapeFilterNew(ULong(0), category, mask))
		'Add the body and shape to the space.
		Game.AddObjectToSpace(Self)
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