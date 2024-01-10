#include "Map_1.h"
#include "Wall.h"
#include "Destructible.h"

Map_1::Map_1(SharedContext* sharedContext) : player(sharedContext, &mapData), secondPlayer(sharedContext, &mapData)
{
	// Initialize the tile map and players
	DefineTileMap();
	LoadMap();
}

void Map_1::LoadMap()
{
	// Load the map based on the defined tile map
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			int tileType = tileMap[i][j];
			switch (tileType)
			{
			case (0):
			{
				// Empty tile, do nothing
			}
			break;

			case (1):
			{
				// Create a destructible object at the specified position
				Destructible* destructible = new Destructible(sf::Vector2f(mapData.gridSize.x / 2 + (j * mapData.gridSize.x), mapData.gridSize.y / 2 + (i * mapData.gridSize.y)), &mapData);
			}
			break;

			case (2):
			{
				// Create a wall object at the specified position
				Wall* wall = new Wall(sf::Vector2f(mapData.gridSize.x / 2 + (j * mapData.gridSize.x), mapData.gridSize.y / 2 + (i * mapData.gridSize.y)), &mapData);
			}
			break;
			}
		}
	}

	// Initialize player objects
	player.Init();
	secondPlayer.Init();
}

void Map_1::Update()
{
	// Update player and map object positions
	player.Update();
	secondPlayer.Update();

	for (auto& mapObj : mapData.mapObjs)
	{
		mapObj->Update();
	}
}

void Map_1::Render(sf::RenderWindow* window)
{
	// Render map objects
	for (auto& mapObj : mapData.mapObjs)
	{
		mapObj->Render(window);
	}
}

void Map_1::Tick(sf::Time elapsed)
{
	// Perform ticking for map objects
	for (auto& mapObj : mapData.mapObjs)
	{
		mapObj->Tick(elapsed);
	}
}

void Map_1::DefineTileMap()
{
	// Define the tile map layout
	// 0: empty | 1: breakable | 2: unbreakable
	tileMap = {
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 0, 1, 0, 0, 1, 1, 1, 2, 0, 1, 2},
		{2, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 2},
		{2, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 2},
		{2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2},
		{2, 1, 1, 0, 0, 1, 2, 0, 1, 1, 0, 2},
		{2, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
	};
}
