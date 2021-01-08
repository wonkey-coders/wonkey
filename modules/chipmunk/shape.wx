
Namespace chipmunk

#Import "chipmunk_glue.h"

Extern

'***** File: Chipmunk7/include/chipmunk/cpShape.h *****

Struct cpPointQueryInfo
	Field shape:cpShape
	Field point:cpVect
	Field distance:cpFloat
	Field gradient:cpVect
End

Struct cpSegmentQueryInfo
	Field shape:cpShape
	Field point:cpVect
	Field normal:cpVect
	Field alpha:cpFloat
End

Struct cpShapeFilter
	Field group:cpGroup
	Field categories:cpBitmask
	Field mask:cpBitmask
End

Const CP_SHAPE_FILTER_ALL:cpShapeFilter
Const CP_SHAPE_FILTER_NONE:cpShapeFilter

Function cpShapeFilterNew:cpShapeFilter( group:cpGroup, categories:cpBitmask, mask:cpBitmask )
Function cpShapeDestroy:Void( shape:cpShape )
Function cpShapeFree:Void( shape:cpShape )
Function cpShapeCacheBB:cpBB( shape:cpShape )
Function cpShapeUpdate:cpBB( shape:cpShape, transform:cpTransform )
Function cpShapePointQuery:cpFloat( shape:cpShape, p:cpVect, out:cpPointQueryInfo Ptr )
Function cpShapeSegmentQuery:cpBool( shape:cpShape, a:cpVect, b:cpVect, radius:cpFloat, info:cpSegmentQueryInfo Ptr )
Function cpShapesCollide:cpContactPointSet( a:cpShape, b:cpShape )
Function cpShapeGetSpace:cpSpace( shape:cpShape )
Function cpShapeGetBody:cpBody( shape:cpShape )
Function cpShapeSetBody:Void( shape:cpShape, body:cpBody )
Function cpShapeGetMass:cpFloat( shape:cpShape )
Function cpShapeSetMass:Void( shape:cpShape, mass:cpFloat )
Function cpShapeGetDensity:cpFloat( shape:cpShape )
Function cpShapeSetDensity:Void( shape:cpShape, density:cpFloat )
Function cpShapeGetMoment:cpFloat( shape:cpShape )
Function cpShapeGetArea:cpFloat( shape:cpShape )
Function cpShapeGetCenterOfGravity:cpVect( shape:cpShape )
Function cpShapeGetBB:cpBB( shape:cpShape )
Function cpShapeGetSensor:cpBool( shape:cpShape )
Function cpShapeSetSensor:Void( shape:cpShape, sensor:cpBool )
Function cpShapeGetElasticity:cpFloat( shape:cpShape )
Function cpShapeSetElasticity:Void( shape:cpShape, elasticity:cpFloat )
Function cpShapeGetFriction:cpFloat( shape:cpShape )
Function cpShapeSetFriction:Void( shape:cpShape, friction:cpFloat )
Function cpShapeGetSurfaceVelocity:cpVect( shape:cpShape )
Function cpShapeSetSurfaceVelocity:Void( shape:cpShape, surfaceVelocity:cpVect )
Function cpShapeGetUserData:cpDataPointer( shape:cpShape )
Function cpShapeSetUserData:Void( shape:cpShape, userData:cpDataPointer )
Function cpShapeGetCollisionType:cpCollisionType( shape:cpShape )
Function cpShapeSetCollisionType:Void( shape:cpShape, collisionType:cpCollisionType )
Function cpShapeGetFilter:cpShapeFilter( shape:cpShape )
Function cpShapeSetFilter:Void( shape:cpShape, filter:cpShapeFilter )
Function cpCircleShapeAlloc:cpCircleShape(  )
Function cpCircleShapeInit:cpCircleShape( circle:cpCircleShape, body:cpBody, radius:cpFloat, offset:cpVect )
Function cpCircleShapeNew:cpShape( body:cpBody, radius:cpFloat, offset:cpVect )
Function cpCircleShapeGetOffset:cpVect( shape:cpShape )
Function cpCircleShapeGetRadius:cpFloat( shape:cpShape )
Function cpSegmentShapeAlloc:cpSegmentShape(  )
Function cpSegmentShapeInit:cpSegmentShape( seg:cpSegmentShape, body:cpBody, a:cpVect, b:cpVect, radius:cpFloat )
Function cpSegmentShapeNew:cpShape( body:cpBody, a:cpVect, b:cpVect, radius:cpFloat )
Function cpSegmentShapeSetNeighbors:Void( shape:cpShape, prev:cpVect, next_:cpVect )
Function cpSegmentShapeGetA:cpVect( shape:cpShape )
Function cpSegmentShapeGetB:cpVect( shape:cpShape )
Function cpSegmentShapeGetNormal:cpVect( shape:cpShape )
Function cpSegmentShapeGetRadius:cpFloat( shape:cpShape )

'***** File: Chipmunk7/include/chipmunk/cpPolyShape.h *****

