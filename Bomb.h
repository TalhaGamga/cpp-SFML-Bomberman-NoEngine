#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MapObject.h"
#include"Collidable.h"
#include "Explosion.h"
#include "CharacterBase.h"

class CharacterBase;

class Bomb :public MapObject, public Collidable
{
public:
	Bomb(sf::Vector2f position, MapData* mapData, CharacterBase* dropper);

	void Update() override;
	void Tick(sf::Time elapsed) override;
	void Render(sf::RenderWindow* window) override;

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	CharacterBase* GetDropper();

protected:
	void CheckCollision() override;

	virtual void onCollisionEnter(Collidable* other)override;
	virtual void onCollisionExit(Collidable* other) override;

private:
	sf::RectangleShape bombShape;
	sf::Texture bombTexture;
	bool isExploded;
	float timer = 10;
	CharacterBase* dropper;
};