' MX2 demo by Playniax!

' Title: Shoot-out
' Version: 1.0
' Release date: 21-06-2016

' Programming  : Tony Smits
' Graphics     : Peter van Driel

' This demo uses outtakes from the Pyro framework!

' For more information about Playniax and Playniax products please visit our website (http://www.playniax.com)!

' Import the assets
#Import "assets/playniax.png"
#Import "assets/bg1.png"
#Import "assets/planet.png"
#Import "assets/p10000.png"
#Import "assets/p10001.png"
#Import "assets/p20000.png"
#Import "assets/p20001.png"
#Import "assets/bullet.png"
#Import "assets/explosion_0.png"
#Import "assets/explosion_1.png"
#Import "assets/explosion_0.txt"
#Import "assets/explosion_1.txt"

' Import some Monkey stuff
#Import "<std>"
#Import "<mojo>"

' And use it
Using std..
Using mojo..

Const VWIDTH:=1024
Const VHEIGHT:=768

Const PLAYER_HITS:=10 ' Number of hits the spaceship can take

' Some backing globas
Global font:Font
Global explosion:=New Image[77] ' Explosion animation
Global planet:Sprite
Global player:=New Player[2] ' Players global
Global removeSprites:=New Stack<Sprite> ' Sprites that need to be removed end up here
Global sprites:=New Stack<Sprite> ' Contains all the sprites displayed on the screen
Global window:PlayniaxGame

