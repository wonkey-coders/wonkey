Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

#Import "assets/"

Class MyWindow Extends Window

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		Print "AssetsDir()=~q"+AssetsDir()+"~q"
		
#If __DESKTOP_TARGET__
		Print "DesktopDir()=~q"+DesktopDir()+"~q"
		
		Print "HomeDir()=~q"+HomeDir()+"~q"
#endif
		
#If __MOBILE_TARGET__
		Print "InternalDir()=~q"+InternalDir()+"~q"
		DeleteFile( "internal::test.txt" )
		SaveString( "Some Test Internal Text!","internal::test.txt" )
		Print "LoadString(~qinternal::test.txt~q)=~q"+LoadString( "internal::test.txt" )+"~q"
		
		Print "ExternalDir()=~q"+ExternalDir()+"~q"
		DeleteFile( "external::test.txt" )
		SaveString( "Some Test External Text!","external::test.txt" )
		Print "LoadString(~qexternal::test.txt~q)=~q"+LoadString( "external::test.txt" )+"~q"
		
#endif
	
		Print "LoadDir(~qasset::~q):"
		PrintDir( "asset::" ) 
		
		Print "LoadDir(AssetsDir())"
		PrintDir( AssetsDir() )
		
		Print "RealPath(AssetsDir())=~q"+RealPath( AssetsDir() )+"~q"
		
		Print "RealPath(~qasset::~q)=~q"+RealPath( "asset::" )+"~q"
		
	End
	
	Method PrintDir( dir:String,indent:String=" " )

		For Local file:=Eachin LoadDir( dir )
			Print indent+"file=~q"+file+"~q size="+GetFileSize( dir+file )+" type="+Int( GetFileType( dir+file ) )
		Next
	End		

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
	
		canvas.DrawText( "Hello World!",Width/2,Height/2,.5,.5 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
