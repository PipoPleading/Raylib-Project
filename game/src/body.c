#include "body.h"
#include "world.h"
#include "integrator.h"

void Step(pbBody* body, float timestep)
{
    //adding gravity to our force here
    body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(pbGravity, body->gravityScale), body->mass));

    body->acceleration = Vector2Scale(body->force, body->imass);

    SemiImplicitEuler(body, timestep);

    // apply damping
    float damping = 1 / (1 + (body->damping * timestep));
    body->velocity = Vector2Scale(body->velocity, damping);

    ClearForce(body);
}

