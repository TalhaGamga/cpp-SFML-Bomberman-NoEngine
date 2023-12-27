#include "LevelManager.h"

void LevelManager::LoadLevel(Level* level)
{
	this->level = level;
}

void LevelManager::StartLevel()
{
}

void LevelManager::EndLevel()
{
}

void LevelManager::ChangeLevel(Level* level)
{
	delete this->level;
	this->level = level;
}

void LevelManager::Update()
{
	level->Update();
}

void LevelManager::Tick(const sf::Time& elapsed)
{
	level->Tick(elapsed);
}

void LevelManager::Render(sf::RenderWindow* window)
{
	level->Render(window);
}