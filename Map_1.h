#pragma once
#include "Map.h"
#include "Wall.h"
#include "Player.h"
#include "Collidable.h"
#include "SecondPlayer.h"

class Map_1 : public Map
{
public:
	Map_1(SharedContext* sharedContext);
	void LoadMap() override;
	void Update() override;
	void Render(sf::RenderWindow* window) override;
	void Tick(sf::Time elapsed) override;

	void CheckCollision() override;

protected:
	void DefineTileMap() override;

private:
	Player player;
	SecondPlayer secondPlayer;
};