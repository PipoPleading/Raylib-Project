#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum pbBodyType
{
    //body type
	BT_Static,
	BT_Kinematic,
	BT_Dynamic
}pbBodyType;

typedef enum
{
    FM_Force,
    FM_Impulse,
    FM_Velocity
}pbForceMode;

typedef struct pbBody
{
	pbBodyType type;
	// acceleration -> velocity
	// velocity -> position

	Vector2 position;
	Vector2 velocity;
    Vector2 acceleration;
	Vector2 force;

	float mass;
	float imass; // 1/mass (static = 0)
    float gravityScale;
    float damping;

	struct pbBody* next;
	struct pbBody* prev;

} pbBody;

inline void ApplyForce(pbBody* body, Vector2 force, pbForceMode fm)
{
    if (body->type != BT_Dynamic) return;

    switch (fm)
    {
    case FM_Force:
    	body->force = Vector2Add(body->force, force);
        break;
    case FM_Impulse:
        // applies a sudden change in momentum
        body->velocity = Vector2Scale(force, body->imass);
        break;
    case FM_Velocity:
        body->velocity = force;
        break;
    }

}

inline void ClearForce(pbBody* body)
{
	body->force = Vector2Zero();
}

void Step(pbBody* body, float timestep);