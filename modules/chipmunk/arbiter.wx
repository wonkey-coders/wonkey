
Namespace chipmunk

#Import "chipmunk_glue.h"

Extern

'***** File: Chipmunk7/include/chipmunk/cpArbiter.h *****

Struct cpContactPointSet
	Field count:Int
	Field normal:cpVect
End

Function cpArbiterGetRestitution:cpFloat( arb:cpArbiter )
Function cpArbiterSetRestitution:Void( arb:cpArbiter, restitution:cpFloat )
Function cpArbiterGetFriction:cpFloat( arb:cpArbiter )
Function cpArbiterSetFriction:Void( arb:cpArbiter, friction:cpFloat )
Function cpArbiterGetSurfaceVelocity:cpVect( arb:cpArbiter )
Function cpArbiterSetSurfaceVelocity:Void( arb:cpArbiter, vr:cpVect )
Function cpArbiterGetUserData:cpDataPointer( arb:cpArbiter )
Function cpArbiterSetUserData:Void( arb:cpArbiter, userData:cpDataPointer )
Function cpArbiterTotalImpulse:cpVect( arb:cpArbiter )
Function cpArbiterTotalKE:cpFloat( arb:cpArbiter )
Function cpArbiterIgnore:cpBool( arb:cpArbiter )
Function cpArbiterGetShapes:Void( arb:cpArbiter, a:cpShape Ptr, b:cpShape Ptr )
Function cpArbiterGetBodies:Void( arb:cpArbiter, a:cpBody Ptr, b:cpBody Ptr )
Function cpArbiterGetContactPointSet:cpContactPointSet( arb:cpArbiter )
Function cpArbiterSetContactPointSet:Void( arb:cpArbiter, set:cpContactPointSet Ptr )
Function cpArbiterIsFirstContact:cpBool( arb:cpArbiter )
Function cpArbiterIsRemoval:cpBool( arb:cpArbiter )
Function cpArbiterGetCount:Int( arb:cpArbiter )
Function cpArbiterGetNormal:cpVect( arb:cpArbiter )
Function cpArbiterGetPointA:cpVect( arb:cpArbiter, i:Int )
Function cpArbiterGetPointB:cpVect( arb:cpArbiter, i:Int )
Function cpArbiterGetDepth:cpFloat( arb:cpArbiter, i:Int )
Function cpArbiterCallWildcardBeginA:cpBool( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardBeginB:cpBool( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardPreSolveA:cpBool( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardPreSolveB:cpBool( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardPostSolveA:Void( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardPostSolveB:Void( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardSeparateA:Void( arb:cpArbiter, space:cpSpace )
Function cpArbiterCallWildcardSeparateB:Void( arb:cpArbiter, space:cpSpace )

Class cpArbiter Extends Void

	Property Restitution:cpFloat() Extension="cpArbiterGetRestitution"
	Setter( restitution:cpFloat ) Extension="cpArbiterSetRestitution"

	Property Friction:cpFloat() Extension="cpArbiterGetFriction"
	Setter( friction:cpFloat ) Extension="cpArbiterSetFriction"

	Property SurfaceVelocity:cpVect() Extension="cpArbiterGetSurfaceVelocity"
	Setter( vr:cpVect ) Extension="cpArbiterSetSurfaceVelocity"
	
	Property UserData:cpDataPointer() Extension="cpArbiterGetUserData"
	Setter( userData:cpDataPointer ) Extension="cpArbiterSetUserData"

	Property TotalImpulse:cpVect() Extension="cpArbiterTotalImpulse"

	Property TotalKE:cpFloat() Extension="cpArbiterTotalKE"

	Property Ignore:cpBool() Extension="cpArbiterIgnore"

	Property IsFirstContact:cpBool() Extension="cpArbiterIsFirstContact"
	
	Property IsRemoval:cpBool() Extension="cpArbiterIsRemoval"
	
	Property Normal:cpVect() Extension="cpArbiterGetNormal"
	
	Property Count:Int() Extension="cpArbiterGetCount"
	
	Method GetShapes:Void( a:cpShape Ptr, b:cpShape Ptr ) Extension="cpArbiterGetShapes"
	
	Method GetBodies:Void( a:cpBody Ptr, b:cpBody Ptr ) Extension="cpArbiterGetBodies"
	
	Method GetCount:Int() Extension="cpArbiterGetCount"
	
	Method GetPointA:cpVect( i:Int ) Extension="cpArbiterGetPointA"

	Method GetPointB:cpVect( i:Int ) Extension="cpArbiterGetPointB"

	Method GetDepth:cpFloat( i:Int ) Extension="cpArbiterGetDepth"
	
End
