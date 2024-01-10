#pragma once
#include "GameStateManager.h"
#include "CharacterBase.h"
#include "Player.h"

using DirectionInputState = std::pair<Direction2D, int>;

// Class representing the second player in the game.
class SecondPlayer
{
public:
	// Constructor for the SecondPlayer class.
	SecondPlayer(SharedContext* sharedContext, MapData* mapData);

	// Destructor for the SecondPlayer class.
	~SecondPlayer();

	// Update method to handle player input and behavior.
	void Update();

	// Initialization method for the second player.
	void Init();

	// Getter for the character associated with the second player.
	CharacterBase* GetCharacter();

private:
	// Input handling method for the "W" key pressed event.
	void pressedW(EventDetails* details);

	// Input handling method for the "W" key released event.
	void releasedW(EventDetails* details);

	// Input handling method for the "S" key pressed event.
	void pressedS(EventDetails* details);

	// Input handling method for the "S" key released event.
	void releasedS(EventDetails* details);

	// Input handling method for the "D" key pressed event.
	void pressedD(EventDetails* details);

	// Input handling method for the "D" key released event.
	void releasedD(EventDetails* details);

	// Input handling method for the "A" key pressed event.
	void pressedA(EventDetails* details);

	// Input handling method for the "A" key released event.
	void releasedA(EventDetails* details);

	// Input handling method for the drop bomb event.
	void dropBomb(EventDetails* details);

	// Method to add input callbacks for the second player.
	void addInputCallbacks();

	// Method to remove input callbacks for the second player.
	void removeInputCallbacks();

	// Method to set the movement direction based on pressed keys.
	void SetMovementDirection();

	// Method called when the character associated with the second player dies.
	void onCharacterdied();

	// Boolean flags to track key press states.
	bool isPressedUpward = false;
	bool isPressedDownward = false;
	bool isPressedRight = false;
	bool isPressedLeft = false;

	// Pointer to the shared context.
	SharedContext* sharedContext;

	// Pointer to the character associated with the second player.
	CharacterBase* character;

	// Mapping of movement input for the second player.
	MovementInput movementInput;

	// Vector representing the movement direction.
	sf::Vector2i movementDirection;
};