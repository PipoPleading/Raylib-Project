#include "force.h"
#include "body.h"

void ApplyGravitation(pbBody* bodies, float strength)
{
    for (pbBody* body1 = bodies; body1; body1 = body1->next)
    {
        for (pbBody* body2 = bodies; body2; body2 = body2->next)
        {
            if(body1 == body2){
                
                Vector2 dir = Vector2Subtract(body2->position, body1->position);
                float distance = Vector2Length(dir);

                distance = fmaxf(1, distance);
                float force = ((body1->mass * body2->mass) / (distance * distance))* strength;

                dir = Vector2Scale(Vector2Normalize(dir), force);

                ApplyForce(body1, dir, FM_Force);
                ApplyForce(body2, Vector2Negate(dir), FM_Force);
            }
        }
    }

}
