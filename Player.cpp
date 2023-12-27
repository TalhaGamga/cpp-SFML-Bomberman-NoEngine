#include "Player.h"
#include "GameStateManager.h"

Player::Player(SharedContext* sharedContext, MapData* mapData) : sharedContext(sharedContext)
{
	character = new FirstCharacter(mapData);

	movementInput.emplace(Axis::Vertical, InputAxis2D
	(DirectionInputState{ Direction2D::Up,0 },
		DirectionInputState{ Direction2D::Down,0 }));

	movementInput.emplace(Axis::Horizontal, InputAxis2D
	(DirectionInputState{ Direction2D::Right,0 },
		DirectionInputState{ Direction2D::Left,0 }));
}

Player::~Player()
{
	removeInputCallbacks();
}

void Player::Init()
{
	addInputCallbacks();
}

CharacterBase* Player::GetCharacter()
{
	return character;
}

void Player::addInputCallbacks()
{
	EventManager* eventManager = sharedContext->eventManager;

	eventManager->AddCallback(StateType::Play, "Key_Up_Pressed", &Player::pressedUpward, this);
	eventManager->AddCallback(StateType::Play, "Key_Down_Pressed", &Player::pressedDownward, this);
	eventManager->AddCallback(StateType::Play, "Key_Right_Pressed", &Player::pressedRight, this);
	eventManager->AddCallback(StateType::Play, "Key_Left_Pressed", &Player::pressedLeft, this);
	eventManager->AddCallback(StateType::Play, "Key_Space_Pressed", &Player::dropBomb, this);

	eventManager->AddCallback(StateType::Play, "Key_Up_Released", &Player::releasedUpward, this);
	eventManager->AddCallback(StateType::Play, "Key_Down_Released", &Player::releasedDownward, this);
	eventManager->AddCallback(StateType::Play, "Key_Right_Released", &Player::releasedRight, this);
	eventManager->AddCallback(StateType::Play, "Key_Left_Released", &Player::releasedLeft, this);
	eventManager->AddCallback(StateType::Play, "Key_Space_Released", &Player::dropBomb, this);
}

void Player::removeInputCallbacks()
{
	EventManager* eventManager = sharedContext->eventManager;

	eventManager->RemoveCallback(StateType::Play, "Key_Up_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_Down_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_Right_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_Left_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_Space_Pressed");

	eventManager->RemoveCallback(StateType::Play, "Key_Up_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_Down_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_Right_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_Left_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_Space_Released");
}


void Player::Update()
{
	SetMovementDirection();
}

void Player::pressedUpward(EventDetails* details)
{
	movementInput[Axis::Vertical].positiveInputState.second = -1;

	movementInput[Axis::Horizontal].positiveInputState.second = 0;
	movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

void Player::releasedUpward(EventDetails* details)
{
	movementInput[Axis::Vertical].positiveInputState.second = 0;
}

void Player::pressedDownward(EventDetails* details)
{
	movementInput[Axis::Vertical].negativeInputState.second = +1;

	movementInput[Axis::Horizontal].positiveInputState.second = 0;
	movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

void Player::releasedDownward(EventDetails* details)
{
	movementInput[Axis::Vertical].negativeInputState.second = 0;
}

void Player::pressedRight(EventDetails* details)
{
	movementInput[Axis::Horizontal].positiveInputState.second = 1;

	movementInput[Axis::Vertical].positiveInputState.second = 0;
	movementInput[Axis::Vertical].negativeInputState.second = 0;
}

void Player::releasedRight(EventDetails* details)
{
	movementInput[Axis::Horizontal].positiveInputState.second = 0;
}


void Player::pressedLeft(EventDetails* details)
{
	movementInput[Axis::Horizontal].negativeInputState.second = -1;

	movementInput[Axis::Vertical].positiveInputState.second = 0;
	movementInput[Axis::Vertical].negativeInputState.second = 0;
}


void Player::releasedLeft(EventDetails* details)
{
	movementInput[Axis::Horizontal].negativeInputState.second = 0;
}


void Player::dropBomb(EventDetails* details)
{
	character->DropBomb();
}

void Player::SetMovementDirection()
{
	movementDirection.x = movementInput[Axis::Horizontal].positiveInputState.second + movementInput[Axis::Horizontal].negativeInputState.second;
	movementDirection.y = movementInput[Axis::Vertical].positiveInputState.second + movementInput[Axis::Vertical].negativeInputState.second;

	character->SetMovementDirection(movementDirection);
}

/*
In C++, if we do not define a default constructor, the compiler generates
a default constructor. However if we define a custom constructor then the
compiler no longer generates a default constructor.
*/
InputAxis2D::InputAxis2D()
{
}