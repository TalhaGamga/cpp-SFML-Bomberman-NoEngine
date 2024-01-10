#pragma once
#include "Window.h"
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>
#include "CharacterBase.h"
#include "Player.h"
#include "Level.h"

// Class representing the main game logic.
class Game
{
public:
	// Constructor.
	Game();

	// Destructor.
	~Game();

	// Update method called during the game loop.
	void Update();

	// Late update method called during the game loop after regular update.
	void LateUpdate();

	// Render method for rendering the game.
	void Render();

	// Get the game window.
	Window* GetWindow();

	// Restart the game clock.
	void RestartClock();

private:
	// Game window.
	Window window;

	// Shared context for game objects.
	SharedContext sharedContext;

	// Game state manager for handling different game states.
	GameStateManager gameStateManager;

	// SFML clock for measuring elapsed time.
	sf::Clock clock;

	// Elapsed time since the last frame.
	sf::Time elapsed;
};
