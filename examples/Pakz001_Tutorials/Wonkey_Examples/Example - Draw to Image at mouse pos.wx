#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class MyWindow Extends Window

	Field image:Image
	
	Field icanvas:Canvas	

	Method New()
		image=New Image( 256,256,TextureFlags.Mipmap|TextureFlags.Dynamic )
		image.Handle=New Vec2f( 0,0 )
		icanvas=New Canvas( image )


		icanvas.Color=Color.White
		icanvas.DrawText( "This way up!",icanvas.Viewport.Width/2,0,.5,0 )
		icanvas.Flush()

	End Method
	
	Method OnRender( canvas:Canvas ) Override

		App.RequestRender()

		canvas.DrawImage( image,App.MouseLocation.x,App.MouseLocation.y,0,.5,.5 )
		
		canvas.DrawText( "Here!",0,0 )
	
	End Method	
	
	Method OnKeyEvent( event:KeyEvent ) Override
	
		Select event.Type
			Case EventType.KeyDown
			Select event.Key
				Case Key.Escape
			    instance.Terminate()
			End Select
		End Select		
	End Method
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End function
