
Namespace stargate

Const NUM_STARS:=100

Struct Star
	Field color:Vec3f
	Field x:Float
	Field y:Float
End

Global stars:Star[]

Global Mountains:Float[]

Global MiniMountains:Image

Function InitPlanet()

	Mountains=New Float[PlanetWidth]
	
	Local h:=160
	Local y0:=PlanetHeight-h,y1:=PlanetHeight-16
	
	Local y:=y1,dy:=-1
	
	For Local x:=0 Until PlanetWidth-h
	
		Mountains[x]=y-1
		
		Local t:=.99
		If x>PlanetWidth/2 t=.9
		
		If Rnd()>t
			dy=-dy
		Endif
		
		y+=dy
		If y<y0 Or y>y1
			dy=-dy
			y+=dy
		Endif
	Next
	
	For Local x:=PlanetWidth-h Until PlanetWidth
		Mountains[x]=y-1
		If y<y1 y+=1
	Next
	
	'create some stars
	
	stars=New Star[NUM_STARS]
	For Local i:=0 Until NUM_STARS
		stars[i].color=New Vec3f( Rnd(),Rnd(),Rnd() ).Normalize()
		stars[i].x=Rnd( ViewWidth )
		stars[i].y=Rnd( ViewHeight )
	Next
	
	'create mini mountains
	
	Local pm:=New Pixmap( ScannerWidth*2,ScannerHeight )
	
	pm.ClearARGB( $ff000000 )
	
	For Local x:=0 Until ScannerWidth
	
		Local y:=Mountains[x*PlanetWidth/ScannerWidth]
		
		y=Clamp( y*ScannerHeight/PlanetHeight,0.0,Float(ScannerHeight-1) )
		
		pm.SetPixelARGB( x,y,$ff884400 )
		pm.SetPixelARGB( x+ScannerWidth,y,$ff884400 )
	Next
	
	MiniMountains=New Image( pm )
	
End

Function RenderPlanet( canvas:Canvas )

	Local x0:=PlanetX( 0 )
	
'	canvas.RenderDrawList( stars,-tx,0 )

	canvas.Color=New Color( .75,.25,0 )
	
	For Local x:=0 Until ViewWidth
		canvas.DrawRect( x,Mountains[ WrapX( x0+x )],2,2 )
	Next
	
	Local tx:=x0*ViewWidth/PlanetWidth
	
	For Local i:=0 Until NUM_STARS
	
		Local rx:=stars[i].x-tx
		If rx<0 rx+=ViewWidth
		
		Local ry:=stars[i].y
		If ry>=Mountains[ PlanetX(rx) ] Continue
		
		canvas.Color=New Color( stars[i].color.x,stars[i].color.y,stars[i].color.z )
		canvas.DrawPoint( rx,ry )
	Next
	
	canvas.Color=Color.White
	
End
