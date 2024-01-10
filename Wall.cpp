#include "Wall.h"
#include "Damageable.h"
#include <random>

Wall::Wall(sf::Vector2f pos, MapData* mapData) : MapObject(mapData)
{
    // Initialize wall shape and properties
    wallShape.setSize(mapData->gridSize - sf::Vector2f(2.0f, 2.0f));
    wallShape.setOrigin(wallShape.getSize().x / 2, wallShape.getSize().y / 2);
    SetPosition(pos);

    // Create a collider for collision detection
    wideCollider = new Collider(&wallShape);

    // Set the collider as an obstacle
    isObstacle = true;

    // Bind collision callbacks
    wideCollider->BindOnCollisionEnter(this, &Wall::onCollisionEnter);
    wideCollider->BindOnCollisionExit(this, &Wall::onCollisionExit);

    // Add the wall to the map objects and collidables
    mapData->AddToMapObjs(this);
    mapData->AddToCollidables(this);

    // Load wall texture if available
    if (wallTexture.loadFromFile("Assets/Sprites/block_04.png"))
    {
        wallShape.setTexture(&wallTexture);
    }

    // Set the wall as an obstacle
    isObstacle = true;
}

Wall::~Wall()
{
    // Destructor for Wall class
}

void Wall::Update()
{
    // Update function for Wall class
}

void Wall::Tick(sf::Time elapsed)
{
    // Tick function for Wall class
}

void Wall::Render(sf::RenderWindow* window)
{
    // Render the wall shape
    window->draw(*this);
}

void Wall::SetPosition(sf::Vector2f pos)
{
    // Set the position of the wall shape
    setPosition(pos);
    wallShape.setPosition(pos);
}

void Wall::Attack(Collidable* other)
{
    // Attack function for Wall class
    // Check if the other collidable is damageable and apply damage
    if (Damageable* otherDamageable = dynamic_cast<Damageable*>(other))
    {
        otherDamageable->TakeDamage(10);
    }
}

void Wall::CheckCollision()
{
    // Check collision function for Wall class
}

void Wall::onCollisionEnter(Collidable* other)
{
    // Callback when a collision with another collidable begins
    // No additional action in this case
}

void Wall::onCollisionExit(Collidable* other)
{
    // Callback when a collision with another collidable ends
    // No additional action in this case
}

void Wall::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    // Draw the wall shape
    window.draw(wallShape);
}
