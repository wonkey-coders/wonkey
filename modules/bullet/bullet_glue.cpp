
#include "bullet_glue.h"

namespace wxBullet{

	btVector3 calculateLocalInertia( btCollisionShape *self,btScalar mass ){
		btVector3 v( 0,0,0 );
		self->calculateLocalInertia( mass,v );
		return v;
	}
	
	btTransform getWorldTransform( btMotionState *self ){
		btTransform t;
		self->getWorldTransform( t );
		return t;
	}

	void rayTest( btCollisionWorld *self,
		const btVector3 &rayFromWorld,
		const btVector3 &rayToWorld,
		btCollisionWorld::RayResultCallback *result ){
	
		self->rayTest( rayFromWorld,rayToWorld,*result );
	}
	
	void convexSweepTest( btCollisionWorld *self,
		const btConvexShape *castShape,
		const btTransform &castFrom,
		const btTransform &castTo,
		btCollisionWorld::ConvexResultCallback *result,
		btScalar allowedCcdPenetration ){
		
		self->convexSweepTest( castShape,castFrom,castTo,*result,allowedCcdPenetration );
	}
}
