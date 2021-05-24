' Import assets:
#Import "../assets/comici.ttf"
#Import "../assets/playniax.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																								' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 1024,768 )																				' Backing global for virtual resolution.

Class PyroExample Extends Window

	' Backing fields:
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		' To use sprites you need to setup the scene with a camera and atleast 1 layer:
		scene=New Scene( Self )																							' Create a scene.
		Local camera:=New Camera( scene )																				' Setup camera.
		camera.ClearColor=New Color( 0,.1,0 )																			' Set a background color.
		Local layer:=New Layer( scene )																					' Add layer.

		' Line:
		Local line:=New LayerLine( layer,0,0,virtualResolution.X,virtualResolution.Y )
		line.Color=New Color( 1,1,0 )

		' Rectangle:
		Local rect:=New LayerRectangle( 200,200 )
		rect.Layer=layer
		rect.Handle=New Vec2f( 0,0 )
		rect.Color=New Color( 0,1,0 )
		rect.X=160
		rect.Y=480
		rect.LineWidth=3

		' Image:
		Local logo:=New LayerSprite( layer,Content.GetImage( "asset::playniax.png" ) )
		logo.X=512
		logo.Y=160

		' Polygon:
		Local polygon:=New LayerPolygon( layer )
		polygon.X=300
		polygon.Y=400
		polygon.Vertices=New Float[]( 28,0, 28,128, -128,128, 80,-80, 180,120 )
		polygon.Color=New Color( 0,1,1 )

		Local polyline:=New LayerPolygon( layer )
		polyline.X=900
		polyline.Y=640
		polyline.Type=1																										' Line modus ( default 0, is polygon ).
		polyline.Vertices=New Float[]( 0,0, 0,-348, -32,-348, 0,-398, 32,-348, 0,-348, 0,0, 32,0, 0,49, -32,0, 0,0 )
		polyline.Color=New Color( 1,0,0 )

		' Label:
		Local label:=New LayerLabel()
		label.Layer=layer
		label.Font=Font.Load( "asset::comici.ttf",48 )
		label.Color=New Color( 1,0,1 )
		label.Text="Hello world!"
		label.X=512
		label.Y=640

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																									' Update must be called before Draw!

		scene.Draw( canvas )																							' Draw all scene objects to canvas.

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
