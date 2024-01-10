#pragma once
#include "CharacterBase.h"
#include <iostream>
#include "Map.h"

// Specialization of std::hash for sf::Vector2i to use it in unordered_map
namespace std {
	template <>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			return hash<int>()(k.x) ^ (hash<int>()(k.y) << 1);
		}
	};
}

// Class representing the first character in the game.
class FirstCharacter : public CharacterBase
{
public:
	// Constructor taking map data, texture file path, and initial position.
	FirstCharacter(MapData* mapData, std::string textureWay, sf::Vector2f initPos);

	// Destructor.
	~FirstCharacter();

	// Update method called during the game loop.
	void Update() override;

	// Tick method called based on elapsed time.
	void Tick(sf::Time elapsed) override;

	// Render method for rendering the character.
	void Render(sf::RenderWindow* window) override;

	// Abstract method for drawing the character.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	// Method for taking damage.
	virtual void TakeDamage(float damage) override;

	// Set the movement direction of the character.
	void SetMovementDirection(sf::Vector2i direction) override;

	// Drop a bomb.
	void DropBomb() override;

protected:
	// Movement method for moving upward.
	void moveUp(sf::Time elapsed) override;

	// Movement method for moving downward.
	void moveDown(sf::Time elapsed) override;

	// Movement method for moving rightward.
	void moveRight(sf::Time elapsed) override;

	// Movement method for moving leftward.
	void moveLeft(sf::Time elapsed) override;

	// Idle method called when there is no movement.
	void idle(sf::Time elapsed) override;

	// Type alias for movement methods.
	using MovementMethod = std::function<void(sf::Time)>;

	// Mapping of movement directions to corresponding movement methods.
	std::unordered_map<sf::Vector2i, MovementMethod> movementMethods{
		{sf::Vector2i(0, 1), std::bind(&FirstCharacter::moveUp, this, std::placeholders::_1)},
		{ sf::Vector2i(0, -1), std::bind(&FirstCharacter::moveDown, this, std::placeholders::_1) },
		{ sf::Vector2i(-1, 0), std::bind(&FirstCharacter::moveLeft, this, std::placeholders::_1) },
		{ sf::Vector2i(1, 0), std::bind(&FirstCharacter::moveRight, this, std::placeholders::_1) },
		{ sf::Vector2i(0, 0), std::bind(&FirstCharacter::idle, this, std::placeholders::_1) }
	};

	// Check for collisions with other collidable objects.
	void CheckCollision() override;

	// Called when a collision with another collidable object occurs.
	void onCollisionEnter(Collidable* other) override;

	// Called when the collision with another collidable object ends.
	void onCollisionExit(Collidable* other) override;

private:
	// Handle the movement direction of the character based on elapsed time.
	void handleMovementDirection(sf::Time elapsed);

	// General movement method for the character.
	void movement(sf::Time& elapsed);

	// Disable movement when colliding with an obstacle.
	void disableMovement(Collidable* other);

	// Enable movement after colliding with an obstacle.
	void enableMovement(Collidable* other);

	// Move the health bar of the character.
	void moveHealthBar();

	// Map data associated with the character.
	MapData* mapData;

	// Flag indicating if the character is blocked.
	bool isBlocked;

	// Position to drop a bomb.
	sf::Vector2f dropPos;

	// Shape representing the collider used for blocking movement.
	sf::RectangleShape* blockerColliderShape;

	// Texture for the character.
	sf::Texture charTexture;

	// Collider used for blocking movement.
	Collider* blockerCollider;
};
