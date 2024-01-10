#pragma once
#include <SFML/Graphics.hpp>
#include "MapObject.h"
#include "Collidable.h"
#include "Damageable.h"
#include "Map.h"
#include "Enums.h"
#include <unordered_map>

// Type alias for mapping directions to rotation angles
using AngleAxis = std::unordered_map<Direction2D, float>;

// Class representing an explosion in the game.
class Explosion : public MapObject, public Collidable
{
public:
	// Constructor taking map data, explosion direction, and position.
	Explosion(MapData* mapData, Direction2D direction, sf::Vector2f pos);

	// Update method called during the game loop.
	void Update() override;

	// Tick method called based on elapsed time.
	void Tick(sf::Time elapsed) override;

	// Render method for rendering the explosion.
	void Render(sf::RenderWindow* window) override;

	// Abstract method for drawing the explosion.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

protected:
	// Check for collisions with other collidable objects.
	void CheckCollision() override;

	// Called when a collision with another collidable object occurs.
	void onCollisionEnter(Collidable* other) override;

	// Called when the collision with another collidable object ends.
	void onCollisionExit(Collidable* other) override;

private:
	// Method to spread the explosion based on elapsed time.
	void Spread(sf::Time& elapsed);

	// Shape representing the explosion.
	sf::RectangleShape* explosionShape;

	// Texture for the explosion.
	sf::Texture explosionTexture;

	// Damage caused by the explosion.
	float damage;

	// Flag indicating if the explosion has collided with an object.
	bool isCollided = false;

	// Time after which the explosion is released.
	float releaseTime = 5.0f;

	// Mapping of directions to rotation angles.
	AngleAxis angleAxis{
		{Direction2D::Right, 0},
		{Direction2D::Down, 90},
		{Direction2D::Left, 180},
		{Direction2D::Up, 270} };
};
