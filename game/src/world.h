#pragma once
#include "body.h"
#include "raylib.h"
typedef struct pbBody pbBody;

extern pbBody* pbBodies;
extern int pbBodyCount;
extern Vector2 pbGravity;

pbBody* CreateBody(Vector2 position, float mass, pbBodyType bodyType);
void AddBody(pbBody* body);
void DestroyBody(pbBody* body);
