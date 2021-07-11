Namespace spacecraft

'The tile set class contains an array of tiles which will be used by a layer on the tilemap. The tilemap will
'pickout the tiles it needs automatically from the tileset.
Class TileSet
	
	'The array of Tile that should contain 16 frames of different tiles
	Field Tiles:Tile[]
	'Name of the tileset
	Field Name:String
	
	'The load method will read a json file and populate the Tiles array with each tile it finds in the json file
	Method Load(file:String)
		'Load the json file
		Local json:=JsonObject.Load(file)
		'Extract the directory from the file name so that we can load the image from the right place later
		Local directory:=ExtractDir(file)
		
		'If the json file contains a files object and it's an array
		If json["files"] And json["files"].IsArray
			'Create the Tiles array and set it to the lenght of the json files array (should be 16)
			Tiles = New Tile[json["files"].ToArray().Length]
			
			'A local index to keep track of the frame we're on
			Local index:Int = 0
			
			'Grab the files array from the json file
			Local files:=json["files"].ToArray()
			
			'Loop through each file
			For Local f:=Eachin files
				Local file:=f.ToObject()
				'Create a new tile in the Tiles array
				Tiles[index] = New Tile
				'Check if the tile type is a poly or a box and load accordingly
				Select file["type"].ToString()
					Case "poly"
						'assign the handle of the image
						Tiles[index].Offset = New Vec2f(file["handlex"].ToNumber(),file["handley"].ToNumber())
						'Get the collision vertices for the poly from the file
						Tiles[index].Verts = JsonFloatArray(file["verts"].ToArray())
						'Set the collision type
						Tiles[index].CollisionType = CollisionTypes.Poly
					Case "box"
						Tiles[index].Offset = New Vec2f(file["handlex"].ToNumber(),file["handley"].ToNumber())
						'Grab the width and height from the file
						Tiles[index].Width = file["width"].ToNumber()
						Tiles[index].Height = file["height"].ToNumber()
						'Set the collision type
						Tiles[index].CollisionType = CollisionTypes.Box
				End
				'Load and store the image using the directory we got earlier
				Tiles[index].Image = Image.Load(directory + file["file"].ToString())
				Print directory + file["file"].ToString()
				index+=1
			Next
		End If
	End
	
	'Method to get a tile from the set by cloning and returning it
	Method GetTile:Tile(index:Int)
		Return Tiles[index].Clone()
	End
	
End

'This enum type simply stores some collision types for easy reference
Enum CollisionTypes
	Box, Circle, Poly
End

'This is a helper function that reads in an array of json values and returns them as an array of floats.
'Pass it a json.ToArray() value
Function JsonFloatArray:Float[](json:Stack<JsonValue>)
	'Create a stack of floats
	Local floats:Stack<Float> = New Stack<Float>
	'Loop through each json value
	For Local value:=Eachin json
		'Add the ToNumber() to the stack
		If value.IsNumber floats.Add(value.ToNumber())
	Next
	'Return the stack as an array of floats
	Return floats.ToArray()
End

