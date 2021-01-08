
Namespace chipmunk

#Import "chipmunk_glue.h"

Extern

'***** File: Chipmunk7/include/chipmunk/chipmunk.h *****

Global cpVersionString:CString
Function cpMomentForCircle:cpFloat( m:cpFloat, r1:cpFloat, r2:cpFloat, offset:cpVect )
Function cpAreaForCircle:cpFloat( r1:cpFloat, r2:cpFloat )
Function cpMomentForSegment:cpFloat( m:cpFloat, a:cpVect, b:cpVect, radius:cpFloat )
Function cpAreaForSegment:cpFloat( a:cpVect, b:cpVect, radius:cpFloat )
Function cpMomentForPoly:cpFloat( m:cpFloat, count:Int, verts:cpVect Ptr, offset:cpVect, radius:cpFloat )
Function cpAreaForPoly:cpFloat( count:Int, verts:cpVect Ptr, radius:cpFloat )
Function cpCentroidForPoly:cpVect( count:Int, verts:cpVect Ptr )
Function cpMomentForBox:cpFloat( m:cpFloat, width:cpFloat, height:cpFloat )
Function cpMomentForBox2:cpFloat( m:cpFloat, box:cpBB )
Function cpConvexHull:Int( count:Int, verts:cpVect Ptr, result:cpVect Ptr, first:Int Ptr, tol:cpFloat )
Function cpClosetPointOnSegment:cpVect( p:cpVect, a:cpVect, b:cpVect )

'***** File: Chipmunk7/include/chipmunk/chipmunk_types.h *****

Alias cpFloat:Double
Function cpfmax:cpFloat( a:cpFloat, b:cpFloat )
Function cpfmin:cpFloat( a:cpFloat, b:cpFloat )
Function cpfabs:cpFloat( f:cpFloat )
Function cpfclamp:cpFloat( f:cpFloat, min:cpFloat, max:cpFloat )
Function cpfclamp01:cpFloat( f:cpFloat )
Function cpflerp:cpFloat( f1:cpFloat, f2:cpFloat, t:cpFloat )
Function cpflerpconst:cpFloat( f1:cpFloat, f2:cpFloat, d:cpFloat )
Alias cpHashValue:libc.uintptr_t
Alias cpCollisionID:libc.uint32_t
Alias cpBool:UByte
Alias cpDataPointer:Void Ptr
Alias cpCollisionType:Int'libc.uintptr_t
Alias cpGroup:libc.uintptr_t
Alias cpBitmask:UInt
Alias cpTimestamp:UInt

Struct cpVect
	Field x:cpFloat
	Field y:cpFloat
End

Struct cpTransform
	Field a:cpFloat
	Field b:cpFloat
	Field c:cpFloat
	Field d:cpFloat
	Field tx:cpFloat
	Field ty:cpFloat
End

Struct cpMat2x2
	Field a:cpFloat
	Field b:cpFloat
	Field c:cpFloat
	Field d:cpFloat
End

'***** File: Chipmunk7/include/chipmunk/cpVect.h *****

Const cpvzero:cpVect
Function cpv:cpVect( x:cpFloat, y:cpFloat )
Function cpveql:cpBool( v1:cpVect, v2:cpVect )
Function cpvadd:cpVect( v1:cpVect, v2:cpVect )
Function cpvsub:cpVect( v1:cpVect, v2:cpVect )
Function cpvneg:cpVect( v:cpVect )
Function cpvmult:cpVect( v:cpVect, s:cpFloat )
Function cpvdot:cpFloat( v1:cpVect, v2:cpVect )
Function cpvcross:cpFloat( v1:cpVect, v2:cpVect )
Function cpvperp:cpVect( v:cpVect )
Function cpvrperp:cpVect( v:cpVect )
Function cpvproject:cpVect( v1:cpVect, v2:cpVect )
Function cpvforangle:cpVect( a:cpFloat )
Function cpvtoangle:cpFloat( v:cpVect )
Function cpvrotate:cpVect( v1:cpVect, v2:cpVect )
Function cpvunrotate:cpVect( v1:cpVect, v2:cpVect )
Function cpvlengthsq:cpFloat( v:cpVect )
Function cpvlength:cpFloat( v:cpVect )
Function cpvlerp:cpVect( v1:cpVect, v2:cpVect, t:cpFloat )
Function cpvnormalize:cpVect( v:cpVect )
Function cpvslerp:cpVect( v1:cpVect, v2:cpVect, t:cpFloat )
Function cpvslerpconst:cpVect( v1:cpVect, v2:cpVect, a:cpFloat )
Function cpvclamp:cpVect( v:cpVect, len:cpFloat )
Function cpvlerpconst:cpVect( v1:cpVect, v2:cpVect, d:cpFloat )
Function cpvdist:cpFloat( v1:cpVect, v2:cpVect )
Function cpvdistsq:cpFloat( v1:cpVect, v2:cpVect )
Function cpvnear:cpBool( v1:cpVect, v2:cpVect, dist:cpFloat )
Function cpMat2x2New:cpMat2x2( a:cpFloat, b:cpFloat, c:cpFloat, d:cpFloat )
Function cpMat2x2Transform:cpVect( m:cpMat2x2, v:cpVect )

