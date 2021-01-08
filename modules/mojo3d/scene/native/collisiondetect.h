
#ifndef BB_COLLISIONDETECT_H
#define BB_COLLISIONDETECT_H

#include "btBulletDynamicsCommon.h"

void initCollisions( btDynamicsWorld *world );
void resetCollisions();
int  getNumCollisions();
void **getCollisions();

#endif
