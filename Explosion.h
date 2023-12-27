#pragma once
#include <SFML/Graphics.hpp>
#include "MapObject.h"
#include "Collidable.h"
#include "Damageable.h"
#include "Map.h"
#include "Enums.h"
#include <unordered_map>

using AngleAxis = std::unordered_map<Direction2D, float>;

class Explosion : public MapObject, public Collidable
{
public:
	Explosion(MapData* mapData, Direction2D direction, sf::Vector2f pos);

	void Update() override;
	void Tick(sf::Time elapsed) override;
	void Render(sf::RenderWindow* window) override;
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

protected:
	void CheckCollision() override;

	void onCollisionEnter(Collidable* other) override;
	void onCollisionExit(Collidable* other) override;

private:
	void Spread(sf::Time& elapsed);
	sf::RectangleShape* explosionShape;
	sf::Texture explosionTexture;
	float damage;
	bool isCollided = false;
	float releaseTime = 5.0f;

	AngleAxis angleAxis{
		{Direction2D::Right, 0},
		{Direction2D::Down, 90},
		{Direction2D::Left, 180},
		{Direction2D::Up, 270} };
};