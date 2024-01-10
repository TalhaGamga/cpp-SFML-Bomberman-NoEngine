#include "Explosion.h"

Explosion::Explosion(MapData* mapData, Direction2D direction, sf::Vector2f pos) : MapObject(mapData), damage(20.0f)
{
    // Initialize the Explosion with the given parameters

    // Create a new RectangleShape for the explosion
    explosionShape = new sf::RectangleShape();
    explosionShape->setSize(sf::Vector2f(10.0f, 10.0f));
    explosionShape->rotate(angleAxis[direction]);

    // Load texture for the explosion if available
    if (explosionTexture.loadFromFile("Assets/Sprites/Flame.png"))
    {
        explosionShape->setTexture(&explosionTexture);
    }

    // Set the position of the explosion
    setPosition(pos);
    explosionShape->setPosition(getPosition());

    // Create a wide collider for collision detection
    wideCollider = new Collider(explosionShape);
    wideCollider->BindOnCollisionEnter(this, &Explosion::onCollisionEnter);

    // Add the explosion to the map objects
    mapData->AddToMapObjs(this);
}

void Explosion::Update()
{
    // Update the explosion, checking for collisions
    CheckCollision();
}

void Explosion::Tick(sf::Time elapsed)
{
    // Update the explosion over time

    // Decrease release time
    releaseTime -= elapsed.asSeconds();
    if (releaseTime < 0)
    {
        // Remove the explosion from map objects if the release time is over
        mapData->RemoveFromMapObjs(this);
    }

    // Spread the explosion
    Spread(elapsed);
}

void Explosion::Render(sf::RenderWindow* window)
{
    // Render the explosion on the window
    window->draw(*this);
}

void Explosion::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    // Draw the explosion shape on the window
    window.draw(*explosionShape);
}

void Explosion::CheckCollision()
{
    // Check collision with other collidables in the map
    for (auto& collidable : mapData->collidables)
    {
        if (collidable == this)
        {
            continue;
        }

        // Check collision enter and exit for the wide collider
        wideCollider->CheckCollisionEnter(collidable);
        wideCollider->CheckCollisionExit(collidable);
    }
}

void Explosion::onCollisionEnter(Collidable* other)
{
    // Handle collision enter events

    // Check if the other collidable is damageable
    if (Damageable* damageable = dynamic_cast<Damageable*>(other))
    {
        damageable->TakeDamage(25.0f);
        isCollided = true;
        return;
    }

    // Check if the other collidable is an obstacle
    if (other && other->isObstacle)
    {
        isCollided = true;
    }
}

void Explosion::onCollisionExit(Collidable* other)
{
    // Handle collision exit events
}

void Explosion::Spread(sf::Time& elapsed)
{
    // Spread the explosion over time

    // Increase the vertical size of the explosion
    if (explosionShape->getSize().y < 40.0f)
    {
        explosionShape->setSize(sf::Vector2f(explosionShape->getSize().x, explosionShape->getSize().y + elapsed.asSeconds() * 150.0f));
        explosionShape->setOrigin(sf::Vector2f(0, explosionShape->getSize().y / 2));
    }

    // Increase the horizontal size of the explosion
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