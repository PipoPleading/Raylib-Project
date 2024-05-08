#pragma once
#include "body.h"

inline void ExplicitEuler(pbBody* body, float timestep)
{
    body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
    //inverse mass is used here, needs to be updated later
    body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
}

inline  void SemiImplicitEuler(pbBody* body, float timestep) 
{
    //inverse mass is used here, needs to be updated later
    body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
    body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
}