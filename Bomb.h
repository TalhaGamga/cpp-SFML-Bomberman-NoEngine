#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MapObject.h"
#include"Collidable.h"
#include "Explosion.h"
#include "CharacterBase.h"

class CharacterBase; // Forward declaration of CharacterBase class

// Bomb class, representing a bomb object in the Bomberman game
class Bomb : public MapObject, public Collidable
{
public:
	// Constructor: Initializes the Bomb object with a position, MapData, and the CharacterBase who dropped it
	Bomb(sf::Vector2f position, MapData* mapData, CharacterBase* dropper);

	// Update function for handling bomb logic
	void Update() override;

	// Tick function for time-based actions
	void Tick(sf::Time elapsed) override;

	// Render function for rendering the bomb on a window
	void Render(sf::RenderWindow* window) override;

	// SFML draw function for rendering the bomb
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	// Getter for the dropper of the bomb
	CharacterBase* GetDropper();

protected:
	// Check for collisions with other objects
	void CheckCollision() override;

	// Collision enter callback function
	virtual void onCollisionEnter(Collidable* other) override;

	// Collision exit callback function
	virtual void onCollisionExit(Collidable* other) override;

private:
	sf::RectangleShape bombShape; // Shape representing the bomb
	sf::Texture bombTexture;      // Texture for the bomb
	bool isExploded;              // Flag indicating whether the bomb has exploded
	float timer = 10;			  // Timer for bomb countdown
	CharacterBase* dropper;       // Pointer to the CharacterBase who dropped the bomb
};