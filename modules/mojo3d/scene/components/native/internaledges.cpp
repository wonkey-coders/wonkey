
#include "internaledges.h"

#include "BulletCollision/CollisionDispatch/btInternalEdgeUtility.h"

namespace{

	bool CustomMaterialCombinerCallback( btManifoldPoint& cp,const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper *colObj1Wrap,int partId1,int index1 ){
	
//		printf( "contact added internal edge contacts!\n" );fflush( stdout );
	
		btAdjustInternalEdgeContacts( cp,colObj1Wrap,colObj0Wrap,partId1,index1 );
		
//		cp.m_combinedRestitution=0;
		
//		cp.m_combinedFriction=1;
		
		return false;
	}
}

namespace bbBullet{

	void createInternalEdgeInfo( btBvhTriangleMeshShape *mesh ){
	
		printf( "create internal edge info!\n" );fflush( stdout );
		
		// enable callback
		gContactAddedCallback=CustomMaterialCombinerCallback;

		// create edge info
		btTriangleInfoMap *info=new btTriangleInfoMap();
		
		btGenerateInternalEdgeInfo( mesh,info );

		mesh->setTriangleInfoMap( info );
	}

}