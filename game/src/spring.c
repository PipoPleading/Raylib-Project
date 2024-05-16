#include "world.h"
#include "spring.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

pbSpring_t* pbSprings = NULL;

pbSpring_t* CreateSpring(struct pbBody* body1, struct pbBody* body2, float restLength, float k)
{
    pbSpring_t* spring = (pbSpring_t*)malloc(sizeof(pbSpring_t));
    assert(spring);

    memset(spring, 0, sizeof(pbSpring_t));
    spring->body1 = body1;
    spring->body2 = body2;
    spring->restLength = restLength;
    spring->k = k;


    return spring;
}

void AddSpring(pbSpring_t* spring)
{
    assert(spring);

    //add element to linked list
    spring->prev = NULL;
    spring->next = pbSprings;

    if (pbSprings) pbSprings->prev = spring;

    //set head of bodies to new element
    pbSprings = spring;

}

void DestroySpring(pbSpring_t* spring)
{
    assert(spring);

    if (spring->prev) spring->prev->next = spring->next;
    if (spring->next) spring->next->prev = spring->prev;

    if (spring == pbSprings) pbSprings = spring->next;

    free(spring);
}

void ApplySpringForce(pbSpring_t* springs) {
    for (pbSpring_t* spring = springs; spring; spring = spring->next)
    {
        Vector2 direction = Vector2Subtract(spring->body2->position, spring->body1->position);
        if (direction.x == 0 && direction.y == 0) continue;

        float length = Vector2Length(direction);
        float x = length - spring->restLength;
        float force = -spring->k * x; // f = -kx <- Hooke's Law

        Vector2 ndirection = Vector2Normalize(direction);

        ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_Force);
        ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_Force);
    }
}