'Tile class for storing the data of each tile. Extends GameObject
Class Tile Extends GameObject
	'If the tile is a polygon shape then we need to store the verts here
	Field Verts:Float[]
	'If the tile is a simple box then store the width and height
	Field Width:Float
	Field Height:Float
	
	'Store the type of collision for this tile
	Field CollisionType:CollisionTypes
	
	'The node grid xy coordinates that this tile refers to. Each MapNode has 4 tiles
	Field NodeLoc:Vec2i
	
	'And offset that we can use to make sure that the Chipmunk collision box aligns with the tile
	Field Offset:Vec2i
	
	'Default constuctor
	Method New()
	End
	
	'Add the tile to the chipmunk space. This will only ever be called when the TileMap.Update method is called
	'at the end of an update loop.
	Method AddToSpace()
		'Reference self so that we can point to this tile in the Shape userdata
		Me = Self
		'Check the type of collision and create a body and shape to add to the space
		Select CollisionType
			Case CollisionTypes.Box
				'Our tiles will not move, so create a Static Body
				Body = cpBodyNewStatic()
				'Position the body in the right place in the world
				Body.Position = cpv(XY.x + Offset.x, XY.y + Offset.y)
				'Add the body to the space
				Game.Space.AddBody(Body)
				'This is Box collision tile so use cpBoxShapeNew to create a new box shape
				Shape = cpBoxShapeNew(Body, Width, Height, 0.0)
				'Set the shapes friction to 1
				Shape.Friction = 1
				'Assign the UserData of the shape to point to this tile so we can access it in the chipmunk space queries
				Shape.UserData = Varptr(Me)
				'Add the shape to the space
				Game.Space.AddShape(Shape)
				'Set the shape filter of the shape to the correct mask, in this case MapTiles. We also tell it that it
				'Can collide with Players and Rocks
				cpShapeSetFilter(Shape, cpShapeFilterNew(ULong(0), MapTiles, MapTiles|Players|Rocks))
			Case CollisionTypes.Poly
				'For poly collisions, similar to above but cpPolyShapeNew is used to create the shape
				Body = cpBodyNewStatic()
				Body.Position = cpv(XY.x - 16,XY.y - 16)
				Game.Space.AddBody(Body)
				'We convert our Verts field into an array of cpVerts that is used to create a cpPolyShape
				'The cpVert array is half the length of our Verts array because it contains verts as opposed to separate 
				'numbers of coordinates
				Local halflength:=Verts.Length/2
				Local verts:=New cpVect[halflength]
				Local count:=0
				For Local it:=0 Until halflength
					'iterate through each Verts and create a cpVert for each one
					verts[it] = cpv(Verts[count],Verts[count+1])
					count+=2
				Next
				'Create the cpPolyShape with the array of cpVerts we just made
				Shape = cpPolyShapeNew(Body, halflength, verts.Data, cpTransformIdentity, 0.0)
				Shape.Friction = 1
				Shape.UserData = Varptr(Me)
				Game.Space.AddShape(Shape)
				cpShapeSetFilter(Shape, cpShapeFilterNew(ULong(0), MapTiles, MapTiles|Players|Rocks))
		End Select
	End Method
	
	'A method to make a copy of the tile. We will store the different types of tiles in the TileSet and then use them
	'to copy and create all the tiles that will draw the map
	Method Clone:Tile()
		Local copy:=New Tile
		copy.Verts = Verts
		copy.Width = Width
		copy.Height = Height
		copy.Offset = Offset
		copy.Image = Image
		
		Return copy
	End
End

'A node is a simple stuct to store the x, y and layer of the terrain node
Struct MapNode
	Field XY:Vec2i
	Field Layer:Int
	
	Method New(xy:Vec2i, layer:Int)
		XY = xy
		Layer = layer
	End
	
	'An example of polymorphism, the New method will be called according to the parameters that are used to call it.
	Method New(x:Int, y:Int, layer:Int)
		XY = New Vec2i(x, y)
		Layer = layer
	End
End

