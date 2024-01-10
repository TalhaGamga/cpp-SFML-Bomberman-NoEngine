#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.h"
#include <functional>
#include "Map.h"

class Collidable;

// Structure to hold collision data, such as collided collidables.
struct CollisionData {
	std::vector<Collidable*> collidedCollidables;
};

// Type aliases for vectors of collision event functions.
using OnCollisionEnter = std::vector<std::function<void(Collidable*)>>;
using OnCollisionExit = std::vector<std::function<void(Collidable*)>>;

// Class representing a collider for detecting collisions with other collidable objects.
class Collider
{
public:
	// Constructor taking a pointer to a rectangle shape associated with the collider.
	Collider(sf::RectangleShape* rect);

	// Checks for collision enter with another collidable object.
	bool CheckCollisionEnter(Collidable* other);

	// Checks for collision exit with another collidable object.
	bool CheckCollisionExit(Collidable* other);

	// Vector of functions to be called when a collision enter event occurs.
	OnCollisionEnter onCollisionEnter;

	// Binds a member function to the collision enter event.
	template <typename T>
	void BindOnCollisionEnter(T* instance, void (T::* method)(Collidable*)) {
		onCollisionEnter.push_back(std::bind(method, instance, std::placeholders::_1));
	}

	// Vector of functions to be called when a collision exit event occurs.
	OnCollisionExit onCollisionExit;

	// Binds a member function to the collision exit event.
	template <typename T>
	void BindOnCollisionExit(T* instance, void (T::* method)(Collidable*)) {
		onCollisionExit.push_back(std::bind(method, instance, std::placeholders::_1));
	}

	// Gets the rectangle shape associated with the collision checker.
	sf::RectangleShape* GetCollisionCheckerRect();

private:
	// Checks for intersection between the collision checker and another collider.
	bool checkCollisionCheckerIntersection(Collider* other);

	/*
	Outer collider is used to detect collision enter and exit.
	It is used in taking damage, hit, etc.
	*/
	sf::RectangleShape* collisionSensorRect;

	// Structure to store collision data.
	CollisionData data;
};
