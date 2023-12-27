#pragma once
#include "CharacterBase.h"
#include <iostream>
#include "Map.h"

namespace std {
	template <>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			return hash<int>()(k.x) ^ (hash<int>()(k.y) << 1);
		}
	};
}

class FirstCharacter : public CharacterBase
{
public:
	FirstCharacter(MapData* mapData);
	~FirstCharacter();

	void Update() override;
	void Tick(sf::Time elapsed) override;
	void Render(sf::RenderWindow* window) override;

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
	virtual void TakeDamage(float damage) override;

	void SetMovementDirection(sf::Vector2i direction) override;
	void DropBomb() override;

protected:
	void moveUp(sf::Time elapsed) override;
	void moveDown(sf::Time elapsed) override;
	void moveRight(sf::Time elapsed) override;
	void moveLeft(sf::Time elapsed) override;
	void idle(sf::Time elapsed) override;

	using MovementMethod = std::function<void(sf::Time)>;

	std::unordered_map<sf::Vector2i, MovementMethod> movementMethods{
		{sf::Vector2i(0, 1), std::bind(&FirstCharacter::moveUp, this, std::placeholders::_1)},
		{ sf::Vector2i(0, -1), std::bind(&FirstCharacter::moveDown, this, std::placeholders::_1) },
		{ sf::Vector2i(-1, 0), std::bind(&FirstCharacter::moveLeft, this, std::placeholders::_1) },
		{ sf::Vector2i(1, 0), std::bind(&FirstCharacter::moveRight, this, std::placeholders::_1) },
		{ sf::Vector2i(0, 0), std::bind(&FirstCharacter::idle, this, std::placeholders::_1) }
	};

	void CheckCollision() override;

	void onCollisionEnter(Collidable* other) override;
	void onCollisionExit(Collidable* other)override;

private:
	void handleMovementDirection(sf::Time elapsed);
	void movement(sf::Time& elapsed);
	void disableMovement(Collidable* other);
	void enableMovement(Collidable* other);
	void moveHealthBar();

	MapData* mapData;
	bool isBlocked;

	sf::Vector2f dropPos;

	sf::RectangleShape* blockerColliderShape;
	sf::Texture charTexture;
	Collider* blockerCollider;
};