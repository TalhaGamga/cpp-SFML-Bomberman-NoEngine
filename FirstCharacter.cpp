#include "FirstCharacter.h"
#include "GameStateManager.h"
#include "Map.h"
#include "Collidable.h"
#include "Damageable.h"

FirstCharacter::FirstCharacter(MapData* mapData, std::string textureWay, sf::Vector2f initPos) : CharacterBase(mapData), isBlocked(false), dropPos(0, 0)
{
    // Initialize FirstCharacter with mapData, texture path, and initial position

    // Create a rectangle shape for the character
    charShape = new sf::RectangleShape();
    charShape->setSize(sf::Vector2f(40.0f, 40.0f));
    charShape->setOrigin(charShape->getSize().x / 2, charShape->getSize().y / 2);

    // Create a wide collider for collision detection
    wideCollider = new Collider(charShape);

    this->mapData = mapData;

    // Set initial position and update position for character shape
    setPosition(initPos);
    charShape->setPosition(getPosition());

    // Bind collision callbacks for wide collider
    wideCollider->BindOnCollisionEnter(this, &FirstCharacter::onCollisionEnter);
    wideCollider->BindOnCollisionExit(this, &FirstCharacter::onCollisionExit);

    initialHp = 250;

    // Blocker
    blockerColliderShape = new sf::RectangleShape(charShape->getSize() - sf::Vector2f(10.0f, 10.0f));
    blockerColliderShape->setOrigin(blockerColliderShape->getSize().x / 2, blockerColliderShape->getSize().y / 2);
    blockerColliderShape->setPosition(charShape->getPosition());

    blockerCollider = new Collider(blockerColliderShape);

    // Bind collision callbacks for blocker collider
    blockerCollider->BindOnCollisionEnter(this, &FirstCharacter::disableMovement);
    blockerCollider->BindOnCollisionExit(this, &FirstCharacter::enableMovement);

    // Add the character to map objects and collidables
    mapData->AddToMapObjs(this);
    mapData->AddToCollidables(this);

    isObstacle = true;

    // Set initial health and create health bar
    SetHp(initialHp);
    healthBar = new HealthBar(this);

    // Load texture for the character if available
    if (charTexture.loadFromFile(textureWay))
    {
        charShape->setTexture(&charTexture);
    }
}

FirstCharacter::~FirstCharacter()
{
    // Destructor for FirstCharacter
}

void FirstCharacter::Update()
{
    // Update the character, checking collision and health bar movement
    blockerColliderShape->setPosition(getPosition() + (sf::Vector2f)movementDirection * 5.0f);
    CheckCollision();
    moveHealthBar();
}

void FirstCharacter::Tick(sf::Time elapsed)
{
    // Handle movement, collisions, and health bar updates over time
    handleMovementDirection(elapsed);
    movement(elapsed);
    healthBar->Tick(elapsed);
}

void FirstCharacter::movement(sf::Time& elapsed)
{
    // Move the character if not blocked
    if (!isBlocked)
    {
        move(movementDirection.x * elapsed.asSeconds() * moveSpeed, movementDirection.y * elapsed.asSeconds() * moveSpeed);
    }

    charShape->setPosition(getPosition());
}

void FirstCharacter::disableMovement(Collidable* other)
{
    // Disable movement when colliding with certain objects

    // Check if colliding with a bomb dropped by the character
    if (Bomb* bomb = dynamic_cast<Bomb*>(other))
    {
        if (bomb->GetDropper() == this)
        {
            return;
        }
    }

    // Check if colliding with an obstacle
    if (other && other->isObstacle)
    {
        isBlocked = true;
    }
}

void FirstCharacter::enableMovement(Collidable* other)
{
    // Enable movement after collision exit
    isBlocked = false;
}

void FirstCharacter::moveHealthBar()
{
    // Move and update the health bar position
    sf::Vector2f healthBarOffSet = sf::Vector2f(getPosition().x, charShape->getGlobalBounds().top - 5.0f);
    healthBar->setPosition(healthBarOffSet);
    healthBar->Update();
}

void FirstCharacter::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    // Draw the character on the window
    window.draw(*charShape);
}

void FirstCharacter::TakeDamage(float damage)
{
    // Reduce character's health and trigger damage events

    currentHp -= damage;

    // Execute damage event callbacks
    for (auto& method : onTakingDamage)
    {
        method();
    }

    printf("%f\n", currentHp);

    // Check if the character is dead
    if (currentHp <= 0)
    {
        onCharacterDied();
        charShape->setFillColor(sf::Color::Red);
    }
}

void FirstCharacter::SetMovementDirection(sf::Vector2i direction)
{
    // Set the movement direction of the character
    movementDirection = direction;
}

void FirstCharacter::onCollisionEnter(Collidable* other)
{
    // Handle collision enter events
}

void FirstCharacter::onCollisionExit(Collidable* other)
{
    // Handle collision exit events
}

void FirstCharacter::Render(sf::RenderWindow* window)
{
    // Render the character and health bar on the window
    window->draw(*this);
    healthBar->Render(window);
}

void FirstCharacter::DropBomb()
{
    // Drop a bomb at a specified position
    dropPos = getPosition() - (sf::Vector2f)movementDirection * 25.0f;
    bomb = new Bomb(dropPos, mapData, this);
}

void FirstCharacter::moveUp(sf::Time elapsed) {}

void FirstCharacter::moveDown(sf::Time elapsed) {}

void FirstCharacter::moveRight(sf::Time elapsed) {}

void FirstCharacter::moveLeft(sf::Time elapsed) {}

void FirstCharacter::idle(sf::Time elapsed) {}

void FirstCharacter::CheckCollision()
{
    // Check collisions with other collidables in the map
    for (auto& collidable : mapData->collidables)
    {
        if (collidable == this)
        {
            continue;
        }

        // Check collision enter and exit for the blocker and wide colliders
        blockerCollider->CheckCollisionEnter(collidable);
        blockerCollider->CheckCollisionExit(collidable);

        wideCollider->CheckCollisionEnter(collidable);
        wideCollider->CheckCollisionExit(collidable);
    }
}

void FirstCharacter::handleMovementDirection(sf::Time elapsed)
{
    // Handle movement direction based on current input
    auto moveItr = movementMethods.find(movementDirection);
    if (moveItr != movementMethods.end())
    {
        moveItr->second(elapsed);
    }
}