Function cpPolyShapeAlloc:cpPolyShape(  )
Function cpPolyShapeInit:cpPolyShape( poly:cpPolyShape, body:cpBody, count:Int, verts:cpVect Ptr, transform:cpTransform, radius:cpFloat )
Function cpPolyShapeInitRaw:cpPolyShape( poly:cpPolyShape, body:cpBody, count:Int, verts:cpVect Ptr, radius:cpFloat )
Function cpPolyShapeNew:cpShape( body:cpBody, count:Int, verts:cpVect Ptr, transform:cpTransform, radius:cpFloat )
Function cpPolyShapeNewRaw:cpShape( body:cpBody, count:Int, verts:cpVect Ptr, radius:cpFloat )
Function cpBoxShapeInit:cpPolyShape( poly:cpPolyShape, body:cpBody, width:cpFloat, height:cpFloat, radius:cpFloat )
Function cpBoxShapeInit2:cpPolyShape( poly:cpPolyShape, body:cpBody, box:cpBB, radius:cpFloat )
Function cpBoxShapeNew:cpShape( body:cpBody, width:cpFloat, height:cpFloat, radius:cpFloat )
Function cpBoxShapeNew2:cpShape( body:cpBody, box:cpBB, radius:cpFloat )
Function cpPolyShapeGetCount:Int( shape:cpShape )
Function cpPolyShapeGetVert:cpVect( shape:cpShape, index:Int )
Function cpPolyShapeGetRadius:cpFloat( shape:cpShape )

Class cpShape Extends Void

	Property Body:cpBody() Extension="cpShapeGetBody"
	Setter( body:cpBody ) Extension="cpShapeSetBody"
	
	Property Mass:cpFloat() Extension="cpShapeGetMass"
	Setter( mass:cpFloat ) Extension="cpShapeSetMass"
	
	Property Density:cpFloat() Extension="cpShapeGetDensity"
	Setter( density:cpFloat ) Extension="cpShapeSetDensity"
	
	Property Sensor:cpBool() Extension="cpShapeGetSensor"
	Setter( sensor:cpBool ) Extension="cpShapeSetSensor"
	
	Property Elasticity:cpFloat() Extension="cpShapeGetElasticity"
	Setter( elasticity:cpFloat ) Extension="cpShapeSetElasticity"
	
	Property Friction:cpFloat() Extension="cpShapeGetFriction"
	Setter( friction:cpFloat ) Extension="cpShapeSetFriction"
	
	Property SurfaceVelocity:cpVect() Extension="cpShapeGetSurfaceVelocity"
	Setter( surfaceVelocity:cpVect ) Extension="cpShapeSetSurfaceVelocity"
	
	Property UserData:cpDataPointer() Extension="cpShapeGetUserData"
	Setter( userData:cpDataPointer ) Extension="cpShapeSetUserData"
	
	Property CollisionType:cpCollisionType() Extension="cpShapeGetCollisionType"
	Setter( collisionType:cpCollisionType ) Extension="cpShapeSetCollisionType"
	
	Property Moment:cpFloat() Extension="cpShapeGetMoment"
	
	Property Area:cpFloat() Extension="cpShapeGetArea"
	
	Property CenterOfGravity:cpVect() Extension="cpShapeGetCenterOfGravity"

	Property CacheBB:cpBB() Extension="cpShapeCacheBB"

	Property BB:cpBB() Extension="cpShapeGetBB"
	
	Property Space:cpSpace() Extension="cpShapeGetSpace"
	
	Property CircleRadius:cpFloat() Extension="cpCircleShapeGetRadius"
	
	Property CircleOffset:cpVect() Extension="cpCircleShapeGetOffset"
	
	Property SegmentA:cpVect() Extension="cpSegmentShapeGetA"
	
	Property SegmentB:cpVect() Extension="cpSegmentShapeGetB"
	
	Property PolyShapeRadius:cpFloat() Extension="cpPolyShapeGetRadius"
	
	Property PolyShapeCount:Int() Extension="cpPolyShapeGetCount"
	
	Method GetPolyShapeCount:Int() Extension="cpPolyShapeGetCount"
	
	Method GetPolyShapeVert:cpVect( index:Int ) Extension="cpPolyShapeGetVert"
	
	Method Update:cpBB( transform:cpTransform ) Extension="cpShapeUpdate"
	
	Method PointQuery:cpFloat( p:cpVect, out:cpPointQueryInfo Ptr ) Extension="cpShapePointQuery"
	
	Method SegmentQuery:cpBool( a:cpVect, b:cpVect, radius:cpFloat, info:cpSegmentQueryInfo Ptr ) Extension="cpShapeSegmentQuery"
	
	Method sCollide:cpContactPointSet( a:cpShape, b:cpShape ) Extension="cpShapesCollide"
	
End

Class cpCircleShape Extends Void
End

Class cpSegmentShape Extends Void
End

Class cpPolyShape Extends Void
End
