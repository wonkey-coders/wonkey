
#include "chipmunk_glue.h"

// ***** cpCollisionHandler *****

namespace{

	cpBool collisionTrueFunc( cpArbiter *arbiter,cpSpace *space,cpDataPointer data ){
		return true;
	}

	void collisionVoidFunc( cpArbiter *arbiter,cpSpace *space,cpDataPointer data ){
	}

	cpBool collisionBeginFunc( cpArbiter *arbiter,cpSpace *space,cpDataPointer data ){
		wx_cpCollisionHandler *handler=(wx_cpCollisionHandler*)data;
		
		return handler->beginFunc( arbiter,space,handler->userData );
	}

	cpBool collisionPreSolveFunc( cpArbiter *arbiter,cpSpace *space,cpDataPointer data ){
		wx_cpCollisionHandler *handler=(wx_cpCollisionHandler*)data;
		
		return handler->preSolveFunc( arbiter,space,handler->userData );
	}

	void collisionPostSolveFunc( cpArbiter *arbiter,cpSpace *space,cpDataPointer data ){
		wx_cpCollisionHandler *handler=(wx_cpCollisionHandler*)data;
		
		handler->postSolveFunc( arbiter,space,handler->userData );
	}

	void collisionSeparateFunc( cpArbiter *arbiter,cpSpace *space,cpDataPointer data ){
		wx_cpCollisionHandler *handler=(wx_cpCollisionHandler*)data;
		
		handler->separateFunc( arbiter,space,handler->userData );
	}
	
	wx_cpCollisionHandler *wxHandler( cpCollisionHandler *handler ){
	
		wx_cpCollisionHandler *wxhandler=(wx_cpCollisionHandler*)handler->userData;
		if( wxhandler ) return wxhandler;
		
		wxhandler=new wx_cpCollisionHandler;	//FIXME: GC leak!
		wxhandler->typeA=handler->typeA;		//assume these are const-ish?
		wxhandler->typeB=handler->typeB;
		wxhandler->beginFunc=wxMakefunc( collisionTrueFunc );
		wxhandler->preSolveFunc=wxMakefunc( collisionTrueFunc );
		wxhandler->postSolveFunc=wxMakefunc( collisionVoidFunc );
		wxhandler->separateFunc=wxMakefunc( collisionVoidFunc );
			
		handler->beginFunc=collisionBeginFunc;
		handler->preSolveFunc=collisionPreSolveFunc;
		handler->postSolveFunc=collisionPostSolveFunc;
		handler->separateFunc=collisionSeparateFunc;
		handler->userData=wxhandler;

		return wxhandler;
	}
}

void wx_cpCollisionHandler::gcMark(){
	wxGCMark( beginFunc );
	wxGCMark( preSolveFunc );
	wxGCMark( postSolveFunc );
	wxGCMark( separateFunc );
}

wx_cpCollisionHandler *wx_cpSpaceAddDefaultCollisionHandler( cpSpace *space ){
	cpCollisionHandler *handler=cpSpaceAddDefaultCollisionHandler( space );
	return wxHandler( handler );
}

wx_cpCollisionHandler *wx_cpSpaceAddCollisionHandler( cpSpace *space,cpCollisionType a,cpCollisionType b ){
	cpCollisionHandler *handler=cpSpaceAddCollisionHandler( space,a,b );
	return wxHandler( handler );	
}

wx_cpCollisionHandler *wx_cpSpaceAddWildcardHandler( cpSpace *space,cpCollisionType t ){
	cpCollisionHandler *handler=cpSpaceAddWildcardHandler( space,t );
	return wxHandler( handler );	
}

// ***** cpSpaceDebugDraw *****

namespace{

	void debugDrawCircle(cpVect pos, cpFloat angle, cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor, cpDataPointer data ){
		wx_cpSpaceDebugDrawOptions *opts=(wx_cpSpaceDebugDrawOptions*)data;
		
		opts->drawCircle( pos,angle,radius,outlineColor,fillColor,opts->userData );
	}
	
	void debugDrawSegment(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data){
		wx_cpSpaceDebugDrawOptions *opts=(wx_cpSpaceDebugDrawOptions*)data;
		
		opts->drawSegment( a,b,color,opts->userData );
	}
	
	void debugDrawFatSegment(cpVect a, cpVect b, cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor, cpDataPointer data){
		wx_cpSpaceDebugDrawOptions *opts=(wx_cpSpaceDebugDrawOptions*)data;
		
		opts->drawFatSegment( a,b,radius,outlineColor,fillColor,opts->userData );
	}
	
	void debugDrawPolygon(int count, const cpVect *verts, cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor, cpDataPointer data){
		wx_cpSpaceDebugDrawOptions *opts=(wx_cpSpaceDebugDrawOptions*)data;
		
		opts->drawPolygon( count,(cpVect*)verts,radius,outlineColor,fillColor,opts->userData );
	}
	
	void debugDrawDot(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data){
		wx_cpSpaceDebugDrawOptions *opts=(wx_cpSpaceDebugDrawOptions*)data;
		
		opts->drawDot( size,pos,color,opts->userData );
	}
	
	cpSpaceDebugColor debugDrawColorForShape(cpShape *shape, cpDataPointer data){
		wx_cpSpaceDebugDrawOptions *opts=(wx_cpSpaceDebugDrawOptions*)data;
		
		return opts->colorForShape( shape,opts->userData );
	}
}

void wx_cpSpaceDebugDrawOptions::gcMark(){

	wxGCMark( drawCircle );
	wxGCMark( drawSegment );
	wxGCMark( drawFatSegment );
	wxGCMark( drawPolygon );
	wxGCMark( colorForShape );
}

void wx_cpSpaceDebugDraw( cpSpace *space,wx_cpSpaceDebugDrawOptions *options ){

	cpSpaceDebugDrawOptions opts;
	
	opts.drawCircle=debugDrawCircle;
	opts.drawSegment=debugDrawSegment;
	opts.drawFatSegment=debugDrawFatSegment;
	opts.drawPolygon=debugDrawPolygon;
	opts.drawDot=debugDrawDot;
	opts.flags=options->flags;
	opts.shapeOutlineColor=options->shapeOutlineColor;
	opts.colorForShape=debugDrawColorForShape;
	opts.constraintColor=options->constraintColor;
	opts.collisionPointColor=options->collisionPointColor;
	opts.data=options;
	
	cpSpaceDebugDraw( space,&opts );
}
