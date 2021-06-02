'
' Create seamless grow tiles.
'
'
'


#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
'
' Here is our tile class.
'
Class tile
	' width and height of the tile
	Field tilewidth:Float,tileheight:Float
	' our image and canvas
	Field tileim:Image
	Field tilecan:Canvas
	' number of different colors on the tile
	Field numzones:Int' (0..x)
	' our base color
	Field col:Color
	' how dense(much) should the added zones be (0.1)
	Field density:Float
	' how much should these zones be spread out (0.1)
	Field spread:Float
	' Here we create our tile
	Method New(tilewidth:Float,tileheight:Float,numzones:Int,density:Float,spread:Float,col:Color)
		Self.tilewidth = tilewidth
		Self.tileheight = tileheight
		Self.numzones = numzones
		Self.col = col
		Self.density = density
		Self.spread = spread
		' Call the generatetiles method
		generatetiles()
	End Method
	Method generatetiles()
		' create our image and canvas
		tileim = New Image(tilewidth,tileheight)
		tilecan = New Canvas(tileim)
		'		
		' Create a array with the image width and height
		' where we create zones(numbers) on.
		' This with the spread and number of zones takes into account
		Local m:Int[,] = New Int[tilewidth,tileheight]
		For Local i:Int=0 Until (tilewidth*tileheight/50)*(spread*3)
			m[Rnd(0,tilewidth),Rnd(0,tileheight)] = Rnd(1,numzones+1)			
		Next
		'
		' Put on edges also
		'
		For Local i:Int=0 To 2
			m[Rnd(tilewidth),0] = Rnd(1,numzones+1)
			m[Rnd(tilewidth),tileheight-1] = Rnd(1,numzones+1)
			m[0,Rnd(tileheight)] = Rnd(1,numzones+1)
			m[tilewidth-1,Rnd(tileheight)] = Rnd(1,numzones+1)
		Next

		'
		'
		' Here we grow the zones. We exit if the desired density is reached
		Local maxdensity:Int=(tilewidth*tileheight)*(density/1.5)
		Local curdensity:Int=0
		While curdensity<maxdensity			
			' pick a random x and y spot in the array
			Local x:Int=Rnd(0,tilewidth)
			Local y:Int=Rnd(0,tileheight)
			' pick a position on or besides this spot
			Local nx:Int=x+Rnd(-2,2)
			Local ny:Int=y+Rnd(-2,2)
			' if this new spot is a zone
			If m[x,y] > 0
				'Make sure that we make it seamless
				' This is done by jumping to the other
				' side if the new position is out of the edge.
				If nx<0 Then nx=tilewidth-1
				If nx>=tilewidth Then nx=0
				If ny<0 Then ny=tileheight-1
				If ny>=tileheight Then ny=0
				' put the chosen spot on the new spot
				m[nx,ny] = m[x,y]
			End If
			' Count or current density
			' This is done by counting every value above 0
			curdensity = 0
			For Local a:Int=0 Until tileheight
			For Local b:Int=0 Until tilewidth
				If m[a,b] > 0 Then curdensity += 1
			Next
			Next
		Wend
		'
		' Here we should have the actual image data
		' finsihed. All we need to do is to turn it 
		' into a image.
		'
		' create the tile image
		' cold is used to get a shade based on the base color
		Local cold:Float=1.0/Float(numzones*3)		
		' Loop through every pixel of the array and image
		For Local y:Int=0 Until tileheight
		For Local x:Int=0 Until tilewidth			
			' set the color base on the array value
			tilecan.Color = col.Blend(Color.Black,Float(m[x,y])*cold)			
			' plot this color into the tile image
			tilecan.DrawPoint(x,y)
		Next
		Next
		' flush the image
		tilecan.Flush()
	End Method
	' Here we draw a map of desired widht and height using the tile
	' at the x and y position
	Method draw(canvas:Canvas,xpos:Int,ypos:Int,w:Int,h:Int)
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			canvas.DrawImage(tileim,xpos+(x*tilewidth),ypos+(y*tileheight))		
		Next
		Next
	End Method	
End Class


Class MyWindow Extends Window
	'
	' Create a array of world with dimensions 6 wide and 5 heigh
	'	
	Field maps:tile[,] = New tile[6,5]	
	Method New()
		' create the initial set of tiles
		makethetiles()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		' If we press space then create new set of tiles
		If Keyboard.KeyReleased(Key.Space)
			makethetiles()
		End If
		' 
		' Draw our tiles to the screen
		For Local y:Int=0 Until 5
		For Local x:Int=0 Until 6
			'Method draw(canvas:Canvas,xpos:Int,ypos:Int,w:Int,h:Int)
			maps[x,y].draw(canvas,x*96,y*96,3,3)
		Next
		Next
		canvas.Color = Color.White
		canvas.DrawText("Press Space to generate new tiles",0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	'
	' Here we create the tiles in our world array
	Method makethetiles()			
		For Local y:Int=0 Until 5
		For Local x:Int=0 Until 6			
			'Method New(tilewidth:Float,tileheight:Float,numzones:Int,density:Float,spread:Float,col:Color)
			maps[x,y] = New tile(32,32,Rnd(1,20),Rnd(.2,1),Rnd(.2,1),New Color(Rnd(.3,.7),Rnd(.3,.7),Rnd(.3,.7)))
		Next
		Next	
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
