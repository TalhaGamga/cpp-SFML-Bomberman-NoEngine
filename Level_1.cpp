#include "Level_1.h"

Level_1::Level_1(SharedContext* sharedContext)
{
	map = new Map_1(sharedContext);
}

void Level_1::StartLevel()
{
}

void Level_1::EndLevel()
{
}

void Level_1::Update()
{
	map->Update();
}

void Level_1::Render(sf::RenderWindow* window)
{
	map->Render(window);
}

void Level_1::Tick(sf::Time elapsed)
{
	map->Tick(elapsed);
}

void Level_1::loadMap()
{
}
