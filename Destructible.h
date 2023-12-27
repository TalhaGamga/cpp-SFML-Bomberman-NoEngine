#pragma once
#include "MapObject.h"
#include "Collidable.h"
#include "Damageable.h"

class Destructible : public MapObject, public Collidable, public Damageable
{
public:
	Destructible(sf::Vector2f pos, MapData* mapData);
	//~Destructible();

	void Update() override;
	void Tick(sf::Time elapsed) override;
	void Render(sf::RenderWindow* window) override;
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
	void TakeDamage(float damage) override;
	void SetPosition(sf::Vector2f pos);

protected:

	void CheckCollision() override;

	virtual void onCollisionEnter(Collidable* other)override;
	virtual void onCollisionExit(Collidable* other) override;
private:
	sf::RectangleShape destructibleShape;
	float damageAffectTime = 1;
	bool isDamaged = false;
};

