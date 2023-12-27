#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.h"
#include <functional>
#include "Map.h"

class Collidable;

struct CollisionData {
	std::vector<Collidable*> collidedCollidables;
};

using OnCollisionEnter = std::vector<std::function<void(Collidable*)>>;
using OnCollisionExit = std::vector<std::function<void(Collidable*)>>;

class Collider
{
public:
	Collider(sf::RectangleShape* rect);

	bool CheckCollisionEnter(Collidable* other);
	bool CheckCollisionExit(Collidable* other);

	OnCollisionEnter onCollisionEnter;
	template <typename T>
	void BindOnCollisionEnter(T* instance, void (T::* method)(Collidable*)) {
		onCollisionEnter.push_back(std::bind(method, instance, std::placeholders::_1));
	}

	OnCollisionExit onCollisionExit;
	template <typename T>
	void BindOnCollisionExit(T* instance, void (T::* method)(Collidable*)) {
		onCollisionExit.push_back(std::bind(method, instance, std::placeholders::_1));
	}

	sf::RectangleShape* GetCollisionCheckerRect();

private:
	bool checkCollisionCheckerIntersection(Collider* other);

	/*
	Outer collider is used to detect collision enter and exit.
	It is used in taking damage, hit, etc.
	*/
	sf::RectangleShape* collisionSensorRect;

	CollisionData data;
};