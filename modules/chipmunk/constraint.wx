
Namespace chipmunk

#Import "chipmunk_glue.h"

Extern

'***** File: Chipmunk7/include/chipmunk/cpConstraint.h *****

Alias cpConstraintPreSolveFunc:Void( cpConstraint, cpSpace )
Alias cpConstraintPostSolveFunc:Void( cpConstraint, cpSpace )

Function cpConstraintDestroy:Void( constraint:cpConstraint )
Function cpConstraintFree:Void( constraint:cpConstraint )
Function cpConstraintGetSpace:cpSpace( constraint:cpConstraint )
Function cpConstraintGetBodyA:cpBody( constraint:cpConstraint )
Function cpConstraintGetBodyB:cpBody( constraint:cpConstraint )
Function cpConstraintGetMaxForce:cpFloat( constraint:cpConstraint )
Function cpConstraintSetMaxForce:Void( constraint:cpConstraint, maxForce:cpFloat )
Function cpConstraintGetErrorBias:cpFloat( constraint:cpConstraint )
Function cpConstraintSetErrorBias:Void( constraint:cpConstraint, errorBias:cpFloat )
Function cpConstraintGetMaxBias:cpFloat( constraint:cpConstraint )
Function cpConstraintSetMaxBias:Void( constraint:cpConstraint, maxBias:cpFloat )
Function cpConstraintGetCollideBodies:cpBool( constraint:cpConstraint )
Function cpConstraintSetCollideBodies:Void( constraint:cpConstraint, collideBodies:cpBool )
Function cpConstraintGetPreSolveFunc:cpConstraintPreSolveFunc( constraint:cpConstraint )
Function cpConstraintSetPreSolveFunc:Void( constraint:cpConstraint, preSolveFunc:cpConstraintPreSolveFunc )
Function cpConstraintGetPostSolveFunc:cpConstraintPostSolveFunc( constraint:cpConstraint )
Function cpConstraintSetPostSolveFunc:Void( constraint:cpConstraint, postSolveFunc:cpConstraintPostSolveFunc )
Function cpConstraintGetUserData:cpDataPointer( constraint:cpConstraint )
Function cpConstraintSetUserData:Void( constraint:cpConstraint, userData:cpDataPointer )
Function cpConstraintGetImpulse:cpFloat( constraint:cpConstraint )

'***** File: Chipmunk7/include/chipmunk/cpPinJoint.h *****

Function cpConstraintIsPinJoint:cpBool( constraint:cpConstraint )
Function cpPinJointAlloc:cpPinJoint(  )
Function cpPinJointInit:cpPinJoint( joint:cpPinJoint, a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect )
Function cpPinJointNew:cpConstraint( a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect )
Function cpPinJointGetAnchorA:cpVect( constraint:cpConstraint )
Function cpPinJointSetAnchorA:Void( constraint:cpConstraint, anchorA:cpVect )
Function cpPinJointGetAnchorB:cpVect( constraint:cpConstraint )
Function cpPinJointSetAnchorB:Void( constraint:cpConstraint, anchorB:cpVect )
Function cpPinJointGetDist:cpFloat( constraint:cpConstraint )
Function cpPinJointSetDist:Void( constraint:cpConstraint, dist:cpFloat )

'***** File: Chipmunk7/include/chipmunk/cpSlideJoint.h *****

Function cpConstraintIsSlideJoint:cpBool( constraint:cpConstraint )
Function cpSlideJointAlloc:cpSlideJoint(  )
Function cpSlideJointInit:cpSlideJoint( joint:cpSlideJoint, a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect, min:cpFloat, max:cpFloat )
Function cpSlideJointNew:cpConstraint( a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect, min:cpFloat, max:cpFloat )
Function cpSlideJointGetAnchorA:cpVect( constraint:cpConstraint )
Function cpSlideJointSetAnchorA:Void( constraint:cpConstraint, anchorA:cpVect )
Function cpSlideJointGetAnchorB:cpVect( constraint:cpConstraint )
Function cpSlideJointSetAnchorB:Void( constraint:cpConstraint, anchorB:cpVect )
Function cpSlideJointGetMin:cpFloat( constraint:cpConstraint )
Function cpSlideJointSetMin:Void( constraint:cpConstraint, min:cpFloat )
Function cpSlideJointGetMax:cpFloat( constraint:cpConstraint )
Function cpSlideJointSetMax:Void( constraint:cpConstraint, max:cpFloat )

