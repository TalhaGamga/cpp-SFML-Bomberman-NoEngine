#include "SecondPlayer.h"
#include "FirstCharacter.h"

// Constructor for SecondPlayer class, initializes character and input configurations
SecondPlayer::SecondPlayer(SharedContext* sharedContext, MapData* mapData) : sharedContext(sharedContext)
{
    // Create a new instance of the FirstCharacter class with specified parameters
    character = new FirstCharacter(mapData, "Assets/Sprites/Ghost_2.png", sf::Vector2f(145.0f, 155.0f));

    // Initialize movement input configurations
    movementInput.emplace(Axis::Vertical, InputAxis2D(DirectionInputState{ Direction2D::Up, 0 },
        DirectionInputState{ Direction2D::Down, 0 }));

    movementInput.emplace(Axis::Horizontal, InputAxis2D(DirectionInputState{ Direction2D::Right, 0 },
        DirectionInputState{ Direction2D::Left, 0 }));

    // Set callback for character death
    character->onCharacterDied = std::bind(&SecondPlayer::onCharacterdied, this);
}

// Destructor for SecondPlayer class, removes input callbacks
SecondPlayer::~SecondPlayer()
{
    removeInputCallbacks();
}

// Update function for SecondPlayer class, called in each frame
void SecondPlayer::Update()
{
    // Set movement direction based on input
    SetMovementDirection();
}

// Initialization function for SecondPlayer class, adds input callbacks
void SecondPlayer::Init()
{
    addInputCallbacks();
}

// Getter for the character associated with SecondPlayer
CharacterBase* SecondPlayer::GetCharacter()
{
    return character;
}

// Callback function for handling "W" key press event
void SecondPlayer::pressedW(EventDetails* details)
{
    movementInput[Axis::Vertical].positiveInputState.second = -1;

    movementInput[Axis::Horizontal].positiveInputState.second = 0;
    movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

// Callback function for handling "W" key release event
void SecondPlayer::releasedW(EventDetails* details)
{
    movementInput[Axis::Vertical].positiveInputState.second = 0;
}

// Callback function for handling "S" key press event
void SecondPlayer::pressedS(EventDetails* details)
{
    movementInput[Axis::Vertical].negativeInputState.second = 1;

    movementInput[Axis::Horizontal].positiveInputState.second = 0;
    movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

// Callback function for handling "S" key release event
void SecondPlayer::releasedS(EventDetails* details)
{
    movementInput[Axis::Vertical].negativeInputState.second = 0;
}

// Callback function for handling "D" key press event
void SecondPlayer::pressedD(EventDetails* details)
{
    movementInput[Axis::Horizontal].positiveInputState.second = 1;

    movementInput[Axis::Vertical].positiveInputState.second = 0;
    movementInput[Axis::Vertical].negativeInputState.second = 0;
}

// Callback function for handling "D" key release event
void SecondPlayer::releasedD(EventDetails* details)
{
    movementInput[Axis::Horizontal].positiveInputState.second = 0;
}

// Callback function for handling "A" key press event
void SecondPlayer::pressedA(EventDetails* details)
{
    movementInput[Axis::Horizontal].negativeInputState.second = -1;

    movementInput[Axis::Vertical].positiveInputState.second = 0;
    movementInput[Axis::Vertical].negativeInputState.second = 0;
}

// Callback function for handling "A" key release event
void SecondPlayer::releasedA(EventDetails* details)
{
    movementInput[Axis::Horizontal].negativeInputState.second = 0;
}

// Callback function for handling bomb drop event
void SecondPlayer::dropBomb(EventDetails* details)
{
    character->DropBomb();
}

// Add input callbacks for SecondPlayer
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

// Remove input callbacks for SecondPlayer
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

// Set the movement direction of SecondPlayer based on input
void SecondPlayer::SetMovementDirection()
{
    movementDirection.x = movementInput[Axis::Horizontal].positiveInputState.second +
        movementInput[Axis::Horizontal].negativeInputState.second;
    movementDirection.y = movementInput[Axis::Vertical].positiveInputState.second +
        movementInput[Axis::Vertical].negativeInputState.second;

    // Update character's movement direction
    character->SetMovementDirection(movementDirection);
}

// Callback function for character death event, switches game state to GameEnd
void SecondPlayer::onCharacterdied()
{
    sharedContext->SwitchState(StateType::GameEnd);
}
