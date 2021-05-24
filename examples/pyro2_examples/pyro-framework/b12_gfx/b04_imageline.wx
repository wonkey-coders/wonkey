#Import "../assets/greenlaser.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"

Using std..
Using mojo..
Using pyro.framework..

Global virtualResolution:=New Vec2i( 1024,768 )																				' Backing global for virtual resolution.

Class PyroExample Extends Window

	Field laserImage:Image

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		ClearColor=Color.Black

		laserImage=Image.Load( "asset::greenlaser.png" )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		DrawLine( canvas,laserImage,MouseLocation,virtualResolution/2,False )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",1024,768 )
	
	App.Run()

End
