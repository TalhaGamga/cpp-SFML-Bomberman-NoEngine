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

using OnCharacterDied = std::function<void()>;

// Base class for characters in the Bomberman game.
class CharacterBase : public MapObject, public Collidable, public Damageable
{
public:
	// Constructor taking a pointer to map data.
	CharacterBase(MapData* mapData);

	// Abstract method to draw the character on the screen.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

	// Abstract methods for setting movement direction and dropping bombs.
	virtual void SetMovementDirection(sf::Vector2i direction) = 0;
	virtual void DropBomb() = 0;

	// Event triggered when the character dies.
	OnCharacterDied onCharacterDied;

protected:
	// Shape representing the character.
	sf::RectangleShape* charShape;

	// Current movement direction.
	sf::Vector2i direction;

	// Target position to move to.
	sf::Vector2f moveTo;

	// Size of the character.
	sf::Vector2f size;

	// Speed at which the character moves.
	float moveSpeed = 50.0f;

	// Pointer to the bomb that the character can drop.
	Bomb* bomb;

	// Abstract methods for movement in different directions and idle state.
	virtual void moveUp(sf::Time elapsed) = 0;
	virtual void moveDown(sf::Time elapsed) = 0;
	virtual void moveRight(sf::Time elapsed) = 0;
	virtual void moveLeft(sf::Time elapsed) = 0;
	virtual void idle(sf::Time elapsed) = 0;

	// Current movement direction (used internally).
	sf::Vector2i movementDirection;

	// Health bar associated with the character.
	HealthBar* healthBar;
};
