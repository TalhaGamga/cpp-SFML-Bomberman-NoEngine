#include "Explosion.h"

Explosion::Explosion(MapData* mapData, Direction2D direction, sf::Vector2f pos) : MapObject(mapData), damage(20.0f)
{

	explosionShape = new sf::RectangleShape();
	explosionShape->setFillColor(sf::Color(220, 20, 20));

	explosionShape->setSize(sf::Vector2f(10.0f, 10.0f));
	explosionShape->rotate(angleAxis[direction]);

	setPosition(pos);
	explosionShape->setPosition(getPosition());

	wideCollider = new Collider(explosionShape);
	wideCollider->BindOnCollisionEnter(this, &Explosion::onCollisionEnter);

	mapData->AddToMapObjs(this);
}

void Explosion::Update()
{
	CheckCollision();
}

void Explosion::Tick(sf::Time elapsed)
{
	releaseTime -= elapsed.asSeconds();
	if (releaseTime < 0)
	{
		mapData->RemoveFromMapObjs(this);
	}


	Spread(elapsed);
}

void Explosion::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

void Explosion::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(*explosionShape);
}

void Explosion::CheckCollision()
{
	for (auto& collidable : mapData->collidables)
	{
		if (collidable == this)
		{
			continue;
		}

		wideCollider->CheckCollisionEnter(collidable);
		wideCollider->CheckCollisionExit(collidable);
	}
}

void Explosion::onCollisionEnter(Collidable* other)
{
	if (Damageable* damageable = dynamic_cast<Damageable*>(other))
	{
		damageable->TakeDamage(25.0f);
		isCollided = true;
		return;
	}

	if (other && other->isObstacle)
	{
		isCollided = true;
	}
}

void Explosion::onCollisionExit(Collidable* other)
{
}


void Explosion::Spread(sf::Time& elapsed)
{

	if (explosionShape->getSize().y < 40.0f)
	{
		explosionShape->setSize(sf::Vector2f(explosionShape->getSize().x, explosionShape->getSize().y + elapsed.asSeconds() * 150.0f));
		explosionShape->setOrigin(sf::Vector2f(0, explosionShape->getSize().y / 2));
	}

	if (explosionShape->getSize().x < 250.0f)
	{
		if (isCollided)
		{
			return;
		}

		explosionShape->setSize(sf::Vector2f(explosionShape->getSize().x + elapsed.asSeconds() * 150.0f, explosionShape->getSize().y));
		explosionShape->setOrigin(sf::Vector2f(0, explosionShape->getSize().y / 2));
	}
}