
Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	Field gesturing:Bool
	
	Field g0:AffineMat3f
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
	End
	
	Method GestureMatrix:AffineMat3f( p0:Vec2f,p1:Vec2f )
	
		Local d:=p1-p0,r:=-ATan2( d.y,d.x ),s:=d.Length
		
		Return New AffineMat3f().Translate( p0 ).Rotate( r ).Scale( s,s )
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		Local gmatrix:=New AffineMat3f
		
		If Not gesturing And Touch.FingerDown( 0 ) And Touch.FingerDown( 1 )
		
			'begin gesturing
			g0=-GestureMatrix( Touch.FingerLocation( 0 ),Touch.FingerLocation( 1 ) )
			
			gesturing=True
		
		Endif
		
		If gesturing And Touch.FingerDown( 0 ) And Touch.FingerDown( 1 )
			
			'gesturing...
			gmatrix=GestureMatrix( Touch.FingerLocation( 0 ),Touch.FingerLocation( 1 ) ) * g0
		
		Else If gesturing
		
			'end gesturing
			gesturing=False
		
		Endif
		
		canvas.PushMatrix()
		
		canvas.Matrix=gmatrix
		
		For Local i:=0 Until 8
			For Local j:=0 Until 8
				canvas.Color= (i~j)&1 ? Color.Yellow Else Color.Grey
				canvas.DrawRect( New Recti( i*Width/8,j*Height/8,(i+1)*Width/8,(j+1)*Height/8 ) )
			Next
		Next
		
		canvas.PopMatrix()
		
		canvas.Color=Color.White
		
		canvas.Scale( 2,2 )
		
		For Local i:=0 Until 10
		
			canvas.DrawText( "Finger "+i+": down="+Int( Touch.FingerDown(i) )+", location="+Touch.FingerLocation(i)+", pressure="+Touch.FingerPressure(i),0,i*canvas.Font.Height )
		
		Next
		
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
