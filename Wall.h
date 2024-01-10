#pragma once
#include "MapObject.h"
#include "Collidable.h"
#include "Map.h"

// Class representing a wall object in the game.
class Wall : public MapObject, public Collidable {
public:
	// Constructor taking the position and map data.
	Wall(sf::Vector2f pos, MapData* mapData);

	// Destructor.
	~Wall();

	// Update method called during the game loop.
	void Update() override;

	// Tick method for handling time-related updates.
	void Tick(sf::Time elapsed) override;

	// Render method for rendering the wall.
	void Render(sf::RenderWindow* window) override;

	// Overridden draw method from sf::Drawable.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	// Set the position of the wall.
	void SetPosition(sf::Vector2f pos);

	// Method to perform an attack on another collidable object.
	void Attack(Collidable* other);

protected:
	// Check for collisions.
	void CheckCollision() override;

	// Callback for when a collidable object enters the collision area.
	virtual void onCollisionEnter(Collidable* other) override;

	// Callback for when a collidable object exits the collision area.
	virtual void onCollisionExit(Collidable* other) override;

private:
	// Rectangle shape representing the wall.
	sf::RectangleShape wallShape;

	// Texture for the wall.
	sf::Texture wallTexture;

	// Pointer to the map data.
	MapData* mapData;
};