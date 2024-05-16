#include "world.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

//assigning NULL
pbBody* pbBodies = 0;
int pbBodyCount = 0;
Vector2 pbGravity;

pbBody* CreateBody(Vector2 position, float mass, pbBodyType bodyType)
{
	pbBody* body = (pbBody*)malloc(sizeof(pbBody));

	assert(body);
	memset(body, 0, sizeof(pbBody));
    body->position = position;
    body->mass = mass;
    body->imass = (bodyType == BT_Dynamic) ? 1 / mass : 0;
    body->type = bodyType;


	return body;
}

void AddBody(pbBody* body)
{
    assert(body);

    //add element to linked list
    body->prev = NULL;
    body->next = pbBodies;

    if (pbBodies) pbBodies->prev = body;

    //set head of bodies to new element
    pbBodies = body;

    pbBodyCount++;
}

void DestroyBody(pbBody* body)
{
	//Assert if provided Body is not NULL
	assert(body);
	//	If 'prev' is not NULL, set 'prev->next' to 'body->next'
	if (body->prev) body->prev->next = body->next;
	//	If 'next' is not NULL, set 'next->prev' to 'body->prev'
	if (body->next) body->next->prev = body->prev;
	//	If body is the head, update head to 'body->next'
	if (pbBodies == body) pbBodies = body->next;
	//	Decrement body count
	pbBodyCount--;
	//	Free the body
	free(body);
}