Class PlayniaxGame Extends Window

	' Constructor
	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		font=Font.Load( "asset::mojo/Roboto-Regular.ttf",32 )

		LoadExplosion()

		' Create the background
		Local bg1:=New Sprite( Image.Load( "asset::bg1.png" ),VWIDTH*.5,VHEIGHT*.5 )
		planet=New Sprite( Image.Load( "asset::planet.png" ),VWIDTH*.5,VHEIGHT*.5 )

		' Create the player sprites
		player[0]=New Player( New Image[]( Image.Load( "asset::p10000.png" ),Image.Load( "asset::p10001.png" ) ),VWIDTH*.25,VHEIGHT*.5,Key.Left,Key.Right,Key.Up,Key.M ) 
		player[1]=New Player( New Image[]( Image.Load( "asset::p20000.png" ),Image.Load( "asset::p20001.png" ) ),VWIDTH*.75,VHEIGHT*.5,Key.Z,Key.X,Key.C,Key.V )

		' Create the little Playniax logo in the right corner of the screen
		Local playniax:=Image.Load( "asset::playniax.png" )
		Local x:=VWIDTH-playniax.Width/2-8
		Local y:=VHEIGHT-playniax.Height/2-8
		New Sprite( playniax,x,y )

	End

	Method OnMeasure:Vec2i() Override
		Return New Vec2i( VWIDTH,VHEIGHT )
	End
	
	Method OnRender( canvas:Canvas ) Override

		' Update game logic
		UpdateSprites()
		PlayerCollisions()
		BullitsCollisions()
		RemoveManager()

		planet.rotation+=.0005	' Rotate the planet

		' Reset player 1 if Key 1 is pressed
		If player[0].enabled=False And Keyboard.KeyHit( Key.Key1 )
			player[0].position=New Vec2f( VWIDTH*.25,VHEIGHT*.5 )
			player[0].rotation=270/360.0*TwoPi
			player[0].speed=New Vec2f()
			player[0].hits=PLAYER_HITS
			player[0].enabled=True
		Endif

		' Reset player 2 if Key 2 is pressed
		If player[1].enabled=False And Keyboard.KeyHit( Key.Key2 )
			player[1].position=New Vec2f( VWIDTH*.75,VHEIGHT*.5 )
			player[1].rotation=270/360.0*TwoPi
			player[1].speed=New Vec2f()
			player[1].hits=PLAYER_HITS
			player[1].enabled=True
		Endif

		App.RequestRender()

		canvas.Clear( New Color( 0,0,0 ) )

		' Draw sprites, scoreboard and help screen
		DrawSprites( canvas )
		DrawScores( canvas )
		DrawHelp( canvas )

	End

	' Draw all sprites
	Method DrawSprites( canvas:Canvas )
		For Local i:=0 Until sprites.Length
			If sprites[i].enabled=True sprites[i].Draw( canvas )
		Next
	End

	Method DrawHelp( canvas:Canvas )

		canvas.BlendMode=BlendMode.Alpha
		
		canvas.Font=font

		If Keyboard.KeyDown( Key.F1 )

			' Display spaceship controls
			canvas.Color=New Color( 0,0,0,.75 )
			canvas.DrawRect( 0,0,window.Width,window.Height )

			Local x:=window.Width/2-140,y:=window.Height/2-172
				
			canvas.Color=New Color( 1,0,0,1 )
			canvas.DrawText( "PLAYER 1",x,y ) ; y+=canvas.Font.Height+4
			canvas.DrawText( "Cursor up = throttle",x,y ) ; y+=canvas.Font.Height
			canvas.DrawText( "Cursor left = turn left",x,y ) ; y+=canvas.Font.Height
			canvas.DrawText( "Cursor right = turn right",x,y ) ; y+=canvas.Font.Height
			canvas.DrawText( "M = fire",x,y ) ; y+=canvas.Font.Height

			y+=16
	
			canvas.Color=New Color( 0,0,1,1 )
			canvas.DrawText( "PLAYER 2",x,y ) ; y+=canvas.Font.Height+4
			canvas.DrawText( "C = throttle",x,y ) ; y+=canvas.Font.Height
			canvas.DrawText( "Z = turn left",x,y ) ; y+=canvas.Font.Height
			canvas.DrawText( "X = turn right",x,y ) ; y+=canvas.Font.Height
			canvas.DrawText( "V = fire",x,y ) ; y+=canvas.Font.Height

		Else

			' Display help key
			canvas.Color=New Color( 1,1,1,1 )
			canvas.DrawText( "F1 = Help",8,VHEIGHT-8-canvas.Font.Height )

		Endif

	End

	' Display progress bar hit counter and points
	Method DrawScores( canvas:Canvas )

		Const spaceX:=256

		Local score:=""

		canvas.BlendMode=BlendMode.Alpha

		canvas.Font=font

		If player[0].enabled=False score="Press 1 to play" Else score=player[0].score

		DrawProgressBar( canvas,spaceX,8,50,8,player[0].hits,PLAYER_HITS,New Color( .5,0,0,1 ),New Color( 1,0,0,1 ) )

		canvas.Color=New Color( 1,0,0,1 )
		canvas.DrawText( score,spaceX,8+8+2 )

		If player[1].enabled=False score="Press 2 to play" Else score=player[1].score
		
		DrawProgressBar( canvas,window.Width-50-spaceX,8,50,8,player[1].hits,PLAYER_HITS,New Color( 0,0,.5,1 ),New Color( 0,0,1,1 ) )
		canvas.Color=New Color( 0,0,1,1 )
		canvas.DrawText( score,window.Width-50-spaceX,8+8+2 )

	End

	' Removes sprites from the stacks
	Method RemoveManager()

		For Local i:=0 Until removeSprites.Length
			If sprites.Length sprites.RemoveEach( removeSprites[i] )
			If player[0].bullets.Length player[0].bullets.RemoveEach( removeSprites[i] )
			If player[1].bullets.Length player[1].bullets.RemoveEach( removeSprites[i] )
		Next

		removeSprites.Clear()

	End

	' Update all sprites
	Method UpdateSprites()
		For Local i:=0 Until sprites.Length
			If sprites[i].enabled=True sprites[i].Update()
		Next
	End

	' Collision logic between players
	Method PlayerCollisions()

		If player[0].enabled And player[1].enabled And CheckCollision( player[0].position.X,player[0].position.Y,21,player[1].position.X,player[1].position.Y,21 )

			Local hits1:=player[0].hits
			Local hits2:=player[1].hits

			player[0].hits-=hits2
			player[1].hits-=hits1

			If player[0].hits<=0
				player[0].enabled=False
				New Explosion( explosion,player[0].position.X,player[0].position.Y,New Vec2f( 2,2 ) )
			Endif

			If player[1].hits<=0
				player[1].enabled=False
				New Explosion( explosion,player[1].position.X,player[1].position.Y,New Vec2f( 2,2 ) )
			Endif

		Endif

	End

	Method BullitsCollisions()

		' Collision logic between player 1 bullets and player 2
		For Local i:=0 Until player[0].bullets.Length
			If player[1].enabled And player[0].bullets.Get( i ).enabled
				If CheckCollision( player[1].position.X,player[1].position.Y,21,player[0].bullets.Get( i ).position.X,player[0].bullets.Get( i ).position.Y,8 )
					player[0].bullets.Get( i ).enabled=False
					removeSprites.Push( player[0].bullets.Get( i ) )
					player[1].hits-=1
					player[0].score+=1
					New Explosion( explosion,player[0].bullets.Get( i ).position.X,player[0].bullets.Get( i ).position.Y,New Vec2f( .15,.15 ) )
					If player[1].hits<=0
						player[1].enabled=False
						New Explosion( explosion,player[1].position.X,player[1].position.Y,New Vec2f( 2,2 ) )
					Endif
				Endif
			Endif
		Next

		' Collision logic between player 2 bullets and player 1
		For Local i:=0 Until player[1].bullets.Length
			If player[0].enabled And player[1].bullets.Get( i ).enabled
				If CheckCollision( player[0].position.X,player[0].position.Y,21,player[1].bullets.Get( i ).position.X,player[1].bullets.Get( i ).position.Y,8 )
					player[1].bullets.Get( i ).enabled=False
					removeSprites.Push( player[1].bullets.Get( i ) )
					player[0].hits-=1
					player[1].score+=1
					New Explosion( explosion,player[1].bullets.Get( i ).position.X,player[1].bullets.Get( i ).position.Y,New Vec2f( .15,.15 ) )
					If player[0].hits<=0
						player[0].enabled=False
						New Explosion( explosion,player[0].position.X,player[0].position.Y,New Vec2f( 2,2 ) )
					Endif
				Endif
			Endif
		Next

	End

