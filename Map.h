#pragma once
#include "MapObject.h"
#include <vector>
#include "GameStateManager.h"
#include "Collidable.h"
#include "Collider.h"
#include "MapObject.h" 

class Collidable;
class Collider;
class MapObject;

// Structure containing data related to the game map.
struct MapData {
	// Vector of map objects present on the map.
	std::vector <MapObject*> mapObjs;

	// Vector of collidable objects present on the map.
	std::vector<Collidable*> collidables;

	// Size of the grid on the map.
	sf::Vector2f gridSize = sf::Vector2f(90.0f, 90.0f);

	// Pointer to the first character on the map.
	Collidable* character1;

	// Pointer to the second character on the map.
	Collidable* character2;

	// Add a map object to the vector of map objects.
	void AddToMapObjs(MapObject* obj) {
		mapObjs.push_back(obj);
	}

	// Remove a map object from the vector of map objects.
	void RemoveFromMapObjs(MapObject* obj) {
		auto it = std::find(mapObjs.begin(), mapObjs.end(), obj);

		if (it != mapObjs.end()) {
			mapObjs.erase(it);
		}
	}

	// Add a collidable object to the vector of collidables.
	void AddToCollidables(Collidable* collidable) {
		collidables.push_back(collidable);
	}

	// Remove a collidable object from the vector of collidables.
	void RemoveFromCollidables(Collidable* collidable) {
		auto it = std::find(collidables.begin(), collidables.end(), collidable);

		if (it != collidables.end()) {
			collidables.erase(it);
		}
	}
};

// Abstract class representing the game map.
class Map {
public:
	// Load the map.
	virtual void LoadMap() = 0;

	// Update method called during the game loop.
	virtual void Update() = 0;

	// Render method for rendering the map.
	virtual void Render(sf::RenderWindow* window) = 0;

	// Tick method called based on elapsed time.
	virtual void Tick(sf::Time elapsed) = 0;

protected:
	// Data structure containing map-related information.
	MapData mapData;

	// 2D vector representing the tile map.
	// 12x8 (0: empty - 1: Destructible 2: Indestructible)
	std::vector<std::vector<int>> tileMap;

	// Define the initial tile map layout.
	virtual void DefineTileMap() = 0;
};
