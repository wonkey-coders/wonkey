
#If __TARGET__="android"

Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		Print "Hello World from permissions demo!"
		
		Local permissions:=New String[](
			"android.permission.INTERNET",
			"android.permission.ACCESS_NETWORK_STATE",
			"android.permission.READ_EXTERNAL_STORAGE",
			"android.permission.WRITE_EXTERNAL_STORAGE",
			"com.android.vending.BILLING" )
			
		For Local i:=0 Until permissions.Length
			Print "CheckPermission(~q"+permissions[i]+"~q)="+CheckPermission( permissions[i] )
		Next
		
		RequestPermissions( permissions,Lambda( results:int[] )
		
			If Not results
				Print "RequestPermissions cancelled"
				Return
			Endif
		
			For Local i:=0 Until results.Length
				If results[i] 
					Print "Permission granted for "+permissions[i] 
				Else
					Print "Permission NOT granted for "+permissions[i]
				Endif
			Next
			
		End )
		
	End

	Method OnRender( canvas:Canvas ) Override
	
		Global n:Int
		
		n+=1
	
		App.RequestRender()
	
		canvas.DrawText( "Hello World! n="+n,Width/2,Height/2,.5,.5 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

#Endif
