#include "Player.h"
#include "GameStateManager.h"

Player::Player(SharedContext* sharedContext, MapData* mapData) : sharedContext(sharedContext)
{
    // Create a new instance of the FirstCharacter class with provided map data and sprite path
    character = new FirstCharacter(mapData, "Assets/Sprites/Ghost.png", sf::Vector2f(945.0f, 595.0f));

    // Initialize the movement input for vertical and horizontal directions
    movementInput.emplace(Axis::Vertical, InputAxis2D
    (DirectionInputState{ Direction2D::Up, 0 },
        DirectionInputState{ Direction2D::Down, 0 }));

    movementInput.emplace(Axis::Horizontal, InputAxis2D
    (DirectionInputState{ Direction2D::Right, 0 },
        DirectionInputState{ Direction2D::Left, 0 }));

    // Bind the onCharacterDied callback to the player instance
    character->onCharacterDied = std::bind(&Player::onCharacterdied, this);
}

Player::~Player()
{
    // Remove input callbacks when the player is destroyed
    removeInputCallbacks();
}

void Player::Init()
{
    // Add input callbacks to initialize the player
    addInputCallbacks();
}

CharacterBase* Player::GetCharacter()
{
    // Return the player's character instance
    return character;
}

void Player::addInputCallbacks()
{
    // Add input callbacks for various player actions
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
    // Remove input callbacks when the player is deactivated or destroyed
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
    // Set the movement direction based on input
    SetMovementDirection();
}

// Input callback functions for different actions

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
    // Trigger the character to drop a bomb
    character->DropBomb();
}

void Player::SetMovementDirection()
{
    // Set the movement direction based on input
    movementDirection.x = movementInput[Axis::Horizontal].positiveInputState.second + movementInput[Axis::Horizontal].negativeInputState.second;
    movementDirection.y = movementInput[Axis::Vertical].positiveInputState.second + movementInput[Axis::Vertical].negativeInputState.second;

    // Update the character's movement direction
    character->SetMovementDirection(movementDirection);
}

void Player::onCharacterdied()
{
    // Switch to the GameEnd state when the player's character dies
    sharedContext->SwitchState(StateType::GameEnd);
}

InputAxis2D::InputAxis2D()
{
    // Default constructor for InputAxis2D
}
