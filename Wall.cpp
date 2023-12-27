#include "Wall.h"
#include "Damageable.h"

Wall::Wall(sf::Vector2f pos, MapData* mapData) : MapObject(mapData)
{
	wallShape.setSize(mapData->gridSize - sf::Vector2f(2.0f, 2.0f));
	wallShape.setOrigin(wallShape.getSize().x / 2, wallShape.getSize().y / 2);
	wallShape.setFillColor(sf::Color(230, 200, 150));
	wallShape.setOutlineColor(sf::Color::White);
	SetPosition(pos);

	wideCollider = new Collider(&wallShape);

	isObstacle = true;

	this->mapData = mapData;

	wideCollider->BindOnCollisionEnter(this, &Wall::onCollisionEnter);
	wideCollider->BindOnCollisionExit(this, &Wall::onCollisionExit);

	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);

	isObstacle = true;
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Tick(sf::Time elapsed)
{
}

void Wall::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

void Wall::SetPosition(sf::Vector2f pos)
{
	setPosition(pos);
	wallShape.setPosition(pos);
}

void Wall::Attack(Collidable* other)
{
	//printf("Attack\n");
	if (Damageable* otherDamageable = dynamic_cast<Damageable*>(other))
	{
		otherDamageable->TakeDamage(10);
	}
}

void Wall::CheckCollision()
{
}

void Wall::onCollisionEnter(Collidable* other)
{
	//
}

void Wall::onCollisionExit(Collidable* other)
{
	//
}

void Wall::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(wallShape);
}