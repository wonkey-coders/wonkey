
#Import "<std>"
#Import "<mojo>"
#Import "<chipmunk>"

#Import "chipmunkdebugger"

Using std..
Using mojo..
Using chipmunk..

Class HelloChipmunk Extends Window

	Field space:cpSpace
	Field ground:cpShape
	
	Field ballBody:cpBody
	Field ballShape:cpShape

	Field ballBody2:cpBody
	Field ballShape2:cpShape

	Field polyBody:cpBody
	Field polyShape:cpShape
	
	Field debugger:=New ChipmunkDebugger
	
	Method New()
	
		ClearColor=Color.Grey'Black

		'Create a new space and set its gravity to 100
		'		
		space=cpSpaceNew()
		space.Gravity=cpv( 0,100 )
		
		'Add a static line segment shape for the ground.
		'We'll make it slightly tilted so the ball will roll off.
		'We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
		'
		ground=cpSegmentShapeNew( space.StaticBody,cpv( -100,15 ),cpv( 100,-15 ),0 )
		ground.Friction=1
		ground.CollisionType=1
		space.AddShape( ground )
		
		Local tshape:=space.AddShape( cpSegmentShapeNew( space.StaticBody,cpv(-Width/2,Height/2-64),cpv(0,Height/2),0 ) )
		tshape.Friction=1
		tshape.CollisionType=1

		tshape=space.AddShape( cpSegmentShapeNew( space.StaticBody,cpv(0,Height/2),cpv(Width/2,Height/2-64),0 ) )
		tshape.Friction=1
		tshape.CollisionType=1
		
		'Now let's make a ball that falls onto the line and rolls off.
		'First we need to make a cpBody to hold the physical properties of the object.
		'These include the mass, position, velocity, angle, etc. of the object.
		'Then we attach collision shapes to the cpBody to give it a size and shape.
		
		Local mass:=1.0
		Local radius:=10.0
  
		'The moment of inertia is like mass for rotation
		'Use the cpMomentFor*() functions to help you approximate it.
		Local moment:=cpMomentForCircle( mass,0,radius,cpvzero )
		
		'The cpSpaceAdd*() functions return the thing that you are adding.
		'It's convenient to create and add an object in one line.
		ballBody=space.AddBody( cpBodyNew( mass,moment ) )
		ballBody.Position=cpv( 0,-100 )

		'Now we create the collision shape for the ball.
		'You can create multiple collision shapes that point to the same body.
		'They will all be attached to the body and move around to follow it.
		ballShape=space.AddShape( cpCircleShapeNew( ballBody,radius,cpvzero ) )
		ballShape.Friction=0.7
		ballShape.CollisionType=2

		ballBody2=space.AddBody( cpBodyNew( mass,moment ) )
		ballBody2.Position=cpv( 50,-100 )
		
		ballShape2=space.AddShape( cpCircleShapeNew( ballBody2,radius,cpvzero ) )
		ballShape2.Friction=0.7
		ballShape2.CollisionType=2
		
		'Now a pentagon...
		mass=0.3
		radius=30.0

		Local NUM_VERTS:=5
		Local verts:=New cpVect[NUM_VERTS]
		For Local it:=0 Until NUM_VERTS
			Local angle:=TwoPi * it / NUM_VERTS
			verts[it]=cpv( radius*Cos( angle ),radius*Sin( angle ) )
		Next

		moment=cpMomentForPoly( mass,NUM_VERTS,verts.Data,cpvzero,0.0 )

		polyBody=space.AddBody( cpBodyNew( mass,moment ) )
		polyBody.Position=cpv( 50.0,-190.0 )
				
		polyShape=space.AddShape( cpPolyShapeNew( polyBody,NUM_VERTS,verts.Data,cpTransformIdentity,0.0 ) )
		polyShape.Friction=0.03
		
		Local handler:=space.AddDefaultCollisionHandler()
		
		'Add collision handler...
		handler.beginFunc=Lambda:cpBool( arbiter:cpArbiter,space:cpSpace,data:cpDataPointer )

			Local a:cpShape,b:cpShape
			
			arbiter.GetShapes( Varptr a,Varptr b )
			
			Print "Collision! a="+a.CollisionType+", b="+b.CollisionType
			
			Return True
		End
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
	
		Const timeStep:=1.0/60.0
		
		space.StepTime( timeStep )
		
'		Local rot:=ballBody.Rotation
'		Local pos:=ballBody.Position
'		Local vel:=ballBody.Velocity
'		Print "ball rot="+ATan2( rot.y,rot.x )+", pos.x="+pos.x+", pos.y="+pos.y+", vel.x="+vel.x+", vel.y="+vel.y
		
		canvas.Translate( Width/2,Height/2 )
		
		debugger.DebugDraw( canvas,space )
	End
	
	Method Cleanup()	'Yeah, right!
		cpShapeFree( ballShape )
		cpBodyFree( ballBody )
		cpShapeFree( ground )
		cpSpaceFree( space )
	End

End

Function Main()

	New AppInstance
	
	New HelloChipmunk
	
	App.Run()
End
