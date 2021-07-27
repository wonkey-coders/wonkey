#Rem
	This sample shows how to use a quadtree to check for objects within a box. It uses an interface which you can use to create a callback to 
	decide what happens when a collision is found.
#End

#Import "<mojo>"
#Import "<std>"
'Import the TimelineFX Module
#Import "<timelinefx>"

'We need the following namespaces 
Using std..
Using mojo..
Using timelinefx..

Class Game Extends Window

	'Field to store the quadtree
	Field QTree:tlQuadTree
	
	'field for our box that will used to query the quad tree
	Field player:tlBox
	
	'A Field to store the canvas
	Field currentCanvas:Canvas

	Method New()
		'create the quadtree and make it the same size as the window. Here we're making it so that the maximum number of times it can
		'be subdivided is 5, and it will sub divide a when 10 objects are added to a quad. These numbers you can change To tweak performance
		'It will vary depending on how you use the quadtree
		QTree = New tlQuadTree(0, 0, Width, Height, 5, 10) 
		
		'Populate the quadtree with a bunch of objects
		For Local c:Int = 1 To 10000
			Local t:Int = Rnd(3)
			Local rect:tlBox
			Local x:Float = Rnd() * Width 
			Local y:Float = Rnd() * Height
			Select t
				Case 0
					'Create a Basic bounding box boundary
					rect = New tlBox(x, y, 10, 10, 0)
				Case 1
					'Create a circle Boundary
					rect = New tlCircle(x, y, 5, 0)
				Case 2
					'Create a polygon boundary
					Local verts:= New Float[](- 10.0, -10.0, -15.0, 0.0, -10.0, 10.0, 10.0, 10.0, 15.0, 0.0, 10.0, -10.0)
					rect = New tlPolygon(x, y, verts, 0)
			End Select
			'Add the boundary to the quadtree
			QTree.AddBox(rect)
		Next
		
		player = New tlBox(0, 0, 50, 50)
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		currentCanvas = canvas
	
		App.RequestRender()
	
		canvas.Clear( New Color(0,0,0,1) )
			
		canvas.BlendMode = BlendMode.Alpha
		
		'position the player box
		player.Position(Mouse.X, Mouse.Y)
		Local time:=App.Millisecs
		'when space is pressed, draw everything on the screen. We do this by calling "ForEachObjectInArea", and define the area as the screen size. We also
		'pass the DrawScreen interface which will be called by the quadtree if it finds something in the are. We also pass the layers that we want to check.
		If Keyboard.KeyDown(Key.Space) QTree.ForEachObjectInArea(0, 0, Width, Height, Self, DrawScreenCallBack, New Int[](0, 1, 2))
		
		'Check for objects within a box using "ForEachObjectWithinBox", passing our player box. We also pass the player as "Data" which is forwarded on to the
		'DrawBoxAction so we can use it to find out if it is actually colliding with anything. We pass the DrawBoxAction interface
		'we created which will be called when the qaudtree finds something within the bounding box of the object. We also pass the layers that we want to check.
		QTree.ForEachObjectInBox(player, self, DrawBoxCallBack, New Int[](0, 1, 2))
		
		'Draw the player box
		player.Draw(canvas)
		time = App.Millisecs - time
		
		canvas.DrawText(time, 10, 10)
	
	End

End

'These are our call back fuctions where we can decide what to do with each object found in the quadtree query.
'The parameters will contain the object found and any data that you pass through to the query.
Function DrawBoxCallBack:Void(foundobject:Object, data:Object)
	'Use casting to create a local rect of whatever boundary object the quad tree has found.
	'This could be either a tlBoundary, tlBoundaryCircle, tlBoundaryLine or tlBoundaryPoly
	Local rect:tlBox = Cast<tlBox>(foundobject)
	'We used the data variable to pass the Game object. This could be
	'any object, such as a game entity, which could have a field containing a tlBoundary representing
	'its bounding box/poly etc.
	Local thegame:= Cast<Game>(data)
	'Do a collision check and store the result
	Local collisionresult:tlCollisionResult = CheckCollision(thegame.player, rect)
	'If there is a collision
	If collisionresult.Intersecting = True
		'if we can check for the type of collision like this, you can have either tlPOLY_COLLISION, tlBOX_COLLISION, tlLINE_COLLISION,tlCIRCLE_COLLISION
		If rect.CollisionType = tlPOLY_COLLISION
			'For any polygon collisions rotate the polygon
			Cast<tlPolygon>(rect).RotateDegrees(1)
		
			'because the polygon has move it needs to be updated within the quadtree.
			Cast<tlPolygon>(rect).UpdateWithinQuadtree()
		End If
		
		'Draw the object that collided with the player box in a different colour
		thegame.currentCanvas.Color = New Color(0, 1, 0)
		rect.Draw(thegame.currentCanvas)
	End If
End

Function DrawScreenCallBack:Void(o:Object, data:Object)
	'Use casting to create a local rect of whatever boundary object the quad tree has found.
	'This could be either a tlBoundary, tlBoundaryCircle, tlBoundaryLine or tlBoundaryPoly
	'Note that the Box object has a Data field that you could use to store another object, say your game entity.
	Local rect:tlBox = Cast<tlBox>(o)
	Local thegame:=Cast<Game>(data)
	thegame.currentCanvas.Color = New Color(0.5, 0.5, 0.5)
	
	'Draw the box that was found
	rect.Draw(thegame.currentCanvas)
End

Function Main()

	New AppInstance
	
	New Game
	
	App.Run()

End