'The TileMap class manages the tile map, including adding and removing tiles
'This tilemap will be a little bit different to normal tilemaps where each grid coordinate contains a certain tile.
'Here each tile coordinate simply contains whether a tile exists there or not, then the tile will be drawn according to 
'whether adjacent tiles are filled. So i refer to grid coordinates as nodes
'
'One node is on the tile map so the corrosponding tiles are drawn (4 corner tiles)
'     /\
'     \/
'
'
'And here 4 nodes in a row are drawn. The tilemap will cheeck the adjacent node and drawn accordingly
'     /¯¯¯\
'     \___/
' 
Class TileMap

	'The number of rows in the tilemap
	Field Rows:Int
	'The number of columns in the tilemap
	Field Cols:Int
	'The size of a tile in pixels
	Field TileSize:Int = 32
	
	'The total width and height in pixels of the tilemap
	Field Width:Int
	Field Height:Int
	
	'A couple of lists to store tiles that need to be added and removed from the chipmunk space
	Field AddList:Stack<MapNode> = New Stack<MapNode>
	Field RemoveList:Stack<Tile> = New Stack<Tile>
	
	'Array to store the tile layers
	Field Layers:TileLayer[]
	
	'We'll need a reference to the Game object so we can access the chipmunk space and other things we might need there
	Field Game:SpaceCraft
	
	Method New(rows:Int = 32, cols:Int = 32, tilesize:Int = 32, layers:Int = 8)
		'Assign the object fields according to the variables passed in to the method
		Rows = rows
		Cols = cols
		TileSize = tilesize
		Width = tilesize * cols
		Height = tilesize * rows
		Layers = New TileLayer[layers]
		For Local c:Int = 0 To layers - 1
			Layers[c] = New TileLayer(Self)
			Layers[c].Index = c
		Next
	End
	
	'Assign a tile set to a layer
	Method AssignTileSet(layer:Int, tileset:TileSet)
		Layers[layer].TileImages = tileset
	End
	
	'We need to be able to translate the screen coordinates into tile map grid coordinates
	'For that we have the next 2 methods which will return the x and y gride coordinates respectively
	Method GetScreenNodeX:Int(x:Float, origin:Vec2f)
		'x is the screen coordinate we're passing in, we need to add the origin to that to convert it 
		'into world coordinates as the player may have scrolled to another area of the tile map
		Local wx:Float = x + origin.x
		'We want the tile map to center on the game origin, so 0,0 in world space is Width/2 and Height/2 in 
		'the tile. We also want the node at the center of the tile so TileSize is also halved. We then divide
		'the whole thing by tile size to get the grid coordinates.
		Return (wx + Width / 2 + TileSize / 2) / TileSize
	End Method

	Method GetScreenNodeY:Int(y:Float, origin:Vec2f)
		Local wy:Float = y + origin.y
		Return (wy + Height / 2 + TileSize / 2) / TileSize
	End Method
	
	'2 methods to convert world coordinates into grid coordinates. Exactly the same methods as the 
	'ScreenNode methods except we don't need to involve the origin.
	Method GetWorldNodeX:Int(wx:Float)
		Return (wx + Width / 2 + TileSize / 2) / TileSize
	End Method
	
	Method GetWorldNodeY:Int(wy:Float)
		Return (wy + Height / 2 + TileSize / 2) / TileSize
	End Method
	
	'Convert a node x coordinate, into a world coordinate. 
	'You can use this to find out where in the world a node is located
	Method NodeXToWorld:Float(x:Int)
		Return x * TileSize - Width / 2.0
	End Method
	
	'Convert a node y coordinate, into a world coordinate. 
	'You can use this to find out where in the world a node is located
	Method NodeYToWorld:Float(y:Int)
		Return y * TileSize - Height / 2.0
	End Method
	
	'Add a tile to the queue to get removed from the chipmunk space next update
	Method AddForRemovalFromSpace(tile:Tile)
		RemoveList.Add(tile)
	End
	
	'Add a node to the queue so that the tiles can be assigned and added the chipmunk space
	Method AddForAddingToSpace(node:MapNode)
		AddList.Add(node)
	End
	
	'Paint on the map with the layer you pass to it
	Method Paint(x:Int, y:Int, layer:Int)
		Layers[layer].Paint(x, y)
	End Method
	
	'Erase a tile from the map
	Method Erase(x:Int, y:Int, layer:Int)
		Layers[layer].Erase(x, y)
	End
	
	'Update the TileMap so that tiles can be added and removed from the map.
	Method Update()
		For Local node:=Eachin AddList
			Layers[node.Layer].AssignTiles(node.XY)
		Next
		For Local tile:=Eachin RemoveList
			If tile.Shape
				cpSpaceRemoveShape(Game.Space, tile.Shape)
				cpShapeFree(tile.Shape) 
				tile.Shape = Null
			End If
			If tile.Body 
				cpSpaceRemoveBody(Game.Space, tile.Body)
				cpBodyFree(tile.Body)
				tile.Body = Null
			End If
		Next
		RemoveList.Clear()
		AddList.Clear()
	End

