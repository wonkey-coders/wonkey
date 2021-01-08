
Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Const Test:="

Test of extended chars:

Ã¦ = &aelig;
Ã¸ = &oslash;
Ã¥ = &aring;
Ã† = &AElig;
Ã˜ = &Oslash;
Ã… = &Aring;

élégant

"

Class MyWindow Extends Window

	Field page:Int

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags|WindowFlags.HighDPI )
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		If Keyboard.KeyHit( Key.Right )
			page=Min( page+1,255 )
		Else If Keyboard.KeyHit( Key.Left )
			page=Max( page-1,0 )
		End
		
		canvas.DrawText( "page="+page+" (arrows to change)",32,8 )
		
		For Local y:=0 Until 16
			For Local x:=0 Until 16
				canvas.DrawText( String.FromChar( y*16+x+page*256 ),x*16+32,y*16+32 )
			Next
		Next
		
		Local y:=0
		For Local line:=Eachin Test.Split( "~n" )
			canvas.DrawText( line,Width/2,y )
			y+=16
		Next
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
