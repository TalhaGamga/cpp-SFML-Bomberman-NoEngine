#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

struct MapData;

// Abstract class representing objects within the game map.
class MapObject : public sf::Drawable, public sf::Transformable
{
public:
	// Constructor taking a pointer to the map data.
	MapObject(MapData* mapData);

	// Tick method called based on elapsed time.
	virtual void Tick(sf::Time elapsed) = 0;

	// Update method called during the game loop.
	virtual void Update() = 0;

	// Render method for rendering the map object.
	virtual void Render(sf::RenderWindow* window) = 0;

	// Draw method required for sf::Drawable, to be implemented in derived classes.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

protected:
	// Pointer to the map data associated with the map object.
	MapData* mapData;
};
