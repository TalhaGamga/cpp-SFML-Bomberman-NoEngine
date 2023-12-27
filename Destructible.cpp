#include "Destructible.h"

Destructible::Destructible(sf::Vector2f pos, MapData* mapData) : MapObject(mapData)
{
	initialHp = 20;
	destructibleShape.setSize(mapData->gridSize - sf::Vector2f(2.0f, 2.0f));
	destructibleShape.setOrigin(destructibleShape.getSize().x / 2, destructibleShape.getSize().y / 2);
	destructibleShape.setFillColor(sf::Color(139, 69, 19));

	SetPosition(pos);

	wideCollider = new Collider(&destructibleShape);

	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);

	isObstacle = true;
}


void Destructible::Update()
{
	destructibleShape.setPosition(getPosition());
}

void Destructible::Tick(sf::Time elapsed)
{
	if (isDamaged)
	{
		damageAffectTime -= elapsed.asSeconds();
		if (damageAffectTime < 0)
		{
			destructibleShape.setFillColor(sf::Color(139, 69, 19));
			damageAffectTime = 1.0f;
			isDamaged = false;
		}
	}
}

void Destructible::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

void Destructible::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(destructibleShape);
}

void Destructible::TakeDamage(float damage)
{
	isDamaged = true;

	destructibleShape.setFillColor(sf::Color::Red);
	initialHp -= damage;

	if (initialHp <= 0)
	{
		auto it = std::find(mapData->collidables.begin(), mapData->collidables.end(), this);
		if (it != mapData->collidables.end())
		{
			mapData->collidables.erase(it);
		}

		auto _it = std::find(mapData->mapObjs.begin(), mapData->mapObjs.end(), this);
		if (_it != mapData->mapObjs.end())
		{
			mapData->mapObjs.erase(_it);
		}

		isDied = true;
	}
}

void Destructible::SetPosition(sf::Vector2f pos)
{
	setPosition(pos);
}

void Destructible::CheckCollision()
{
}

void Destructible::onCollisionEnter(Collidable* other)
{
}

void Destructible::onCollisionExit(Collidable* other)
{
}
