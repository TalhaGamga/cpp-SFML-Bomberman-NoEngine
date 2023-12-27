#pragma once
#include <SFML/System/Time.hpp>
#include "Level.h"

class LevelManager
{
public:
	void LoadLevel(Level* level);
	void StartLevel();
	void EndLevel();
	void ChangeLevel(Level* level);
	void Update();
	void Render(sf::RenderWindow* window);
	void Tick(const sf::Time& elapsed);

private:
	Level* level;
};

