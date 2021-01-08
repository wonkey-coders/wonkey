#rem

gnsh-bitmap font from opengameart.org:

https://opengameart.org/content/bitmap-font-0

#end

Namespace myapp

#Import "<std>"
#Import "<mojo>"

'simple image font
#Import "gnsh-bitmapfont-colour1.png"

'monochrome angel font
#Import "testfont.fnt"
#Import "testfont_0.png"

'fullcolor angel font
#Import "coolfont.fnt"
#Import "coolfont.png"

Using std..
Using mojo..

Class MyWindow Extends Window
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		'Example of loading a ttf font directly
'		Style.Font=FreeTypeFont.Load( "asset::fonts/DejaVuSans.ttf",32 )
		
		'Example of loading a simple image font where chars are 15x36
'		Style.Font=ImageFont.Load( "asset::gnsh-bitmapfont-colour1.png",15,36 )

		'Example of loading a monochrome angel font
'		Style.Font=AngelFont.Load( "asset::testfont.fnt" )

		'Example of loading a fullcolor angel font
		Style.Font=AngelFont.Load( "asset::coolfont.fnt" )
		
		ClearColor=Color.Blue	'so we can see nice drop shadow.
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		canvas.DrawText( "The Quick Brown Fox Jumps Over The Lazy Dog",0,0 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
