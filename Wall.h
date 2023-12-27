#pragma once
#include "MapObject.h"
#include "Collidable.h"
#include "Map.h"

class Wall : public MapObject, public Collidable
{
public:
	Wall(sf::Vector2f pos, MapData* mapData);
	~Wall();

	void Update() override;
	void Tick(sf::Time elapsed) override;
	void Render(sf::RenderWindow* window) override;
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	void SetPosition(sf::Vector2f pos);

	void Attack(Collidable* other);

protected:

	void CheckCollision() override;

	virtual void onCollisionEnter(Collidable* other)override;
	virtual void onCollisionExit(Collidable* other) override;


private:
	sf::RectangleShape wallShape;
	MapData* mapData;
};