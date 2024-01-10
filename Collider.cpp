#include "Collider.h"
#include "Collidable.h"
#include <cstdlib>
#include <iostream>
#include "MapObject.h"

// Constructor for Collider class
Collider::Collider(sf::RectangleShape* rect)
{
    collisionSensorRect = rect;
}

// Getter function to retrieve the collision checker rectangle
sf::RectangleShape* Collider::GetCollisionCheckerRect()
{
    return collisionSensorRect;
}

// Check if a collision with another Collidable has occurred, trigger events if so
bool Collider::CheckCollisionEnter(Collidable* other)
{
    // Check if the other Collidable is valid
    if (!other)
    {
        return false;
    }

    // Check if the other Collidable is already in the collidedCollidables list
    for (auto& collidable : data.collidedCollidables)
    {
        if (other == collidable)
        {
            return false;
        }
    }

    // Check for intersection with the global bounds of the collision rectangles
    bool isCollided = collisionSensorRect->getGlobalBounds().intersects(other->GetCollider()->collisionSensorRect->getGlobalBounds());

    // If a collision occurred, add the Collidable to the collidedCollidables list and trigger events
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

// Check if a collision exit has occurred with another Collidable, trigger events if so
bool Collider::CheckCollisionExit(Collidable* other)
{
    // Find the other Collidable in the collidedCollidables list
    auto it = std::find(data.collidedCollidables.begin(), data.collidedCollidables.end(), other);

    // If found in the list, check for collision exit and trigger events
    if (it != data.collidedCollidables.end())
    {
        // If there is no longer an intersection, remove from collidedCollidables and trigger events
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

// Check if there is an intersection between the collision checker rectangles of two Colliders
bool Collider::checkCollisionCheckerIntersection(Collider* other)
{
    // Check for intersection of global bounds of the collision rectangles
    bool intersection = collisionSensorRect->getGlobalBounds().intersects(other->collisionSensorRect->getGlobalBounds());

    return intersection;
}
