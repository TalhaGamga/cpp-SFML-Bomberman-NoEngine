#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

// Class representing the credits state in the game.
class CreditsState : public BaseState
{
public:
	// Constructor taking a pointer to the game state manager.
	CreditsState(GameStateManager* stateManager) : BaseState(stateManager) {}

	// Destructor.
	~CreditsState() override {}

	// Called when the state is created.
	void OnCreate() override;

	// Called when the state is destroyed.
	void OnDestroy() override;

	// Adds input callbacks for the state.
	void AddInputCallbacks() override;

	// Removes input callbacks for the state.
	void RemoveInputCallbacks() override;

	// Activates the state.
	void Activate() override;

	// Deactivates the state.
	void Deactivate() override;

	// Updates the state.
	void  Update() override;

	// Ticks the state based on elapsed time.
	void  Tick(const sf::Time& time) override;

	// Draws the state.
	void Draw() override;

private:
	// Callback function for handling mouse clicks.
	void MouseClick(EventDetails* details);

	// Text object for displaying credits information.
	sf::Text text;

	// Size of rectangles used for visual separation in the display.
	sf::Vector2f rectSize;

	// Position of rectangles in the display.
	sf::Vector2f rectPos;

	// Padding between rectangles.
	unsigned int rectPadding;

	// Font used for text rendering.
	sf::Font font;

	// Array of rectangle shapes for visual separation.
	sf::RectangleShape rects[6];

	// Array of text labels for displaying credits information.
	sf::Text labels[6];
};
