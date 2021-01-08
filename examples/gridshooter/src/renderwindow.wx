
#Rem
Features:
- Simple camera coordinates. Any x and y drawing coordinate becomes a world coordinate.
- Easy to use Parallax
- "World space" mouse coordinates
- Render to texture, allows "pixel perfect" games
- Display debug info on screen with Echo( "info" )
#End

#Import "<mojo>"
#Import "area"

Using mojo..
Using std..

Class RenderWindow Extends Window

	Field canvas :Canvas						'Main canvas currently in use
	Field camera :Area<Double>					'Camera coordinates
	
	Field renderToTexture := False				'Causes all canvas rendering to be directed to a fixed size texture
	Field filterTextures := True				'Turns on/off texture smoothing. Off for pixel art.
	Field bgColor := Color.DarkGrey				'Background color
	Field borderColor := Color.Black 			'Letterboxing border color
	Field debug := False						'Toggles display of debug info ( Echo() )
	
	Protected
	
	Global _echoStack:= New Stack<String>		'Contains all the text messages to be displayed
	
	Field _init := False
	Field _flags :TextureFlags					'flags used on the render texture
	
	Field _parallax := 1.0
	Field _parallaxCam :Area<Double>
	
	Field _virtualRes:= New Vec2i				'Virtual rendering size
	Field _mouse := New Vec2i					'temporarily stores mouse coords
	Field _adjustedMouse := New Vec2i			'Mouse corrected for layout style and camera position
	Field _layerInitiated := False

	
	Field _fps	:= 60							'fps counter
	Field _fpscount	:= 0.0						'temporary fps counter
	Field _tick := 0							'Only stores the current time once every second
	
	Field _renderTexture :Texture				'Render target for renderToTexture
	Field _renderImage :Image					'Image that uses the render target
	Field _textureCanvas :Canvas				'Canvas that uses _renderImage
	Field _windowCanvas: Canvas					'main window canvas
	
	Public
	
	
	'**************************************************** Properties ****************************************************
	
	'Mouse coordinates in WORLD units, corrected for camera
	Property Mouse:Vec2i()						
		Return _adjustedMouse
	End
	
	'You can set the parallax before any drawing operation
	Property Parallax:Float()					
		Return _parallax
	Setter( value:Float )
		_parallax = value
		_parallaxCam.Position( camera.X * _parallax, camera.Y * _parallax )
		If _layerInitiated
			canvas.PopMatrix()
			_layerInitiated = False
		End
		canvas.PushMatrix()
'   		canvas.Translate( ( -camera.X * _parallax ) + _cameraOffset.X, ( -camera.Y * _parallax ) + _cameraOffset.Y  )
		canvas.Translate( ( -camera.X * _parallax ) + camera.Width/2.0, ( -camera.Y * _parallax ) + camera.Height/2.0  )

		_layerInitiated = True
	End
	
	'Returns the camera corrected for current parallax 
	Property CameraRect:Rect<Double>()
		Return _parallaxCam.Rect
	End
	
	'Flags used by the Render Texture
	Property Flags:TextureFlags()
		Return _flags
	End
	
	'Efective frame rate
	Property FPS:Int()
		Return _fps
	End
	
	'corner window coordinates	
	Property Left:Float()
		Return -Width/2.0
	End
	
	Property Right:Float()
		Return Width/2.0
	End
	
	Property Top:Float()
		Return -Height/2.0
	End
	
	Property Bottom:Float()
		Return Height/2.0
	End
	
	
	'**************************************************** Public methods ****************************************************
	
	
	Method New( title:String, width:Int, height:Int, filterTextures:Bool = True, renderToTexture:Bool = False, flags:WindowFlags = WindowFlags.Resizable )
		Super.New( title, width, height, flags )
		Layout = "letterbox"
		ClearColor = borderColor
		Style.BackgroundColor = bgColor
		
		Self.renderToTexture = renderToTexture
		Self.filterTextures = filterTextures
		
		camera = New Area<Double>( 0, 0, width, height )
		_parallaxCam = New Area<Double>( 0, 0, width, height )
		
		SetVirtualResolution( width, height )
'   		SelectCanvas()
	End
	

	Method OnRender( windowCanvas:Canvas ) Override
		App.RequestRender()
		
		If Not _init
			_init = True