'***** File: Chipmunk7/include/chipmunk/cpPivotJoint.h *****

Function cpConstraintIsPivotJoint:cpBool( constraint:cpConstraint )
Function cpPivotJointAlloc:cpPivotJoint(  )
Function cpPivotJointInit:cpPivotJoint( joint:cpPivotJoint, a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect )
Function cpPivotJointNew:cpConstraint( a:cpBody, b:cpBody, pivot:cpVect )
Function cpPivotJointNew2:cpConstraint( a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect )
Function cpPivotJointGetAnchorA:cpVect( constraint:cpConstraint )
Function cpPivotJointSetAnchorA:Void( constraint:cpConstraint, anchorA:cpVect )
Function cpPivotJointGetAnchorB:cpVect( constraint:cpConstraint )
Function cpPivotJointSetAnchorB:Void( constraint:cpConstraint, anchorB:cpVect )

'***** File: Chipmunk7/include/chipmunk/cpGrooveJoint.h *****

Function cpConstraintIsGrooveJoint:cpBool( constraint:cpConstraint )
Function cpGrooveJointAlloc:cpGrooveJoint(  )
Function cpGrooveJointInit:cpGrooveJoint( joint:cpGrooveJoint, a:cpBody, b:cpBody, groove_a:cpVect, groove_b:cpVect, anchorB:cpVect )
Function cpGrooveJointNew:cpConstraint( a:cpBody, b:cpBody, groove_a:cpVect, groove_b:cpVect, anchorB:cpVect )
Function cpGrooveJointGetGrooveA:cpVect( constraint:cpConstraint )
Function cpGrooveJointSetGrooveA:Void( constraint:cpConstraint, grooveA:cpVect )
Function cpGrooveJointGetGrooveB:cpVect( constraint:cpConstraint )
Function cpGrooveJointSetGrooveB:Void( constraint:cpConstraint, grooveB:cpVect )
Function cpGrooveJointGetAnchorB:cpVect( constraint:cpConstraint )
Function cpGrooveJointSetAnchorB:Void( constraint:cpConstraint, anchorB:cpVect )

'***** File: Chipmunk7/include/chipmunk/cpDampedSpring.h *****

Function cpConstraintIsDampedSpring:cpBool( constraint:cpConstraint )
Alias cpDampedSpringForceFunc:cpFloat( cpConstraint, cpFloat )
Function cpDampedSpringAlloc:cpDampedSpring(  )
Function cpDampedSpringInit:cpDampedSpring( joint:cpDampedSpring, a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect, restLength:cpFloat, stiffness:cpFloat, damping:cpFloat )
Function cpDampedSpringNew:cpConstraint( a:cpBody, b:cpBody, anchorA:cpVect, anchorB:cpVect, restLength:cpFloat, stiffness:cpFloat, damping:cpFloat )
Function cpDampedSpringGetAnchorA:cpVect( constraint:cpConstraint )
Function cpDampedSpringSetAnchorA:Void( constraint:cpConstraint, anchorA:cpVect )
Function cpDampedSpringGetAnchorB:cpVect( constraint:cpConstraint )
Function cpDampedSpringSetAnchorB:Void( constraint:cpConstraint, anchorB:cpVect )
Function cpDampedSpringGetRestLength:cpFloat( constraint:cpConstraint )
Function cpDampedSpringSetRestLength:Void( constraint:cpConstraint, restLength:cpFloat )
Function cpDampedSpringGetStiffness:cpFloat( constraint:cpConstraint )
Function cpDampedSpringSetStiffness:Void( constraint:cpConstraint, stiffness:cpFloat )
Function cpDampedSpringGetDamping:cpFloat( constraint:cpConstraint )
Function cpDampedSpringSetDamping:Void( constraint:cpConstraint, damping:cpFloat )
Function cpDampedSpringGetSpringForceFunc:cpDampedSpringForceFunc( constraint:cpConstraint )
Function cpDampedSpringSetSpringForceFunc:Void( constraint:cpConstraint, springForceFunc:cpDampedSpringForceFunc )

'***** File: Chipmunk7/include/chipmunk/cpDampedRotarySpring.h *****

