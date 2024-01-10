#include "Game.h"
#include <iostream>
#include "FirstCharacter.h"

Game::Game() : window("Bomberman", sf::Vector2u(1080, 720)),
gameStateManager(&sharedContext)
{
    // Initialize the Game class, including the window and game state manager
    sharedContext.window = &window;
    sharedContext.eventManager = window.GetEventManager();

    gameStateManager.Init();
}

Game::~Game() {}

void Game::Update()
{
    window.Update(); // Update window events
    gameStateManager.Update(elapsed);
}

void Game::Render()
{
    window.BeginDraw(); // Clear
    gameStateManager.Draw();
    window.EndDraw(); // Display
}

void Game::LateUpdate()
{
    gameStateManager.ProcessRequest();
    RestartClock();
}

Window* Game::GetWindow()
{
    return &window;
}

void Game::RestartClock()
{
    // Restart the clock and accumulate elapsed time for fixed time step updates
    elapsed += clock.restart();

    float frameTime = 1.0f / 60.0f;

    if (elapsed.asSeconds() >= frameTime)
    {
        elapsed -= sf::seconds(frameTime);
    }
}
