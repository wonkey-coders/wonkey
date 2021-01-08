
Namespace mojo3d

Class RayCastResult

	Field time:Float
	Field body:RigidBody
	Field point:Vec3f
	Field normal:Vec3f
	
	Method New()
	End
	
	Method New( btresult:btCollisionWorld.ClosestRayResultCallback Ptr )
		time=btresult->m_closestHitFraction
		body=Cast<RigidBody>( btresult->m_collisionObject.getUserPointer() )
		point=btresult->m_hitPointWorld
		normal=btresult->m_hitNormalWorld
	End
	
	Method New( btresult:btCollisionWorld.ClosestConvexResultCallback Ptr )
		
		Local castFrom:=Cast<Vec3f>( btresult->m_convexFromWorld )
		Local castTo:=Cast<Vec3f>( btresult->m_convexToWorld )
		
		time=btresult->m_closestHitFraction
		body=Cast<RigidBody>( btresult->m_hitCollisionObject.getUserPointer() )
		point=(castTo-castFrom) * btresult->m_closestHitFraction + castFrom
		normal=btresult->m_hitNormalWorld
	End
	
End

