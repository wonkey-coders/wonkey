
#ifndef WX_COLLISIONDETECT_H
#define WX_COLLISIONDETECT_H

#include "btBulletDynamicsCommon.h"

void initCollisions( btDynamicsWorld *world );
void resetCollisions();
int  getNumCollisions();
void **getCollisions();

#endif
