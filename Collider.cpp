#include "Collider.h"
#include "Collidable.h"
#include <cstdlib>
#include <iostream>
#include "MapObject.h"

Collider::Collider(sf::RectangleShape* rect)
{
	collisionSensorRect = rect;
}

sf::RectangleShape* Collider::GetCollisionCheckerRect()
{
	return collisionSensorRect;
}

bool Collider::CheckCollisionEnter(Collidable* other)
{
	if (!other)
	{
		return false;
	}

	for (auto& collidable : data.collidedCollidables)
	{
		if (other == collidable)
		{
			return false;
		}
	}

	bool isCollided = collisionSensorRect->getGlobalBounds().intersects(other->GetCollider()->collisionSensorRect->getGlobalBounds());

	if (isCollided)
	{
		data.collidedCollidables.push_back(other);

		for (auto& method : onCollisionEnter)
		{
			method(other);
		}
	}

	return isCollided;
}

bool Collider::CheckCollisionExit(Collidable* other)
{
	auto it = std::find(data.collidedCollidables.begin(), data.collidedCollidables.end(), other);

	if (it != data.collidedCollidables.end())
	{
		if (!checkCollisionCheckerIntersection(other->GetCollider()))
		{
			data.collidedCollidables.erase(it);

			for (auto& method : onCollisionExit)
			{
				method(other);
			}
			return true;
		}
	}

	return false;
}


bool Collider::checkCollisionCheckerIntersection(Collider* other)
{
	bool intersection = collisionSensorRect->getGlobalBounds().intersects(other->collisionSensorRect->getGlobalBounds());

	return intersection;
}

