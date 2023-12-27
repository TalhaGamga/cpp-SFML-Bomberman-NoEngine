#pragma once
#include "FirstCharacter.h"
#include "GameStateManager.h"
#include "Enums.h"

using DirectionInputState = std::pair<Direction2D, int>;
struct InputAxis2D {

	InputAxis2D();

	InputAxis2D(DirectionInputState positiveInputState, DirectionInputState negativeInputState)
		:positiveInputState(positiveInputState), negativeInputState(negativeInputState) {}

	DirectionInputState positiveInputState;
	DirectionInputState negativeInputState;
};

using MovementInput = std::unordered_map<Axis, InputAxis2D>;

class Player
{
public:
	Player(SharedContext* sharedContext, MapData* mapData);
	~Player();

	void Update();

	void Init();

	CharacterBase* GetCharacter();

private:
	void pressedUpward(EventDetails* details);
	void releasedUpward(EventDetails* details);
	void pressedDownward(EventDetails* details);
	void releasedDownward(EventDetails* details);
	void pressedRight(EventDetails* details);
	void releasedRight(EventDetails* details);
	void pressedLeft(EventDetails* details);
	void releasedLeft(EventDetails* details);
	void dropBomb(EventDetails* details);

	void addInputCallbacks();
	void removeInputCallbacks();
	void SetMovementDirection();

	bool isPressedUpward = false;
	bool isPressedDownward = false;
	bool isPressedRight = false;
	bool isPressedLeft = false;

	SharedContext* sharedContext;

	CharacterBase* character;

	MovementInput movementInput;

	sf::Vector2i movementDirection;
};

