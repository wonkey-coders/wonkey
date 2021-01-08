
Namespace stargate

#Import "stargatesprites.png"

#Import "Laser_Shoot5.wav"
#Import "Explosion6.wav"
#Import "Powerup8.wav"

Global sprites:Image

Function GrabImage:Image( x:Int,y:Int,w:Int,h:Int )

	Local image:=New Image( sprites,x,y,w,h )
	image.Handle=New Vec2f( .5,.5 )
	Return image
	
End

Function GrabAnim:Image[]( x:Int,y:Int,w:Int,h:Int,count:Int,x_pitch:Int )

	Local images:=New Image[count]

	For Local i:=0 Until count
		images[i]=GrabImage( x,y,w,h )
		images[i].Handle=New Vec2f( .5,.5 )
		x+=x_pitch
	Next
	
	Return images
End

Function InitAssets()

	sprites=Image.Load( "asset::stargatesprites.png" )

End
