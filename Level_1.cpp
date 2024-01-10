#include "Level_1.h"

// Constructor for Level_1, initializes the map with the provided SharedContext
Level_1::Level_1(SharedContext* sharedContext)
{
	map = new Map_1(sharedContext);
}

// StartLevel method, placeholder for any actions to be taken at the start of the level
void Level_1::StartLevel()
{
	// Implementation of actions to be taken at the start of the level
}

// EndLevel method, placeholder for any actions to be taken at the end of the level
void Level_1::EndLevel()
{
	// Implementation of actions to be taken at the end of the level
}

// Update method, updates the map in the level
void Level_1::Update()
{
	map->Update();
}

// Render method, renders the map in the level to the provided window
void Level_1::Render(sf::RenderWindow* window)
{
	map->Render(window);
}

// Tick method, processes time-based updates in the level
void Level_1::Tick(sf::Time elapsed)
{
	map->Tick(elapsed);
}

// loadMap method, placeholder for loading the map (not implemented in this snippet)
void Level_1::loadMap()
{
	// Implementation of map loading (if applicable)
}
