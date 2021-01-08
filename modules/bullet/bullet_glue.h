
#ifndef WX_BULLET_H
#define WX_BULLET_H

#include "btBulletDynamicsCommon.h"

namespace wxBullet{

	btVector3 calculateLocalInertia( btCollisionShape *self,btScalar mass );
	
	btTransform getWorldTransform( btMotionState *self );
	
	struct Point2PointConstraint : public btPoint2PointConstraint{
		
		Point2PointConstraint(btRigidBody* rbA,btRigidBody* rbB, const btVector3& pivotInA,const btVector3& pivotInB):
		btPoint2PointConstraint(*rbA,*rbB,pivotInA,pivotInB){}

		Point2PointConstraint(btRigidBody* rbA,const btVector3& pivotInA):
		btPoint2PointConstraint(*rbA,pivotInA){}
	};

	struct HingeConstraint : public btHingeConstraint{
			
		HingeConstraint(btRigidBody *rbA, btRigidBody *rbB, const btVector3 &pivotInA, const btVector3 &pivotInB, const btVector3 &axisInA, const btVector3 &axisInB, bool useReferenceFrameA=false):
		btHingeConstraint(*rbA, *rbB, pivotInA, pivotInB, axisInA, axisInB, useReferenceFrameA){}
 
		HingeConstraint(btRigidBody *rbA, const btVector3 &pivotInA, const btVector3 &axisInA, bool useReferenceFrameA=false):
		btHingeConstraint(*rbA, pivotInA, axisInA, useReferenceFrameA){}
 
		HingeConstraint(btRigidBody *rbA, btRigidBody *rbB, const btTransform &rbAFrame, const btTransform &rbBFrame, bool useReferenceFrameA=false):
		btHingeConstraint(*rbA, *rbB, rbAFrame, rbBFrame, useReferenceFrameA){}
 
		HingeConstraint(btRigidBody *rbA, const btTransform &rbAFrame, bool useReferenceFrameA=false):
		btHingeConstraint(*rbA, rbAFrame, useReferenceFrameA){}
	};
	
	struct SliderConstraint : public btSliderConstraint{

		SliderConstraint(btRigidBody *rbA, btRigidBody *rbB, const btTransform &frameInA, const btTransform &frameInB, bool useLinearReferenceFrameA):
		btSliderConstraint(*rbA,*rbB, frameInA, frameInB, useLinearReferenceFrameA){}
 
		SliderConstraint(btRigidBody *rbB, const btTransform &frameInB, bool useLinearReferenceFrameA):
		btSliderConstraint(*rbB, frameInB, useLinearReferenceFrameA){}
	};
	
	struct FixedConstraint : public btFixedConstraint{
		
		FixedConstraint(btRigidBody* rbA,btRigidBody* rbB, const btTransform& frameInA,const btTransform& frameInB):
		btFixedConstraint(*rbA,*rbB,frameInA,frameInB){}
	};
	
	struct MotionState : public btMotionState{
		
		virtual void setWorldTransform( btTransform *worldTrans ){
		}

		virtual void getWorldTransform( btTransform *worldTrans ){
		}

		virtual void setWorldTransform( const btTransform &worldTrans ){
			
			this->setWorldTransform( const_cast<btTransform*>( &worldTrans ) );
		}
				
		virtual void getWorldTransform( btTransform &worldTrans )const{
			
			const_cast<MotionState*>( this )->getWorldTransform( &worldTrans );
		}
	};
	
	struct DefaultMotionState : public btDefaultMotionState{

		DefaultMotionState(){
		}
		
 		DefaultMotionState( const btTransform &startTrans,const btTransform &centerOfMassOffset ):btDefaultMotionState( startTrans,centerOfMassOffset ){
 		}

		void setWorldTransform( btTransform *worldTrans ){
		
			btDefaultMotionState::setWorldTransform( *worldTrans );
		}

		void getWorldTransform( btTransform *worldTrans ){

			btDefaultMotionState::getWorldTransform( *worldTrans );
		}
	};
	
	void rayTest( btCollisionWorld *self,
		const btVector3 &rayFromWorld,
		const btVector3 &rayToWorld,
		btCollisionWorld::RayResultCallback *result );

	void convexSweepTest( btCollisionWorld *self,
		const btConvexShape *castShape,
		const btTransform &castFrom,
		const btTransform &castTo,
		btCollisionWorld::ConvexResultCallback *result,
		btScalar allowedCcdPenetration );
}

#endif
