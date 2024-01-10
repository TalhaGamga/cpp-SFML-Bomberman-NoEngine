#include "LevelManager.h"

// LoadLevel method, sets the current level to the provided level
void LevelManager::LoadLevel(Level* level)
{
	this->level = level;
}

// StartLevel method, placeholder for any actions to be taken at the start of the level
void LevelManager::StartLevel()
{
	// Implementation of actions to be taken at the start of the level
}

// EndLevel method, placeholder for any actions to be taken at the end of the level
void LevelManager::EndLevel()
{
	// Implementation of actions to be taken at the end of the level
}

// ChangeLevel method, changes the current level to the provided level, deleting the previous level
void LevelManager::ChangeLevel(Level* level)
{
	delete this->level;
	this->level = level;
}

// Update method, updates the current level
void LevelManager::Update()
{
	level->Update();
}

// Tick method, processes time-based updates in the current level
void LevelManager::Tick(const sf::Time& elapsed)
{
	level->Tick(elapsed);
}

// Render method, renders the current level to the provided window
void LevelManager::Render(sf::RenderWindow* window)
{
	level->Render(window);
}
