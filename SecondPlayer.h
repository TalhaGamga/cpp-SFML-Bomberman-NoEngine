#pragma once
#include "GameStateManager.h"
#include "CharacterBase.h"
#include "Player.h"

using DirectionInputState = std::pair<Direction2D, int>;
//struct InputAxis2D {
//
//	InputAxis2D();
//
//	InputAxis2D(DirectionInputState positiveInputState, DirectionInputState negativeInputState)
//		:positiveInputState(positiveInputState), negativeInputState(negativeInputState) {}
//
//	DirectionInputState positiveInputState;
//	DirectionInputState negativeInputState;
//};

using MovementInput = std::unordered_map<Axis, InputAxis2D>;

class SecondPlayer
{
public:
	SecondPlayer(SharedContext* sharedContext, MapData* mapData);
	~SecondPlayer();

	void Update();

	void Init();

	CharacterBase* GetCharacter();

private:
	void pressedW(EventDetails* details);
	void releasedW(EventDetails* details);
	void pressedS(EventDetails* details);
	void releasedS(EventDetails* details);
	void pressedD(EventDetails* details);
	void releasedD(EventDetails* details);
	void pressedA(EventDetails* details);
	void releasedA(EventDetails* details);
	void dropBomb(EventDetails* details);

	void addInputCallbacks();
	void removeInputCallbacks();
	void SetMovementDirection();

	void onCharacterdied();

	bool isPressedUpward = false;
	bool isPressedDownward = false;
	bool isPressedRight = false;
	bool isPressedLeft = false;

	SharedContext* sharedContext;

	CharacterBase* character;

	MovementInput movementInput;

	sf::Vector2i movementDirection;
};
