#include "Game.h"
#include <iostream>

int main()
{
	// Create a Game instance
	Game game;

	// Main game loop
	while (!game.GetWindow()->IsDone())
	{
		// Update game logic
		game.Update();

		// Render the game
		game.Render();

		// Perform late updates
		game.LateUpdate();
	}

	return 0;
};