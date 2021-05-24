' Import assets:
#Import "../assets/playniax.png"
#Import "../assets/background.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																				' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 640,480 )																	' Backing global for virtual resolution.

Class PyroExample Extends Window

	' Backing fields:
	Field camera:=New Camera[2]
	Field logo:LayerSprite
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		' To use sprites you need to setup the scene with a camera and atleast 1 layer:
		scene=New Scene( Self )																			' Create a scene.

		' Create cameras:
		camera[0]=New Camera( scene )
		camera[1]=New Camera( scene )

		' Set splitscreen:
		SetHorizontalSplitScreen( camera[0],camera[1],virtualResolution )
		' ( this adds a viewport to the cameras )

		Local viewport:=camera[0].Viewport.Size															' The split screen commands sets a viewport on the camera and we need the size for setting zoom and rotation points.

		camera[0].RotationPoint=viewport/2																' Rotation point is the center of the screen ( 0,0 by default ).
		camera[0].ZoomPoint=viewport/2																	' Zoom point is the center of the screen ( 0,0 by default ).

		camera[1].RotationPoint=viewport/2																' Rotation point is the center of the screen ( 0,0 by default ).
		camera[1].ZoomPoint=viewport/2																	' Zoom point is the center of the screen ( 0,0 by default ).

		Local layer:=New Layer( scene )																	' Add layer.

		' Create the background sprite:
		' (  Note that the content manager is used to load the images but Image.Load can also be used instead )
		Local background:=New LayerSprite( layer,Content.GetImage( "asset::background.png" ) )
		background.Location=viewport/2																	' Center of the screen.
		
		' Create the logo sprite:
		logo=New LayerSprite( layer,Content.GetImage( "asset::playniax.png" ) )
		logo.Location=viewport/2

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		logo.Rotation+=.01
		
		scene.Update()																					' Update must be called before Draw!

		' Zoom and rotate keys:
		If Keyboard.KeyDown( Key.LeftControl )
			If Keyboard.KeyDown( Key.R ) camera[0].Rotation-=.05
			If Keyboard.KeyDown( Key.Z ) camera[0].Zoom-=.01
		Else
			If Keyboard.KeyDown( Key.R ) camera[0].Rotation+=.05
			If Keyboard.KeyDown( Key.Z ) camera[0].Zoom+=.01
		Endif
		
		scene.Draw( canvas )																			' Draw all scene objects to canvas.

		canvas.DrawText( "Use R or Left Control+R to rotate.",8,8 )
		canvas.DrawText( "Use Z or Left Control+Z to zoom in/out.",8,8+canvas.Font.Height )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
