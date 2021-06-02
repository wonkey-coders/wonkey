' (Firepower) 'Fire Power' Remake Project (Based on the Amiga Game from 1987)

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global tilewidth:Int=64
Global tileheight:Int=64

Class tile
	'Sand (desert) tiles
	Field sand1im:Image
	Field sand1can:Canvas
	Field sandshadowtopim:Image
	Field sandshadowtopcan:Canvas
	Field sandshadowleftim:Image
	Field sandshadowleftcan:Canvas
	Field sandshadowrightim:Image
	Field sandshadowrightcan:Canvas
	Field sandshadowbottomim:Image
	Field sandshadowbottomcan:Canvas
	Field sandshadowbottomleftim:Image
	Field sandshadowbottomleftcan:Canvas
	Field sandshadowbottomrightim:Image
	Field sandshadowbottomrightcan:Canvas
	Field sandshadowtopleftim:Image
	Field sandshadowtopleftcan:Canvas
	Field sandshadowtoprightim:Image
	Field sandshadowtoprightcan:Canvas
	'Road tiles
	Field roadhorim:Image
	Field roadhorcan:Canvas
	Field roadverim:Image
	Field roadvercan:Canvas
	Field roadtopleftim:Image
	Field roadtopleftcan:Canvas
	Field roadbottomrightim:Image
	Field roadbottomrightcan:Canvas
	Field roadtoprightim:Image
	Field roadtoprightcan:Canvas
	Field roadbottomleftim:Image
	Field roadbottomleftcan:Canvas
	Field roadbottomleftrightim:Image
	Field roadbottomleftrightcan:Canvas
	Field roadbottomtoprightim:Image
	Field roadbottomtoprightcan:Canvas
	Field roadbottomtopleftim:Image
	Field roadbottomtopleftcan:Canvas
	Field roadtopleftrightim:Image
	Field roadtopleftrightcan:Canvas
	Field roadbottomtopleftrightim:Image
	Field roadbottomtopleftrightcan:Canvas
	
	' 
	' Walls
	Field wallgatebottomim:Image
	Field wallgatebottomcan:Canvas
	Field wallgatetopim:Image
	Field wallgatetopcan:Canvas
	Field wallhorim:Image
	Field wallhorcan:Canvas
	Field wallverim:Image
	Field wallvercan:Canvas
	Field wallbottomleftim:Image
	Field wallbottomleftcan:Canvas
	Field wallbottomleftrightim:Image
	Field wallbottomleftrightcan:Canvas
	Field wallbottomrightim:Image
	Field wallbottomrightcan:Canvas
	Field wallbottomtopleftrightim:Image
	Field wallbottomtopleftrightcan:Canvas
	Field walltopleftim:Image
	Field walltopleftcan:Canvas
	Field walltoprightim:Image
	Field walltoprightcan:Canvas
	Field walltopleftrightim:Image
	Field walltopleftrightcan:Canvas
	
	Field towertopim:Image
	Field towertopcan:Canvas
	
		
	Method New()
		' Create sand tiles
		sand1im = New Image(tilewidth,tileheight)
		sand1can = New Canvas(sand1im)
		makesand1(sand1can)		
		sandshadowtopim = New Image(tilewidth,tileheight)
		sandshadowtopcan = New Canvas(sandshadowtopim)
		makesandshadowtop(sandshadowtopcan)
		sandshadowleftim = New Image(tilewidth,tileheight)
		sandshadowleftcan = New Canvas(sandshadowleftim)
		makesandshadowleft(sandshadowleftcan)
		sandshadowrightim = New Image(tilewidth,tileheight)
		sandshadowrightcan = New Canvas(sandshadowrightim)
		makesandshadowright(sandshadowrightcan)
		sandshadowbottomim = New Image(tilewidth,tileheight)
		sandshadowbottomcan = New Canvas(sandshadowbottomim)
		makesandshadowbottom(sandshadowbottomcan)
		sandshadowbottomleftim = New Image(tilewidth,tileheight)
		sandshadowbottomleftcan = New Canvas(sandshadowbottomleftim)
		makesandshadowbottomleft(sandshadowbottomleftcan)
		sandshadowbottomrightim = New Image(tilewidth,tileheight)
		sandshadowbottomrightcan = New Canvas(sandshadowbottomrightim)
		makesandshadowbottomright(sandshadowbottomrightcan)
		sandshadowtopleftim = New Image(tilewidth,tileheight)
		sandshadowtopleftcan = New Canvas(sandshadowtopleftim)
		makesandshadowtopleft(sandshadowtopleftcan)
		sandshadowtoprightim = New Image(tilewidth,tileheight)
		sandshadowtoprightcan = New Canvas(sandshadowtoprightim)
		makesandshadowtopright(sandshadowtoprightcan)


		' Create road tiles
		roadhorim = New Image(tilewidth,tileheight)
		roadhorcan = New Canvas(roadhorim)
		makeroadhor(roadhorcan)
		roadtopleftim = New Image(tilewidth,tileheight)
		roadtopleftcan = New Canvas(roadtopleftim)
		makeroadtopleft(roadtopleftcan)
		roadverim = New Image(tilewidth,tileheight)
		roadvercan = New Canvas(roadverim)
		makeroadver(roadvercan)
		roadbottomrightim = New Image(tilewidth,tileheight)
		roadbottomrightcan = New Canvas(roadbottomrightim)
		makeroadbottomright(roadbottomrightcan)
		roadtoprightim = New Image(tilewidth,tileheight)
		roadtoprightcan = New Canvas(roadtoprightim)
		makeroadtopright(roadtoprightcan)
		roadbottomleftim = New Image(tilewidth,tileheight)
		roadbottomleftcan = New Canvas(roadbottomleftim)
		makeroadbottomleft(roadbottomleftcan)
		roadbottomleftrightim = New Image(tilewidth,tileheight)
		roadbottomleftrightcan = New Canvas(roadbottomleftrightim)
		makeroadbottomleftright(roadbottomleftrightcan)
		roadbottomtoprightim = New Image(tilewidth,tileheight)
		roadbottomtoprightcan = New Canvas(roadbottomtoprightim)
		makeroadbottomtopright(roadbottomtoprightcan)
		roadbottomtopleftim = New Image(tilewidth,tileheight)
		roadbottomtopleftcan = New Canvas(roadbottomtopleftim)
		makeroadbottomtopleft(roadbottomtopleftcan)
		roadtopleftrightim = New Image(tilewidth,tileheight)
		roadtopleftrightcan = New Canvas(roadtopleftrightim)
		makeroadtopleftright(roadtopleftrightcan)
		roadbottomtopleftrightim = New Image(tilewidth,tileheight)
		roadbottomtopleftrightcan = New Canvas(roadbottomtopleftrightim)
		makeroadbottomtopleftright(roadbottomtopleftrightcan)

		'Create wall tiles
		wallgatebottomim = New Image(tilewidth,tileheight)
		wallgatebottomcan = New Canvas(wallgatebottomim)
		makewallgatebottom(wallgatebottomcan)
		wallgatetopim = New Image(tilewidth,tileheight)
		wallgatetopcan = New Canvas(wallgatetopim)
		makewallgatetop(wallgatetopcan)
		wallhorim = New Image(tilewidth,tileheight)
		wallhorcan = New Canvas(wallhorim)
		makewallhor(wallhorcan)
		wallbottomleftim = New Image(tilewidth,tileheight)
		wallbottomleftcan = New Canvas(wallbottomleftim)
		makewallbottomleft(wallbottomleftcan)
		wallbottomleftrightim = New Image(tilewidth,tileheight)
		wallbottomleftrightcan = New Canvas(wallbottomleftrightim)
		makewallbottomleftright(wallbottomleftrightcan)
		wallbottomrightim = New Image(tilewidth,tileheight)
		wallbottomrightcan = New Canvas(wallbottomrightim)
		makewallbottomright(wallbottomrightcan)
		wallbottomtopleftrightim = New Image(tilewidth,tileheight)
		wallbottomtopleftrightcan = New Canvas(wallbottomtopleftrightim)
		makewallbottomtopleftright(wallbottomtopleftrightcan)
		wallverim = New Image(tilewidth,tileheight)
		wallvercan = New Canvas(wallverim)
		makewallver(wallvercan)
		walltoprightim = New Image(tilewidth,tileheight)
		walltoprightcan = New Canvas(walltoprightim)
		makewalltopright(walltoprightcan)
		walltopleftim = New Image(tilewidth,tileheight)
		walltopleftcan = New Canvas(walltopleftim)
		makewalltopleft(walltopleftcan)
		walltopleftrightim = New Image(tilewidth,tileheight)
		walltopleftrightcan = New Canvas(walltopleftrightim)
		makewalltopleftright(walltopleftrightcan)

		towertopim = New Image(tilewidth,tileheight)
		towertopcan = New Canvas(towertopim)
		maketowertopim(towertopcan)

		
	End Method
	Method makesand1(canvas:Canvas)
		canvas.Color = Color.White
		' background color
		canvas.Clear(Color.Yellow.Blend(Color.Red,.25))
		' Noise
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Yellow * Rnd()
			canvas.DrawPoint(x,y)
		Next
		canvas.Flush()
	End Method
	Method makesandshadowtop(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=Rnd(Rnd(tileheight/4))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		canvas.Flush()
	End Method
	Method makesandshadowleft(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise left
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		canvas.Flush()
	End Method
	Method makesandshadowright(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		canvas.Flush()
	End Method
	Method makesandshadowbottom(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise bottom
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=tileheight-Rnd(Rnd(tileheight/4))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		canvas.Flush()
	End Method
	Method makesandshadowbottomleft(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise bottom
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=tileheight-Rnd(Rnd(tileheight/4))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		' add noise left
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight-tileheight/4)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		

		canvas.Flush()
	End Method

	Method makesandshadowbottomright(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise bottom
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=tileheight-Rnd(Rnd(tileheight/4))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight-tileheight/4)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		

		canvas.Flush()
	End Method

	Method makesandshadowtopleft(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=Rnd(Rnd(tileheight/4))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		

		' add noise left
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight/4,tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		

		canvas.Flush()
	End Method

	Method makesandshadowtopright(canvas:Canvas)
		' make standard sand tile
		makesand1(canvas)
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=Rnd(Rnd(tileheight/4))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight/4,tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next		

		canvas.Flush()
	End Method


	' road section
	Method makeroadhor(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road top side
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(0,0,tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight/24,tilewidth,tileheight/24)
		'road bottom side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,tileheight-(tileheight/12),tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight-tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()
	End Method
	Method makeroadtopleft(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road right side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(tilewidth-tilewidth/12,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth-tilewidth/24,0,tilewidth/24,tileheight)
		'road bottom side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,tileheight-(tileheight/12),tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight-tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()		
	End Method
	Method makeroadver(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road right side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(tilewidth-tilewidth/12,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth-tilewidth/24,0,tilewidth/24,tileheight)
		'road left side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth/24,0,tilewidth/24,tileheight)

		canvas.Flush()
	End Method

	Method makeroadbottomright(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road left side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth/24,0,tilewidth/24,tileheight)
		'road top side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,0,tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()		
	End Method
	Method makeroadtopright(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road left side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth/24,0,tilewidth/24,tileheight)
		'road bottom side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,tileheight-(tileheight/12),tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight-tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()		
	End Method
	Method makeroadbottomleft(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road right side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(tilewidth-tilewidth/12,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth-tilewidth/24,0,tilewidth/24,tileheight)
		'road top side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,0,tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()		
	End Method
	Method makeroadbottomleftright(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road top side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,0,tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()		
	End Method
	Method makeroadbottomtopright(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road left side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth/24,0,tilewidth/24,tileheight)
		
		canvas.Flush()		
	End Method
	Method makeroadbottomtopleft(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road right side
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(tilewidth-tilewidth/12,0,tilewidth/24,tileheight)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawRect(tilewidth-tilewidth/24,0,tilewidth/24,tileheight)
		
		canvas.Flush()		
	End Method
	Method makeroadtopleftright(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		'road bottom side
		canvas.Color = Color.Grey.Blend(Color.White,.2)				
		canvas.DrawRect(0,tileheight-(tileheight/12),tilewidth,tileheight/24)
		canvas.Color = Color.Grey.Blend(Color.Black,.8)
		canvas.DrawRect(0,tileheight-tileheight/24,tilewidth,tileheight/24)
		
		canvas.Flush()		
	End Method
	Method makeroadbottomtopleftright(canvas:Canvas)
		canvas.Clear(Color.Grey)
		'road noise
		roadnoise(canvas)
		canvas.Flush()		
	End Method

	'
	' Make Wall graphics
	'
	Method makewallgatebottom(canvas:Canvas)
		makesandshadowtop(canvas)
		'sand shadow on the left side of the wall gate
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth/6-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next
		makewallrectbottom(canvas,0,tileheight/8,tilewidth,tileheight/3)
		makewallrecttop(canvas,tilewidth/6,0,tilewidth/1.5,tileheight)
		canvas.Flush()
	End Method
	Method makewallgatetop(canvas:Canvas)
		makesandshadowbottom(canvas)
		' sand shadow on the left side of the wall gate
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth/6-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next

		makewallrectbottom(canvas,0,tileheight-tileheight/2,tilewidth,tileheight/3)
		makewallrecttop(canvas,tilewidth/6,0,tilewidth/1.5,tileheight)
		canvas.Flush()
	End Method

	Method makewallhor(canvas:Canvas)
		makesand1(canvas)
		' add shadow on the bottom of the wall		
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)
			Local y:Int=tileheight/1.2+(Rnd(Rnd(tileheight/4)))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next
		
		wallsurface(canvas,0,tileheight/6,tilewidth,tileheight/1.5)
		walltopline(canvas,0,tileheight/6,tilewidth)
		wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth)
		'makewallrecttop(canvas,0,tileheight/6,tilewidth,tileheight/1.5)
		canvas.Flush()
	End Method

	Method makewallver(canvas:Canvas)
		makesand1(canvas)
		' shadow sand of the left side of the wall
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth/6-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next
		wallsurface(canvas,tilewidth/6,0,tilewidth/1.5,tileheight)
		wallleftline(canvas,tilewidth/6,0,tileheight)
		wallrightline(canvas,tilewidth-tilewidth/6,0,tileheight)
		canvas.Flush()
	End Method

	Method makewallbottomleft(canvas:Canvas)
		makesand1(canvas)
		wallsurface(canvas,0,tileheight/6,tilewidth/1.28,tileheight/1.5)
		wallsurface(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)

		'makewallrecttop(canvas,0,tileheight/6,tilewidth/1.28,tileheight/1.5)
		'makewallrecttop(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)
		walltopline(canvas,0,tileheight/6,tilewidth/1.28)
		wallleftline(canvas,tilewidth/6,tileheight-tileheight/6,tileheight/6)
		wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth/6)
		wallrightline(canvas,tilewidth-tilewidth/6,tileheight/6,tileheight)
		canvas.Flush()
	End Method
	
	Method makewallbottomleftright(canvas:Canvas)
		makesand1(canvas)
		wallsurface(canvas,0,tileheight/6,tilewidth,tileheight/1.5)
		wallsurface(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)

		'makewallrecttop(canvas,0,tileheight/6,tilewidth/1.28,tileheight/1.5)
		'makewallrecttop(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)
		walltopline(canvas,0,tileheight/6,tilewidth)
		wallleftline(canvas,tilewidth/6,tileheight-tileheight/6,tileheight/6)
		wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth/6)
		wallbottomline(canvas,tilewidth-tilewidth/6,tileheight-tileheight/6,tilewidth/6)
		wallrightline(canvas,tilewidth-tilewidth/6,tileheight-tileheight/6,tileheight/6)
		canvas.Flush()
		
		
	End Method

	Method makewallbottomright(canvas:Canvas)
		makesand1(canvas)
		wallsurface(canvas,tilewidth/6,tileheight/6,tilewidth,tileheight/1.5)
		wallsurface(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)

		'makewallrecttop(canvas,0,tileheight/6,tilewidth/1.28,tileheight/1.5)
		'makewallrecttop(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)
		walltopline(canvas,tilewidth/6,tileheight/6,tilewidth)
		wallleftline(canvas,tilewidth/6,tileheight/6,tileheight)
		'wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth/6)
		wallbottomline(canvas,tilewidth-tilewidth/4,tileheight-tileheight/6,tilewidth/4)
		wallrightline(canvas,tilewidth-tilewidth/6,tileheight-tileheight/4,tileheight)
		
		canvas.Flush()
		
		
	End Method

	Method makewallbottomtopleftright(canvas:Canvas)
		makesand1(canvas)
		wallsurface(canvas,0,tileheight/6,tilewidth,tileheight/1.5)
		wallsurface(canvas,tilewidth/6,0,tilewidth/1.5,tileheight)

		'makewallrecttop(canvas,0,tileheight/6,tilewidth/1.28,tileheight/1.5)
		'makewallrecttop(canvas,tilewidth/6,tileheight/6,tilewidth/1.5,tileheight)
		'walltopline(canvas,0,tileheight/6,tilewidth)
		 'top side
		wallleftline(canvas,tilewidth/6,0,tileheight/5)
		wallrightline(canvas,tilewidth-tilewidth/6,0,tileheight/5)
		walltopline(canvas,0,tileheight/6,tilewidth/5) 'left
		walltopline(canvas,tilewidth-tilewidth/5,tileheight/6,tilewidth)'right
		'bottom side
		wallleftline(canvas,tilewidth/6,tileheight-tileheight/5,tileheight)
		wallrightline(canvas,tilewidth-tilewidth/6,tileheight-tileheight/5,tileheight)
		wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth/5) 'left
		wallbottomline(canvas,tilewidth-tilewidth/5,tileheight-tileheight/6,tilewidth)'right

		canvas.Flush()
		
		
	End Method

	Method makewalltopright(canvas:Canvas)
		makesand1(canvas)
		
		' add shadow on the bottom of the wall		
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)+tilewidth/6
			Local y:Int=tileheight/1.2+(Rnd(Rnd(tileheight/4)))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next	
		' shadow sand of the left side of the wall
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=tilewidth/6-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next			
		
		wallsurface(canvas,tilewidth/6,tileheight/6,tilewidth,tileheight/1.5)
		wallsurface(canvas,tilewidth/6,0,tilewidth/1.5,tileheight/1.5)

		wallleftline(canvas,tilewidth/6,0,tileheight/1.2)
		wallbottomline(canvas,tilewidth/6,tileheight-tileheight/6,tilewidth)
		wallrightline(canvas,tilewidth-tilewidth/6,0,tileheight/6)
		walltopline(canvas,tilewidth-tilewidth/5,tileheight/6,tilewidth)
		canvas.Flush()
		
	End Method


	Method makewalltopleft(canvas:Canvas)
		makesand1(canvas)
		
		' add shadow on the bottom of the wall		
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)+tilewidth/6
			Local y:Int=tileheight/1.2+(Rnd(Rnd(tileheight/4)))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next	

		'toptobottom		
		wallsurface(canvas,0,tileheight/6,tilewidth-tilewidth/5,tileheight/1.5)
	
		wallsurface(canvas,tilewidth/6,0,tilewidth/1.5,tileheight/1.5)

		wallleftline(canvas,tilewidth/6,0,tileheight/6)
		wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth-tilewidth/5)
		wallrightline(canvas,tilewidth-tilewidth/6,0,tileheight/1.3)
		walltopline(canvas,0,tileheight/6,tilewidth/6)
		canvas.Flush()
		
	End Method
	
	Method makewalltopleftright(canvas:Canvas)
		makesand1(canvas)
		' add shadow on the bottom of the wall		
		' add noise top top
		For Local i:Int=0 Until tilewidth*tileheight/10
			Local x:Int=Rnd(tilewidth)+tilewidth/6
			Local y:Int=tileheight/1.2+(Rnd(Rnd(tileheight/4)))
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y)
		Next	

		'toptobottom		
		wallsurface(canvas,0,tileheight/6,tilewidth,tileheight/1.5)
	
		wallsurface(canvas,tilewidth/6,0,tilewidth/1.5,tileheight/1.5)

		wallleftline(canvas,tilewidth/6,0,tileheight/6)
		wallbottomline(canvas,0,tileheight-tileheight/6,tilewidth)
		wallrightline(canvas,tilewidth-tilewidth/6,0,tileheight/5)
		walltopline(canvas,0,tileheight/6,tilewidth/6)
		walltopline(canvas,tilewidth-tilewidth/6,tileheight/6,tilewidth/6)
		canvas.Flush()
		
	End Method

	Method maketowertopim(canvas:Canvas)
		'canvas.Color = Color.Grey
		'canvas.DrawRect(0,0,tilewidth,tileheight)
		makesand1(canvas)
		' shadow sand of the left side of the wall
		' add noise right
		For Local i:Int=0 Until tilewidth*tileheight/15
			Local x:Int=tilewidth/6-Rnd(Rnd(tilewidth/4))
			Local y:Int=Rnd(tileheight-tileheight/3)
			canvas.Color = Color.Brown * Rnd()
			canvas.DrawPoint(x,y+tileheight/3)
		Next
		wallsurface(canvas,tilewidth/6,tileheight/3,tilewidth/1.5,tileheight/1.4)
		wallleftline(canvas,tilewidth/6,tileheight/3,tileheight/1.4)
		wallrightline(canvas,tilewidth-tilewidth/6,tileheight/3,tileheight/1.4)
		
		
		canvas.Color = Color.Grey.Blend(Color.Yellow,.2)
		canvas.DrawRect(tilewidth/6+2,tileheight/3,tilewidth/1.5-4,2)
		
		canvas.Color = Color.Brown.Blend(Color.Yellow,.2)
		canvas.DrawRect(tilewidth/6+2,tileheight/3+2,tilewidth/1.5-4,10)		
		
		
		canvas.Color = Color.Brown.Blend(Color.Black,.2)
		canvas.DrawRect(tilewidth/6+4,tileheight/3+5,tilewidth/1.5-8,12)



		canvas.Color = Color.Black
		canvas.DrawRect(tilewidth/1.8,tileheight/3+2,2,17)
		canvas.DrawRect(tilewidth/6,tileheight/3+17,tilewidth/1.6,2)

		canvas.Color = Color.Grey.Blend(Color.Black,.2)
		canvas.DrawRect(tilewidth/2-tilewidth/8,tileheight/3,tilewidth/5,19)


		'wallarmortop(canvas,tileheight/3)		
'		wallsurface(canvas,tilewidth/6,tileheight/3,tilewidth-tilewidth/3,tileheight-tileheight/6)
'		canvas.Color = Color.Black
'		canvas.DrawRect(tilewidth/6-tilewidth/12,tileheight/3),tilewidth/12,tileheight-tileheight/6)
		canvas.Flush()
	End Method

	'
	' Graphics methods	
	'
	Method walltopline(canvas:Canvas,x1:Int,y1:Int,w1:Int)
		'top
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1,y1,x1+w1,y1)
		canvas.DrawLine(x1,y1+1,x1+w1,y1+1)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1,y1+2,x1+w1,y1+2)
		canvas.DrawLine(x1,y1+3,x1+w1,y1+3)
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1+4,x1+w1,y1+4)
		canvas.DrawLine(x1,y1+5,x1+w1,y1+5)		
	End Method
	Method wallleftline(canvas:Canvas,x1:Int,y1:Int,h1:Int)
		'left
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1,x1,y1+h1)
		canvas.DrawLine(x1+1,y1,x1+1,y1+h1)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1+2,y1+2,x1+2,y1+h1)
		canvas.DrawLine(x1+3,y1+2,x1+3,y1+h1)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1+4,y1+2,x1+4,y1+h1)
		canvas.DrawLine(x1+5,y1+2,x1+5,y1+h1)
	End Method
	Method wallbottomline(canvas:Canvas,x1:Int,y1:Int,w1:Int)
		'bottom
		Local h1:Int=-2
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1,y1+h1-5,x1+w1,y1+h1-5)
		canvas.DrawLine(x1,y1+h1-4,x1+w1,y1+h1-4)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1,y1+h1-3,x1+w1,y1+h1-3)
		canvas.DrawLine(x1,y1+h1-2,x1+w1,y1+h1-2)
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1+h1-1,x1+w1,y1+h1-1)
		canvas.DrawLine(x1,y1+h1,x1+w1,y1+h1)		
	End Method
		
	Method wallrightline(canvas:Canvas,x1:Int,y1:Int,h1:Int)
		Local w1:Int=-2
		'right
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1+w1-1,y1,x1+w1-1,y1+h1)
		canvas.DrawLine(x1+w1-2,y1,x1+w1-2,y1+h1)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1+w1-3,y1+2,x1+w1-3,y1+h1)
		canvas.DrawLine(x1+w1-4,y1+2,x1+w1-4,y1+h1)
		canvas.Color = Color.Black
		canvas.DrawLine(x1+w1-5,y1+4,x1+w1-5,y1+h1)
		canvas.DrawLine(x1+w1-6,y1+4,x1+w1-6,y1+h1)
		
	End Method	
		
	Method makewallrectbottom(canvas:Canvas,x1:Int,y1:Int,w1:Int,h1:Int)		
		'solid block
		wallsurface(canvas,x1,y1,w1,h1)		
		'top
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1,y1,x1+w1,y1)
		canvas.DrawLine(x1,y1+1,x1+w1,y1+1)
		canvas.DrawLine(x1,y1+2,x1+w1,y1+2)
		canvas.DrawLine(x1,y1+3,x1+w1,y1+3)
		'left
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1,x1,y1+h1)
		canvas.DrawLine(x1+1,y1,x1+1,y1+h1)
		canvas.DrawLine(x1+2,y1+1,x1+2,y1+h1)
		canvas.DrawLine(x1+3,y1+2,x1+3,y1+h1)
		'right
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1+w1-1,y1,x1+w1-1,y1+h1)
		canvas.DrawLine(x1+w1-2,y1,x1+w1-2,y1+h1)
		canvas.DrawLine(x1+w1-3,y1,x1+w1-3,y1+h1)
		canvas.DrawLine(x1+w1-4,y1,x1+w1-4,y1+h1)				
		'bottom
		canvas.Color = Color.Black	
		canvas.DrawLine(x1,y1+h1,x1+w1-1,y1+h1)
		canvas.DrawLine(x1,y1+h1-1,x1+w1-2,y1+h1-1)		
		canvas.DrawLine(x1,y1+h1-2,x1+w1-3,y1+h1-2)
		canvas.DrawLine(x1,y1+h1-3,x1+w1-4,y1+h1-3)
		
	End Method
	Method makewallrecttop(canvas:Canvas,x1:Int,y1:Int,w1:Int,h1:Int)		
		'solid block
		wallsurface(canvas,x1,y1,w1,h1)		
		'top
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1,y1,x1+w1,y1)
		canvas.DrawLine(x1,y1+1,x1+w1,y1+1)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1,y1+2,x1+w1,y1+2)
		canvas.DrawLine(x1,y1+3,x1+w1,y1+3)
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1+4,x1+w1,y1+4)
		canvas.DrawLine(x1,y1+5,x1+w1,y1+5)
		'left
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1,x1,y1+h1)
		canvas.DrawLine(x1+1,y1,x1+1,y1+h1)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1+2,y1+2,x1+2,y1+h1)
		canvas.DrawLine(x1+3,y1+2,x1+3,y1+h1)
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1+4,y1+2,x1+4,y1+h1)
		canvas.DrawLine(x1+5,y1+2,x1+5,y1+h1)
		'right
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1+w1-1,y1,x1+w1-1,y1+h1)
		canvas.DrawLine(x1+w1-2,y1,x1+w1-2,y1+h1)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1+w1-3,y1+2,x1+w1-3,y1+h1)
		canvas.DrawLine(x1+w1-4,y1+2,x1+w1-4,y1+h1)
		canvas.Color = Color.Black
		canvas.DrawLine(x1+w1-5,y1+4,x1+w1-5,y1+h1)
		canvas.DrawLine(x1+w1-6,y1+4,x1+w1-6,y1+h1)
		'bottom
		canvas.Color = Color.Grey.Blend(Color.White,.2)
		canvas.DrawLine(x1+4,y1+h1-5,x1+w1-2,y1+h1-5)
		canvas.DrawLine(x1+4,y1+h1-4,x1+w1-2,y1+h1-4)
		canvas.Color = Color.Grey
		canvas.DrawLine(x1+2,y1+h1-3,x1+w1,y1+h1-3)
		canvas.DrawLine(x1+2,y1+h1-2,x1+w1,y1+h1-2)
		canvas.Color = Color.Black
		canvas.DrawLine(x1,y1+h1-1,x1+w1,y1+h1-1)
		canvas.DrawLine(x1,y1+h1,x1+w1,y1+h1)
	End Method

	Method wallsurface(canvas:Canvas,x1:Int,y1:Int,w1:Int,h1:Int)
		canvas.Color = Color.Grey
		canvas.DrawRect(x1,y1,w1,h1)
		For Local i:Int=0 Until w1*h1/20
			Local x:Int=Rnd(w1)+x1
			Local y:Int=Rnd(h1)+y1			
			canvas.Color = Color.Grey.Blend(Color.Green,Rnd(.5))
			canvas.DrawPoint(x,y)
		Next
	End Method
	Method roadnoise(canvas:Canvas)
		'road noise
		For Local i:Int=0 Until tilewidth*tileheight/30
			Local x:Int=Rnd(tilewidth)
			Local y:Int=Rnd(tileheight)
			If Rnd()<.5 Then
				canvas.Color = Color.Grey.Blend(Color.Green,Rnd(.5))
			Else
				canvas.Color = Color.Grey.Blend(Color.White,Rnd(.5))
			End If
			canvas.DrawPoint(x,y)
		Next		
	End Method

	'
	' Draw methods
	'

	Method drawsand1(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sand1im,x,y)
	End Method
	Method drawsandshadowtop(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowtopim,x,y)
	End Method
	Method drawsandshadowleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowleftim,x,y)
	End Method
	Method drawsandshadowright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowrightim,x,y)
	End Method
	Method drawsandshadowbottom(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowbottomim,x,y)
	End Method
	Method drawsandshadowbottomleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowbottomleftim,x,y)		
	End Method
	Method drawsandshadowbottomright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowbottomrightim,x,y)		
	End Method
	Method drawsandshadowtopleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowtopleftim,x,y)		
	End Method
	Method drawsandshadowtopright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(sandshadowtoprightim,x,y)		
	End Method
	Method drawroadhor(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadhorim,x,y)
	End Method
	Method drawroadtopleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadtopleftim,x,y)
	End Method
	Method drawroadver(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadverim,x,y)
	End Method
	Method drawroadbottomright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadbottomrightim,x,y)
	End Method
	Method drawroadtopright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadtoprightim,x,y)
	End Method
	Method drawroadbottomleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadbottomleftim,x,y)
	End Method
	Method drawroadbottomleftright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadbottomleftrightim,x,y)
	End Method
	Method drawroadbottomtopright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadbottomtoprightim,x,y)
	End Method
	Method drawroadbottomtopleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadbottomtopleftim,x,y)
	End Method
	Method drawroadtopleftright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadtopleftrightim,x,y)
	End Method
	Method drawroadbottomtopleftright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(roadbottomtopleftrightim,x,y)
	End Method
	' Draw walls
	Method drawgatebottom(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallgatebottomim,x,y)
	End Method
	Method drawgatetop(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallgatetopim,x,y)
	End Method
	Method drawwallhor(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallhorim,x,y)
	End Method
	Method drawwallbottomleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallbottomleftim,x,y)
	End Method
	Method drawwallbottomleftright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallbottomleftrightim,x,y)
	End Method
	Method drawwallbottomright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallbottomrightim,x,y)
	End Method
	Method drawwallbottomtopleftright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallbottomtopleftrightim,x,y)
	End Method
	Method drawwallver(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(wallverim,x,y)
	End Method
	Method drawwalltopright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(walltoprightim,x,y)
	End Method
	Method drawwalltopleft(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(walltopleftim,x,y)
	End Method
	Method drawwalltopleftright(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(walltopleftrightim,x,y)
	End Method
	Method drawtowertop(canvas:Canvas,x:Int,y:Int)
		canvas.DrawImage(towertopim,x,y)
	End Method
End Class

Global mytile:tile

Class MyWindow Extends Window

	Method New()
		mytile = New tile()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		For Local y:Int=0 Until Height Step tileheight
		For Local x:Int=0 Until Width Step tilewidth
			mytile.drawsand1(canvas,x,y)
		Next
		Next
		
		'Line of sand above the road
		'mytile.drawsandshadowbottom(canvas,200-128,200-64)
		'mytile.drawsandshadowbottom(canvas,200-64,200-64)
		'mytile.drawsandshadowbottom(canvas,200,200-64)
		'mytile.drawsandshadowbottom(canvas,200+64,200-64)
		'mytile.drawsandshadowbottom(canvas,200+64*2,200-64)
		'mytile.drawsandshadowbottom(canvas,200+64*3,200-64)
		'mytile.drawsandshadowbottom(canvas,200+64*4,200-64)
		'line of roads
		mytile.drawroadhor(canvas,200-128,200)
		mytile.drawroadhor(canvas,200-64,200)
		mytile.drawroadhor(canvas,200,200)
		mytile.drawroadhor(canvas,200+64,200)
		mytile.drawroadhor(canvas,200+64*2,200)
		mytile.drawroadhor(canvas,200+64*3,200)
		mytile.drawroadbottomleft(canvas,200+64*4,200)
		'Line of sand below the road
		mytile.drawsandshadowtop(canvas,200-128,200+64)
		mytile.drawsandshadowtop(canvas,200-64,200+64)
		mytile.drawsandshadowtop(canvas,200,200+64)
		mytile.drawsandshadowtop(canvas,200+64,200+64)
		mytile.drawsandshadowtop(canvas,200+64*2,200+64)
		mytile.drawsandshadowtopright(canvas,200+64*3,200+64)
		'and road besides it
		mytile.drawroadver(canvas,200+64*4,200+64)
		
		'The gate at the bottom and top
		mytile.drawgatetop(canvas,200+64*2,200-64)
		
		mytile.drawwallhor(canvas,200+64,200-128)
		mytile.drawwallver(canvas,200+128,200-192)
		mytile.drawwallbottomtopleftright(canvas,200+128,200-128)
		mytile.drawwallhor(canvas,200+64*3,200-128)
		
		mytile.drawgatebottom(canvas,200+64*2,200+64)
		mytile.drawwallhor(canvas,200+64*3,200+128)
		mytile.drawwalltopleftright(canvas,200+64*2,200+128)
		mytile.drawwallhor(canvas,200+64*1,200+128)
		
		
		mytile.drawtowertop(canvas,100,300)
		mytile.drawwallbottomtopleftright(canvas,100,364)
		mytile.drawtowertop(canvas,100-64,364)
		mytile.drawtowertop(canvas,164,364)
		mytile.drawtowertop(canvas,100,300+128)
		
		
		
		If Keyboard.KeyDown(Key.Key1)
			mytile.drawsand1(canvas,100,100)
			mytile.drawsandshadowtop(canvas,100,100-64)
			mytile.drawsandshadowleft(canvas,100-64,100)
			mytile.drawsandshadowright(canvas,100+64,100)
			mytile.drawsandshadowbottom(canvas,100,100+64)
			
			mytile.drawsandshadowbottomleft(canvas,100-64,100+64)
			mytile.drawsandshadowbottomright(canvas,100+64,100+64)
			mytile.drawsandshadowtopleft(canvas,100-64,100-64)
			mytile.drawsandshadowtopright(canvas,100+64,100-64)
	
			
			mytile.drawroadhor(canvas,400,200)
			mytile.drawroadtopleft(canvas,400+64,200)
			mytile.drawroadver(canvas,400+64,200-64)
			mytile.drawroadbottomright(canvas,400-64,200)
			mytile.drawroadver(canvas,400-64,200+64)
			mytile.drawroadtopright(canvas,400-64,200+128)
			mytile.drawroadbottomleft(canvas,400+64,200-128)
			mytile.drawroadbottomtopleftright(canvas,100,400)
			mytile.drawroadbottomleftright(canvas,200,400)
			mytile.drawroadbottomtopright(canvas,200+64,400)
			mytile.drawroadbottomtopleft(canvas,200+128,400)
			mytile.drawroadtopleftright(canvas,200+256,400)
			
			
		End if
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
