' 
' Chunk system example (2d)
'
' Here I show you a way to handle chunks. Chunks are a name for
' parts of something. In a 3d game for instance a chunk could be
' a part of the map. Each chunk next to the other would form the 
' game map. If a chunk is out of range it can easily be removed
' and any new chunks can be added to the game.
'
' Here I use a stack list to store image chunks. (2d images)
' Using the cursor keys you can move tile by tile through the map.
'
' The example here is 2d but the system might teach you how you can
' apply it to the game of you choice.
'


#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


' The chunk width and height. 
Global chunkwidth:Int=32
Global chunkheight:Int=32

' Here we have a chunk class
' This one contains a image that is ment as the terrain 
'
Class chunk
	Field x:Int,y:Int
	Field seed:Int
	Field im:Image
	Field can:Canvas
	Field deleteme:Bool
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		Self.seed = x*y
		im = New Image(chunkwidth,chunkheight)
		can = New Canvas(im)
		createimage()
	End Method
	Method createimage()
		SeedRnd(seed)
		can.Clear(Color.White)
		For Local i:Int=0 Until 20
			Local x:Int=Rnd(im.Width)
			Local y:Int=Rnd(im.Height)
			can.Color = New Color(Rnd(1),Rnd(1),Rnd(1))
			can.DrawOval(x,y,Rnd(3,10),Rnd(3,10))
		Next
		can.Flush()
	End Method
End Class



Class MyWindow Extends Window
	
	' The chunks stack list contains the active visible chunks
	' 
	Field chunks:Stack<chunk>
	' This is the camera location 
	Field camerax:Int,cameray:Int
		

	Method New()
		' Create our new chunks stack list
		chunks = New Stack<chunk>
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' update the chunks
		updatechunks()
		' draw our chunks
		drawchunks(canvas)
		' Move using the cursor keys		
		If Keyboard.KeyReleased(Key.Left) Then camerax-=1
		If Keyboard.KeyReleased(Key.Right) Then camerax+=1
		If Keyboard.KeyReleased(Key.Up) Then cameray-=1
		If Keyboard.KeyReleased(Key.Down) Then cameray+=1
		
		canvas.DrawText(camerax+","+cameray+" Cursor keys to move",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	'
	' This method draws the active visible chunks on the screen
	Method drawchunks(canvas:Canvas)
		Local x:Int=Width/2-(camerax*chunkwidth)
		Local y:Int=Height/2-(cameray*chunkheight)
		For Local i:Int=0 Until chunks.Length
			Local x2:Int=chunks[i].x*chunkwidth
			Local y2:Int=chunks[i].y*chunkheight
			canvas.DrawImage(chunks[i].im,x2+x,y2+y)
		Next
	End Method
	'
	' This method updates the chunk list.
	' It removes any that are out of range and creates new
	' in range chunks.
	Method updatechunks()
		' If chunk is out of distance then flag for removal
		For Local i:Int=0 Until chunks.Length
			If distance(chunks[i].x,chunks[i].y,camerax,cameray) > 3
				chunks[i].deleteme = True
			End If
		Next
		' Remove chunks that are set for removal
		For Local i:Int=0 Until chunks.Length
			If chunks[i].deleteme = True Then 
				chunks[i].im.Discard()				
				chunks.Erase(i)
			End If
		Next
		' here we check around the camera and see if any of
		' these coordinates the chunks are not on the list and created
		' yet.
		For Local y:Int=cameray-3 To cameray+3
		For Local x:Int=camerax-3 To camerax+3
			' Do not add if exists
			Local add:Bool=True
			For Local i:Int=0 Until chunks.Length
				If chunks[i].x = x And chunks[i].y = y Then add=False
			Next
			' If new chunk then create it
			If add = True
				chunks.Push(New chunk(x,y))
			End If
		Next 
		Next
	End Method
	' Helper function
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x1-x2)+Abs(y1-y2)
	End Function
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
