#include "FirstCharacter.h"
#include "GameStateManager.h" 
#include "Map.h"
#include "Collidable.h"
#include "Damageable.h"

FirstCharacter::FirstCharacter(MapData* mapData, std::string textureWay, sf::Vector2f initPos) : CharacterBase(mapData), isBlocked(false), dropPos(0, 0)
{
	charShape = new sf::RectangleShape();
	charShape->setSize(sf::Vector2f(40.0f, 40.0f));
	charShape->setOrigin(charShape->getSize().x / 2, charShape->getSize().y / 2);

	wideCollider = new Collider(charShape);

	this->mapData = mapData;

	setPosition(initPos);
	charShape->setPosition(getPosition());

	wideCollider->BindOnCollisionEnter(this, &FirstCharacter::onCollisionEnter);
	wideCollider->BindOnCollisionExit(this, &FirstCharacter::onCollisionExit);

	initialHp = 100;

	// Blocker
	blockerColliderShape = new sf::RectangleShape(charShape->getSize() - sf::Vector2f(2.0f, 2.0f));
	blockerColliderShape->setOrigin(blockerColliderShape->getSize().x / 2, blockerColliderShape->getSize().y / 2);
	blockerColliderShape->setPosition(charShape->getPosition());

	//blockerColliderShape->setFillColor(sf::Color::Blue);

	blockerCollider = new Collider(blockerColliderShape);

	blockerCollider->BindOnCollisionEnter(this, &FirstCharacter::disableMovement);
	blockerCollider->BindOnCollisionExit(this, &FirstCharacter::enableMovement);

	mapData->AddToMapObjs(this);
	mapData->AddToCollidables(this);

	isObstacle = true;

	SetHp(100);

	healthBar = new HealthBar(this);

	if (charTexture.loadFromFile(textureWay))
	{
		charShape->setTexture(&charTexture);
	}
};

FirstCharacter::~FirstCharacter()
{
}

void FirstCharacter::Update()
{
	blockerColliderShape->setPosition(getPosition() + (sf::Vector2f)movementDirection);

	CheckCollision();

	moveHealthBar();
}

void FirstCharacter::Tick(sf::Time elapsed)
{
	handleMovementDirection(elapsed);

	movement(elapsed);

	healthBar->Tick(elapsed);
}

void FirstCharacter::movement(sf::Time& elapsed)
{
	if (!isBlocked)
	{
		move(movementDirection.x * elapsed.asSeconds() * moveSpeed, movementDirection.y * elapsed.asSeconds() * moveSpeed);
	}

	charShape->setPosition(getPosition());
}

void FirstCharacter::disableMovement(Collidable* other)
{

	if (Bomb* bomb = dynamic_cast<Bomb*>(other))
	{
		if (bomb->GetDropper() == this)
		{
			return;
		}
	}

	if (other && other->isObstacle)
	{
		isBlocked = true;
	}
}

void FirstCharacter::enableMovement(Collidable* other)
{
	isBlocked = false;
}

void FirstCharacter::moveHealthBar()
{
	sf::Vector2f healthBarOffSet = sf::Vector2f(getPosition().x, charShape->getGlobalBounds().top - 5.0f);
	healthBar->setPosition(healthBarOffSet);
	healthBar->Update();
}

void FirstCharacter::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(*charShape);
	//window.draw(*blockerColliderShape);
}

void FirstCharacter::TakeDamage(float damage)
{
	currentHp -= damage;

	for (auto& method : onTakingDamage)
	{
		method();
	}

	printf("%f\n", currentHp);
	if (currentHp <= 0)
	{
		mapData->RemoveFromMapObjs(this);
		mapData->RemoveFromCollidables(this);
	}
}

void FirstCharacter::SetMovementDirection(sf::Vector2i direction)
{
	movementDirection = direction;
}

void FirstCharacter::onCollisionEnter(Collidable* other)
{
	//printf("character onCollision Enter");
}


void FirstCharacter::onCollisionExit(Collidable* other)
{
	//printf("character onCollision Exit");
}


void FirstCharacter::Render(sf::RenderWindow* window)
{
	window->draw(*this);
	healthBar->Render(window);
}

void FirstCharacter::DropBomb()
{
	dropPos = getPosition() - (sf::Vector2f)movementDirection * 25.0f;
	bomb = new Bomb(dropPos, mapData, this);
}

void FirstCharacter::moveUp(sf::Time elapsed)
{
	//std::cout << "Move Up" << std::endl;
}

void FirstCharacter::moveDown(sf::Time elapsed)
{
	//std::cout << "Move Down" << std::endl;
}

void FirstCharacter::moveRight(sf::Time elapsed)
{
	//std::cout << "Move Right" << std::endl;
}

void FirstCharacter::moveLeft(sf::Time elapsed)
{
	//std::cout << "Move Left" << std::endl;
}

void FirstCharacter::idle(sf::Time elapsed) {
	//std::cout << "Idle" << std::endl;
}

void FirstCharacter::CheckCollision()
{
	for (auto& collidable : mapData->collidables)
	{
		if (collidable == this)
		{
			continue;
		}

		blockerCollider->CheckCollisionEnter(collidable);
		blockerCollider->CheckCollisionExit(collidable);

		wideCollider->CheckCollisionEnter(collidable);
		wideCollider->CheckCollisionExit(collidable);
	}
}

void FirstCharacter::handleMovementDirection(sf::Time elapsed)
{
	auto moveItr = movementMethods.find(movementDirection);
	if (moveItr != movementMethods.end())
	{
		moveItr->second(elapsed);
	}
}