'   			canvas = windowCanvas
			SelectCanvas()
			WindowStart()
			Return
		End
		
		FrameUpdate()
		
		Style.BackgroundColor = bgColor
		Self._windowCanvas = windowCanvas
		
		'Picks current drawing canvas based on renderToTexture
		SelectCanvas()

		'Mouse in world coordinates
		_mouse = TransformPointFromView( App.MouseLocation, Null )
		_adjustedMouse.x = _mouse.x + camera.Left
		_adjustedMouse.y = _mouse.y + camera.Top
		
		'the Parallax property will always set the canvas translation before drawing.
		Parallax = 1.0		
		FrameDraw()
		
		''Closes' the drawing for any parallax layer
		If _layerInitiated
			canvas.PopMatrix()
			_layerInitiated = False
		End
		
		'Draws render to texture image onto _windowCanvas
		If renderToTexture
			canvas.Flush()
			_windowCanvas.DrawImage( _renderImage, 0, 0 )
		End
		
		'Resets canvas colors for each frame
		_textureCanvas.Color = Color.White
		_windowCanvas.Color = Color.White
		
		'Draw message stack, then clear it every frame
		If debug Then DebugInfo()
		Local y := 2
		For Local t := Eachin _echoStack
			_windowCanvas.DrawText( t, 5, y )
			y += _windowCanvas.Font.Height
		Next
		_echoStack.Clear()
		
		'Basic fps counter
		If Millisecs() - _tick > 1008
			_fps = _fpscount
			_tick = Millisecs()
			_fpscount=0
		Else
			_fpscount +=1
		End
		
		'App quit
		If ( Keyboard.KeyHit( Key.Escape ) ) 
			App.Terminate()
		End
	End
	
	
	Method OnMeasure:Vec2i() Override
		Return _virtualRes
	End		

	
	
	Method OnWindowEvent(event:WindowEvent) Override
		Select event.Type
			Case EventType.WindowMoved
			Case EventType.WindowResized
				App.RequestRender()
			Case EventType.WindowGainedFocus
			Case EventType.WindowLostFocus
			Default
				Super.OnWindowEvent(event)
		End
	End
	

	Method SetVirtualResolution( width:Int, height:Int )
		_virtualRes = New Vec2i( width, height )
		MinSize = New Vec2i( width/2, height/2 )
		
		camera.Width = width
		camera.Height = height
		_parallaxCam.Width = Width
		_parallaxCam.Height = Height
		
		_renderTexture = New Texture( width, height, PixelFormat.RGBA32, _flags )
		_renderImage = New Image( _renderTexture )
		_renderImage.Handle=New Vec2f( 0, 0 )
		_textureCanvas = New Canvas( _renderImage )
'		_textureCanvas.Font = App.DefaultFont
	End


	Method CycleLayout()
		Select Layout
		Case "fill"
			Layout="letterbox"
		Case "letterbox"
			Layout="stretch"
		Case "stretch"
			Layout="float"
		Case "float"
'   			Layout="fill"
			Layout = "letterbox"
		End
	End
	
	
	'**************************************************** Protected Methods ****************************************************
	'These allow RenderWindow to be extended without the need for OnUpdate and OnDraw to call Super.xxx().
	'i.e: A MyGameEngine class can extend RenderWindow and override FrameDraw() and add specific features, leaving OnDraw() alone, as long as it is called somewhere.
	
	Protected
	
	Method WindowStart() Virtual
		OnStart()
	End
	
	Method FrameUpdate() Virtual
		OnUpdate()
	End
	
	Method FrameDraw() Virtual
		OnDraw()
	End
	
	Method DebugInfo() Virtual
		Echo( "Window resolution: " + Frame.Width + ", " + Frame.Height )
		Echo( "Virtual resolution: " + Width + ", " + Height )
		Echo( "Mouse:" + Mouse.x + "," + Mouse.y )
		Echo( "Camera:" + Int( camera.X ) + "," + Int( camera.Y ) )
		Echo( "Layout: " + Layout )
		If renderToTexture
			Echo( "renderToTexture = True" )
		Else
			Echo( "renderToTexture = False" )
		End
		Echo( "Camera: " + camera.ToString() )
		Echo( "FPS: " + FPS )
	End
	
	Method SelectCanvas()
		If renderToTexture
			canvas = _textureCanvas
		Else
			canvas = _windowCanvas
		End
		canvas.Clear( bgColor )
	End
	
	'**************************************************** Virtual Methods ****************************************************
	Public
	
	Method OnStart() Virtual
	End
	
	Method OnUpdate() Virtual
	End
	
	Method OnDraw() Virtual
	End

	'**************************************************** Static functions ****************************************************
	
	Function Echo( text:String )
		_echoStack.Push( text )
	End
	
End

