#pragma once
#include "Collider.h"
#include <string>

class Collider; // Forward declaration of the Collider class.

// Interface for objects that can be collided with.
class Collidable
{
public:
	// Indicates if the object is considered an obstacle.
	bool isObstacle;

	// Gets the collider associated with the object.
	Collider* GetCollider();

protected:
	// Pointer to a wider collider for more extensive collision detection.
	Collider* wideCollider;

	// Abstract method to check for collisions.
	virtual void CheckCollision() = 0;

	// Abstract method called when a collision with another collidable object occurs.
	virtual void onCollisionEnter(Collidable* other) = 0;

	// Abstract method called when the collision with another collidable object ends.
	virtual void onCollisionExit(Collidable* other) = 0;
};
