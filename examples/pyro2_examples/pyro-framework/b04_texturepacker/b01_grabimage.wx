#Import "../assets/monkey.png"
#Import "../assets/monkey.txt"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"															' Import pyro framework.

Using std..
Using mojo..
Using pyro.framework..

Class PyroExample Extends Window

	Field monkey:=New Image[23]
	Field frame:=0.0

	Method New()

		Local image:=Image.Load( "asset::monkey.png" )								' PNG file created with texture packer ( from a collection of PNG files ).
		Local data:=LoadString( "asset::monkey.txt" )								' Data file created with texture packer.

		monkey[0]=TexturePacker.GrabImage( image,data,"walk0000.png" )
		monkey[1]=TexturePacker.GrabImage( image,data,"walk0001.png" )
		monkey[2]=TexturePacker.GrabImage( image,data,"walk0002.png" )
		monkey[3]=TexturePacker.GrabImage( image,data,"walk0003.png" )
		monkey[4]=TexturePacker.GrabImage( image,data,"walk0004.png" )
		monkey[5]=TexturePacker.GrabImage( image,data,"walk0005.png" )
		monkey[6]=TexturePacker.GrabImage( image,data,"walk0006.png" )
		monkey[7]=TexturePacker.GrabImage( image,data,"walk0007.png" )
		monkey[8]=TexturePacker.GrabImage( image,data,"walk0008.png" )
		monkey[9]=TexturePacker.GrabImage( image,data,"walk0009.png" )
		monkey[10]=TexturePacker.GrabImage( image,data,"walk0010.png" )
		monkey[11]=TexturePacker.GrabImage( image,data,"walk0011.png" )
		monkey[12]=TexturePacker.GrabImage( image,data,"walk0012.png" )
		monkey[13]=TexturePacker.GrabImage( image,data,"walk0013.png" )
		monkey[14]=TexturePacker.GrabImage( image,data,"walk0014.png" )
		monkey[15]=TexturePacker.GrabImage( image,data,"walk0015.png" )
		monkey[16]=TexturePacker.GrabImage( image,data,"walk0016.png" )
		monkey[17]=TexturePacker.GrabImage( image,data,"walk0017.png" )
		monkey[18]=TexturePacker.GrabImage( image,data,"walk0018.png" )
		monkey[19]=TexturePacker.GrabImage( image,data,"walk0019.png" )
		monkey[20]=TexturePacker.GrabImage( image,data,"walk0020.png" )
		monkey[21]=TexturePacker.GrabImage( image,data,"walk0021.png" )
		monkey[22]=TexturePacker.GrabImage( image,data,"walk0022.png" )
		
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
