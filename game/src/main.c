#include"body.h"
#include "raylib.h"
#include "raymath.h"
#include "mathf.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100000

int main(void)
{
	//resolution
	InitWindow(800, 450, "Physics Engine");
	SetTargetFPS(60);

	//cating as it returns a void/base pointer
	Body* bodies = (Body*)malloc(sizeof(Body) * MAX_BODIES);
	//true if bodies exists, if not false
	assert(bodies);

	int bodyCount = 0;

	// game loop
	while (!WindowShouldClose())
	{
		// update
		//deltatime :pog:
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0))
		{
			bodies[bodyCount].position = position;
			bodies[bodyCount].velocity = CreateVector2(GetRandomFloatValue01(-5, 5), GetRandomFloatValue01(-5, 5));
			bodyCount++;
		}

		// render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10, 10, 20, LIME );
		DrawText(TextFormat("FRAME: %.4f", dt),10, 30, 20, LIME );

		//minor cursor delay
		for (int i = 0; i < bodyCount; i++)
		{
			bodies[i].position = Vector2Add(bodies[i].position, bodies[i].velocity);
			DrawCircle((int)bodies[i].position.x, (int)bodies[i].position.y, 10, GREEN);
		}

		DrawCircle((int)position.x, (int)position.y, 10, SKYBLUE);

		EndDrawing();
	}

	CloseWindow();

	free(bodies);

	return 0;
}