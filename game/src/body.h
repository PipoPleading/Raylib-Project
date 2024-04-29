#pragma once
#include "raylib.h"

typedef struct Body
{
	// force -> velocity
	// velocity -> position

	Vector2 position;
	Vector2 velocity;
	Vector2 force;

} Body;