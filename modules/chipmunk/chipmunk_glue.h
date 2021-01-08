
#ifndef WX_CHIPMUNK_GLUE_H
#define WX_CHIPMUNK_GLUE_H

#include <chipmunk/chipmunk.h>

#include <wxwonkey.h>

// ***** cpCollisionHandler *****

typedef wxFunction<cpBool(cpArbiter*,cpSpace*,cpDataPointer)> wx_cpCollisionBeginFunc;
typedef wxFunction<cpBool(cpArbiter*,cpSpace*,cpDataPointer)> wx_cpCollisionPreSolveFunc;
typedef wxFunction<void(cpArbiter*,cpSpace*,cpDataPointer)> wx_cpCollisionPostSolveFunc;
typedef wxFunction<void(cpArbiter*,cpSpace*,cpDataPointer)> wx_cpCollisionSeparateFunc;

struct wx_cpCollisionHandler : public wxObject{

	cpCollisionType typeA;
	cpCollisionType typeB;
	wx_cpCollisionBeginFunc beginFunc;
	wx_cpCollisionPreSolveFunc preSolveFunc;
	wx_cpCollisionPostSolveFunc postSolveFunc;
	wx_cpCollisionSeparateFunc separateFunc;
	cpDataPointer userData;
	
	void gcMark();
};

wx_cpCollisionHandler *wx_cpSpaceAddDefaultCollisionHandler( cpSpace* );
wx_cpCollisionHandler *wx_cpSpaceAddCollisionHandler( cpSpace*,cpCollisionType,cpCollisionType );
wx_cpCollisionHandler *wx_cpSpaceAddWildcardHandler( cpSpace*,cpCollisionType );

// ***** cpSpaceDebugDraw *****

typedef wxFunction<void(cpVect,cpFloat,cpFloat,cpSpaceDebugColor,cpSpaceDebugColor,cpDataPointer)> wx_cpSpaceDebugDrawCircleImpl;
typedef wxFunction<void(cpVect,cpVect,cpSpaceDebugColor,cpDataPointer)> wx_cpSpaceDebugDrawSegmentImpl;
typedef wxFunction<void(cpVect,cpVect,cpFloat,cpSpaceDebugColor,cpSpaceDebugColor,cpDataPointer)> wx_cpSpaceDebugDrawFatSegmentImpl;
typedef wxFunction<void(int,cpVect*,cpFloat,cpSpaceDebugColor,cpSpaceDebugColor,cpDataPointer)> wx_cpSpaceDebugDrawPolygonImpl;
typedef wxFunction<void(cpFloat,cpVect,cpSpaceDebugColor,cpDataPointer)> wx_cpSpaceDebugDrawDotImpl;
typedef wxFunction<cpSpaceDebugColor(cpShape*,cpDataPointer)> wx_cpSpaceDebugDrawColorForShapeImpl;

struct wx_cpSpaceDebugDrawOptions : public wxObject{

	wx_cpSpaceDebugDrawCircleImpl drawCircle;
	wx_cpSpaceDebugDrawSegmentImpl drawSegment;
	wx_cpSpaceDebugDrawFatSegmentImpl drawFatSegment;
	wx_cpSpaceDebugDrawPolygonImpl drawPolygon;
	wx_cpSpaceDebugDrawDotImpl drawDot;
	cpSpaceDebugDrawFlags flags;
	cpSpaceDebugColor shapeOutlineColor;
	wx_cpSpaceDebugDrawColorForShapeImpl colorForShape;
	cpSpaceDebugColor constraintColor;
	cpSpaceDebugColor collisionPointColor;
	cpDataPointer userData;
	
	void gcMark();
};

void wx_cpSpaceDebugDraw( cpSpace *space,wx_cpSpaceDebugDrawOptions *options );

#endif
