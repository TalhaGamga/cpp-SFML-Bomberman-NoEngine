#pragma once
#include "Map.h"
class Level
{
public:
	virtual void StartLevel() = 0;
	virtual void EndLevel() = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void Tick(sf::Time elapsed) = 0;

protected:
	virtual void loadMap() = 0;
	Map* map;
};