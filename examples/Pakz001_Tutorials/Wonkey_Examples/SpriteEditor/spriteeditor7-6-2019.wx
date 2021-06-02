'
' press 'c' to copy currently selected sprite data as a [][] array into the 
' clipboard buffer.
'

' map view. (XXX....)
' hand icon for moving (map)
' grid icon for toggling grid
' box tool (icons)(filled/outline)
' circle tool (icons)(filled/outline)
' 16x16 and 32x32 sprite sizes (setup screen on startup)
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
	Field numtools:Int
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
	'
	' palette	
	Field c64color:Color[] ' our colors
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
	' Bottom Bar
	Field bottombarx:Int,bottombary:Int
	Field bottombarwidth:Int,bottombarheight:Int
	Field bottombarcolor:Color
	
	Method New()


		'palette setup
		inic64colors()
		paletteeraser = 0
		palettex = 640-150
		palettey = 32
		palettewidth = 32*4
		paletteheight = 32*4
		numpalette = 16
		palettecellwidth = 32
		palettecellheight = 32		

		'Bottom bar (global)
		bottombarx = 0
		bottombary = 480-24
		bottombarwidth = 640
		bottombarheight = 24	
		bottombarcolor = Color.Puce

		
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
		

		'sprite canvas setup
		canvasx = 32
		canvasy = 32
		spritewidth = 8
		spriteheight = 8
		map = New Int[spritewidth,spriteheight]	
		selectionbuffer = New Int[spritewidth,spriteheight]	
		
		canvaswidth=256
		canvasheight=256
		gridwidth = canvaswidth/spritewidth		
		gridheight = canvasheight/spriteheight


		'	
		'spritelib setup
		spritelibx = 0
		spriteliby = canvasheight+32+32
		spritelibwidth = 640
		spritelibheight = 128
		numspritelib = 80
		spritelibselected = 0
		spritelibscale = 4
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
		tooly = 200
		toolwidth = 32*4
		toolheight = 32*3
		numtools = 12
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
		
	End Method

	Method spritelibview(canvas:Canvas)
		canvas.Color = Color.Black
		canvas.DrawRect(spritelibx,spriteliby,spritelibwidth,spritelibheight)
		canvas.Color = Color.White
		Local num:Int=0
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
			spritelibcan[spritelibselected].Color = c64color[map[x,y]]
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
			canvas.Color = c64color[map[x,y]]			
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
						End If
						If selectionactive = True
							selectionendx = x
							selectionendy = y							
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
			
			' Copy to clipboard
			If Keyboard.KeyReleased(Key.C)
				copytoclipboard()
			End if

		Next
		Next
		updatepreview()
		updatespritelib()
	End Method
	
	Method previewselection(canvas:Canvas,drawit:Bool=False)
		If selectionstartx = selectionendx And selectionstarty = selectionendy Then Return
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
		    canvas.Color = c64color[paletteselected]
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
			canvas.Color = c64color[cc]
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
			previewcan.Color = c64color[map[x,y]]
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
		If topbarcurrentid = topbarspriteeditid
			bottombarview(canvas)
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
			topbarview(canvas)
			tilemapview(canvas)
			spritelibview(canvas)
		End If
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
