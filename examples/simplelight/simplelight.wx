
Namespace myapp

#Import "<std>"
#Import "<mojo>"

#Import "Slate Tiles II_D.png"
#Import "Slate Tiles II_N.png"
#Import "Slate Tiles II_S.png"
#Import "cone_orange.png"
#Import "Monkey2-logo-48.png"

Using std..
Using mojo..

Class MyWindow Extends Window

	Field _floor:Image
	
	Field _light:Image
	
	Field _logo:Image
	
	Method New()
		Super.New( "Test Window",640,480,WindowFlags.Resizable )
	
		ClearColor=Color.Black
	
		_floor=Image.LoadBump( "asset::Slate Tiles II_D.png","asset::Slate Tiles II_N.png","asset::Slate Tiles II_S.png",.75,True )
		
		_light=Image.LoadLight( "asset::cone_orange.png" )
		
		_light.Handle=New Vec2f( .5,0 )
		
		_light.Scale=New Vec2f( .5,.5 )
	
		_logo=Image.Load( "asset::Monkey2-logo-48.png" )
		
		_logo.Handle=New Vec2f( .5 )
		
		_logo.ShadowCaster=New ShadowCaster( _logo.Width/2,20 )

	End
	
	Method OnRender( canvas:Canvas ) Override
	
		Global viewRot:=0.0
		
		viewRot+=.001
		canvas.Translate( Width/2,Height/2 )
		canvas.Scale( Sin( viewRot*3 )*.25+1.25,Cos( viewRot*5 )*.25+1.25 )
		canvas.Rotate( viewRot )
		canvas.Translate( -Width/2,-Height/2 )
		
		Local rmouse:=-canvas.Matrix * Mouse.Location
		
		Global lightRot:=0.0
		lightRot+=.02
	
		App.RequestRender()
		
		canvas.AmbientLight=Color.DarkGrey
		
		canvas.BeginLighting()
		
		canvas.AddLight( _light,rmouse.X,rmouse.Y,lightRot )
		canvas.AddLight( _light,rmouse.X,rmouse.Y,lightRot+Pi )
		canvas.AddLight( _light,rmouse.X,rmouse.Y,lightRot+Pi/2 )
		canvas.AddLight( _light,rmouse.X,rmouse.Y,lightRot+Pi+Pi/2 )
		
		For Local x:=0 Until Width Step _floor.Width

			For Local y:=0 Until Height Step _floor.Height

				canvas.DrawImage( _floor,x,y )

			Next

		Next
		
		For Local an:=0.0 Until TwoPi Step TwoPi/8.0
		
			canvas.DrawImage( _logo,Width/2+Cos( an ) * Width/4,Height/2 + Sin( an ) * Height/4 )
		
		Next
		
		canvas.EndLighting()
		
		canvas.DrawText( Floor( App.FPS+.5 ),Width/2,0,.5,0 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
