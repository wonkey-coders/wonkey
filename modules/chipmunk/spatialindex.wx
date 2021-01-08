
Namespace chipmunk

Extern

'***** File: Chipmunk7/include/chipmunk/cpSpatialIndex.h *****

'Note: raw types/functions only - haven't had a good look at this yet.

Alias cpSpatialIndexBBFunc:cpBB( Void Ptr )
Alias cpSpatialIndexIteratorFunc:Void( Void Ptr, Void Ptr )
Alias cpSpatialIndexQueryFunc:cpCollisionID( Void Ptr, Void Ptr, cpCollisionID, Void Ptr )
Alias cpSpatialIndexSegmentQueryFunc:cpFloat( Void Ptr, Void Ptr, Void Ptr )
Struct cpSpatialIndex
	Field klass:cpSpatialIndexClass Ptr
	Field bbfunc:cpSpatialIndexBBFunc
	Field staticIndex:cpSpatialIndex Ptr
	Field dynamicIndex:cpSpatialIndex Ptr
End
Function cpSpaceHashAlloc:cpSpaceHash Ptr(  )
Function cpSpaceHashInit:cpSpatialIndex Ptr( hash:cpSpaceHash Ptr, celldim:cpFloat, numcells:Int, bbfunc:cpSpatialIndexBBFunc, staticIndex:cpSpatialIndex Ptr )
Function cpSpaceHashNew:cpSpatialIndex Ptr( celldim:cpFloat, cells:Int, bbfunc:cpSpatialIndexBBFunc, staticIndex:cpSpatialIndex Ptr )
Function cpSpaceHashResize:Void( hash:cpSpaceHash Ptr, celldim:cpFloat, numcells:Int )
Function cpBBTreeAlloc:cpBBTree Ptr(  )
Function cpBBTreeInit:cpSpatialIndex Ptr( tree:cpBBTree Ptr, bbfunc:cpSpatialIndexBBFunc, staticIndex:cpSpatialIndex Ptr )
Function cpBBTreeNew:cpSpatialIndex Ptr( bbfunc:cpSpatialIndexBBFunc, staticIndex:cpSpatialIndex Ptr )
Function cpBBTreeOptimize:Void( index:cpSpatialIndex Ptr )
Alias cpBBTreeVelocityFunc:cpVect( Void Ptr )
Function cpBBTreeSetVelocityFunc:Void( index:cpSpatialIndex Ptr, func:cpBBTreeVelocityFunc )
Function cpSweep1DAlloc:cpSweep1D Ptr(  )
Function cpSweep1DInit:cpSpatialIndex Ptr( sweep:cpSweep1D Ptr, bbfunc:cpSpatialIndexBBFunc, staticIndex:cpSpatialIndex Ptr )
Function cpSweep1DNew:cpSpatialIndex Ptr( bbfunc:cpSpatialIndexBBFunc, staticIndex:cpSpatialIndex Ptr )
Alias cpSpatialIndexDestroyImpl:Void( cpSpatialIndex Ptr )
Alias cpSpatialIndexCountImpl:Int( cpSpatialIndex Ptr )
Alias cpSpatialIndexEachImpl:Void( cpSpatialIndex Ptr, cpSpatialIndexIteratorFunc, Void Ptr )
Alias cpSpatialIndexContainsImpl:cpBool( cpSpatialIndex Ptr, Void Ptr, cpHashValue )
Alias cpSpatialIndexInsertImpl:Void( cpSpatialIndex Ptr, Void Ptr, cpHashValue )
Alias cpSpatialIndexRemoveImpl:Void( cpSpatialIndex Ptr, Void Ptr, cpHashValue )
Alias cpSpatialIndexReindexImpl:Void( cpSpatialIndex Ptr )
Alias cpSpatialIndexReindexObjectImpl:Void( cpSpatialIndex Ptr, Void Ptr, cpHashValue )
Alias cpSpatialIndexReindexQueryImpl:Void( cpSpatialIndex Ptr, cpSpatialIndexQueryFunc, Void Ptr )
Alias cpSpatialIndexQueryImpl:Void( cpSpatialIndex Ptr, Void Ptr, cpBB, cpSpatialIndexQueryFunc, Void Ptr )
Alias cpSpatialIndexSegmentQueryImpl:Void( cpSpatialIndex Ptr, Void Ptr, cpVect, cpVect, cpFloat, cpSpatialIndexSegmentQueryFunc, Void Ptr )
Struct cpSpatialIndexClass
	Field destroy:cpSpatialIndexDestroyImpl
	Field count:cpSpatialIndexCountImpl
	Field each:cpSpatialIndexEachImpl
	Field contains:cpSpatialIndexContainsImpl
	Field insert:cpSpatialIndexInsertImpl
	Field remove:cpSpatialIndexRemoveImpl
	Field reindex:cpSpatialIndexReindexImpl
	Field reindexObject:cpSpatialIndexReindexObjectImpl
	Field reindexQuery:cpSpatialIndexReindexQueryImpl
	Field query:cpSpatialIndexQueryImpl
	Field segmentQuery:cpSpatialIndexSegmentQueryImpl
End
Function cpSpatialIndexFree:Void( index:cpSpatialIndex Ptr )
Function cpSpatialIndexCollideStatic:Void( dynamicIndex:cpSpatialIndex Ptr, staticIndex:cpSpatialIndex Ptr, func:cpSpatialIndexQueryFunc, data:Void Ptr )
Function cpSpatialIndexDestroy:Void( index:cpSpatialIndex Ptr )
Function cpSpatialIndexCount:Int( index:cpSpatialIndex Ptr )
Function cpSpatialIndexEach:Void( index:cpSpatialIndex Ptr, func:cpSpatialIndexIteratorFunc, data:Void Ptr )
Function cpSpatialIndexContains:cpBool( index:cpSpatialIndex Ptr, obj:Void Ptr, hashid:cpHashValue )
Function cpSpatialIndexInsert:Void( index:cpSpatialIndex Ptr, obj:Void Ptr, hashid:cpHashValue )
Function cpSpatialIndexRemove:Void( index:cpSpatialIndex Ptr, obj:Void Ptr, hashid:cpHashValue )
Function cpSpatialIndexReindex:Void( index:cpSpatialIndex Ptr )
Function cpSpatialIndexReindexObject:Void( index:cpSpatialIndex Ptr, obj:Void Ptr, hashid:cpHashValue )
Function cpSpatialIndexQuery:Void( index:cpSpatialIndex Ptr, obj:Void Ptr, bb:cpBB, func:cpSpatialIndexQueryFunc, data:Void Ptr )
Function cpSpatialIndexSegmentQuery:Void( index:cpSpatialIndex Ptr, obj:Void Ptr, a:cpVect, b:cpVect, t_exit:cpFloat, func:cpSpatialIndexSegmentQueryFunc, data:Void Ptr )
Function cpSpatialIndexReindexQuery:Void( index:cpSpatialIndex Ptr, func:cpSpatialIndexQueryFunc, data:Void Ptr )

Struct cpSpaceHash
End

Struct cpBBTree
End

Struct cpSweep1D
End
