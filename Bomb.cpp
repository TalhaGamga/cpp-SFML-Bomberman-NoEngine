#include "Bomb.h"
#include "Explosion.h"
#include "Enums.h"

// Constructor for Bomb class.
Bomb::Bomb(sf::Vector2f position, MapData* mapData, CharacterBase* dropper) : MapObject(mapData), isExploded(false)
{
	// Set up the bomb shape with size, color, and origin.
	bombShape.setFillColor(sf::Color(169, 169, 169));
	bombShape.setSize(sf::Vector2f(50.0F, 50.0f));
	bombShape.setOrigin(bombShape.getSize().x / 2, bombShape.getSize().y / 2);

	// Calculate grid indices based on position.
	int indX = static_cast<int>(position.x / 90.0f);
	int indY = static_cast<int>(position.y / 90.0f);

	// Calculate adjusted position based on grid indices.
	float xPos = 45 + indX * 90;
	float yPos = 45 + indY * 90;

	// Set the position of the bomb.
	setPosition(xPos, yPos);

	// Create a wide collider for the bomb.
	wideCollider = new Collider(&bombShape);

	// Set the dropper of the bomb.
	this->dropper = dropper;

	// Add the bomb to map objects and collidables.
	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);

	// Set the obstacle flag to true.
	isObstacle = true;

	// Load the bomb texture.
	if (bombTexture.loadFromFile("Assets/Sprites/bomb.png"))
	{
		bombShape.setTexture(&bombTexture);
	}
}

// Update method for the bomb.
void Bomb::Update()
{
	bombShape.setPosition(getPosition());
}

// Tick method to handle the bomb's timer.
void Bomb::Tick(sf::Time elapsed)
{
	timer -= elapsed.asSeconds();
	if (!isExploded && timer < 0)
	{
		// Set the bomb as exploded.
		isExploded = true;

		// Create explosions in all four directions.
		for (int i = 0; i < 4; i++)
		{
			Explosion* explosion = new Explosion(mapData, Direction2D(i), getPosition());
		}

		// Remove the bomb from collidables and map objects.
		mapData->RemoveFromCollidables(this);
		mapData->RemoveFromMapObjs(this);

		// Delete the bomb.
		delete this;
	}
}

// Render method for the bomb.
void Bomb::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

// Draw method for the bomb as a drawable.
void Bomb::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(bombShape);
}

// Getter for the dropper of the bomb.
CharacterBase* Bomb::GetDropper()
{
	return dropper;
}

// Collision checking method for the bomb.
void Bomb::CheckCollision()
{
}

// Method called when another collidable enters collision with the bomb.
void Bomb::onCollisionEnter(Collidable* other)
{
}

// Method called when another collidable exits collision with the bomb.
void Bomb::onCollisionExit(Collidable* other)
{
}