Function cpConstraintIsDampedRotarySpring:cpBool( constraint:cpConstraint )
Alias cpDampedRotarySpringTorqueFunc:cpFloat( cpConstraint, cpFloat )
Function cpDampedRotarySpringAlloc:cpDampedRotarySpring(  )
Function cpDampedRotarySpringInit:cpDampedRotarySpring( joint:cpDampedRotarySpring, a:cpBody, b:cpBody, restAngle:cpFloat, stiffness:cpFloat, damping:cpFloat )
Function cpDampedRotarySpringNew:cpConstraint( a:cpBody, b:cpBody, restAngle:cpFloat, stiffness:cpFloat, damping:cpFloat )
Function cpDampedRotarySpringGetRestAngle:cpFloat( constraint:cpConstraint )
Function cpDampedRotarySpringSetRestAngle:Void( constraint:cpConstraint, restAngle:cpFloat )
Function cpDampedRotarySpringGetStiffness:cpFloat( constraint:cpConstraint )
Function cpDampedRotarySpringSetStiffness:Void( constraint:cpConstraint, stiffness:cpFloat )
Function cpDampedRotarySpringGetDamping:cpFloat( constraint:cpConstraint )
Function cpDampedRotarySpringSetDamping:Void( constraint:cpConstraint, damping:cpFloat )
Function cpDampedRotarySpringGetSpringTorqueFunc:cpDampedRotarySpringTorqueFunc( constraint:cpConstraint )
Function cpDampedRotarySpringSetSpringTorqueFunc:Void( constraint:cpConstraint, springTorqueFunc:cpDampedRotarySpringTorqueFunc )

'***** File: Chipmunk7/include/chipmunk/cpRotaryLimitJoint.h *****

Function cpConstraintIsRotaryLimitJoint:cpBool( constraint:cpConstraint )
Function cpRotaryLimitJointAlloc:cpRotaryLimitJoint(  )
Function cpRotaryLimitJointInit:cpRotaryLimitJoint( joint:cpRotaryLimitJoint, a:cpBody, b:cpBody, min:cpFloat, max:cpFloat )
Function cpRotaryLimitJointNew:cpConstraint( a:cpBody, b:cpBody, min:cpFloat, max:cpFloat )
Function cpRotaryLimitJointGetMin:cpFloat( constraint:cpConstraint )
Function cpRotaryLimitJointSetMin:Void( constraint:cpConstraint, min:cpFloat )
Function cpRotaryLimitJointGetMax:cpFloat( constraint:cpConstraint )
Function cpRotaryLimitJointSetMax:Void( constraint:cpConstraint, max:cpFloat )

'***** File: Chipmunk7/include/chipmunk/cpRatchetJoint.h *****

Function cpConstraintIsRatchetJoint:cpBool( constraint:cpConstraint )
Function cpRatchetJointAlloc:cpRatchetJoint(  )
Function cpRatchetJointInit:cpRatchetJoint( joint:cpRatchetJoint, a:cpBody, b:cpBody, phase:cpFloat, ratchet:cpFloat )
Function cpRatchetJointNew:cpConstraint( a:cpBody, b:cpBody, phase:cpFloat, ratchet:cpFloat )
Function cpRatchetJointGetAngle:cpFloat( constraint:cpConstraint )
Function cpRatchetJointSetAngle:Void( constraint:cpConstraint, angle:cpFloat )
Function cpRatchetJointGetPhase:cpFloat( constraint:cpConstraint )
Function cpRatchetJointSetPhase:Void( constraint:cpConstraint, phase:cpFloat )
Function cpRatchetJointGetRatchet:cpFloat( constraint:cpConstraint )
Function cpRatchetJointSetRatchet:Void( constraint:cpConstraint, ratchet:cpFloat )

'***** File: Chipmunk7/include/chipmunk/cpGearJoint.h *****

Function cpConstraintIsGearJoint:cpBool( constraint:cpConstraint )
Function cpGearJointAlloc:cpGearJoint(  )
Function cpGearJointInit:cpGearJoint( joint:cpGearJoint, a:cpBody, b:cpBody, phase:cpFloat, ratio:cpFloat )
Function cpGearJointNew:cpConstraint( a:cpBody, b:cpBody, phase:cpFloat, ratio:cpFloat )
Function cpGearJointGetPhase:cpFloat( constraint:cpConstraint )
Function cpGearJointSetPhase:Void( constraint:cpConstraint, phase:cpFloat )
Function cpGearJointGetRatio:cpFloat( constraint:cpConstraint )
Function cpGearJointSetRatio:Void( constraint:cpConstraint, ratio:cpFloat )

'***** File: Chipmunk7/include/chipmunk/cpSimpleMotor.h *****

