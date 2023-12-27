#pragma once
#include "Level.h"
#include "Map_1.h"

class Level_1 : public Level
{
public:
	Level_1(SharedContext* sharedContext);
	void StartLevel() override;
	void EndLevel() override;
	void Update() override;
	void Render(sf::RenderWindow* window) override;
	void Tick(sf::Time elapsed) override;

private:
	void loadMap() override;
};

