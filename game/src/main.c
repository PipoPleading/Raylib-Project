#include "body.h"
#include "mathf.h"
#include "integrator.h"
#include "world.h"
#include "force.h"
#include "render.h"
#include "editor.h"
#include "spring.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100000

int main(void)
{
    pbBody* selectedBody = NULL;
    pbBody* connectBody = NULL;

	//resolution
	InitWindow(1280, 720, "Physics Engine");
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

        selectedBody = GetBodyIntersect(pbBodies, position);
        if (selectedBody) {
            Vector2 screen = ConvertWorldToScreen(selectedBody->position);
            DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(selectedBody->mass) + 5, YELLOW);
        }

        //create body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
            //constructing bodies
			pbBody* body = CreateBody(ConvertScreenToWorld(position), pbEditorData.MassMinValue, pbEditorData.BodyTypeActive);

            body->damping = pbEditorData.DampingValue; //0 is cool
            body->gravityScale = pbEditorData.GravitationValue;


            AddBody(body);
            //applying effects
            //ApplyForce(body, (Vector2) { GetRandomFloatValue01(-100, 100), GetRandomFloatValue01(-100, 100) }, FM_Velocity);
		}

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectBody = selectedBody;
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) DrawLineBodyToPosition(connectBody, position);
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody) {
            if (selectedBody && selectedBody != connectBody) {
                pbSpring_t* spring = CreateSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position), 20);
                AddSpring(spring);
            }
        }

        //apply force
        ApplyGravitation(pbBodies, pbEditorData.GravitationValue);
        ApplySpringForce(pbSprings);

		//update bodies
        for (pbBody* body = pbBodies; body; body = body->next)
        {
            Step(body, dt);

        }

		// render
		BeginDrawing();
		ClearBackground(BLACK);


		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10, 10, 20, LIME );
		DrawText(TextFormat("FRAME: %.4f", dt),10, 30, 20, LIME );


        for (pbBody* body = pbBodies; body; body = body->next)
        {
            Vector2 screen = ConvertWorldToScreen(body->position);
            DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), GREEN);

        }

        for (pbSpring_t* spring = pbSprings; spring; spring = spring->next)
        {
            Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
            Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
            DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, PURPLE);

        }

        //new mouse draw
        DrawEditor(position);

		EndDrawing();
	}

	CloseWindow();

	free(pbBodies);

	return 0;
}