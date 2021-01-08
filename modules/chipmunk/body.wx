
Namespace chipmunk

#Import "chipmunk_glue.h"

Extern

'***** File: Chipmunk7/include/chipmunk/cpBody.h *****

Enum cpBodyType
End
Const CP_BODY_TYPE_DYNAMIC:cpBodyType
Const CP_BODY_TYPE_KINEMATIC:cpBodyType
Const CP_BODY_TYPE_STATIC:cpBodyType

Alias cpBodyVelocityFunc:Void( cpBody, cpVect, cpFloat, cpFloat )
Alias cpBodyPositionFunc:Void( cpBody, cpFloat )

Alias cpBodyShapeIteratorFunc:Void( cpBody, cpShape, Void Ptr )
Alias cpBodyConstraintIteratorFunc:Void( cpBody, cpConstraint, Void Ptr )
Alias cpBodyArbiterIteratorFunc:Void( cpBody, cpArbiter, Void Ptr )

Function cpBodyAlloc:cpBody(  )
Function cpBodyInit:cpBody( body:cpBody, mass:cpFloat, moment:cpFloat )
Function cpBodyNew:cpBody( mass:cpFloat, moment:cpFloat )
Function cpBodyNewKinematic:cpBody(  )
Function cpBodyNewStatic:cpBody(  )
Function cpBodyDestroy:Void( body:cpBody )
Function cpBodyFree:Void( body:cpBody )
Function cpBodyActivate:Void( body:cpBody )
Function cpBodyActivateStatic:Void( body:cpBody, filter:cpShape )
Function cpBodySleep:Void( body:cpBody )
Function cpBodySleepWithGroup:Void( body:cpBody, group:cpBody )
Function cpBodyIsSleeping:cpBool( body:cpBody )
Function cpBodyGetType:cpBodyType( body:cpBody )
Function cpBodySetType:Void( body:cpBody, type:cpBodyType )
Function cpBodyGetSpace:cpSpace( body:cpBody )
Function cpBodyGetMass:cpFloat( body:cpBody )
Function cpBodySetMass:Void( body:cpBody, m:cpFloat )
Function cpBodyGetMoment:cpFloat( body:cpBody )
Function cpBodySetMoment:Void( body:cpBody, i:cpFloat )
Function cpBodyGetPosition:cpVect( body:cpBody )
Function cpBodySetPosition:Void( body:cpBody, pos:cpVect )
Function cpBodyGetCenterOfGravity:cpVect( body:cpBody )
Function cpBodySetCenterOfGravity:Void( body:cpBody, cog:cpVect )
Function cpBodyGetVelocity:cpVect( body:cpBody )
Function cpBodySetVelocity:Void( body:cpBody, velocity:cpVect )
Function cpBodyGetForce:cpVect( body:cpBody )
Function cpBodySetForce:Void( body:cpBody, force:cpVect )
Function cpBodyGetAngle:cpFloat( body:cpBody )
Function cpBodySetAngle:Void( body:cpBody, a:cpFloat )
Function cpBodyGetAngularVelocity:cpFloat( body:cpBody )
Function cpBodySetAngularVelocity:Void( body:cpBody, angularVelocity:cpFloat )
Function cpBodyGetTorque:cpFloat( body:cpBody )
Function cpBodySetTorque:Void( body:cpBody, torque:cpFloat )
Function cpBodyGetRotation:cpVect( body:cpBody )
Function cpBodyGetUserData:cpDataPointer( body:cpBody )
Function cpBodySetUserData:Void( body:cpBody, userData:cpDataPointer )
Function cpBodySetVelocityUpdateFunc:Void( body:cpBody, velocityFunc:cpBodyVelocityFunc )
Function cpBodySetPositionUpdateFunc:Void( body:cpBody, positionFunc:cpBodyPositionFunc )
Function cpBodyUpdateVelocity:Void( body:cpBody, gravity:cpVect, damping:cpFloat, dt:cpFloat )
Function cpBodyUpdatePosition:Void( body:cpBody, dt:cpFloat )
Function cpBodyLocalToWorld:cpVect( body:cpBody, point:cpVect )
Function cpBodyWorldToLocal:cpVect( body:cpBody, point:cpVect )
Function cpBodyApplyForceAtWorldPoint:Void( body:cpBody, force:cpVect, point:cpVect )
Function cpBodyApplyForceAtLocalPoint:Void( body:cpBody, force:cpVect, point:cpVect )
Function cpBodyApplyImpulseAtWorldPoint:Void( body:cpBody, impulse:cpVect, point:cpVect )
Function cpBodyApplyImpulseAtLocalPoint:Void( body:cpBody, impulse:cpVect, point:cpVect )
Function cpBodyGetVelocityAtWorldPoint:cpVect( body:cpBody, point:cpVect )
Function cpBodyGetVelocityAtLocalPoint:cpVect( body:cpBody, point:cpVect )
Function cpBodyKineticEnergy:cpFloat( body:cpBody )
Function cpBodyEachShape:Void( body:cpBody, func:cpBodyShapeIteratorFunc, data:Void Ptr )
Function cpBodyEachConstraint:Void( body:cpBody, func:cpBodyConstraintIteratorFunc, data:Void Ptr )
Function cpBodyEachArbiter:Void( body:cpBody, func:cpBodyArbiterIteratorFunc, data:Void Ptr )

