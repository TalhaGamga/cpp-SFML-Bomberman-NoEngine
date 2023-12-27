#pragma once
#include "Window.h"
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>
#include "CharacterBase.h"
#include "Button.h"
#include "Player.h"
#include "Level.h"

class Game
{
public:
	Game();
	~Game();

	void Update();

	void LateUpdate();
	void Render();
	Window* GetWindow();
	void RestartClock();

private:
	Window window;
	SharedContext sharedContext;
	GameStateManager gameStateManager;

	sf::Clock clock;
	sf::Time elapsed;
};