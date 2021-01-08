'   Copyleft notice: All code created by Leo Santos (www.leosantos.com)
'   Feel free to use it in any form, but please include a credit.
'   More importantly, do not claim to have created any of it, unless you modify it substantially.
'   Thanks!

#Import "gamegraphics/gamegraphics"
#Import "src/renderwindow"
#Import "src/actor"
#Import "src/player"
#Import "src/bullet"
#Import "src/orb"

#Import "fonts/classic_sans.ttf"
#Import "images/grid.png"
#Import "images/starfield.png"
#Import "images/hero.png"
#Import "images/jet.png"
#Import "images/bullet.png"
#Import "images/orbSmall.png"

Using mojo..
Using std..

'To do: move out of collision

Class Game Extends RenderWindow

	Global scrollSpeed := 5.0
	Global scrollLimitY:Double = 60
	Global cameraSpeed := 1.0
	
	Field hero:Player	
	Field bg:Background
	Field bgGrid:Background
	Field smallFont:Font

	Field colorTint:= New Color( 0.25, 1.0, 0.5 )
		
	Method New()					
		Super.New( "Test", 420, 240, False, True )		'name, width, height, filterTextures, renderToTexture
		Layout = "letterbox-int"
	End
	
	Method OnStart() Override
		Actor.camera = camera
	
		'Load sprites & font
		canvas.Font = Font.Load( "asset::classic_sans.ttf", 10 )
		bg = New Background( "asset::starfield.png" )
		bgGrid = New Background( "asset::grid.png" )
		
		Local heroSprite := New Sprite( "asset::hero.png", 3, 32, 32, False )
		heroSprite.AddAnimationClip( "idle", New Int[]( 0 ) )
		heroSprite.AddAnimationClip( "up", New Int[]( 1 ) )
		heroSprite.AddAnimationClip( "down", New Int[]( 2 ) )
		
		Local jetSprite := New Sprite( "asset::jet.png", 2, 16, 16, False )
		jetSprite.AddAnimationClip( "idle", New Int[]( 0,1 ) )
		jetSprite.frameRate = 30
		
		Local bulletSprite := New Sprite( "asset::bullet.png", 5, 32, 32, False )
		bulletSprite.AddAnimationClip( "idle", New Int[] ( 0 ) )
		bulletSprite.AddAnimationClip( "hit", New Int[] ( 1,2,3,4 ), False )
		bulletSprite.frameRate = 15
		
		Local orbSprite := New Sprite( "asset::orbSmall.png", 5, 16, 16, False )
		orbSprite.AddAnimationClip( "idle", New Int[] ( 0,1,2,3 ) )
		
		'Create player sprite
		hero = New Player( heroSprite )
		
		'Create reusable enemy orbs
		SeedRnd( 12345 )
		Local offset:= 0
		For Local n := 0 Until 20
			Local neworb := New Orb( orbSprite )
			neworb.Reset()
			neworb.position.X += offset
			offset += 16
		Next
		
		'Pool of 10 reusable bullets
		For Local n := 0 Until 10
			Local b := New Bullet( bulletSprite )
			Actor.bulletPool.Push( b )
		Next
		Bullet.player = hero
		Bullet.cullDistance = Width
		
		canvas.TextureFilteringEnabled = False	'New feature in v009
	End
	
	
	Method OnUpdate() Override
		'camera scrolls up & down a bit, 90's shooter style
		camera.X += scrollSpeed			
		If Keyboard.KeyDown( Key.Up )
			camera.Y -= cameraSpeed
		Else If Keyboard.KeyDown( Key.Down )
			camera.Y += cameraSpeed
		End
		camera.Y = Clamp( camera.Y, -scrollLimitY, scrollLimitY )
		
		'Update all actors
		Actor.UpdateAll()
		
		'Display debug info
		If Keyboard.KeyHit( Key.D ) Then debug = Not debug
	End
	
	
	Method OnDraw() Override
		canvas.Color = colorTint

		'Draw bg objects in three layers with different parallax
		canvas.Alpha = 1.0
		Parallax = 0.1
		bg.Draw( canvas, 0, 0, 1.0, CameraRect )
		
		canvas.Alpha = 0.5
		canvas.DrawText( "Monkey2 Side Scrolling Demo by Leo Santos. Press space to shoot!", 260, 100 )
		
		canvas.Alpha = 0.25
		Parallax = 0.25
		bgGrid.Draw( canvas, 32, 32, 1.0, CameraRect )
		
		canvas.Alpha = 0.5
		Parallax = 1.0
		bgGrid.Draw( canvas, 0, 0, 1.0, CameraRect )
		
		'Draw all actors
		canvas.Alpha = 1.0
		canvas.Color= Color.White
		Actor.DrawAll( canvas )
	End

End

Function Main()
	New AppInstance
	New Game()
	App.Run()
End