Class cpBody Extends Void

	Property Type:cpBodyType() Extension="cpBodyGetType"
	Setter( type:cpBodyType ) Extension="cpBodySetType"
	
	Property Mass:cpFloat() Extension="cpBodyGetMass"
	Setter( m:cpFloat ) Extension="cpBodySetMass"
	
	Property Moment:cpFloat() Extension="cpBodyGetMoment"
	Setter( i:cpFloat ) Extension="cpBodySetMoment"
	
	Property Position:cpVect() Extension="cpBodyGetPosition"
	Setter( pos:cpVect ) Extension="cpBodySetPosition"
	
	Property CenterOfGravity:cpVect() Extension="cpBodyGetCenterOfGravity"
	Setter( cog:cpVect ) Extension="cpBodySetCenterOfGravity"
	
	Property Velocity:cpVect() Extension="cpBodyGetVelocity"
	Setter( velocity:cpVect ) Extension="cpBodySetVelocity"
	
	Property Force:cpVect() Extension="cpBodyGetForce"
	Setter( force:cpVect ) Extension="cpBodySetForce"
	
	Property Angle:cpFloat() Extension="cpBodyGetAngle"
	Setter( a:cpFloat ) Extension="cpBodySetAngle"
	
	Property AngularVelocity:cpFloat() Extension="cpBodyGetAngularVelocity"
	Setter( angularVelocity:cpFloat ) Extension="cpBodySetAngularVelocity"
	
	Property Torque:cpFloat() Extension="cpBodyGetTorque"
	Setter( torque:cpFloat ) Extension="cpBodySetTorque"
	
	Property UserData:cpDataPointer() Extension="cpBodyGetUserData"
	Setter( userData:cpDataPointer ) Extension="cpBodySetUserData"
		
	Property KineticEnergy:cpFloat() Extension="cpBodyKineticEnergy"
	
	Property Rotation:cpVect() Extension="cpBodyGetRotation"
	
	Property Space:cpSpace() Extension="cpBodyGetSpace"
	
	Property IsSleeping:cpBool() Extension="cpBodyIsSleeping"
	
	Method Activate:Void() Extension="cpBodyActivate"
	
	Method ActivateStatic:Void( filter:cpShape ) Extension="cpBodyActivateStatic"
	
	Method Sleep:Void() Extension="cpBodySleep"
	
	Method SleepWithGroup:Void( group:cpBody ) Extension="SleepWithGroup"
	
	Method UpdateVelocity:Void( gravity:cpVect, damping:cpFloat, dt:cpFloat ) Extension="cpBodyUpdateVelocity"
	
	Method UpdatePosition:Void( dt:cpFloat ) Extension="cpBodyUpdatePosition"
	
	Method LocalToWorld:cpVect( point:cpVect ) Extension="cpBodyLocalToWorld"
	
	Method WorldToLocal:cpVect( point:cpVect ) Extension="cpBodyWorldToLocal"
	
	Method ApplyForceAtWorldPoint:Void( force:cpVect, point:cpVect ) Extension="cpBodyApplyForceAtWorldPoint"
		
	Method ApplyForceAtLocalPoint:Void( force:cpVect, point:cpVect ) Extension="cpBodyApplyForceAtLocalPoint"
	
	Method ApplyImpulseAtWorldPoint:Void( impulse:cpVect, point:cpVect ) Extension="cpBodyApplyImpulseAtWorldPoint"
	
	Method ApplyImpulseAtLocalPoint:Void( impulse:cpVect, point:cpVect ) Extension="cpBodyApplyImpulseAtLocalPoint"
	
	Method GetVelocityAtWorldPoint:cpVect( point:cpVect ) Extension="cpBodyGetVelocityAtWorldPoint"
	
	Method GetVelocityAtLocalPoint:cpVect( point:cpVect ) Extension="cpBodyGetVelocityAtLocalPoint"

End
