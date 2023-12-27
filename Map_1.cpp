#include "Map_1.h"
#include "Wall.h"
#include "Destructible.h"

Map_1::Map_1(SharedContext* sharedContext) : player(sharedContext, &mapData)
{
	DefineTileMap();

	LoadMap();
}

void Map_1::LoadMap() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			int tileType = tileMap[i][j];
			switch (tileType)
			{
			case (0):
			{

			}
			break;

			case (1):
			{
				Destructible* destructible = new Destructible(sf::Vector2f(mapData.gridSize.x / 2 + (j * mapData.gridSize.x), mapData.gridSize.y / 2 + (i * mapData.gridSize.y)), &mapData);
			}
			break;

			case (2):
			{
				Wall* wall = new Wall(sf::Vector2f(mapData.gridSize.x / 2 + (j * mapData.gridSize.x), mapData.gridSize.y / 2 + (i * mapData.gridSize.y)), &mapData);
			}
			break;
			}
		}
	}

	player.Init();
}

void Map_1::Update()
{
	player.Update();

	for (auto& mapObj : mapData.mapObjs)
	{
		mapObj->Update();
	}

}

void Map_1::Render(sf::RenderWindow* window)
{
	for (auto& mapObj : mapData.mapObjs)
	{
		mapObj->Render(window);
	}
}

void Map_1::Tick(sf::Time elapsed)
{
	for (auto& mapObj : mapData.mapObjs)
	{
		mapObj->Tick(elapsed);
	}
}

void Map_1::CheckCollision()
{
	//for (auto& i : collidables)
	//{
	//	for (auto& j : collidables)
	//	{
	//		if (i != j)
	//		{
	//			i->GetCollider()->CheckCollisionEnter(j->GetCollider());
	//			i->GetCollider()->CheckCollisionExit(j->GetCollider());
	//		}
	//	}
	//}
}

void Map_1::DefineTileMap()
{
	tileMap = {
		{0,0,1,2,0,1,1,2,2,0,1,0},
		{0,1,1,0,0,1,0,1,2,0,1,2},
		{1,0,2,0,1,2,2,0,1,0,0,1},
		{1,1,0,1,2,0,0,2,1,1,0,0},
		{2,1,2,2,1,2,1,1,1,1,2,2},
		{0,1,1,0,0,1,2,0,1,2,0,1},
		{1,1,1,0,1,2,0,1,2,0,1,2},
		{0,1,1,0,2,1,2,0,2,1,2,0} };
}
