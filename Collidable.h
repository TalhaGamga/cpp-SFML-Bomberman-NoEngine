#pragma once
#include "Collider.h"
#include <string>

class Collider;

class Collidable
{
public:
	bool isObstacle;
	Collider* GetCollider();
	bool isKilled = false;

protected:
	Collider* wideCollider;

	virtual void CheckCollision() = 0;

	virtual void onCollisionEnter(Collidable* other) = 0;

	virtual void onCollisionExit(Collidable* other) = 0;
};