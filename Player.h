#pragma once
#include "FirstCharacter.h"
#include "GameStateManager.h"
#include "Enums.h"

// Alias for representing a pair of direction and input state.
using DirectionInputState = std::pair<Direction2D, int>;

// Structure representing 2D input axis with positive and negative input states.
struct InputAxis2D {
    InputAxis2D();

    InputAxis2D(DirectionInputState positiveInputState, DirectionInputState negativeInputState)
        : positiveInputState(positiveInputState), negativeInputState(negativeInputState) {}

    DirectionInputState positiveInputState;
    DirectionInputState negativeInputState;
};

// Alias for representing movement input configuration.
using MovementInput = std::unordered_map<Axis, InputAxis2D>;

// Class representing the player in the game.
class Player
{
public:
    // Constructor taking a pointer to the shared context and map data.
    Player(SharedContext* sharedContext, MapData* mapData);

    // Destructor.
    ~Player();

    // Update method called during the game loop.
    void Update();

    // Initialize the player.
    void Init();

    // Get the character associated with the player.
    CharacterBase* GetCharacter();

private:
    // Callback methods for handling input events.
    void pressedUpward(EventDetails* details);
    void releasedUpward(EventDetails* details);
    void pressedDownward(EventDetails* details);
    void releasedDownward(EventDetails* details);
    void pressedRight(EventDetails* details);
    void releasedRight(EventDetails* details);
    void pressedLeft(EventDetails* details);
    void releasedLeft(EventDetails* details);
    void dropBomb(EventDetails* details);

    // Add input callbacks for the player.
    void addInputCallbacks();

    // Remove input callbacks for the player.
    void removeInputCallbacks();

    // Set the movement direction based on input.
    void SetMovementDirection();

    // Callback for when the character dies.
    void onCharacterdied();

    // Flags indicating whether certain movement keys are pressed.
    bool isPressedUpward = false;
    bool isPressedDownward = false;
    bool isPressedRight = false;
    bool isPressedLeft = false;

    // Pointer to the shared context.
    SharedContext* sharedContext;

    // Pointer to the character associated with the player.
    CharacterBase* character;

    // Mapping of movement input configurations.
    MovementInput movementInput;

    // Current movement direction of the player.
    sf::Vector2i movementDirection;
};

