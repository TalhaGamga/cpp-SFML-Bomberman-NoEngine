#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 
#include "EventManager.h"
#include "Bomb.h"
#include <functional>
#include <unordered_map>
#include "Collidable.h"
#include "MapObject.h"
#include "Map.h"
#include "Damageable.h"
#include "HealthBar.h"

class Bomb;

class CharacterBase : public MapObject, public Collidable, public Damageable
{
public:
	CharacterBase(MapData* mapData);

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

	virtual void SetMovementDirection(sf::Vector2i direction) = 0;
	virtual void DropBomb() = 0;

protected:
	sf::RectangleShape* charShape;

	sf::Vector2i direction;
	sf::Vector2f moveTo;
	sf::Vector2f size;
	float moveSpeed = 50.0f;
	Bomb* bomb;

	virtual void moveUp(sf::Time elapsed) = 0;
	virtual void moveDown(sf::Time elapsed) = 0;
	virtual void moveRight(sf::Time elapsed) = 0;
	virtual void moveLeft(sf::Time elapsed) = 0;
	virtual void idle(sf::Time elapsed) = 0;

	sf::Vector2i movementDirection;

	HealthBar* healthBar;
};