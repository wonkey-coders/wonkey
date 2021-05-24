#Import "../assets/ship2.png"
#Import "../assets/crystal.png"
#Import "../assets/ship.txt"
#Import "../assets/crystal.txt"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"																					' Import pyro framework.

Using std..
Using mojo..
Using pyro.framework..

Global canvas:Canvas
Global collisionLayer:CollisionLayer<TestObject>
Global shipImage:Image
Global shipMask:Int[]
Global tileImage:Image
Global tileMask:Int[]
	
Class TestObject
	Field name:=""
End

Class PyroExample Extends Window

	Method New()

		shipImage=Image.Load( "asset::ship2.png" )
		tileImage=Image.Load( "asset::crystal.png" )

		shipImage.Handle=New Vec2f( .5,.5 )
		tileImage.Handle=New Vec2f( .5,.5 )

		collisionLayer=New CollisionLayer<TestObject>()								' Create a collision layer of 640 x 480 with an accuracy of 1 pixel.

		' Load the collision masks created with the editor
		shipMask=collisionLayer.Load( "asset::ship.txt" )
		tileMask=collisionLayer.Load( "asset::crystal.txt" )

		' Create some example objects
		Local t:TestObject

		t=New TestObject
		t.name="object 1"															' The Name field can be used to identify the object.
		collisionLayer.Draw( 330,100,t,tileMask )									' Draw objectt using tileMask on the layer.

		t=New TestObject
		t.name="object 2"
		collisionLayer.Draw( 330,300,t,tileMask )

		t=New TestObject
		t.name="object 3"
		collisionLayer.Draw( 200,200,t,shipMask )

	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		canvas.Clear( Color.Black )
		
		Local x:=App.MouseLocation.X
		Local y:=App.MouseLocation.Y

		Local o:=collisionLayer.Get( x,y,shipMask )									' Get Object from mouse location.
		If o canvas.DrawText( "Colliding with: "+o.name,0,0	 )						' Draw name of object.

		canvas.BlendMode=BlendMode.Additive
		
		If Keyboard.KeyDown( Key.Space )
			collisionLayer.Draw( canvas )
		Else
			canvas.DrawImage( tileImage,330,100 )
			canvas.DrawImage( tileImage,330,300 )
			canvas.DrawImage( shipImage,200,200 )
		Endif

		canvas.DrawImage( shipImage,x,y )											' Draw ship.

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
