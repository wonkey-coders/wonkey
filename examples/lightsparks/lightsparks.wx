
Namespace myapp

#Import "<std>"
#Import "<mojo>"

#Import "Slate Tiles II_D.png"
#Import "Slate Tiles II_N.png"
#Import "Slate Tiles II_S.png"
#Import "pointlight_light.png"

Using std..
Using mojo..

Class Spark

	Field x:Float
	Field y:Float
	Field vx:Float
	Field vy:Float
	Field light:Image
	Field color:Color

	Method New( x:Float,y:Float,light:Image )
		Self.x=x
		Self.y=y
		Self.light=light
		Self.color=New Color( Rnd(),Rnd()/2,Rnd()/4,1 )
		Local an:=Rnd() * TwoPi
		Local r:=Rnd( 1,5 )
		Self.vx=Cos( an ) * r
		Self.vy=Sin( an ) * r
	End
	
	Method Render( canvas:Canvas )
		vy+=.1
		x+=vx
		y+=vy
		canvas.Color=color
		canvas.AddLight( light,x,y )
	End
End

Class MyWindow Extends Window

	Field _floor:Image
	
	Field _light:Image
	
	Field _spark:Image
	
	Field _sparks:=New Stack<Spark>
	
	Method New()
	
		ClearColor=Color.Black
	
		_floor=Image.LoadBump( "asset::Slate Tiles II_D.png","asset::Slate Tiles II_N.png","asset::Slate Tiles II_S.png",.5 )
		
		_light=Image.LoadLight( "asset::pointlight_light.png" )
		
		_light.Handle=New Vec2f( .5,.5 )
	
		_light.Scale=New Vec2f( 3,3 )
		
		_spark=New Image( _light,_light.Rect )
		
		_spark.Scale=New Vec2f( .5,.5 )
		
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		canvas.BeginLighting()
	
		If Mouse.ButtonDown( MouseButton.Left ) 
'			For Local i:=0 Until 50
				_sparks.Push( New Spark( Mouse.X,Mouse.Y,_spark ) )
'			Next
		Endif
		
		Local put:=0
		For Local spark:=Eachin _sparks
			spark.Render( canvas )
			If spark.y>Height+_spark.Radius Continue
			_sparks[put]=spark
			put+=1
		Next
		_sparks.Resize( put )
		
		canvas.Color=Color.White
		
		canvas.AddLight( _light,Mouse.X,Mouse.Y )
		
		For Local x:=0 Until Width Step _floor.Width

			For Local y:=0 Until Height Step _floor.Height

				canvas.DrawImage( _floor,x,y )

			Next

		Next
		
		canvas.EndLighting()
		
		canvas.DrawText( Round( App.FPS ),Width/2,0,.5,0 )
		
		GCCollect()
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
