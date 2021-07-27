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