Function cpConstraintIsSimpleMotor:cpBool( constraint:cpConstraint )
Function cpSimpleMotorAlloc:cpSimpleMotor(  )
Function cpSimpleMotorInit:cpSimpleMotor( joint:cpSimpleMotor, a:cpBody, b:cpBody, rate:cpFloat )
Function cpSimpleMotorNew:cpConstraint( a:cpBody, b:cpBody, rate:cpFloat )
Function cpSimpleMotorGetRate:cpFloat( constraint:cpConstraint )
Function cpSimpleMotorSetRate:Void( constraint:cpConstraint, rate:cpFloat )

Class cpConstraint Extends Void

	Property Space:cpSpace() Extension="cpConstraintGetSpace"
	
	Property BodyA:cpBody() Extension="cpConstraintGetBodyA"
	
	Property BodyB:cpBody() Extension="cpConstraintGetBodyB"
	
	Property MaxForce:cpFloat() Extension="cpConstraintGetMaxForce"
	Setter( maxForce:cpFloat ) Extension="cpConstraintSetMaxForce"
	
	Property ErrorBias:cpFloat() Extension="cpConstraintGetErrorBias"
	Setter( errorBias:cpFloat ) Extension="cpConstraintSetErrorBias"
	
	Property MaxBias:cpFloat() Extension="cpConstraintGetMaxBias"
	Setter( maxBias:cpFloat ) Extension="cpConstraintSetMaxBias"
	
	Property CollideBodies:cpBool() Extension="cpConstraintGetCollideBodies"
	Setter( collideBodies:cpBool ) Extension="cpConstraintSetCollideBodies"
	
	Property UserData:cpDataPointer() Extension="cpConstraintGetUserData"
	Setter( userData:cpDataPointer ) Extension="cpConstraintSetUserData"
	
	Property Impulse:cpFloat() Extension="cpConstraintGetImpulse"
	
	'pin joint
	Property IsPinJoint:cpBool() Extension="cpConstraintIsPinJoint"
	
	Property PinJointAnchorA:cpVect() Extension="cpPinJointGetAnchorA"
	Setter( anchorA:cpVect ) Extension="cpPinJointSetAnchorA"
	
	Property PinJointAnchorB:cpVect() Extension="cpPinJointGetAnchorB"
	Setter( anchorB:cpVect ) Extension="cpPinJointSetAnchorB"
	
	Property PinJointDist:cpFloat() Extension="cpPinJointGetDist"
	Setter( dist:cpFloat ) Extension="cpPinJointSetDist"
	
	'slide joint
	Property IsSlideJoint:cpBool() Extension="cpConstraintIsSliceJoint"

	Property SlideJointAnchorA:cpVect() Extension="cpSlideJointGetAnchorA"
	Setter( anchorA:cpVect ) Extension="cpSlideJointSetAnchorA"
	
	Property SlideJointAnchorB:cpVect() Extension="cpSlideJointGetAnchorB"
	Setter( anchorB:cpVect ) Extension="cpSlideJointSetAnchorB"
	
	Property SlideJointMin:cpFloat() Extension="cpSlideJointGetMin"
	Setter( min:cpFloat ) Extension="cpSlideJointSetMin"
	
	Property SlideJointMax:cpFloat() Extension="cpSlideJointGetMax"
	Setter( max:cpFloat ) Extension="cpSlideJointSetMax"
	
	'pivot joint
	Property IsPivotJoint:cpBool() Extension="cpConstraintIsPivotJoint"
	
	Property PivotJointAnchorA:cpVect() Extension="cpPivotJointGetAnchorA"
	Setter( anchorA:cpVect ) Extension="cpPivotJointSetAnchorA"
	
	Property PivotJointAnchorB:cpVect() Extension="cpPivotJointGetAnchorB"
	Setter( anchorB:cpVect ) Extension="cpPivotJointSetAnchorB"

	'groove joint	
	Property IsGrooveJoint:cpBool() Extension="cpConstraintIsGrooveJoint"

	Property GrooveJointGrooveA:cpVect() Extension="cpGrooveJointGetGrooveA"
	Setter( GrooveA:cpVect ) Extension="cpGrooveJointSetGrooveA"
	
	Property GrooveJointGrooveB:cpVect() Extension="cpGrooveJointGetGrooveB"
	Setter( GrooveB:cpVect ) Extension="cpGrooveJointSetGrooveB"

	Property GrooveJointAnchorB:cpVect() Extension="cpGrooveJointGetAnchorB"
	Setter( anchorB:cpVect ) Extension="cpGrooveJointSetAnchorB"

	'damped spring
	Property IsDampedSpring:cpBool() Extension="cpConstraintIsDampedSpring"

	Property DampedSpringAnchorA:cpVect() Extension="cpDampedSpringGetAnchorA"
	Setter( anchorA:cpVect ) Extension="cpDampedSpringSetAnchorA"
	
	Property DampedSpringAnchorB:cpVect() Extension="cpDampedSpringGetAnchorB"
	Setter( anchorB:cpVect ) Extension="cpDampedSpringSetAnchorB"

	Property DampedSpringRestLength:cpFloat() Extension="cpDampedSpringGetRestLength"
	Setter( restLength:cpFloat ) Extension="cpDampedSpringSetRestLength"
	
	Property DampedSpringStiffness:cpFloat() Extension="cpDampedSpringGetStiffness"
	Setter( stiffness:cpFloat ) Extension="cpDampedSpringSetStiffness"
	
	Property DampedSpringDamping:cpFloat() Extension="cpDampedSpringGetDamping"
	Setter( damping:cpFloat ) Extension="cpDampedSpringSetDamping"
	
	'damped rotary spring
	Property IsDampedRotarySpring:cpBool() Extension="cpConstraintIsDampedRotarySpring"

	Property DampedRotarySpringRestAngle:cpFloat() Extension="cpDampedRotarySpringGetRestAngle"
	Setter( restAngle:cpFloat ) Extension="cpDampedRotarySpringSetRestAngle"
	
	Property DampedRotarySpringStiffness:cpFloat() Extension="cpDampedRotarySpringGetStiffness"
	Setter( stiffness:cpFloat ) Extension="cpDampedRotarySpringSetStiffness"
	
	Property DampedRotarySpringDamping:cpFloat() Extension="cpDampedRotarySpringGetDamping"
	Setter( damping:cpFloat ) Extension="cpDampedRotarySpringSetDamping"

	'rotary limit joint
	Property IsRotaryLimitJoint:cpBool() Extension="cpConstraintIsRotaryLimitJoint"
	
	Property RotaryLimitJointMin:cpFloat() Extension="cpRotaryLimitJointGetMin"
	Setter( min:cpFloat ) Extension="cpRotaryLimitJointSetMin"
	
	Property RotaryLimitJointMax:cpFloat() Extension="cpRotaryLimitJointGetMax"
	Setter( max:cpFloat ) Extension="cpRotaryLimitJointSetMax"

	'ratchet joint
	Property IsRatchetJoint:cpBool() Extension="cpConstraintIsRatchetJoint"

	Property RatchetJointAngle:cpFloat() Extension="cpRatchetJointGetAngle"
	Setter( angle:cpFloat ) Extension="cpRatchetJointSetAngle"

	Property RatchetJointPhase:cpFloat() Extension="cpRatchetJointGetPhase"
	Setter( phase:cpFloat ) Extension="cpRatchetJointSetPhase"

	Property RatchetJointRatchet:cpFloat() Extension="cpRatchetJointGetRatchet"
	Setter( ratchet:cpFloat ) Extension="cpRatchetJointSetRatchet"

	'gear joint
	Property IsGearJoint:cpBool() Extension="cpConstraintIsGearJoint"

	Property GearJointPhase:cpFloat() Extension="cpGearJointGetPhase"
	Setter( phase:cpFloat ) Extension="cpGearJointSetPhase"
	
	Property GearJointRatio:cpFloat() Extension="cpGearJointGetRatio"
	Setter( ratio:cpFloat ) Extension="cpGearJointSetRatio"
	
	'simple motor
	Property IsSimpleMotor:cpBool() Extension="cpConstraintIsSimpleMotor"

	Property SimpleMotorRate:cpFloat() Extension="cpSimpleMotorGetRate"
	Setter( rate:cpFloat ) Extension="cpSimpleMotorSetRate"
			
End

Class cpPinJoint Extends Void
End

Class cpSlideJoint Extends Void
End

Class cpPivotJoint Extends Void
End

Class cpGrooveJoint Extends Void
End

Class cpDampedSpring Extends Void
End

Class cpDampedRotarySpring Extends Void
End

Class cpRotaryLimitJoint Extends Void
End

Class cpRatchetJoint extends Void
End

Class cpGearJoint Extends Void
End

Class cpSimpleMotor Extends Void
End