End

'The TilerLayer class will manage each layer of the tile map. Each layer could be a different type of tile
Class TileLayer
	'Nodes is a 2d array that tells us if a piece of terrain exists at each coordinate
	Field Nodes:Int[,]
	'Tiles is a 2d array that contains all the Tiles which will be drawn according to the terrain nodes that exist on the map.
	Field Tiles:Tile[,]
	'The tilemap that this layer belongs to
	Field Map:TileMap
	'The tile set that the layer uses to draw with
	Field TileImages:TileSet
	'The index of the layer in the TileMap
	Field Index:Int
	
	Method New(map:TileMap)
		Map = map
		'Set the tiles array to the correct dimensions
		Tiles = New Tile[Map.Cols, Map.Rows]
		'Note that the nodes array is 1 less in size because the nodes are at the center of 4 tiles so there
		'isn't a node on the outer edge
		Nodes = New Int[Map.Cols - 1, Map.Rows - 1]
	End
	
	Method Paint(x:Int, y:Int)
		If x>=0 And x<Map.Cols-1 And y>=0 And y<Map.Rows-1
			If Not Nodes[x, y]
				'Add node to the TileMap AddList so that it will get added at the next update
				Map.AddForAddingToSpace(New MapNode(x, y, Index))
				'Set the node coordinate to 1 to mark it as "filled"
				Nodes[x, y] = 1
			End If 
		End
	End
	
	Method Erase(x:Int, y:Int)
		If x>=0 And x<Map.Cols-1 And y>=0 And y<Map.Rows-1
			If Nodes[x, y]
				Nodes[x, y] = 0
				Map.AddForRemovalFromSpace(Tiles[x, y])
			End If 
		End If 
	End
	
	'The AssignTiles method takes a node coordinate and assigns the correct tiles to that node. 
	Method AssignTiles(xy:Vec2i)
		
		Local xy2:=New Vec2i(xy.x + 1, xy.y + 1)

		'At this stage of the tutorial, we'll just assign a single block tile that we can add to the space
		'and test things are working ok up to this point
		
		'Get the tile from the tile set
		Tiles[xy.x, xy.y] = TileImages.GetTile(BlockTileA)
		'Set the XY coordinates of the tile to the correct place in the world
		Tiles[xy.x, xy.y].XY = New Vec2f(Map.NodeXToWorld(xy.x), Map.NodeYToWorld(xy.y))
		'Store the grid coordinates of the node this tile is assigned to
		Tiles[xy.x, xy.y].NodeLoc = xy
		'Set the game so we have an easy reference to it
		Tiles[xy.x, xy.y].Game = Map.Game
		'Add it to the queue so that the tile gets added to the chipmunk space next update
		Tiles[xy.x, xy.y].AddToSpace()
		
	End
End

'These consts make the code a bit easier to read by putting name to each tile type (top left, block etc.) rather that
'just using the number on it's own
Const TopLeftCornerTile:Int = 0
Const TopRightCornerTile:Int = 1
Const BottomLeftCornerTile:Int = 2
Const BottomRightCornerTile:Int = 3
Const SlopeDownLeftTile:Int = 4
Const SlopeDownRightTile:Int = 5
Const SlopeUpRightTile:Int = 6
Const SlopeUpLeftTile:Int = 7
Const LeftEdgeTile:Int = 8
Const BottomEdgeTile:Int = 9
Const RightEdgeTile:Int = 10
Const TopEdgeTile:Int = 11
Const DiagonalLeftTile:Int = 12
Const DiagonalRightTile:Int = 13
Const BlockTileA:Int = 14
Const BlockTileB:Int = 15






