
Namespace mojo3d

#Import "native/collisiondetect.cpp"
#Import "native/collisiondetect.h"

Extern Private

Function initCollisions( world:btDynamicsWorld )
Function resetCollisions()
Function getNumCollisions:Int()
Function getCollisions:Void Ptr Ptr()

Public

Class World
	
	Method New( scene:Scene )
		
		_scene=scene
		
		Local broadphase:=New btDbvtBroadphase()
		
		Local config:=New btDefaultCollisionConfiguration()

		Local dispatcher:=New btCollisionDispatcher( config )
		
		Local solver:=New btSequentialImpulseConstraintSolver()
		
		_btworld=New btDiscreteDynamicsWorld( dispatcher,broadphase,solver,config )

'	//from BenchmarkDemo.cpp!		
'	///the following 3 lines increase the performance dramatically, with a little bit of loss of quality
'	m_dynamicsWorld->getSolverInfo().m_solverMode |=SOLVER_ENABLE_FRICTION_DIRECTION_CACHING; //don't recalculate friction values each frame
'	m_dynamicsWorld->getSolverInfo().m_numIterations = 5; //few solver iterations 
'	//m_defaultContactProcessingThreshold = 0.f;//used when creating bodies: body->setContactProcessingThreshold(...);
		
		initCollisions( _btworld )

		Gravity=New Vec3f( 0,-9.81,0 )
	End
	
	Property Scene:Scene()
	
		Return _scene
	End

	Property Gravity:Vec3f()
	
		Return _btworld.getGravity()
		
	Setter( gravity:Vec3f )
	
		_btworld.setGravity( gravity )
	End
	
	Method RayCast:RayCastResult( rayFrom:Vec3f,rayTo:Vec3f,collisionMask:Int )
		
		Local btresult:=New btCollisionWorld.ClosestRayResultCallback( rayFrom,rayTo )
		
		btresult.m_collisionFilterGroup=collisionMask
		btresult.m_collisionFilterMask=collisionMask
		
		_btworld.rayTest( rayFrom,rayTo,Cast<btCollisionWorld.RayResultCallback Ptr>( Varptr btresult ) )
		
		If Not btresult.hasHit() Return Null
		
		Return New RayCastResult( Varptr btresult )
	End
	
	Method ConvexSweep:RayCastResult( collider:ConvexCollider,castFrom:AffineMat4f,castTo:AffineMat4f,collisionMask:Int )
		
		Local btresult:=New btCollisionWorld.ClosestConvexResultCallback( castFrom.t,castTo.t )

		btresult.m_collisionFilterGroup=collisionMask
		btresult.m_collisionFilterMask=collisionMask
		
		_btworld.convexSweepTest( Cast<btConvexShape>( collider.Validate() ),castFrom,castTo,Cast<btCollisionWorld.ConvexResultCallback Ptr>( Varptr btresult ),0 )
		
		If Not btresult.hasHit() Return Null
		
		Return New RayCastResult( Varptr btresult )
	End
	
	Method ConvexSweep:RayCastResult( collider:ConvexCollider,castFrom:Vec3f,castTo:Vec3f,collisionMask:Int )
		
		Return ConvexSweep( collider,AffineMat4f.Translation( castFrom ),AffineMat4f.Translation( castTo ),collisionMask )
	End

	Method Update( elapsed:Float )
		
		resetCollisions()
		
		_btworld.stepSimulation( elapsed,_scene.MaxSubSteps,1.0/_scene.UpdateRate )
		
		Local n:=getNumCollisions()
		
		Local p:=getCollisions()
		
		For Local i:=0 Until n
			
			Local body0:=Cast<RigidBody>( p[i*2] )
			Local body1:=Cast<RigidBody>( p[i*2+1] )
			
			body0.Collided( body1 )
			body1.Collided( body0 )
		Next
		
		resetCollisions()
	End
	
	Property btWorld:btDynamicsWorld()
		
		Return _btworld
	End
	
	Internal
	
	Method Add( body:RigidBody )
		
'		Print "World.Add( RigidBody )"
		
		_bodies.Add( body )
		
		Local btbody:=body.btBody
		
		btbody.setUserPointer( Cast<Void Ptr>( body ) )
		
'		btbody.setWorldTransform( body.Entity.Matrix )
		
		_btworld.addRigidBody( btbody,body.CollisionGroup,body.CollisionMask )
	End
	
	Method Remove( body:RigidBody )
		
'		Print "World.Remove( RigidBody )"
		
		Local btbody:=body.btBody
		
		_btworld.removeRigidBody( btbody )
		
		body.btBody.setUserPointer( Null )

		_bodies.Remove( body )
	End
	
	Private
	
	Field _scene:Scene
	
	Field _btworld:btDynamicsWorld
	
	Field _bodies:=New Stack<RigidBody>

End
