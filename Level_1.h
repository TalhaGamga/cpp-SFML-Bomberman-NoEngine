#pragma once
#include "Level.h"
#include "Map_1.h"

// Class representing Level 1 of the game.
class Level_1 : public Level
{
public:
	// Constructor taking a pointer to the shared context.
	Level_1(SharedContext* sharedContext);

	// Start the level.
	void StartLevel() override;

	// End the level.
	void EndLevel() override;

	// Update method called during the game loop.
	void Update() override;

	// Render method for rendering the level.
	void Render(sf::RenderWindow* window) override;

	// Tick method called based on elapsed time.
	void Tick(sf::Time elapsed) override;

private:
	// Load the map specific to Level 1.
	void loadMap() override;
};
