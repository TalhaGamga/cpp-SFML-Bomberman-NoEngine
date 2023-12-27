#include "Wall.h"
#include "Damageable.h"
#include <random>

Wall::Wall(sf::Vector2f pos, MapData* mapData) : MapObject(mapData)
{
	wallShape.setSize(mapData->gridSize - sf::Vector2f(2.0f, 2.0f));
	wallShape.setOrigin(wallShape.getSize().x / 2, wallShape.getSize().y / 2);
	SetPosition(pos);

	wideCollider = new Collider(&wallShape);

	isObstacle = true;

	this->mapData = mapData;

	wideCollider->BindOnCollisionEnter(this, &Wall::onCollisionEnter);
	wideCollider->BindOnCollisionExit(this, &Wall::onCollisionExit);

	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);


	std::random_device rd;  // A random seed generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<int> distribution(0, 3); // Range: [0, 7]
	// Generate a random number
	int randomNumber = distribution(gen);
	// Convert the random number to a string
	std::string randomNumberString = std::to_string(randomNumber);
	// Create the file path
	std::string fileWay = "Assets/Sprites/block_0" + randomNumberString + ".png";

	std::cout << fileWay << std::endl;

	if (wallTexture.loadFromFile(fileWay))
	{
		wallShape.setTexture(&wallTexture);
	}

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