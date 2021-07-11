#Rem
	This sample shows how to use a quadtree to check for objects using a ray cast. It uses an interface which you can use to create a callback to 
	decide what happens when a collision is found.
#End

#Import "<mojo>"
#Import "<std>"
'Import the TimelineFX Module
#Import "<timelinefx>"

'We need the following namespaces (std and mojo are already imported in timelinefx module so that's why you don't need to import them above)
Using std..
Using mojo..
Using timelinefx..

Class Game Extends Window

	'Field to store the quadtree
	Field QTree:tlQuadTree
	
	'A vector to store the direction of the ray
	Field ray:tlVector2
	Field mat:tlMatrix2
	
	'The origin of the ray
	Field vpoint:tlVector2
	
	Field currentCanvas:Canvas
	Field point:tlVector2
	Field currentslice:Float
	Field faceangle:Float

	Method New()
		'create the quadtree and make it the same size as the window. Here we're making it so that the maximum number of times it can
		'be subdivided is 5, and it will sub divide a when 10 objects are added to a quad. These numbers you can change To tweak performance
		'It will vary depending on how you use the quadtree
		QTree = New tlQuadTree(0, 0, Width, Height, 5, 10)
		
		point = New tlVector2
		
		'Populate the quadtree with a bunch of objects
		For Local c:Int = 1 To 100
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
		
		'Create the ray
		ray = New tlVector2(0, 0)
		vpoint = New tlVector2(400, 400)
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		currentCanvas = canvas
	
		App.RequestRender()
	
		canvas.Clear( New Color(0,0,0,1) )
			
		canvas.BlendMode = BlendMode.Alpha
		
		If Mouse.ButtonDown(MouseButton.Left) vpoint = New tlVector2(Mouse.X, Mouse.Y)
		ray = New tlVector2(Mouse.X - point.x, Mouse.Y - point.y).Normalise()
		
		If Keyboard.KeyDown(Key.Left) faceangle-=0.1
		If Keyboard.KeyDown(Key.Right) faceangle+=0.1
		
		'Set our point coordinates.
		point= vpoint.Clone()
		
		QTree.UnHighlight(0)
		'Draw everything on the screen. We do this by calling "ForEachObjectInArea", and define the area as the screen size. We also
		'pass the DrawScreen interface which will be called by the quadtree if it finds something in the are. We also pass the layers that we want to check.
		QTree.ForEachObjectInArea(0, 0, Width, Height, Self, DrawScreenCallBack, New Int[](0, 1, 2))
		
		Local raytime:=Millisecs()
		'query the quadtree with the ray and run our call back if it hit. Otherwise draw the full length of the ray (300)
		'we're using the data variable here to pass through the Point to the interface
		For Local i:=0.0 To 360 Step 0.1
			ray = New tlVector2(0, 1)
			Local Direction:=DegRad(i)+faceangle
			mat = New tlMatrix2(Cos(Direction), Sin(Direction), -Sin(Direction), Cos(Direction))
			ray = mat.TransformVector(ray).Normalise()
			If Not QTree.RayCast(point.x, point.y, ray, 300.0, Self, RayCallBack, New Int[](0, 1, 2))
				canvas.Color = New Color( 1, 0, 0 )
				canvas.DrawLine (point.x, point.y, point.x + (ray.x * 300), point.y + (ray.y * 300))
			End If
		Next
		raytime=Millisecs() - raytime
		'QTree.Draw(canvas, 0, 0, 0)
		canvas.DrawText("Ray Time (including drawing): " + raytime, 10, 10)
	End

End

'These are our callbacks which are used so that we can program what happens when the quadtree finds things in the area that we're checking. In this case
'we're doing a raycast on the quadtree so it will pass the first object that is hit by the ray.
'The callback function for a line and ray query has an additional parameter which will contain the result of the 
'collision where you can find out things such as the intersection point.
Function RayCallBack:Void(ObjectTheRayHit:Object, Data:Object, Result:tlCollisionResult)
	'cast the objects to some local variables
	Local thegame:=Cast<Game>(Data)
	Local box:tlBox = Cast<tlBox>(ObjectTheRayHit)
	
	'if the ray does not originate inside an object then draw the ray and intersection point
	If Not Result.RayOriginInside
		thegame.currentCanvas.Color = New Color( 1, 0, 0 )
		thegame.currentCanvas.DrawLine(thegame.point.x, thegame.point.y, Result.RayIntersection.x, Result.RayIntersection.y)
	End If
	
	Result.RayDistance
	
	'draw the box the ray hit
	thegame.currentCanvas.Color = New Color( 1, 1, 1 )
	box.Draw(thegame.currentCanvas)
End

Function DrawScreenCallBack:Void(o:Object, data:Object)
	'Use casting to create a local rect of whatever boundary object the quad tree has found.
	'This could be either a tlBoundary, tlBoundaryCircle, tlBoundaryLine or tlBoundaryPoly
	'Note that the Box object has a Data field that you could use to store another object, say your game entity.
	Local rect:tlBox = Cast<tlBox>(o)
	Local thegame:=Cast<Game>(data)
	thegame.currentCanvas.Color = New Color(1, 1, 1)
	
	'Draw the box that was found
	rect.Draw(thegame.currentCanvas)
End

Function Main()

	New AppInstance
	
	New Game
	
	App.Run()

End