End

' The base sprite (the other sprites extend Sprite)
Class Sprite

	' Sprite backing fields
	Field blendMode:=BlendMode.Alpha
	Field color:=New Color( 1,1,1,1 )
	Field images:Image[]
	Field enabled:=True
	Field frame:=0.0
	Field rotation:=0.0
	Field scale:=New Vec2f( 1,1 )
	Field position:=New Vec2f

	Method New()
	End
	
	' Constructor
	Method New( image:Image,x:Int,y:Int )

		Self.images=New Image[]( image )
		Self.position.X=x
		Self.position.Y=y

		' Set image handles to center
		For Local i:=0 Until Self.images.Length
			Self.images[i].Handle=New Vec2f( .5,.5 )
		Next

		' Add sprite to the sprites stack
		sprites.Push( Self )

	End

	' Constructor
	Method New( images:Image[],x:Int,y:Int )

		Self.images=images
		Self.position.X=x
		Self.position.Y=y

		' Set image handles to center
		For Local i:=0 Until Self.images.Length
			Self.images[i].Handle=New Vec2f( .5,.5 )
		Next

		sprites.Push( Self )

	End

	' Draw sprite
	Method Draw( canvas:Canvas )
		canvas.BlendMode=blendMode
		canvas.Color=color
		canvas.DrawImage( images[frame],position,-rotation,scale )
	End

	' Update code goes here
	Method Update() Virtual
	End

End

' The player sprite
Class Player Extends Sprite

	Field bullets:=New Stack<Sprite>
	Field hits:=PLAYER_HITS
	Field fire:=Key.None
	Field fireDelay:=0
	Field left:=Key.None
	Field right:=Key.None
	Field score:=0
	Field speed:=New Vec2f
	Field throttle:=Key.None

	' Constructor
	Method New( images:Image[],x:Int,y:Int,left:Key=Key.None,right:Key=Key.None,throttle:Key=Key.None,fire:Key=Key.None )

		Self.images=images
		Self.position.X=x
		Self.position.Y=y
		Self.rotation=270/360.0*TwoPi
		Self.left=left
		Self.right=right
		Self.throttle=throttle
		Self.fire=fire

		' Set image handles to center
		For Local i:=0 Until Self.images.Length
			Self.images[i].Handle=New Vec2f( .5,.5 )
		Next

		' Add sprite to the sprites stack
		sprites.Push( Self )

	End

	Method Update() Override

		' Player turn control
		If Keyboard.KeyDown( left ) rotation-=.1
		If Keyboard.KeyDown( right ) rotation+=.1

		' Player throttle control
		If Keyboard.KeyDown( throttle )

			speed.X+=Cos( rotation )*.2
			speed.Y+=Sin( rotation )*.2

		Endif

		position.X+=speed.X
		position.Y+=speed.Y

		' Control ship borders
		If position.X<0 position.X=window.Width
		If position.Y<0 position.Y=window.Height
		If position.X>window.Width position.X=0
		If position.Y>window.Height position.Y=0

		' Fire bullets
		If Keyboard.KeyDown( fire ) And fireDelay<Millisecs()
			Local bullet:=New Bullet( Image.Load( "asset::bullet.png" ),position.X,position.Y )
			bullets.Push( bullet )
			bullet.speed.X=Cos( rotation )*16
			bullet.speed.Y=Sin( rotation )*16
			bullet.rotation=rotation
			fireDelay=Millisecs()+100
		Endif

		' Animate
		frame+=.5
		frame=frame Mod images.Length

		' Slow down
		speed.X*=.98
		speed.Y*=.98

	End

