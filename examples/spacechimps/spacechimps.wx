
Namespace spacechimps

#Import "<std>"
#Import "<mojo>"

#Import "assets/bang.wav"
#Import "assets/spaceship_32.png"

Using std..
Using mojo..

Const VirtualWidth:=320'640
Const VirtualHeight:=240'480

Class MyWindow Extends Window

	Field timer:Timer
	Field laser:Sound
	Field image:Image
	Field pos:=New Vec2f
	Field vel:=New Vec2f
	Field rot:Float
	Field filter:Bool=True

	Method New( title:String,width:Int,height:Int,flags:WindowFlags )
	
		'Call super class constructor - this just passes the arguments 'up' to the Window class constructor.
		'
		Super.New( title,width,height,flags )
		
'		Layout="fill"
		'if you use letterbox layout, don't forget to implement the OnMeasure() method (see below).
		'
		Layout="letterbox"

		'Window clear color - this is effectively Letterbox color.
		'		
		ClearColor=New Color( .03,.03,.03 )
		
		'load audio/images
		'
		LoadResources()
		
		'Set initial image pos
		'
		pos=New Vec2f( VirtualWidth/2,VirtualHeight/2 )
		
		'Start update timer
		'
'		timer=New Timer( 60,OnUpdate )

		'Enable vsync.
		'	
		SwapInterval=1
	End
	
	Method LoadResources()
		
		'Load laser sound effect
		'		
		laser=Sound.Load( "asset::bang.wav" )
		
		'Load spaceship image.
		'
		'Note: scaling image here via Image.Scale is faster than scaling via Canvas matrix.
		'
		image=Image.Load( "asset::spaceship_32.png" )
		image.Scale=New Vec2f( 2 )
		image.Handle=New Vec2f( .5 )
	End
	
	Method OnKeyEvent( event:KeyEvent ) Override
		Select event.Type
		Case EventType.KeyDown
			Select event.Key
			Case Key.Enter
				If event.Modifiers & Modifier.Alt
					If Fullscreen EndFullscreen() Else BeginFullscreen()
				Endif
			Case Key.S
				'toggle vsync
				'
				SwapInterval=1-SwapInterval
			Case Key.T
				'toggle timer
				'
				If timer
					timer.Cancel()
					timer=Null
					RequestRender()
				Else
					timer=New Timer( 60,OnUpdate )
				Endif
			Case Key.F
				'toggle texture filtering
				'
				filter=Not filter
			End
		End
	End

	Method OnWindowEvent( event:WindowEvent ) Override
	
		Select event.Type
		Case EventType.WindowGainedFocus
			If timer timer.Suspended=False
		Case EventType.WindowLostFocus
			If timer timer.Suspended=True
		Default
			Super.OnWindowEvent( event )
		End
	End
	
	Method OnUpdate()
	
		RequestRender()
		
		'give GC a bit of a thrash....
		'
		'LoadResources()
		
		'rotate
		'
		If Keyboard.KeyDown( Key.Left )
			rot+=.1
		Else If Keyboard.KeyDown( Key.Right )
			rot-=.1
		Endif
		
		'wrap rot to [-Pi,Pi)
		'
		rot=(rot+Pi*3) Mod TwoPi-Pi

		'calc forward vector..
		'
		Local dir:=New Vec2f( Cos( rot ),-Sin( rot ) )

		'thrust
		'
		If Keyboard.KeyDown( Key.Up )
			vel+=(dir * 5 - vel) *.025	'arcadey thruster
'			vel+=dir * .03				'realistic...
		Else
			vel*=.999
		End
		
		'add velocity to position
		'
		pos+=vel
		
		'wrap pos to [0,size)
		'
		pos.x=(pos.x+Width) Mod Width
		pos.y=(pos.y+Height) Mod Height
		
		If Keyboard.KeyPressed( Key.Space )
			laser.Play()
'			Print "Fire!"
		End

		If Keyboard.KeyReleased( Key.Space )
'			Print "UnFire!"
		End
		
	End
	
	Field ms:=0

	Method OnRender( canvas:Canvas ) Override
	
		Local e:=App.Millisecs-ms	'ideally, e should be 16,17,17,16,17,17 ie: 16.6666...
'		If e<>16 And e<>17 Print "elapsed="+e	'show glitches
		ms+=e
		
		If Not timer OnUpdate()
		
		'Turn off texture filtering for a 'pixel art' look
		'
		canvas.TextureFilteringEnabled=filter
		
		canvas.Clear( Color.Black )

		canvas.DrawText( "FPS="+App.FPS,Width/2,0,.5,0 )
		canvas.DrawText( "Arrow keys to fly",Width/2,16,.5,0 )
		canvas.DrawText( "Swap interval="+SwapInterval +" ('S' to toggle)",Width/2,32,.5,0 )
		canvas.DrawText( "Timer sync="+(timer ? "true" Else "false")+" ('T' to toggle)",Width/2,48,.5,0 )
		canvas.DrawText( "Filtering="+(filter ? "true" Else "false")+" ('F' to toggle)",Width/2,64,.5,0 )
		
		'Draw image
		'
		Local x:=pos.x,y:=pos.y,r:=rot-Pi/2
		
		canvas.DrawImage( image,x,y,r )

		'Draw wrap around(s)
		'
		If x-image.Radius<0 canvas.DrawImage( image,x+Width,y,r )
		If x+image.Radius>Width canvas.DrawImage( image,x-Width,y,r )
		
		If y-image.Radius<0 canvas.DrawImage( image,x,y+Height,r )
		If y+image.Radius>Height canvas.DrawImage( image,x,y-Height,r )
	End
	
	Method OnMeasure:Vec2i() Override
	
		Return New Vec2i( VirtualWidth,VirtualHeight )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow( "Chimps in Space!",640,480,WindowFlags.Resizable )
	
	App.Run()
End
