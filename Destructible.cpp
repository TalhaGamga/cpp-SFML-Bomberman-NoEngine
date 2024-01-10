#include "Destructible.h"

// Constructor for Destructible class, initializes properties and sets up collision
Destructible::Destructible(sf::Vector2f pos, MapData* mapData) : MapObject(mapData)
{
	// Set initial health points
	initialHp = 80;

	// Set size and origin of the destructible shape
	destructibleShape.setSize(mapData->gridSize - sf::Vector2f(2.0f, 2.0f));
	destructibleShape.setOrigin(destructibleShape.getSize().x / 2, destructibleShape.getSize().y / 2);

	// Set position of the destructible object
	SetPosition(pos);

	// Create a wide collider for collision detection
	wideCollider = new Collider(&destructibleShape);

	// Add the object to the map objects and collidables lists
	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);

	// Load texture for the destructible object
	if (destructibleTexture.loadFromFile("Assets/Sprites/crate_02.png"))
	{
		destructibleShape.setTexture(&destructibleTexture);
	}

	// Mark the object as an obstacle
	isObstacle = true;
}

// Update the position of the destructible object
void Destructible::Update()
{
	destructibleShape.setPosition(getPosition());
}

// Perform periodic updates for the destructible object
void Destructible::Tick(sf::Time elapsed)
{
	// If the object is damaged, change its color temporarily
	if (isDamaged)
	{
		damageAffectTime -= elapsed.asSeconds();
		if (damageAffectTime < 0)
		{
			r -= 35.0f;
			destructibleShape.setFillColor(sf::Color(r, 0, 0));
			damageAffectTime = 1.0f;
			isDamaged = false;
		}
	}
}

// Render the destructible object on the window
void Destructible::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

// Draw the destructible shape
void Destructible::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(destructibleShape);
}

// Apply damage to the destructible object
void Destructible::TakeDamage(float damage)
{
	// Mark the object as damaged and change its color
	isDamaged = true;
	destructibleShape.setFillColor(sf::Color::Red);

	// Reduce the initial health points
	initialHp -= damage;

	// If health points fall below zero, remove the object from the map
	if (initialHp <= 0)
	{
		// Remove from collidables list
		auto it = std::find(mapData->collidables.begin(), mapData->collidables.end(), this);
		if (it != mapData->collidables.end())
		{
			mapData->collidables.erase(it);
		}

		// Remove from map objects list
		auto _it = std::find(mapData->mapObjs.begin(), mapData->mapObjs.end(), this);
		if (_it != mapData->mapObjs.end())
		{
			mapData->mapObjs.erase(_it);
		}

		// Mark the object as dead
		isDied = true;
	}
}

// Set the position of the destructible object
void Destructible::SetPosition(sf::Vector2f pos)
{
	setPosition(pos);
}

// Check collision for the destructible object
void Destructible::CheckCollision()
{
	// Implementation not provided
}

// Handle collision enter for the destructible object
void Destructible::onCollisionEnter(Collidable* other)
{
	// Implementation not provided
}

// Handle collision exit for the destructible object
void Destructible::onCollisionExit(Collidable* other)
{
	// Implementation not provided
}