End

' Player bullet sprite
Class Bullet Extends Sprite

	Field speed:=New Vec2f

	Method New( image:Image,x:Int,y:Int )
		Super.New (image,x,y )
	End
	
	Method Update() Override

		position.X+=speed.X
		position.Y+=speed.Y

		' Control bullet borders (remove when it leaves the screen)
		If position.X<0 Or position.Y<0 Or position.X>window.Width Or position.Y>window.Height
			enabled=False
			removeSprites.Push( Self )
		Endif

	End

End

' Explosion sprite
Class Explosion Extends Sprite

	' Constructor
	Method New( images:Image[],x:Int,y:Int,scale:Vec2f )
		Super.New (images,x,y )
		Self.blendMode=BlendMode.Additive
		Self.scale=scale
	End

	Method Update() Override
		' Animate
		frame+=.5
		If frame>=images.Length removeSprites.Push( Self )
	End

End

' Draws the players progress bar (outtake from the Pyro framework)
Function DrawProgressBar( canvas:Canvas,x:Int,y:Int,width:Int,height:Int,value:Int,maximum:Int,surfaceColor:Color=New Color( 0,.5,0,1 ),color:Color=New Color( 0,1,0,1 ) )

	Local s:=Float( maximum )/Float( width )

	canvas.Color=surfaceColor

	canvas.DrawRect( x,y,width,height )

	If value>0
		canvas.Color=color
		If value<width*s
			canvas.DrawRect( x,y,value/s,height )
		Else
			canvas.DrawRect( x,y,width,height )
		Endif
	Endif

End

' Checks if circles overlap (outtake from the Pyro framework)
Function CheckCollision:Bool( x1:Float,y1:Float,radius1:Float,x2:Float,y2:Float,radius2:Float )
	Return ( ( x2-x1 )*( x2-x1 )+( y2-y1 )*( y2-y1 ) )<( radius1+radius2 )*( radius1+radius2 )
End

' Grab sprite from sprite sheet (outtake from the Pyro framework)
Function GrabSprite:Image( image:Image,path:String,name:String )

	For Local l:=Eachin path.Split( "~n" )
		If l.StartsWith( name )
			Local f:=l.Split( ":" )
			If f.Length=5 Return New Image( image,New Recti( Int( f[1] ),Int( f[2] ),Int( f[1] )+Int( f[3] ),Int( f[2] )+Int( f[4] ) ) )
		Endif
	Next
	Return Null

End

' Load the explosions using a sprite sheet and txt file (outtake from the Pyro framework)
Function LoadExplosion()

	Local image:=Image.Load( "asset::explosion_0.png" )
	Local data:=LoadString( "asset::explosion_0.txt" )

	For Local i:=0 To 48
		explosion[i]=GrabSprite( image,data,"explosion"+i+".png" )
		explosion[i].Handle=New Vec2f( .5,.5 )
	Next

	image=Image.Load( "asset::explosion_1.png" )
	data=LoadString( "asset::explosion_1.txt" )

	For Local i:=49 To 76
		explosion[i]=GrabSprite( image,data,"explosion"+i+".png" )
		explosion[i].Handle=New Vec2f( .5,.5 )
	Next

End

' Some init code
Function Main()

	New AppInstance
	
	window=New PlayniaxGame( "Shoot-out",640,480 )
	
	App.Run()

End
