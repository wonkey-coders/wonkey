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
					Case "box"
						Tiles[index].Offset = New Vec2f(file["handlex"].ToNumber(),file["handley"].ToNumber())
						'Grab the width and height from the file
						Tiles[index].Width = file["width"].ToNumber()
						Tiles[index].Height = file["height"].ToNumber()
				End
				'Load and store the image using the directory we got earlier
				Tiles[index].Image = Image.Load(directory + file["file"].ToString())
				Print directory + file["file"].ToString()
				index+=1
			Next
		End If
	End
	
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
	
	'And offset that we can use to make sure that the Chipmunk collision box aligns with the tile
	Field Offset:Vec2i
	
	'Default constuctor
	Method New()
	
	End
	
	'A method to make a copy of the tile. We will store the different types of tiles in the TileSet and then use them
	'to copy and create all the tiles that will draw the map
	Method Clone:Tile()
		Local copy:=New Tile
		copy.Verts = Verts
		copy.Width = Width
		copy.Height = Height
		copy.Handle = Handle
		copy.Image = Image
		
		Return copy
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
	
	Method New(rows:Int = 32, cols:Int = 32, tilesize:Int = 32)
		'Assign the object fields according to the variables passed in to the method
		Rows = rows
		Cols = cols
		TileSize = tilesize
		Width = tilesize * cols
		Height = tilesize * rows
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

End