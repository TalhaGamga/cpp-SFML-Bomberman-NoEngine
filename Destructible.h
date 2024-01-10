#pragma once
#include "MapObject.h"
#include "Collidable.h"
#include "Damageable.h"

// Class representing a destructible object in the game.
class Destructible : public MapObject, public Collidable, public Damageable
{
public:
	// Constructor taking position and map data.
	Destructible(sf::Vector2f pos, MapData* mapData);

	// Update method called during the game loop.
	void Update() override;

	// Tick method called based on elapsed time.
	void Tick(sf::Time elapsed) override;

	// Render method for rendering the destructible object.
	void Render(sf::RenderWindow* window) override;

	// Abstract method for drawing the destructible object.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	// Method for taking damage.
	void TakeDamage(float damage) override;

	// Sets the position of the destructible object.
	void SetPosition(sf::Vector2f pos);

protected:
	// Check for collisions with other collidable objects.
	void CheckCollision() override;

	// Called when a collision with another collidable object occurs.
	virtual void onCollisionEnter(Collidable* other) override;

	// Called when the collision with another collidable object ends.
	virtual void onCollisionExit(Collidable* other) override;

private:
	// Shape representing the destructible object.
	sf::RectangleShape destructibleShape;

	// Texture for the destructible object.
	sf::Texture destructibleTexture;

	// Time during which damage affects the object.
	float damageAffectTime = 1;

	// Flag indicating if the object is currently damaged.
	bool isDamaged = false;

	// Represents red of rpg color 
	float r = 215.0f;
};
