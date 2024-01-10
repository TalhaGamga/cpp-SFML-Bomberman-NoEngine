#pragma once
#include "Map.h"

// Abstract class representing a game level.
class Level
{
public:
	// Start the level.
	virtual void StartLevel() = 0;

	// End the level.
	virtual void EndLevel() = 0;

	// Update method called during the game loop.
	virtual void Update() = 0;

	// Render method for rendering the level.
	virtual void Render(sf::RenderWindow* window) = 0;

	// Tick method called based on elapsed time.
	virtual void Tick(sf::Time elapsed) = 0;

protected:
	// Load the map for the level.
	virtual void loadMap() = 0;

	// Pointer to the map associated with the level.
	Map* map;
};
