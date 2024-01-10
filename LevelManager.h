#pragma once
#include <SFML/System/Time.hpp>
#include "Level.h"

// Class managing the current game level.
class LevelManager
{
public:
	// Load a new level.
	void LoadLevel(Level* level);

	// Start the current level.
	void StartLevel();

	// End the current level.
	void EndLevel();

	// Change to a new level.
	void ChangeLevel(Level* level);

	// Update method called during the game loop.
	void Update();

	// Render method for rendering the current level.
	void Render(sf::RenderWindow* window);

	// Tick method called based on elapsed time.
	void Tick(const sf::Time& elapsed);

private:
	// Pointer to the current level.
	Level* level;
};
