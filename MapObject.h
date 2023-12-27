#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

struct MapData;

class MapObject : public sf::Drawable, public sf::Transformable
{
public:
	MapObject(MapData* mapData);

	virtual void Tick(sf::Time elapsed) = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

protected:
	MapData* mapData;
};