'
' press 'c' to copy currently selected sprite data as a [][] array into the 
' clipboard buffer.
'

' map view. (XXX....)
' zoom in/out
' hand icon for moving (map/sprite)
' triangle tool (filled/outline)
' poly tool (filled/outlines)
' mirror/flip tool check if selection is active and flip/mirror in that

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class spriteeditor
	' This is a class that holds x and y variables.
	' used for : floodfill
	Class pathnode
		Field x:Int,y:Int
		Method New(x:Int,y:Int)
			Self.x = x
			Self.y = y
		End Method
	End Class

	' start setup
	Field startsetuppalettemode:Int=0 '0=c64 1=db32
	Field startsetupdone:Bool
	Field startsetupx:Int
	Field startsetupy:Int
	Field startsetupwidth:Int
	Field startsetupheight:Int
	Field startsetupim:Image[]
	Field startsetupcan:Canvas[]
	Field startsetupselected:Int=0
	Field startsetup8x8id:Int=0
	Field startsetup16x16id:Int=1
	Field startsetup32x32id:Int=2
	Field startsetupc64id:Int=3
	Field startsetupdb32id:Int=4
	Field numstartsetup:Int=5
	'
	'tool view
	Field toolx:Int,tooly:Int
	Field toolwidth:Int,toolheight:Int
	Field toolim:Image[]
	Field toolcan:Canvas[]
	Field toolgridtoggle:Bool=True
	Field toolselected:Int=0
	Field toolpencilid:Int=0
	Field tooleraserid:Int=1
	Field toolfillid:Int=2
	Field toollineid:Int=3
	Field toolselectionid:Int=4
	Field toolcopyid:Int=5
	Field toolpasteid:Int=6
	Field toolcutid:Int=7
	Field toolflipverticalid:Int=8
	Field toolfliphorizontalid:Int=9
	Field toolcolorpickerid:Int=10
	Field toolgridid:Int=11
	Field toolfilledrectid:Int=12
	Field tooloutlinerectid:Int=13
	Field toolfilledcircleid:Int=14
	Field tooloutlinecircleid:Int=15
	Field numtools:Int=16
	Field delay:Int
	Field delaydefault:Int=20
	
	'
	' sprite library
	Field spritelibx:Int,spriteliby:Int
	Field spritelibwidth:Int,spritelibheight:Int
	Field numspritelib:Int
	Field spritelibim:Image[]
	Field spritelibcan:Canvas[]
	Field spritelibmap:Int[,,]
	Field spritelibselected:Int=0
	Field spritelibscale:Float
	
	'
	'preview
	Field previewim:Image
	Field previewcan:Canvas
	Field previewx:Int,previewy:Int
	Field previewwidth:Int,previewheight:Int
	Field previewcellwidth:Int,previewcellheight:Int

	' tile map view
	Field tilemapx:Int,tilemapy:Int
	Field tilemapwidth:Int,tilemapheight:Int
	Field tilemaptileshorizontal:Int,tilemaptilesvertical:Int
	Field tilemaptilesscreenhorizontal:Int
	Field tilemaptilesscreenvertical:Int
	Field tilemap:Int[,]
	'
	'sprite view
	Field map:Int[,]
	Field canvasx:Int,canvasy:Int 'canvas x and y position on the scrern
	Field canvaswidth:Float,canvasheight:Float 'width and height of our canvas
	Field gridwidth:Float,gridheight:Float	 ' grids width and height
	Field spritewidth:Int,spriteheight:Int ' our main sprite width and height
	' line tool fields
	Field linepressed:Bool=False
	Field lineactive:Bool=False
	Field linestartx:Int,linestarty:Int
	Field lineendx:Int,lineendy:Int	
	' Selection fields
	Field selectionpressed:Bool=False 
	Field selectionactive:Bool=False
	Field selectionstartx:Int,selectionstarty:Int
	Field selectionendx:Int,selectionendy:Int
	Field selectionbuffer:Int[,] 'our copy paste buffer
	Field selectionbufferstartx:Int,selectionbufferstarty:Int
	Field selectionbufferendx:Int,selectionbufferendy:Int
	Field selectionnegativeswitchx:Bool=False ' switch if negative selection
	Field selectionnegativeswitchy:Bool=False
	' filled/outlined rectsangles and circles fields
	Field bcselectionpressed:Bool=False 
	Field bcselectionactive:Bool=False
	Field bcselectionstartx:Int,bcselectionstarty:Int
	Field bcselectionendx:Int,bcselectionendy:Int
	Field bcselectionbuffer:Int[,] 'our copy paste buffer
	Field bcselectionbufferstartx:Int,bcselectionbufferstarty:Int
	Field bcselectionbufferendx:Int,bcselectionbufferendy:Int
	Field bcselectionnegativeswitchx:Bool=False ' switch if negative selection
	Field bcselectionnegativeswitchy:Bool=False
	
	'
	' palette	
	Field c64color:Color[] ' our colors
	Field db32color:Color[] ' our colors	
	Field paletteselected:Int ' our selected color from palette
	Field paletteeraser:Int
	Field palettex:Int,palettey:Int 'screen x and y
	Field palettewidth:Float,paletteheight:Float ' our palette screen w and h
	Field palettecellwidth:Float,palettecellheight:Float 'cell width and height of color
	Field numpalette:Int 'number of colors
	
	'
	' Top Bar
	Field topbarx:Int,topbary:Int
	Field topbarwidth:Int,topbarheight:Int
	Field topbarcolor:Color
	Field topbarim:Image[]
	Field topbarcan:Canvas[]
	Field topbarspriteeditid:Int=0	
	Field topbarmapeditid:Int=1
	Field numtopbaricons:Int=2
	Field topbarcurrentid:Int=0

	'
	' Middle bar
	Field middlebarx:Int,middlebary:Int
	Field middlebarwidth:Int,middlebarheight:Int
	Field middlebarcolor:Color
	Field middlebarim:Image[]
	Field middlebarcan:Canvas[]
	Field middlebar0id:Int=0
	Field middlebar1id:Int=1
	Field middlebar2id:Int=2
	Field middlebar3id:Int=3
	Field nummiddlebaricons:Int=4
	Field middlebarcurrentid:Int=0
	'
	' Bottom Bar
	Field bottombarx:Int,bottombary:Int
	Field bottombarwidth:Int,bottombarheight:Int
	Field bottombarcolor:Color
	
	Method New()
		'palette setup
		inic64colors()
		inidb32colors()
		paletteeraser = 0
		palettex = 640-150
		palettey = 32
		palettewidth = 32*4
		paletteheight = 32*4
		numpalette = 16
		palettecellwidth = 32
		palettecellheight = 32		


		'start setup setup
		' be sure to start the editor with the selection
		startsetupdone=False 
		startsetupx = 320-80
		startsetupy = 150
		startsetupwidth = 150
		startsetupheight = 200-35
		startsetupim = New Image[numstartsetup]
		startsetupcan = New Canvas[numstartsetup]
		For Local i:Int=0 Until numstartsetup
			startsetupim[i] = New Image(32,32)
			startsetupcan[i] = New Canvas(startsetupim[i])
		Next
		startsetupsetup()



		'sprite canvas setup
		canvasx = 32
		canvasy = 28
		spritewidth = 16
		spriteheight = 16
		map = New Int[spritewidth,spriteheight]	
		selectionbuffer = New Int[spritewidth,spriteheight]	
		
		canvaswidth=256
		canvasheight=256
		gridwidth = canvaswidth/spritewidth		
		gridheight = canvasheight/spriteheight

		'Bottom bar (global)
		bottombarx = 0
		bottombary = 480-24
		bottombarwidth = 640
		bottombarheight = 24	
		bottombarcolor = Color.Puce

		'
		' Middle bar
		middlebarx = 0
		middlebary = canvasheight+32
		middlebarwidth = 640
		middlebarheight = 32
		middlebarcolor = Color.LightGrey
		nummiddlebaricons = 4
		middlebarim = New Image[nummiddlebaricons]
		middlebarcan = New Canvas[nummiddlebaricons]
		For Local i:Int=0 Until nummiddlebaricons
			middlebarim[i] = New Image(32,32)
			middlebarcan[i] = New Canvas(middlebarim[i])
		Next
		setupmiddlebar()
		
		'Top bar (global)
		
		topbarx = 0
		topbary = 0
		topbarwidth = 640
		topbarheight = 24
		topbarcolor = Color.Puce
		topbarim = New Image[3]
		topbarcan = New Canvas[3]
		For Local i:Int=0 Until 2
			topbarim[i] = New Image(32,32)
			topbarcan[i] = New Canvas(topbarim[i])
		Next
		setuptopbar()
		

		'	
		'spritelib setup
		spritelibx = 0
		spriteliby = canvasheight+32+32
		spritelibwidth = 640
		spritelibheight = 128
		numspritelib = 80*4
		spritelibselected = 0
		spritelibscale = 2
		spritelibim = New Image[numspritelib]
		spritelibcan = New Canvas[numspritelib]		
		For Local i:Int=0 Until numspritelib
			spritelibim[i] = New Image(spritewidth*spritelibscale,spriteheight*spritelibscale)
			spritelibcan[i] = New Canvas(spritelibim[i])
			spritelibcan[i].Clear(Color.Black)
			spritelibcan[i].Flush()
		Next	
		spritelibmap = New Int[numspritelib,spritewidth,spriteheight]	

		'
		'tilemap setup
		tilemapx = 0
		tilemapy = 32
		tilemaptileshorizontal = 100
		tilemaptilesvertical = 100
		tilemapwidth = 640
		tilemapheight= 256
		tilemaptilesscreenhorizontal = tilemapwidth/(spritewidth*spritelibscale)
		tilemaptilesscreenvertical = tilemapheight/(spriteheight*spritelibscale)
		tilemap = New Int[tilemaptileshorizontal,tilemaptilesvertical]

		' tool view
		toolx = 340
		tooly = 186-32
		toolwidth = 32*4
		toolheight = 32*4
		'numtools = 12
		toolim = New Image[numtools]
		toolcan = New Canvas[numtools]
		For Local i:Int=0 Until numtools
			toolim[i] = New Image(32,32)
			toolcan[i] = New Canvas(toolim[i])
			toolcan[i].Clear(Color.Black)
			toolcan[i].Flush()
		Next

		setuptoolview()
		

		'
		' previewview setup
		previewx = 640-100
		previewy = 200
		previewcellwidth = 5
		previewcellheight = 5
		previewwidth = spritewidth*previewcellwidth
		previewheight = spriteheight*previewcellheight
		previewim = New Image(previewwidth,previewheight)
		previewcan = New Canvas(previewim)
		updatepreview()
		
	End Method

	Method startsetupsetup()
		' the 8x8 selection button
		Local eightxeight := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,1,1,1,12,12,12,12,12,1,1,1,12,12,12),
		New Int[](12,12,1,12,1,12,1,12,1,12,1,12,1,12,12,12),
		New Int[](12,12,1,1,1,12,12,1,12,12,1,1,1,12,12,12),
		New Int[](12,12,1,12,1,12,1,12,1,12,1,12,1,12,12,12),
		New Int[](12,12,1,1,1,12,12,12,12,12,1,1,1,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12))		
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			startsetupcan[startsetup8x8id].Color = c64color[eightxeight[y][x]]
			If eightxeight[y][x] = 0 Then startsetupcan[startsetup8x8id].Alpha=0 Else startsetupcan[startsetup8x8id].Alpha=1
			startsetupcan[startsetup8x8id].DrawRect(x*2,y*2,2,2)
		Next
		Next		
		startsetupcan[startsetup8x8id].Flush()
		
		'the 16x16 selection button
		Local sixteenxsixteen:= New Int[][] (
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](1,12,1,1,1,12,12,12,12,12,1,12,1,1,1,12),
		New Int[](1,12,1,12,12,12,1,12,1,12,1,12,1,12,12,12),
		New Int[](1,12,1,1,1,12,12,1,12,12,1,12,1,1,1,12),
		New Int[](1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12),
		New Int[](1,12,1,1,1,12,12,12,12,12,1,12,1,1,1,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			startsetupcan[startsetup16x16id].Color = c64color[sixteenxsixteen[y][x]]
			If sixteenxsixteen[y][x] = 0 Then startsetupcan[startsetup16x16id].Alpha=0 Else startsetupcan[startsetup16x16id].Alpha=1
			startsetupcan[startsetup16x16id].DrawRect(x*2,y*2,2,2)
		Next
		Next		
		startsetupcan[startsetup16x16id].Flush()

		' the 32x32 selection button
		Local thirtytwoxthirtytwo := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](1,1,12,1,1,12,12,12,12,12,1,1,12,1,1,12),
		New Int[](12,1,12,12,1,12,1,12,1,12,12,1,12,12,1,12),
		New Int[](1,1,12,1,1,12,12,1,12,12,1,1,12,1,1,12),
		New Int[](12,1,12,1,12,12,1,12,1,12,12,1,12,1,12,12),
		New Int[](1,1,12,1,1,12,12,12,12,12,1,1,12,1,1,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			startsetupcan[startsetup32x32id].Color = c64color[thirtytwoxthirtytwo[y][x]]
			If thirtytwoxthirtytwo[y][x] = 0 Then startsetupcan[startsetup32x32id].Alpha=0 Else startsetupcan[startsetup32x32id].Alpha=1
			startsetupcan[startsetup32x32id].DrawRect(x*2,y*2,2,2)
		Next
		Next		
		startsetupcan[startsetup32x32id].Flush()

		' the c64 palette selection button
		Local c641616 := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,1,1,12,12,12,1,1,12,12,1,12,12,12,12),
		New Int[](12,1,12,12,12,12,1,12,12,12,12,1,12,12,12,12),
		New Int[](12,1,12,12,12,12,1,12,12,12,12,1,12,12,1,12),
		New Int[](12,1,12,12,12,12,1,1,1,12,12,1,1,1,1,12),
		New Int[](12,1,12,12,12,12,1,12,12,1,12,12,12,12,1,12),
		New Int[](12,1,12,12,12,12,1,12,12,1,12,12,12,12,1,12),
		New Int[](12,12,1,1,12,12,12,1,1,12,12,12,12,12,1,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			startsetupcan[startsetupc64id].Color = c64color[c641616[y][x]]
			If c641616[y][x] = 0 Then startsetupcan[startsetupc64id].Alpha=0 Else startsetupcan[startsetupc64id].Alpha=1
			startsetupcan[startsetupc64id].DrawRect(x*2,y*2,2,2)
		Next
		Next		
		startsetupcan[startsetupc64id].Flush()

		' the db32 palette selection button
		Local db321616 := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,1,12,1,12,12,12,1,1,12,12,1,1,1,12),
		New Int[](12,12,1,12,1,12,12,12,12,12,1,12,12,12,1,12),
		New Int[](12,12,1,12,1,12,12,12,12,12,1,12,12,12,1,12),
		New Int[](12,1,1,12,1,1,12,12,1,1,12,12,1,1,1,12),
		New Int[](1,12,1,12,1,12,1,12,12,12,1,12,1,12,12,12),
		New Int[](1,12,1,12,1,12,1,12,12,12,1,12,1,12,12,12),
		New Int[](1,1,1,12,1,1,1,12,1,1,12,12,1,1,1,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			startsetupcan[startsetupdb32id].Color = c64color[db321616[y][x]]
			If db321616[y][x] = 0 Then startsetupcan[startsetupdb32id].Alpha=0 Else startsetupcan[startsetupdb32id].Alpha=1
			startsetupcan[startsetupdb32id].DrawRect(x*2,y*2,2,2)
		Next
		Next		
		startsetupcan[startsetupdb32id].Flush()


	End Method

	Method startsetupview(canvas:Canvas)
		canvas.Color = Color.Black
		canvas.DrawRect(startsetupx-1,startsetupy-1,startsetupwidth+2,startsetupheight+2)

		canvas.Color = c64color[12]
		canvas.DrawRect(startsetupx,startsetupy,startsetupwidth,startsetupheight)

		Local selected:Bool=False		
		For Local i:Int=0 Until 3
			canvas.Color = Color.Grey.Blend(Color.Black,.5)
			canvas.DrawRect(startsetupx+8+20,startsetupy+8+i*48,32,32)
			canvas.Color = Color.White
			canvas.DrawImage(startsetupim[i],startsetupx+9+20,startsetupy+9+i*48,0,.9,.9)
			' draw the palette buttons
			canvas.Color = Color.Black
			canvas.DrawRect(startsetupx+8+50,startsetupy+8+i*48,32,32)
			canvas.Color = Color.White
			canvas.DrawImage(startsetupim[3],startsetupx+9+50,startsetupy+9+i*48,0,.9,.9)
			canvas.Color = Color.Black
			canvas.DrawRect(startsetupx+8+80,startsetupy+8+i*48,32,32)
			canvas.Color = Color.White
			canvas.DrawImage(startsetupim[4],startsetupx+9+80,startsetupy+9+i*48,0,.9,.9)
						
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,startsetupx+9+50,startsetupy+9+i*48,32,32)
					startsetupselected = i
					startsetuppalettemode = 0
					selected = true
				End If
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,startsetupx+9+80,startsetupy+9+i*48,32,32)
					startsetupselected = i
					startsetuppalettemode = 1
					selected = true
				End If				
			End If
		Next

		If selected = True
			If startsetuppalettemode = 1 ' if the db32 palette was selected
				paletteeraser = 0
				palettex = 640-150
				palettey = 32
				palettewidth = 32*4
				paletteheight = 32*4
				numpalette = 32
				palettecellwidth = 32*4/4
				palettecellheight = 32*4/8
			End If
			
			Select startsetupselected
				Case 0
					spritelibscale = 4
					spritewidth = 8
					spriteheight = 8
					map = New Int[spritewidth,spriteheight]	
					selectionbuffer = New Int[spritewidth,spriteheight]	
					gridwidth = canvaswidth/spritewidth		
					gridheight = canvasheight/spriteheight	
					spritelibmap = New Int[numspritelib,spritewidth,spriteheight]					
				Case 1
					spritelibscale = 2
					spritewidth = 16
					spriteheight = 16
					map = New Int[spritewidth,spriteheight]	
					selectionbuffer = New Int[spritewidth,spriteheight]	
					gridwidth = canvaswidth/spritewidth		
					gridheight = canvasheight/spriteheight					
					spritelibmap = New Int[numspritelib,spritewidth,spriteheight]	
				Case 2
					spritelibscale = 1
					spritewidth = 32
					spriteheight = 32
					map = New Int[spritewidth,spriteheight]	
					selectionbuffer = New Int[spritewidth,spriteheight]	
					gridwidth = canvaswidth/spritewidth		
					gridheight = canvasheight/spriteheight
					spritelibmap = New Int[numspritelib,spritewidth,spriteheight]											
			End Select
			startsetupdone = True
		End If
	End Method

	Method toolview(canvas:Canvas)
		canvas.Color=Color.Black
		canvas.DrawRect(toolx,tooly,toolwidth,toolheight)
		canvas.Color=Color.White
		If delay>0 Then delay-=1
		Local num:Int=0
		For Local y:Int=tooly Until tooly+toolheight Step 32
		For Local x:Int=toolx Until toolx+toolwidth Step 32
			Local pointx:Int=x
			Local pointy:Int=y
			If toolselected = num 
				canvas.Color = Color.Yellow
				canvas.DrawRect(pointx,pointy,32,32)
				canvas.Color = Color.White
				canvas.Scissor = New Recti(pointx+2,pointy+2,pointx+30,pointy+30)
				canvas.DrawImage(toolim[num],pointx,pointy)
				canvas.Scissor = New Recti(0,0,640,480)
			Else
				canvas.DrawImage(toolim[num],pointx,pointy)
			End If
			'
			' Interaction with the tool area
			'
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,32,32)
					toolselected = num


					' Pastethe selected area
					If toolselected = toolpasteid
						If selectionstartx = selectionendx And selectionstarty = selectionendy Then 
						Else
							For Local y1:Int=selectionbufferstarty To selectionbufferendy
							For Local x1:Int=selectionbufferstartx To selectionbufferendx
								Local destx:Int=selectionstartx+x1-selectionbufferstartx
								Local desty:Int=selectionstarty+y1-selectionbufferstarty
								If x1<0 Or y1<0 Or x1>=map.GetSize(0) Or y1>=map.GetSize(1) Then Continue
								If destx<0 Or desty<0 Or destx>=map.GetSize(0) Or desty>=map.GetSize(1) Then Continue
								If destx>selectionendx Or desty>selectionendy Then Continue
								map[destx,desty] = selectionbuffer[x1,y1]
							Next
							Next
							toolselected = toolpencilid
						End If						
					End If
				
					
					' Copy the selected area
					If toolselected = toolcopyid
						If selectionstartx = selectionendx And selectionstarty = selectionendy Then 
							
						Else
							selectionbufferstartx = selectionstartx
							selectionbufferstarty = selectionstarty
							selectionbufferendx = selectionendx
							selectionbufferendy = selectionendy
							For Local y1:Int=selectionstarty To selectionendy
							For Local x1:Int=selectionstartx To selectionendx
								selectionbuffer[x1,y1] = map[x1,y1]
							Next
							Next
							toolselected = toolpencilid
						End If						
					End If
					' Cut the selected area		
					If toolselected = toolcutid
						If selectionstartx = selectionendx And selectionstarty = selectionendy Then 
						
						Else
							For Local y1:Int=selectionstarty To selectionendy
							For Local x1:Int=selectionstartx To selectionendx
								map[x1,y1] = paletteeraser
							Next
							Next
						toolselected = toolpencilid
						End If
					End If
					
					' Mirror vertically
					If toolselected = toolflipverticalid And delay <= 0
						Local tempmap:Int[,] = New Int[map.GetSize(0),map.GetSize(1)]
						For Local y1:Int=0 Until map.GetSize(1)
						For Local x1:Int=0 Until map.GetSize(0)
							tempmap[x1,y1] = map[x1,y1]
						Next
						Next
						For Local y1:Int=0 Until map.GetSize(1)
						For Local x1:Int=0 Until map.GetSize(0)							
							map[x1,y1] = tempmap[x1,map.GetSize(1)-1-y1]
						Next
						Next
						delay = delaydefault
						toolselected = toolpencilid
					End If
					' Mirror Horizontal
					If toolselected = toolfliphorizontalid And delay <= 0
						Local tempmap:Int[,] = New Int[map.GetSize(0),map.GetSize(1)]
						For Local y1:Int=0 Until map.GetSize(1)
						For Local x1:Int=0 Until map.GetSize(0)
							tempmap[x1,y1] = map[x1,y1]
						Next
						Next
						For Local y1:Int=0 Until map.GetSize(1)
						For Local x1:Int=0 Until map.GetSize(0)							
							map[x1,y1] = tempmap[map.GetSize(0)-1-x1,y1]
						Next
						Next
						delay = delaydefault
						toolselected = toolpencilid
					End If
					' Grid toggle
					If toolselected = toolgridid And delay <= 0
						If toolgridtoggle = True Then toolgridtoggle = False Else toolgridtoggle = True
						delay = delaydefault
						toolselected = toolpencilid
					End If
				End If								
			End If				
			num+=1
			If num>=numtools Then Exit
			
		Next
		Next
	End Method

	Method setupmiddlebar()
		Local zero := New Int[][] (
		New Int[](0,12,12,12,12,12,12,0),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,1,12,1,12,12),
		New Int[](12,12,12,1,12,1,12,12),
		New Int[](12,12,12,1,12,1,12,12),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			middlebarcan[middlebar0id].Color = c64color[zero[y][x]]
			If zero[y][x] = 0 Then middlebarcan[middlebar0id].Alpha=0 Else middlebarcan[middlebar0id].Alpha=1
			middlebarcan[middlebar0id].DrawRect(x*4,y*4,4,4)
		Next
		Next		
		middlebarcan[middlebar0id].Flush()

		Local one := New Int[][] (
		New Int[](0,12,12,12,12,12,12,0),
		New Int[](12,12,12,1,1,12,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			middlebarcan[middlebar1id].Color = c64color[one[y][x]]
			If one[y][x] = 0 Then middlebarcan[middlebar1id].Alpha=0 Else middlebarcan[middlebar1id].Alpha=1
			middlebarcan[middlebar1id].DrawRect(x*4,y*4,4,4)
		Next
		Next		
		middlebarcan[middlebar1id].Flush()
		
		Local two := New Int[][] (
		New Int[](0,12,12,12,12,12,12,0),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,12,1,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,1,12,12,12,12),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			middlebarcan[middlebar2id].Color = c64color[two[y][x]]
			If two[y][x] = 0 Then middlebarcan[middlebar2id].Alpha=0 Else middlebarcan[middlebar2id].Alpha=1
			middlebarcan[middlebar2id].DrawRect(x*4,y*4,4,4)
		Next
		Next		
		middlebarcan[middlebar2id].Flush()

		Local three := New Int[][] (
		New Int[](0,12,12,12,12,12,12,0),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,12,1,12,12),
		New Int[](12,12,12,12,1,1,12,12),
		New Int[](12,12,12,12,12,1,12,12),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,12,12,12,12,12,12))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			middlebarcan[middlebar3id].Color = c64color[three[y][x]]
			If three[y][x] = 0 Then middlebarcan[middlebar3id].Alpha=0 Else middlebarcan[middlebar3id].Alpha=1
			middlebarcan[middlebar3id].DrawRect(x*4,y*4,4,4)
		Next
		Next		
		middlebarcan[middlebar3id].Flush()
	

	End Method

	Method setuptopbar()
		Local mapedit := New Int[][] (
		New Int[](1,1,1,0,0,1,1,0),
		New Int[](1,1,1,0,0,1,1,0),
		New Int[](1,1,1,0,0,0,0,0),
		New Int[](0,0,0,1,1,1,1,1),
		New Int[](1,1,0,1,1,1,1,1),
		New Int[](1,1,0,1,1,1,1,1),
		New Int[](0,0,0,1,1,1,1,1),
		New Int[](0,0,0,1,1,1,1,1))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			topbarcan[topbarmapeditid].Color = c64color[mapedit[y][x]]
			If mapedit[y][x] = 0 Then topbarcan[topbarmapeditid].Alpha=0 Else topbarcan[topbarmapeditid].Alpha=1
			topbarcan[topbarmapeditid].DrawRect(x*4,y*4,4,4)
		Next
		Next		
		topbarcan[topbarmapeditid].Flush()

		Local spriteedit := New Int[][] (
		New Int[](1,0,0,0,0,0,0,1),
		New Int[](0,1,0,0,0,0,1,0),
		New Int[](0,1,0,1,1,0,1,0),
		New Int[](0,0,1,1,1,1,0,0),
		New Int[](0,1,1,0,0,1,1,0),
		New Int[](0,1,1,1,1,1,1,0),
		New Int[](0,0,1,1,1,1,0,0),
		New Int[](0,1,0,1,1,0,1,0))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			topbarcan[topbarspriteeditid].Color = c64color[spriteedit[y][x]]
			If spriteedit[y][x] = 0 Then topbarcan[topbarspriteeditid].Alpha=0 Else topbarcan[topbarspriteeditid].Alpha=1
			topbarcan[topbarspriteeditid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		topbarcan[topbarspriteeditid].Flush()
		
	End Method

	Method setuptoolview()
		'read icons
		Local pencil := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,1,1,1,12,12,12),
		New Int[](12,1,1,1,12,1,12,12),
		New Int[](12,1,1,12,1,1,1,12),
		New Int[](12,1,12,1,1,1,1,1),
		New Int[](12,12,1,1,1,1,1,1),
		New Int[](12,12,12,1,1,1,1,1),
		New Int[](12,12,12,12,1,1,1,1))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolpencilid].Color = c64color[pencil[y][x]]
			toolcan[toolpencilid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolpencilid].Flush()
		
		Local eraser := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,12,1,12,12,12,12),
		New Int[](12,12,1,1,1,12,12,12),
		New Int[](12,1,1,12,1,1,12,12),
		New Int[](12,12,1,1,12,1,1,12),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[tooleraserid].Color = c64color[eraser[y][x]]
			toolcan[tooleraserid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[tooleraserid].Flush()

		Local fill := New Int[][] (
		New Int[](12,12,12,1,12,12,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,12,12,1,12,12),
		New Int[](1,1,1,1,1,1,1,12),
		New Int[](12,1,1,1,1,1,1,1),
		New Int[](1,12,1,1,1,1,1,12),
		New Int[](12,12,12,1,1,1,12,12),
		New Int[](1,12,12,12,1,12,12,12))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolfillid].Color = c64color[fill[y][x]]
			toolcan[toolfillid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolfillid].Flush()

		Local line := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,12,12,12,12,12,12),
		New Int[](12,12,1,12,12,12,12,12),
		New Int[](12,12,12,1,12,12,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,12,12,12,12,1,12,12),
		New Int[](12,12,12,12,12,12,1,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toollineid].Color = c64color[line[y][x]]
			toolcan[toollineid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toollineid].Flush()

		Local selection := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,12,1,1,12,1,12),
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,12,1,1,12,1,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolselectionid].Color = c64color[selection[y][x]]
			toolcan[toolselectionid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolselectionid].Flush()

		Local copy := New Int[][] (
		New Int[](1,12,12,12,12,12,12,12),
		New Int[](1,1,12,1,1,12,1,12),
		New Int[](1,1,1,12,12,12,12,12),
		New Int[](1,1,1,1,12,12,1,12),
		New Int[](1,1,1,12,12,12,1,12),
		New Int[](1,1,12,12,12,12,12,12),
		New Int[](1,12,12,1,1,12,1,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolcopyid].Color = c64color[copy[y][x]]
			toolcan[toolcopyid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolcopyid].Flush()

		Local paste := New Int[][] (
		New Int[](12,12,12,1,12,12,12,12),
		New Int[](12,12,1,1,1,12,1,12),
		New Int[](12,1,1,1,12,12,12,12),
		New Int[](1,1,1,1,12,12,1,12),
		New Int[](12,1,1,1,12,12,1,12),
		New Int[](12,12,1,1,12,12,12,12),
		New Int[](12,12,12,1,1,12,1,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolpasteid].Color = c64color[paste[y][x]]
			toolcan[toolpasteid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolpasteid].Flush()

		Local cut := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,12,1,12,12,12,12),
		New Int[](12,12,12,12,1,12,12,12),
		New Int[](12,1,12,12,1,12,12,12),
		New Int[](12,12,1,1,12,1,1,12),
		New Int[](12,12,12,12,1,12,1,1),
		New Int[](12,12,12,12,1,1,12,12),
		New Int[](12,12,12,12,12,1,1,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolcutid].Color = c64color[cut[y][x]]
			toolcan[toolcutid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolcutid].Flush()


		Local flipvertical := New Int[][] (
		New Int[](12,12,12,1,1,12,12,12),
		New Int[](12,12,1,1,1,1,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,12,1,1,12,12,12),
		New Int[](12,12,12,1,1,12,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,1,1,1,1,12,12),
		New Int[](12,12,12,1,1,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolflipverticalid].Color = c64color[flipvertical[y][x]]
			toolcan[toolflipverticalid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolflipverticalid].Flush()
		
		Local fliphorizontal := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,1,1,12,12,1,1,12),
		New Int[](1,1,1,1,1,1,1,1),
		New Int[](1,1,1,1,1,1,1,1),
		New Int[](12,1,1,12,12,1,1,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,12,12,12,12,12,12,12))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolfliphorizontalid].Color = c64color[fliphorizontal[y][x]]
			toolcan[toolfliphorizontalid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolfliphorizontalid].Flush()

		Local colorpicker := New Int[][] (
		New Int[](12,1,1,12,12,12,12,12),
		New Int[](1,1,12,12,1,12,12,12),
		New Int[](1,12,12,1,12,12,12,12),
		New Int[](12,12,1,12,1,12,12,12),
		New Int[](12,1,12,1,12,1,12,12),
		New Int[](12,12,12,12,1,12,1,12),
		New Int[](12,12,12,12,12,1,1,12),
		New Int[](12,12,12,12,12,12,12,1))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolcolorpickerid].Color = c64color[colorpicker[y][x]]
			toolcan[toolcolorpickerid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolcolorpickerid].Flush()

		Local grid := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,12,12,12,12,12,12,12))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolgridid].Color = c64color[grid[y][x]]
			toolcan[toolgridid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolgridid].Flush()
		
				
		Local filledrect := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,12,12,12,12,12,12))		
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[toolfilledrectid].Color = c64color[filledrect[y][x]]
			toolcan[toolfilledrectid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolfilledrectid].Flush()

		Local outlinerect := New Int[][] (
		New Int[](12,12,12,12,12,12,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,12,12,12,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			toolcan[tooloutlinerectid].Color = c64color[outlinerect[y][x]]
			toolcan[tooloutlinerectid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[tooloutlinerectid].Flush()

		Local filledcircle := New Int[][] (
		New Int[](12,12,12,1,1,12,12,12),
		New Int[](12,12,1,1,1,1,12,12),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](1,1,1,1,1,1,1,1),
		New Int[](1,1,1,1,1,1,1,1),
		New Int[](12,1,1,1,1,1,1,12),
		New Int[](12,12,1,1,1,1,12,12),
		New Int[](12,12,12,1,1,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8			
			Local p:Int=filledcircle[y][x]
			toolcan[toolfilledcircleid].Color = c64color[p]
			toolcan[toolfilledcircleid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[toolfilledcircleid].Flush()

		Local outlinecircle := New Int[][] (
		New Int[](12,12,12,1,1,12,12,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](1,12,12,12,12,12,12,1),
		New Int[](1,12,12,12,12,12,12,1),
		New Int[](12,1,12,12,12,12,1,12),
		New Int[](12,12,1,12,12,1,12,12),
		New Int[](12,12,12,1,1,12,12,12))
		For Local y:Int=0 Until 8
		For Local x:Int=0 Until 8
			Local p:Int=outlinecircle[y][x]
			toolcan[tooloutlinecircleid].Color = c64color[p]
			toolcan[tooloutlinecircleid].DrawRect(x*4,y*4,4,4)
		Next
		Next
		toolcan[tooloutlinecircleid].Flush()

End Method

	Method spritelibview(canvas:Canvas)
		canvas.Color = Color.Black
		canvas.DrawRect(spritelibx,spriteliby,spritelibwidth,spritelibheight)
		canvas.Color = Color.White
		Local num:Int=(middlebarcurrentid*80)
		For Local y:Int=spriteliby Until spriteliby+spritelibheight Step spriteheight*spritelibscale
		For Local x:Int=spritelibx Until spritelibx+spritelibwidth Step spritewidth*spritelibscale
			Local pointx:Int=x
			Local pointy:Int=y

			If num = spritelibselected
				
				canvas.Color = Color.White
				canvas.DrawRect(pointx,pointy,spritewidth*spritelibscale,spriteheight*spritelibscale)
				canvas.Scissor = New Recti(pointx+2,pointy+2,pointx+spritewidth*spritelibscale-3,pointy+spriteheight*spritelibscale-3)
				'canvas.Scissor(z1)
				canvas.DrawImage(spritelibim[num],pointx,pointy)	
				'Local z2:=New Recti(0,0,640,480)
				canvas.Scissor = New Recti(0,0,640,480)
			Else
				canvas.Color = Color.White
				canvas.DrawImage(spritelibim[num],pointx,pointy)	
				
			End If

			


			
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,spritewidth*spritelibscale,spriteheight*spritelibscale)
					spritelibselected = num
					spritelibcopytocanvas()
				End If					
			End If
					
			num+=1
			If num>=numspritelib Then Exit
		Next
			If num>=numspritelib Then Exit
		Next
	
	End Method
	

	Method updatespritelib()
		For Local y:Int=0 Until spriteheight
		For Local x:Int=0 Until spritewidth
			Local pointx:Float=x*spritelibscale
			Local pointy:Float=y*spritelibscale
			If startsetuppalettemode = 0
				spritelibcan[spritelibselected].Color = c64color[map[x,y]]
				Else
				spritelibcan[spritelibselected].Color = db32color[map[x,y]]
			End If
			spritelibcan[spritelibselected].DrawRect(pointx,pointy,spritelibscale,spritelibscale)			
			spritelibmap[spritelibselected,x,y] = map[x,y]
		Next
		Next
		spritelibcan[spritelibselected].Flush()
	End Method

	Method spritelibcopytocanvas()
		For Local y:Int=0 Until spriteheight
		For Local x:Int=0 Until spritewidth
			map[x,y] = spritelibmap[spritelibselected,x,y]
		Next
		Next		
	End Method

	Method spriteview(canvas:Canvas)
		
		canvas.Color = Color.Grey
		
		For Local y:Int=0 Until spriteheight
		For Local x:Int=0 Until spritewidth
			Local pointx:Int=(x*gridwidth)+canvasx
			Local pointy:Int=(y*gridheight)+canvasy
			'canvas.DrawRect()
			If startsetuppalettemode = 0
				canvas.Color = c64color[map[x,y]]			
				Else
				canvas.Color = db32color[map[x,y]]			
			End If
			canvas.DrawRect(pointx,pointy,gridwidth,gridheight)
			
			'
			' Mouse down (LEFT)
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,gridwidth,gridheight)=True								
					If toolselected = toolpencilid
						map[x,y] = paletteselected
					End If
					If toolselected = tooleraserid
						map[x,y] = paletteeraser
					End If
					If toolselected = toolfillid
						fillatposition(x,y)
					End If
	
				End If					
			End If
	
			' Line tool
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,gridwidth,gridheight)
					If toolselected = toollineid
						If linepressed = False And lineactive = False
							lineactive = True
							linepressed = True
							linestartx = x
							linestarty = y							
						End If
						If lineactive = True
							lineendx = x
							lineendy = y
							
						End If					
					End If
				End If
			End If
			If Mouse.ButtonDown(MouseButton.Left) = False
				If toolselected = toollineid
					If lineactive = True						
						previewline(canvas,True)
						lineactive = False
						linepressed = False						
					End If
				End If
			End if
			
			' Selection Tool
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,gridwidth,gridheight)
					If toolselected = toolselectionid
						If selectionpressed = False And selectionactive = False
							selectionactive = True
							selectionpressed = True
							selectionstartx = x
							selectionstarty = y
							selectionnegativeswitchx = True
							selectionnegativeswitchy = True
						End If
						If selectionactive = True
							selectionendx = x
							selectionendy = y
							If selectionendx < selectionstartx Then 
								selectionendx-=1
								If selectionnegativeswitchx Then 
									selectionnegativeswitchx = False
									selectionstartx+=1
								End If
							End If
							If selectionendy < selectionstarty Then 
								selectionendy-=1
								If selectionnegativeswitchy Then 
									selectionnegativeswitchy = False
									selectionstarty+=1
								End If
							End If
							
						End If						
					End If
				End If
			End If
			If Mouse.ButtonDown(MouseButton.Left) = False
				If toolselected = toolselectionid
					If selectionactive = True						
						'previewselection(canvas,True)
						selectionactive = False
						selectionpressed = False	

						' if the end is smaller then then start then switch them
						If selectionendx<selectionstartx Then 
							Local a:Int=selectionstartx
							Local b:Int=selectionendx
							selectionstartx = b+1 
							selectionendx = a -1
						End If
						If selectionendy<selectionstarty Then
							Local a:Int=selectionstarty
							Local b:Int=selectionendy
							selectionstarty = b +1
							selectionendy = a -1 
						End If

						'
					End If
				End If
			End if

			' Remove the selection with rmb
			If Mouse.ButtonDown(MouseButton.Right) = True
				selectionstartx=0
				selectionstarty=0
				selectionendx=0
				selectionendy=0
			End If
					
			'		
			' Mouse down (MIDDLE) Color Picker
			If Mouse.ButtonDown(MouseButton.Middle)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,gridwidth,gridheight)
					paletteselected = map[x,y]
				End If
			End if
			If Mouse.ButtonDown(MouseButton.Left)
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,gridwidth,gridheight)
					If toolselected = toolcolorpickerid
						paletteselected = map[x,y]
					End If
				End If
			End if

		'
		' Mouse Down(LEFT) Filled rect / outlined rect / filled circle / outlined circle
		If Mouse.ButtonDown(MouseButton.Left)
			If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,gridwidth,gridheight)
				If toolselected = toolfilledrectid Or toolselected = tooloutlinerectid Or toolselected = toolfilledcircleid Or toolselected = tooloutlinecircleid
					If bcselectionpressed = False And bcselectionactive = False
						bcselectionactive = True
						bcselectionpressed = True
						bcselectionstartx = x
						bcselectionstarty = y
						bcselectionnegativeswitchx = True
						bcselectionnegativeswitchy = True
					End If
					If bcselectionactive = True
						bcselectionendx = x
						bcselectionendy = y
						If bcselectionendx < bcselectionstartx Then 
							bcselectionendx-=1
							If bcselectionnegativeswitchx Then 
								bcselectionnegativeswitchx = False
								bcselectionstartx+=1
							End If
						End If
						If bcselectionendy < bcselectionstarty Then 
							bcselectionendy-=1
							If bcselectionnegativeswitchy Then 
								bcselectionnegativeswitchy = False
								bcselectionstarty+=1
							End If
						End If
						
					End If						
				End If
			End If
		End If
		If Mouse.ButtonDown(MouseButton.Left) = False
			If toolselected = toolfilledrectid Or toolselected = tooloutlinerectid Or toolselected = toolfilledcircleid Or toolselected = tooloutlinecircleid
				If bcselectionactive = True						
					'previewselection(canvas,True)
					bcselectionactive = False
					bcselectionpressed = False	

					' if the end is smaller then then start then switch them
					If bcselectionendx<bcselectionstartx Then 
						Local a:Int=bcselectionstartx
						Local b:Int=bcselectionendx
						bcselectionstartx = b+1 
						bcselectionendx = a -1
					End If
					If bcselectionendy<bcselectionstarty Then
						Local a:Int=bcselectionstarty
						Local b:Int=bcselectionendy
						bcselectionstarty = b +1
						bcselectionendy = a -1 
					End If
					'
					' Do the filling
					If toolselected = toolfilledrectid Or toolselected = tooloutlinerectid
						For Local y:Int=bcselectionstarty To bcselectionendy
						For Local x:Int=bcselectionstartx To bcselectionendx
							If toolselected = toolfilledrectid Then map[x,y] = paletteselected
							If toolselected = tooloutlinerectid
								If x = bcselectionstartx Or x = bcselectionendx Or y = bcselectionendy Or y=bcselectionstarty
									map[x,y] = paletteselected
								End If
							End If
						Next
						Next
					Elseif toolselected = toolfilledcircleid Or toolselected = tooloutlinecircleid
						' add circle code here	
						
						Local w:Int=Abs(bcselectionstartx-bcselectionendx)+1
						Local h:Int=Abs(bcselectionstarty-bcselectionendy)+1

						If toolselected = tooloutlinecircleid						
							Local ti:Image = New Image(spritewidth,spriteheight)
							Local tc:Canvas = New Canvas(ti)
							tc.Clear(Color.Black)
							tc.Color = Color.White
							tc.OutlineMode=OutlineMode.Smooth
							tc.OutlineColor = Color.Green
							tc.OutlineWidth = 0
							tc.DrawOval(bcselectionstartx,bcselectionstarty,w-1,h-1)
							tc.Flush()
							For Local y:Int=0 Until spriteheight
							For Local x:Int=0 Until spritewidth
								If ti.GetPixel(x,y) = Color.Green
									map[x,y] = paletteselected
								End If
							Next
							Next
						Else
							Local ti:Image = New Image(spritewidth,spriteheight)
							Local tc:Canvas = New Canvas(ti)
							tc.Clear(Color.Black)
							tc.Color = Color.White
							tc.DrawOval(bcselectionstartx-1,bcselectionstarty-1,w+1,h+1)
							tc.Flush()
							For Local y:Int=0 Until spriteheight
							For Local x:Int=0 Until spritewidth
								If ti.GetPixel(x,y) <> Color.Black
									map[x,y] = paletteselected
								End If
							Next
							Next

						End If
					
					End If
					'
					bcselectionendy=0
					bcselectionendx=0
					bcselectionstarty=0
					bcselectionstartx=0
				End If
			End If
		End if
			
			
			' Copy to clipboard
			If Keyboard.KeyReleased(Key.C)
				copytoclipboard()
			End if

		Next
		Next
		updatepreview()
		updatespritelib()
	End Method
	
	' Selection for the selection tool or the filled outlined tools
	'
	Method previewselection(canvas:Canvas,drawit:Bool=False)
		' the selection rectangle
		If selectionstartx = selectionendx And selectionstarty = selectionendy Then
		Else
			Local x1:Int=canvasx+(selectionstartx*gridwidth)
			Local y1:Int=canvasy+(selectionstarty*gridheight)
			Local x2:Int=canvasx+((selectionendx+1)*gridwidth)
			Local y2:Int=canvasy+((selectionendy+1)*gridheight)		
					
			
			canvas.Color = Color.White
			canvas.DrawLine(x1,y1,x2,y1)
			canvas.DrawLine(x1,y1,x1,y2)
			canvas.DrawLine(x1,y2,x2,y2)
			canvas.DrawLine(x2,y1,x2,y2)
			canvas.Color = Color.Black
			x1+=1;y1+=1;x2-=1;y2-=1
			canvas.DrawLine(x1,y1,x2,y1)
			canvas.DrawLine(x1,y1,x1,y2)
			canvas.DrawLine(x1,y2,x2,y2)
			canvas.DrawLine(x2,y1,x2,y2)
			x1+=2;y1+=2;x2-=2;y2-=2
			canvas.DrawLine(x1,y1,x2,y1)
			canvas.DrawLine(x1,y1,x1,y2)
			canvas.DrawLine(x1,y2,x2,y2)
			canvas.DrawLine(x2,y1,x2,y2)
		End If
		' the filled outlined tool
		If bcselectionstartx = bcselectionendx And bcselectionstarty = bcselectionendy Then 
		Else
			Local x1:Int=canvasx+(bcselectionstartx*gridwidth)
			Local y1:Int=canvasy+(bcselectionstarty*gridheight)
			Local x2:Int=canvasx+((bcselectionendx+1)*gridwidth)
			Local y2:Int=canvasy+((bcselectionendy+1)*gridheight)		
			
			canvas.Color = Color.White
			canvas.DrawLine(x1,y1,x2,y1)
			canvas.DrawLine(x1,y1,x1,y2)
			canvas.DrawLine(x1,y2,x2,y2)
			canvas.DrawLine(x2,y1,x2,y2)
			canvas.Color = Color.Black
			x1+=1;y1+=1;x2-=1;y2-=1
			canvas.DrawLine(x1,y1,x2,y1)
			canvas.DrawLine(x1,y1,x1,y2)
			canvas.DrawLine(x1,y2,x2,y2)
			canvas.DrawLine(x2,y1,x2,y2)
			x1+=2;y1+=2;x2-=2;y2-=2
			canvas.DrawLine(x1,y1,x2,y1)
			canvas.DrawLine(x1,y1,x1,y2)
			canvas.DrawLine(x1,y2,x2,y2)
			canvas.DrawLine(x2,y1,x2,y2)
		End If
	End Method
	
	Method previewline(canvas:Canvas,drawit:Bool=False)
		If lineactive = False Then Return
		Local x1:Int=linestartx,y1:Int=linestarty
		Local x2:Int=lineendx,y2:Int=lineendy		
	    Local dx:Int, dy:Int, sx:Int, sy:Int, e:Int
	    dx = Abs(x2 - x1)
	    sx = -1
	    If x1 < x2 Then sx = 1      
	    dy = Abs(y2 - y1)
	    sy = -1
	    If y1 < y2 Then sy = 1
	    If dx < dy Then 
	        e = dx / 2 
	    Else 
	        e = dy / 2          
	    End If
	    Local exitloop:Bool=False
	    While exitloop = False
		    Local pointx:Int=canvasx+(x1*gridwidth)
		    Local pointy:Int=canvasy+(y1*gridheight)
		    If startsetuppalettemode = 0
		    	canvas.Color = c64color[paletteselected]
		    	else
			    canvas.Color = db32color[paletteselected]
			End If
			canvas.DrawRect(pointx,pointy,gridwidth,gridheight)  
			If drawit=True Then 				
				If x1<0 Or y1<0 Or x1>=spritewidth Or y1>=spriteheight Then Exit
				map[x1,y1] = paletteselected
			End If
	      If x1 = x2 
	          If y1 = y2
	              exitloop = True
	          End If
	      End If
	      If dx > dy Then
	          x1 += sx ; e -= dy 
	           If e < 0 Then e += dx ; y1 += sy
	      Else
	          y1 += sy ; e -= dx 
	          If e < 0 Then e += dy ; x1 += sx
	      Endif
	
	    Wend
			
	End Method
	
	Method fillatposition(x:Int,y:Int)
		Local ol:List<pathnode> = New List<pathnode>
	 	' Add the start position on the list
	 	ol.AddLast(New pathnode(x,y))
	 	' set the cloes map at the start position to distance 1
	 	Local colorundermouse:Int=map[x,y]
	 	map[x,y] = paletteselected
	 	
	 	' some helper arrays. We can determine the top,right,and bottom
	 	' and left position cells with these numbers.
	 	Local dx:Int[] = New Int[](0,1,0,-1)
	 	Local dy:Int[] = New Int[](-1,0,1,0)
	 	' While there is contents in the list
	 	While ol.Count() <> 0
		 	
	 		' Get the current location
	 		Local x1:Int=ol.First.x
	 		Local y1:Int=ol.First.y
	 		' Remove the current location from the list
	 		ol.RemoveFirst()
	 		' Get 4 new positions around the current positions
			For Local i:=0 Until 4
				' Set new x and y
				Local nx:Int=x1+dx[i]
				Local ny:Int=y1+dy[i]
				' If the coordinates are inside the map
				If nx>=0 And ny>=0 And nx<spritewidth And ny<spriteheight
					' If the closedmap is not written to yet
		 			If map[nx,ny] = colorundermouse And map[nx,ny] <> paletteselected
		 				' Set the new distance based on the current distance
		 				map[nx,ny] = paletteselected
		 				' Add new position to the list
		 				ol.AddLast(New pathnode(nx,ny))
		 			End If
	 			End If
			Next
	 	Wend
 	 		
	End Method
	
	Method spritegrid(canvas:Canvas)
		' If grid noview then exit this method		
		If toolgridtoggle = False Then Return
		
		' draw our grid	
		canvas.Color = Color.Grey
		
		For Local y:Int=0 Until spriteheight
		For Local x:Int=0 Until spritewidth
			Local pointx:Int=(x*gridwidth)+canvasx
			Local pointy:Int=(y*gridheight)+canvasy
			canvas.DrawLine(pointx,pointy,pointx+gridwidth,pointy)			
			canvas.DrawLine(pointx,pointy,pointx,pointy+gridheight)
		Next
		Next
	End Method
	Method paletteview(canvas:Canvas)
		canvas.Color = Color.Black
		canvas.DrawRect(palettex,palettey,palettewidth,paletteheight)
		canvas.Scissor = New Recti(palettex+2,palettey+2,palettex+2+palettewidth-4,palettey+2+paletteheight-4)
		canvas.Color = Color.White
		Local cc:Int=0
		For Local y:Int=0 Until paletteheight Step palettecellheight
		For Local x:Int=0 Until palettewidth Step palettecellwidth
			If cc>=numpalette Then Exit			
			Local pointx:Float=x+palettex
			Local pointy:Float=y+palettey
			'
			' Draw our color
			If startsetuppalettemode = 0
				canvas.Color = c64color[cc]
				Else
				canvas.Color = db32color[cc]
			End If
			canvas.DrawRect(pointx,pointy,palettecellwidth,palettecellheight)
			'
			' Draw a white bar around the currently selected color
			If paletteselected = cc
				canvas.OutlineMode = OutlineMode.Solid
				canvas.OutlineWidth = 3
				canvas.OutlineColor = Color.Black
				canvas.DrawRect(pointx+2,pointy+2,palettecellwidth-4,palettecellheight-4)
				canvas.OutlineMode = OutlineMode.Solid
				canvas.OutlineWidth = 1
				canvas.OutlineColor = Color.Yellow
				canvas.DrawRect(pointx+2,pointy+2,palettecellwidth-4,palettecellheight-4)	
				canvas.OutlineMode = OutlineMode.None
			End If
			'
			' Select our color
			If Mouse.ButtonDown(MouseButton.Left)				
				If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,palettecellwidth,palettecellheight) = True
					paletteselected = cc
				End If
			End if
			'
			cc+=1			
		Next
		Next
		canvas.Scissor = New Recti(0,0,640,480)
		'canvas.Color = c64color[2]
	End Method
	
	Method updatepreview()			
		previewcan.Clear(Color.Black)	
		For Local y:Int=0 Until map.GetSize(1)
		For Local x:Int=0 Until map.GetSize(0)
			Local pointx:Int=x*previewcellwidth
			Local pointy:Int=y*previewcellheight
			If startsetuppalettemode = 0
				previewcan.Color = c64color[map[x,y]]
				Else
				previewcan.Color = db32color[map[x,y]]
			End If
			previewcan.DrawRect(pointx,pointy,previewcellwidth,previewcellheight)
		Next
		Next
		previewcan.Flush()
	End Method
	Method previewview(canvas:Canvas)		
		canvas.Color = Color.White
		canvas.DrawRect(previewx,previewy,previewwidth,previewheight)
		canvas.DrawImage(previewim,previewx+1,previewy+1,0,.95,.95)		
	End Method
	
	Method middlebarview(canvas:Canvas)
		canvas.Color = middlebarcolor
		canvas.DrawRect(middlebarx,middlebary,middlebarwidth,middlebarheight)
		canvas.Color = middlebarcolor/2
		canvas.DrawRect(middlebarx,middlebary+middlebarheight/2,middlebarwidth,middlebarheight/2)
		' Draw the icons ..
		Local num:Int=0
		For Local x:Int=640-128 Until 640 Step 32
			If num>=nummiddlebaricons Then Continue
			Local pointx:Int=x+middlebarx
			Local pointy:Int=middlebary
			If middlebarcurrentid = num Then
				canvas.Color=Color.White								
				Else
				canvas.Color=Color.DarkGrey						
			End If
			canvas.DrawImage(middlebarim[num],pointx,pointy)
			'
			' Selection of the sprite editor or the map editor
			If Mouse.ButtonDown(MouseButton.Left)
			If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,32,32)
				middlebarcurrentid = num
			End If
			End if			
			
			num+=1
		Next
		
	End Method

	Method topbarview(canvas:Canvas)
		canvas.Color = topbarcolor
		canvas.DrawRect(topbarx,topbary,topbarwidth,topbarheight)
		canvas.Color = topbarcolor/2
		canvas.DrawRect(topbarx,topbary+topbarheight/2,topbarwidth,topbarheight/2)
		'
		' Draw the icons ..
		Local num:Int=0
		For Local x:Int=640-200 Until 640 Step 32
			If num>=numtopbaricons Then Continue
			Local pointx:Int=x+topbarx
			Local pointy:Int=topbary+3
			If topbarcurrentid = num Then
				canvas.Color=Color.White								
				Else
				canvas.Color=Color.DarkGrey						
			End If
			canvas.DrawImage(topbarim[num],pointx,pointy,0,.6,.6)
			'
			' Selection of the sprite editor or the map editor
			If Mouse.ButtonDown(MouseButton.Left)
			If rectsoverlap(Mouse.X,Mouse.Y,1,1,pointx,pointy,32,32)
				topbarcurrentid = num
			End If
			End if			
			
			num+=1
		Next
		
	End Method

	Method bottombarview(canvas:Canvas)
		canvas.Color = bottombarcolor
		canvas.DrawRect(bottombarx,bottombary,bottombarwidth,bottombarheight)
		canvas.Color = bottombarcolor/2
		canvas.DrawRect(bottombarx,bottombary+bottombarheight/2,bottombarwidth,bottombarheight/2)
	End Method
	
	Method tilemapview(canvas:Canvas)		
		canvas.Color = Color.Black
		canvas.DrawRect(tilemapx,tilemapy,tilemapwidth,tilemapheight)
		canvas.Color = Color.White
		For Local y:Int=0 Until tilemaptilesscreenvertical
		For Local x:Int=0 Until tilemaptilesscreenhorizontal
			Local pointx:Int=(x*spritewidth*spritelibscale)+tilemapx
			Local pointy:Int=(y*spriteheight*spritelibscale)+tilemapy
			canvas.DrawImage(spritelibim[tilemap[x,y]],pointx,pointy)			
			
		Next
		Next
		If Mouse.ButtonDown(MouseButton.Left)
			If rectsoverlap(Mouse.X,Mouse.Y,1,1,tilemapx,tilemapy,tilemapwidth,tilemapheight)
				Local x:Int=(Mouse.X-tilemapx) / (spritewidth*spritelibscale)
				Local y:Int=(Mouse.Y-tilemapy) / (spriteheight*spritelibscale)
				If x<0 Or y<0 Or x>=tilemaptileshorizontal Or y>=tilemaptilesvertical Then 
				Else
				tilemap[x,y] = spritelibselected
				End If
			End If
		End If
	End Method
	
	Method draw(canvas:Canvas)
		' We start the sprite editor with the sprite dimension
		' resolution selection.
		If startsetupdone = False
			startsetupview(canvas)
			Return
		End If
		' Here is the map and sprite editor section
		If topbarcurrentid = topbarspriteeditid
			bottombarview(canvas)
			middlebarview(canvas)
			topbarview(canvas)
			spriteview(canvas)
			previewline(canvas)
			spritegrid(canvas)
			previewselection(canvas)		
			paletteview(canvas)
			previewview(canvas)
			spritelibview(canvas)
			toolview(canvas)
		Elseif topbarcurrentid = topbarmapeditid
			bottombarview(canvas)
			middlebarview(canvas)
			topbarview(canvas)
			tilemapview(canvas)
			spritelibview(canvas)
		End If
	End Method
	Method inidb32colors()
		db32color = New Color[32]
		db32color[0 ] = New Color(intof(0),intof(0),intof(0))
		db32color[1 ] = New Color(intof(34),intof(32),intof(52))
		db32color[2 ] = New Color(intof(69),intof(40),intof(60))
		db32color[3 ] = New Color(intof(102),intof(57),intof(49))
		db32color[4 ] = New Color(intof(143),intof(86),intof(59))
		db32color[5 ] = New Color(intof(223),intof(113),intof(38))
		db32color[6 ] = New Color(intof(217),intof(160),intof(102))
		db32color[7 ] = New Color(intof(238),intof(195),intof(154))
		db32color[8 ] = New Color(intof(251),intof(242),intof(54))
		db32color[9 ] = New Color(intof(153),intof(229),intof(80))
		db32color[10] = New Color(intof(106),intof(190),intof(48))
		db32color[11] = New Color(intof(55),intof(148),intof(110))
		db32color[12] = New Color(intof(75),intof(105),intof(47))
		db32color[13] = New Color(intof(82),intof(75),intof(36))
		db32color[14] = New Color(intof(50),intof(60),intof(57))
		db32color[15] = New Color(intof(63),intof(63),intof(116))
		db32color[16] = New Color(intof(48),intof(96),intof(130))
		db32color[17] = New Color(intof(91),intof(110),intof(225))
		db32color[18] = New Color(intof(99),intof(155),intof(225))
		db32color[19] = New Color(intof(95),intof(205),intof(228))
		db32color[20] = New Color(intof(203),intof(219),intof(252))
		db32color[21] = New Color(intof(255),intof(255),intof(255))
		db32color[22] = New Color(intof(155),intof(173),intof(183))
		db32color[23] = New Color(intof(132),intof(126),intof(135))
		db32color[24] = New Color(intof(105),intof(106),intof(106))
		db32color[25] = New Color(intof(89),intof(86),intof(82))
		db32color[26] = New Color(intof(118),intof(66),intof(138))
		db32color[27] = New Color(intof(172),intof(50),intof(50))
		db32color[28] = New Color(intof(217),intof(87),intof(99))
		db32color[29] = New Color(intof(215),intof(123),intof(186))
		db32color[30] = New Color(intof(143),intof(151),intof(74))
		db32color[31] = New Color(intof(138),intof(111),intof(48))
	End Method
	
	Method inic64colors()
		c64color = New Color[16]
		c64color[0 ] = New Color(intof(0)  ,intof(0)  ,intof(0)  )'Black
		c64color[1 ] = New Color(intof(255),intof(255),intof(255))'White
		c64color[2 ] = New Color(intof(136),intof(0)  ,intof(0)  )'Red
		c64color[3 ] = New Color(intof(170),intof(255),intof(238))'Cyan
		c64color[4 ] = New Color(intof(204),intof(68) ,intof(204))'Violet / Purple
		c64color[5 ] = New Color(intof(0)  ,intof(204),intof(85) )'Green
		c64color[6 ] = New Color(intof(0)  ,intof(0)  ,intof(170))'Blue
		c64color[7 ] = New Color(intof(238),intof(238),intof(119))'Yellow
		c64color[8 ] = New Color(intof(221),intof(136),intof(85) )'Orange
		c64color[9 ] = New Color(intof(102),intof(68) ,intof(0)  )'Brown
		c64color[10] = New Color(intof(255),intof(119),intof(119))'Light red
		c64color[11] = New Color(intof(51) ,intof(51) ,intof(51) )'Dark grey / Grey 1
		c64color[12] = New Color(intof(119),intof(119),intof(119))'Grey 2
		c64color[13] = New Color(intof(170),intof(255),intof(102))'Light green
		c64color[14] = New Color(intof(0)  ,intof(136),intof(255))'Light blue
		c64color[15] = New Color(intof(187),intof(187),intof(187))'Light grey / grey 3
	End Method
	
	
	
	Function intof:Float(a:Int)
		Return 1.0/255.0*a
	End Function

	Method copytoclipboard()
		Local out:String="Field map := New Int[][] ("+String.FromChar(10)
		For Local y:Int=0 Until spriteheight
			Local a:String
		For Local x:Int=0 Until spritewidth
			a+=map[x,y]+","
		Next
		Local l:Int=a.Length
		a=a.Slice(0,a.Length-1)
		out += "New Int[]("+a+"),"+String.FromChar(10)
		Next
		out=out.Slice(0,out.Length-2)
		out+=")"
		instance.ClipboardText = out
	End Method


End Class



Class MyWindow Extends Window
	Field myspriteeditor:spriteeditor
	
	Method New()
		myspriteeditor = New spriteeditor()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(New Color(.2,.2,.2,1))		
		myspriteeditor.draw(canvas)

		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
'	New AppInstance		
	instance = New AppInstance
	New MyWindow
	
	App.Run()
End Function

Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)   	
    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    Return True
End
Function circlerectcollide:Bool(cx:Int,cy:Int,cr:Int, rx:Int,ry:Int,rw:Int,rh:Int)
    Local closestx:Float = Clamp(cx, rx, rx+rw)
    Local closesty:Float = Clamp(cy, ry, ry+rh)
    Local distancex :Float = cx - closestx
    Local distancey:Float = cy - closesty
    Local distancesquared:Float = (distancex * distancex) + (distancey * distancey)
    Return distancesquared < (cr * cr)
End Function

