#include "Game.h"
#include <iostream>
#include "Button.h"

int  main()
{
	Game game; // Creating our game object

	while (!game.GetWindow()->IsDone())
	{
		//Game loop	
		game.Update();
		game.Render();
		game.LateUpdate();
	}

	return 0;
};
