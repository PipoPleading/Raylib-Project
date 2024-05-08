#pragma once
//#include "body.h"
// or	
#include "raylib.h"
typedef struct pbBody pbBody;

extern pbBody* pbBodies;
extern int pbBodyCount;
extern Vector2 pbGravity;

pbBody* CreateBody();
void DestroyBody(pbBody* body);
