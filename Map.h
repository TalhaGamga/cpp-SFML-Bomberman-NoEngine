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

struct MapData {
	std::vector <MapObject*> mapObjs;
	std::vector<Collidable*> collidables;
	sf::Vector2f gridSize = sf::Vector2f(90.0f, 90.0f);
	Collidable* character1;
	Collidable* character2;

	void AddToMapObjs(MapObject* obj) {
		mapObjs.push_back(obj);
	}

	void RemoveFromMapObjs(MapObject* obj) {
		auto it = std::find(mapObjs.begin(), mapObjs.end(), obj);

		if (it != mapObjs.end())
		{
			mapObjs.erase(it);
		}
	}

	void AddToCollidables(Collidable* collidable) {
		collidables.push_back(collidable);
	}

	void RemoveFromCollidables(Collidable* collidable) {
		auto it = std::find(collidables.begin(), collidables.end(), collidable);

		if (it != collidables.end())
		{
			collidables.erase(it);
		}
	}


};

class Map {
public:
	virtual void LoadMap() = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void Tick(sf::Time elapsed) = 0;

	virtual void CheckCollision() = 0;

protected:
	MapData mapData;

	// 12x8 (0: empty - 1: Destructible 2: Indestructible)
	std::vector<std::vector<int>> tileMap;

	virtual void DefineTileMap() = 0;
};