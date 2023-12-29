#include "SecondPlayer.h"
#include "FirstCharacter.h"

SecondPlayer::SecondPlayer(SharedContext* sharedContext, MapData* mapData) :sharedContext(sharedContext)
{
	character = new FirstCharacter(mapData, "Assets/Sprites/Ghost_2.png", sf::Vector2f(1060.0f, 700.0f));

	movementInput.emplace(Axis::Vertical, InputAxis2D
	(DirectionInputState{ Direction2D::Up,0 },
		DirectionInputState{ Direction2D::Down,0 }));

	movementInput.emplace(Axis::Horizontal, InputAxis2D
	(DirectionInputState{ Direction2D::Right,0 },
		DirectionInputState{ Direction2D::Left,0 }));

	character->onCharacterDied = std::bind(&SecondPlayer::onCharacterdied, this);
}

SecondPlayer::~SecondPlayer()
{
	removeInputCallbacks();
}

void SecondPlayer::Update()
{
	SetMovementDirection();
}

void SecondPlayer::Init()
{
	addInputCallbacks();
}

CharacterBase* SecondPlayer::GetCharacter()
{
	return character;
}

void SecondPlayer::pressedW(EventDetails* details)
{
	movementInput[Axis::Vertical].positiveInputState.second = -1;

	movementInput[Axis::Horizontal].positiveInputState.second = 0;
	movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

void SecondPlayer::releasedW(EventDetails* details)
{
	movementInput[Axis::Vertical].positiveInputState.second = 0;
}

void SecondPlayer::pressedS(EventDetails* details)
{
	movementInput[Axis::Vertical].negativeInputState.second = +1;

	movementInput[Axis::Horizontal].positiveInputState.second = 0;
	movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

void SecondPlayer::releasedS(EventDetails* details)
{
	movementInput[Axis::Vertical].negativeInputState.second = 0;
}

void SecondPlayer::pressedD(EventDetails* details)
{
	movementInput[Axis::Horizontal].positiveInputState.second = 1;

	movementInput[Axis::Vertical].positiveInputState.second = 0;
	movementInput[Axis::Vertical].negativeInputState.second = 0;
}

void SecondPlayer::releasedD(EventDetails* details)
{
	movementInput[Axis::Horizontal].positiveInputState.second = 0;
}

void SecondPlayer::pressedA(EventDetails* details)
{
	movementInput[Axis::Horizontal].negativeInputState.second = -1;

	movementInput[Axis::Vertical].positiveInputState.second = 0;
	movementInput[Axis::Vertical].negativeInputState.second = 0;
}

void SecondPlayer::releasedA(EventDetails* details)
{
	movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

void SecondPlayer::dropBomb(EventDetails* details)
{
	character->DropBomb();
}

void SecondPlayer::addInputCallbacks()
{
	EventManager* eventManager = sharedContext->eventManager;

	eventManager->AddCallback(StateType::Play, "Key_W_Pressed", &SecondPlayer::pressedW, this);
	eventManager->AddCallback(StateType::Play, "Key_A_Pressed", &SecondPlayer::pressedA, this);
	eventManager->AddCallback(StateType::Play, "Key_S_Pressed", &SecondPlayer::pressedS, this);
	eventManager->AddCallback(StateType::Play, "Key_D_Pressed", &SecondPlayer::pressedD, this);
	eventManager->AddCallback(StateType::Play, "Key_LShift_Pressed", &SecondPlayer::dropBomb, this);

	eventManager->AddCallback(StateType::Play, "Key_W_Released", &SecondPlayer::releasedW, this);
	eventManager->AddCallback(StateType::Play, "Key_A_Released", &SecondPlayer::releasedA, this);
	eventManager->AddCallback(StateType::Play, "Key_S_Released", &SecondPlayer::releasedS, this);
	eventManager->AddCallback(StateType::Play, "Key_D_Released", &SecondPlayer::releasedD, this);

}

void SecondPlayer::removeInputCallbacks()
{
	EventManager* eventManager = sharedContext->eventManager;

	eventManager->RemoveCallback(StateType::Play, "Key_W_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_A_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_S_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_D_Pressed");
	eventManager->RemoveCallback(StateType::Play, "Key_LShift_Pressed");

	eventManager->RemoveCallback(StateType::Play, "Key_W_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_A_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_S_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_D_Released");
	eventManager->RemoveCallback(StateType::Play, "Key_Space_Released");
}

void SecondPlayer::SetMovementDirection()
{
	movementDirection.x = movementInput[Axis::Horizontal].positiveInputState.second + movementInput[Axis::Horizontal].negativeInputState.second;
	movementDirection.y = movementInput[Axis::Vertical].positiveInputState.second + movementInput[Axis::Vertical].negativeInputState.second;

	character->SetMovementDirection(movementDirection);
}
void SecondPlayer::onCharacterdied()
{
	sharedContext->SwitchState(StateType::GameEnd);
}
