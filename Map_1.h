#pragma once
#include "Map.h"
#include "Wall.h"
#include "Player.h"
#include "Collidable.h"
#include "SecondPlayer.h"

// Class representing the specific map implementation for Level 1.
class Map_1 : public Map
{
public:
	// Constructor taking a pointer to the shared context.
	Map_1(SharedContext* sharedContext);

	// Load the specific map for Level 1.
	void LoadMap() override;

	// Update method called during the game loop.
	void Update() override;

	// Render method for rendering the Level 1 map.
	void Render(sf::RenderWindow* window) override;

	// Tick method called based on elapsed time.
	void Tick(sf::Time elapsed) override;

protected:
	// Define the tile map layout for Level 1.
	void DefineTileMap() override;

private:
	// Player object representing the main character on the map.
	Player player;

	// SecondPlayer object representing the second character on the map.
	SecondPlayer secondPlayer;
};
