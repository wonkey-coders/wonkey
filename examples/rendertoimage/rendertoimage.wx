
Namespace test

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

#Import "assets/spaceship.png"

'A dynamic image has its contents updated frequently so doesn't need to be managed in case of graphics device resets.
'
Const Dynamic:=False'True

Class MyWindow Extends mojo.app.Window

	Field image:Image
	
	Field icanvas:Canvas

	Method New()
	
		image=New Image( 256,256,PixelFormat.RGBA8,Dynamic ? TextureFlags.Dynamic Else Null )
		
		image.Texture.Flags|=TextureFlags.Filter
		
		image.Handle=New Vec2f( .5,.5 )
		
		icanvas=New Canvas( image )
		
		If Not Dynamic RenderImage()
	End
	
	Method RenderImage()
	
		'render to image...
		For Local x:=0 Until 16
			For Local y:=0 Until 16
				If (x~y)&1
					icanvas.Color=New Color( Sin( Millisecs()*.01 )*.5+.5,Cos( Millisecs()*.02 )*.5+.5,.5 )
				Else
					icanvas.Color=Color.Yellow
				Endif
				icanvas.DrawRect( x*16,y*16,16,16 )
			Next
		Next
		
		icanvas.Color=Color.White
		
		icanvas.DrawText( "This way up!",icanvas.Viewport.Width/2,0,.5,0 )
		
		icanvas.Flush()
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		If Dynamic RenderImage()

		Global rot:=0.0
		rot+=.001
		
		canvas.DrawImage( image,App.MouseLocation.x,App.MouseLocation.y,rot )
		
		canvas.DrawText( "Here!",0,0 )
	End
	
	Method OnKeyEvent( event:KeyEvent ) Override
	
		Select event.Type
		Case EventType.KeyDown
			Select event.Key
			Case Key.Space
				Print "Invalidating graphics!"
				mojo.graphics.glutil.glGraphicsSeq+=1
			End
		End
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