'***** File: Chipmunk7/include/chipmunk/cpBB.h *****

Struct cpBB
	Field l:cpFloat
	Field b:cpFloat
	Field r:cpFloat
	Field t:cpFloat
End
Function cpBBNew:cpBB( l:cpFloat, b:cpFloat, r:cpFloat, t:cpFloat )
Function cpBBNewForExtents:cpBB( c:cpVect, hw:cpFloat, hh:cpFloat )
Function cpBBNewForCircle:cpBB( p:cpVect, r:cpFloat )
Function cpBBIntersects:cpBool( a:cpBB, b:cpBB )
Function cpBBContainsBB:cpBool( bb:cpBB, other:cpBB )
Function cpBBContainsVect:cpBool( bb:cpBB, v:cpVect )
Function cpBBMerge:cpBB( a:cpBB, b:cpBB )
Function cpBBExpand:cpBB( bb:cpBB, v:cpVect )
Function cpBBCenter:cpVect( bb:cpBB )
Function cpBBArea:cpFloat( bb:cpBB )
Function cpBBMergedArea:cpFloat( a:cpBB, b:cpBB )
Function cpBBSegmentQuery:cpFloat( bb:cpBB, a:cpVect, b:cpVect )
Function cpBBIntersectsSegment:cpBool( bb:cpBB, a:cpVect, b:cpVect )
Function cpBBClampVect:cpVect( bb:cpBB, v:cpVect )
Function cpBBWrapVect:cpVect( bb:cpBB, v:cpVect )
Function cpBBOffset:cpBB( bb:cpBB, v:cpVect )

'***** File: Chipmunk7/include/chipmunk/cpTransform.h *****

Const cpTransformIdentity:cpTransform
Function cpTransformNew:cpTransform( a:cpFloat, b:cpFloat, c:cpFloat, d:cpFloat, tx:cpFloat, ty:cpFloat )
Function cpTransformNewTranspose:cpTransform( a:cpFloat, c:cpFloat, tx:cpFloat, b:cpFloat, d:cpFloat, ty:cpFloat )
Function cpTransformInverse:cpTransform( t:cpTransform )
Function cpTransformMult:cpTransform( t1:cpTransform, t2:cpTransform )
Function cpTransformPoint:cpVect( t:cpTransform, p:cpVect )
Function cpTransformVect:cpVect( t:cpTransform, v:cpVect )
Function cpTransformbBB:cpBB( t:cpTransform, bb:cpBB )
Function cpTransformTranslate:cpTransform( translate:cpVect )
Function cpTransformScale:cpTransform( scaleX:cpFloat, scaleY:cpFloat )
Function cpTransformRotate:cpTransform( radians:cpFloat )
Function cpTransformRigid:cpTransform( translate:cpVect, radians:cpFloat )
Function cpTransformRigidInverse:cpTransform( t:cpTransform )
Function cpTransformWrap:cpTransform( outer:cpTransform, inner:cpTransform )
Function cpTransformWrapInverse:cpTransform( outer:cpTransform, inner:cpTransform )
Function cpTransformOrtho:cpTransform( bb:cpBB )
Function cpTransformBoneScale:cpTransform( v0:cpVect, v1:cpVect )
Function cpTransformAxialScale:cpTransform( axis:cpVect, pivot:cpVect, scale:cpFloat )

