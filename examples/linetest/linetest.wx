
Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		ClearColor=Color.Black
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		Local w:=Width
		Local h:=Height
		
		canvas.Color=Color.Red
		canvas.DrawLine( 0,0,w-1,0 )
		canvas.DrawLine( w-1,0,w-1,h-1 )
		canvas.DrawLine( w-1,h-1,0,h-1 )
		canvas.DrawLine( 0,h-1,0,0 )
		
		canvas.LineWidth=2
		canvas.LineSmoothing=True

		canvas.Color=Color.Orange
		canvas.DrawLine( 2,2,w-3,2 )
		canvas.DrawLine( w-3,2,w-3,h-3 )
		canvas.DrawLine( w-3,h-3,2,h-3 )
		canvas.DrawLine( 2,h-3,2,2 )

		SeedRnd( 1234 )
		For Local i:=0 Until 100
			canvas.LineWidth=Rnd( 2,5 )
			canvas.Color=New Color( Rnd(1),Rnd(.75),Rnd(.5) )
			canvas.DrawLine( Int( Rnd(w) ),Int( Rnd(h) ),Int( Rnd(w) ),Int( Rnd(h) ) )
		Next
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
