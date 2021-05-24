#Import "../assets/monkey.png"
#Import "../assets/monkey.txt"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"															' Import pyro framework.

Using std..
Using mojo..
Using pyro.framework..

Class PyroExample Extends Window

	Field monkey:Image[]
	Field frame:=0.0

	Method New()

		Local image:=Image.Load( "asset::monkey.png" )								' PNG file created with texture packer ( from a collection of PNG files ).
		Local data:=LoadString( "asset::monkey.txt" )								' Data file created with texture packer.

		monkey=TexturePacker.GrabImages( image,data )
		
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		canvas.DrawImage( monkey[frame],0,0 )

		frame+=.1
		frame=frame Mod monkey.Length

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
