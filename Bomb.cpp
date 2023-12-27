#include "Bomb.h"
#include "Explosion.h"
#include "Enums.h"

Bomb::Bomb(sf::Vector2f position, MapData* mapData, CharacterBase* dropper) : MapObject(mapData), isExploded(false)
{
	bombShape.setFillColor(sf::Color(169, 169, 169));
	bombShape.setSize(sf::Vector2f(50.0F, 50.0f));
	bombShape.setOrigin(bombShape.getSize().x / 2, bombShape.getSize().y / 2);

	int indX = static_cast<int>(position.x / 90.0f);
	int indY = static_cast<int>(position.y / 90.0f);

	float xPos = 45 + indX * 90;
	float yPos = 45 + indY * 90;

	setPosition(xPos, yPos);

	wideCollider = new Collider(&bombShape);

	this->dropper = dropper;

	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);

	isObstacle = true;

	if (bombTexture.loadFromFile("Assets/Sprites/bomb.png"))
	{
		bombShape.setTexture(&bombTexture);
	}
}

void Bomb::Update()
{
	bombShape.setPosition(getPosition());
}

void Bomb::Tick(sf::Time elapsed)
{
	timer -= elapsed.asSeconds();
	if (!isExploded && timer < 0)
	{
		isExploded = true;

		for (int i = 0; i < 4; i++)
		{
			Explosion* explosion = new Explosion(mapData, Direction2D(i), getPosition());
		}

		mapData->RemoveFromCollidables(this);
		mapData->RemoveFromMapObjs(this);

		delete this;
	}
}

void Bomb::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

void Bomb::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(bombShape);
}

CharacterBase* Bomb::GetDropper()
{
	return dropper;
}

void Bomb::CheckCollision()
{
}

void Bomb::onCollisionEnter(Collidable* other)
{
}

void Bomb::onCollisionExit(Collidable* other)
{
}