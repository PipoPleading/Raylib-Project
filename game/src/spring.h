#pragma once

typedef struct pbSpring
{
    struct pbBody* body1;
    struct pbBody* body2;
    float restLength;
    float k; //stiffness

    struct pbSpring* next;
    struct pbSpring* prev;
} pbSpring_t;

extern pbSpring_t* pbSprings;

//forward declaration to prevent excess header inclusion
pbSpring_t* CreateSpring(struct pbBody* body1, struct pbBody* body2, float restLength, float k);
void AddSpring(pbSpring_t* spring);
void DestroySpring(pbSpring_t* spring);
void DestroyAllSprings();

void ApplySpringForce(pbSpring_t* springs);