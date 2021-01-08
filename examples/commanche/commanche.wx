
'// Commanche Voxel for Monkey2 by GW, Original code by Sebastian Macke

#Import "<std>"
#Import "<mojo>"

#Import "assets/C1W.png"
#Import "assets/D1.png"

Using std..
Using mojo..

Const WIDTH:Int =512
Const HEIGHT:Int =256
Const MAPW:Int = 1024
Const MAPH:Int = 1024

Global Cmap:Pixmap
Global Dmap:Pixmap
Global PmapDest:Pixmap
Global image:Image
Global depth:Float = 400
Global Camera:tCamera 

Class tCamera
	Field x:Float = 512	 	'// x position on the map
	Field y:Float = 800 	'// y position on the map
	Field height:Float = 78 '// height of the camera
	Field angle:Float = 0 	'// direction of the camera
	Field v:Float = -100	'// horizon position (look up And down)
End Class

'-----------------------------------------------------------------------------------------------------------
Class MyWindow Extends Window
	Field pm:Pixmap
	Field img:Image
	'-----------------------------------------------------------------------------------------------------------
	Method New(title : String  , width : Int , height : Int  , flags : WindowFlags =Null)
		Super.New(title,width,height,flags)
		Camera = New tCamera
'		Print "Loading map"
		LoadMap()
		ClearColor=Color.Black
		SwapInterval=0
	End Method
	'-----------------------------------------------------------------------------------------------------------
	Method OnRender( canvas:Canvas ) Override
		PmapDest.Clear(Color.Black)
		App.RequestRender()
		UpdateCamera()
		UpdateSim()
		
		image.Texture.PastePixmap( PmapDest,0,0 )
		canvas.DrawRect( 0,0,WIDTH*2,HEIGHT*2,image )

		canvas.DrawText( App.FPS,10,10 )
	End
	'-----------------------------------------------------------------------------------------------------------
	Method LoadMap:Void()
'		Print "in Loadmap"	
		Dmap = Pixmap.Load("asset::D1.png",PixelFormat.RGBA32)
		Cmap = Pixmap.Load("asset::C1W.png",PixelFormat.RGBA32)
		
		If Not Dmap Then Print "no Dmap!"
		If Not Cmap Then Print "no Cmap!"
'		Print "dmap=" + Dmap.Width + " " + Dmap.Height
		PmapDest = New Pixmap(WIDTH, HEIGHT,PixelFormat.RGBA32)
		image=New Image( WIDTH,HEIGHT,TextureFlags.Dynamic )
'		Print PmapDest.Width + "##" 
	End Method
	'-----------------------------------------------------------------------------------------------------------
	Method UpdateCamera()
		If Keyboard.KeyDown(Key.A|Key.Raw)
			Camera.angle+= 2* .0174532925
		Endif
		If Keyboard.KeyDown(Key.S|Key.Raw)
			Camera.x+=4 * Sin(Camera.angle)
			Camera.y+=4 * Cos(Camera.angle)
		Endif	
		If Keyboard.KeyDown(Key.D|Key.Raw)
			Camera.angle-= 2* .0174532925
		Endif	
		If Keyboard.KeyDown(Key.W|Key.Raw)
			Camera.x-=4 * Sin(Camera.angle)
			Camera.y-=4 * Cos(Camera.angle)
		Endif	
		If Keyboard.KeyDown(Key.R|Key.Raw)
			Camera.height+=2
		Endif
		If Keyboard.KeyDown(Key.F|Key.Raw)
			Camera.height-=2
		Endif	
		If Keyboard.KeyDown(Key.Q|Key.Raw)
			Camera.v+=2
		Endif
		If Keyboard.KeyDown(Key.E|Key.Raw)
			Camera.v-=2
		Endif
	End Method
	'-----------------------------------------------------------------------------------------------------------
	Method UpdateSim()
		Local sinang:Float = Sin(Camera.angle)
		Local cosang:Float = Cos(Camera.angle)
		Local y3d:Float = -depth * 1.5
	
		For Local i:Int = 0 Until WIDTH
			Local x3d:Float = (i - WIDTH / 2) * 1.5 * 1.5
			Local rotx:Float = cosang * x3d + sinang * y3d
			Local roty:Float = -sinang * x3d + cosang * y3d		
			Raycast(i, Camera.x, Camera.y, rotx + Camera.x, roty + Camera.y, y3d / Sqrt(x3d * x3d + y3d * y3d))
		Next
	End Method
	'-----------------------------------------------------------------------------------------------------------
	Method Raycast(line:Int, x1:Float, y1:Float, x2:Float, y2:Float, d:Float)
		Local dx:Float = x2 - x1
		Local dy:Float = y2 - y1
		Local r:Float = Sqrt(dx * dx + dy * dy)
		dx = dx / r
		dy = dy / r
		Local ymin:Float = 256
		
		For Local i:Int = 1 Until r - 20
			x1+=dx
			y1+=dy
			Local h:Int = Camera.height - Int(((Dmap.GetPixelARGB(Int((x1)) & 1023, Int((y1)) & 1023)) Shr 16) & 255)
			Local y3:Float = Abs(d) * i
			Local z3:Int = h / y3 * 100 - Camera.v
			
			If (z3 < 0) Then z3 = 0
			If(z3 < HEIGHT - 1) 
				Local col:= Cmap.GetPixelARGB(Int(x1) & 1023, Int(y1) & 1023)
				For Local k:Int = z3 Until ymin
					PmapDest.SetPixelARGB( line,k,col )
				Next
				If (ymin > z3) Then ymin = (z3)
			Endif
		Next
	End Method
End
'-----------------------------------------------------------------------------------------------------------
Function Main()

	New AppInstance
	
	'Show raw key mappings...	
	Print "W->"+Keyboard.KeyName( Key.W | Key.Raw )
	Print "A->"+Keyboard.KeyName( Key.A | Key.Raw )
	Print "S->"+Keyboard.KeyName( Key.S | Key.Raw )
	Print "D->"+Keyboard.KeyName( Key.D | Key.Raw )
	
	New MyWindow("Commanche",WIDTH*2,HEIGHT*2)

	App.Run()
End
