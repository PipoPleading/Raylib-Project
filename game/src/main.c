#include "body.h"
#include "mathf.h"
#include "integrator.h"
#include "world.h"
#include "force.h"
#include "render.h"
#include "editor.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include <world.c>

#define MAX_BODIES 100000

int main(void)
{
	//resolution
	InitWindow(800, 450, "Physics Engine");
	SetTargetFPS(60);

    //initialize world
    pbGravity = (Vector2){ 0, -1 };

	// game loop
	while (!WindowShouldClose())
	{
		// update
		//deltatime :pog:
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
        pbScreenZoom += GetMouseWheelMove() * 0.2f;
        pbScreenZoom = Clamp(pbScreenZoom, 0.1f, 10);
        UpdateEditor(position);

        //potential for loop
		if (IsMouseButtonDown(0))
		{
            //constructing bodies
			pbBody* body = CreateBody();
			body->position = ConvertScreenToWorld(position);
            body->mass = GetRandomFloatValue01(0.1f, 1);
            body->imass = 1 / body->mass;
            body->type = BT_Dynamic;
            body->damping = 0.5f; //0 is cool
            body->gravityScale = 20;

            //applying effects
            //ApplyForce(body, (Vector2) { GetRandomFloatValue01(-100, 100), GetRandomFloatValue01(-100, 100) }, FM_Velocity);
		}

        //apply force
        ApplyGravitation(pbBodies, 30);

		//update bodies
        for (pbBody* body = pbBodies; body; body = body->next)
        {
            Step(body, dt);

        }

		// render
		BeginDrawing();
		ClearBackground(BLACK);

        DrawEditor();

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10, 10, 20, LIME );
		DrawText(TextFormat("FRAME: %.4f", dt),10, 30, 20, LIME );

        DrawCircle((int)position.x, (int)position.y, 5, SKYBLUE);

		//minor cursor delay
        for (pbBody* body = pbBodies; body; body = body->next)
        {
            Vector2 screen = ConvertWorldToScreen(body->position);
            DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), GREEN);

        }

		//DrawCircle((int)position.x, (int)position.y, body->mass, SKYBLUE);

		EndDrawing();
	}

	CloseWindow();

	free(pbBodies);

	return 0;
}