#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

// Class representing the game end state.
class GameEndState : public BaseState
{
public:
	// Constructor taking a pointer to the game state manager.
	GameEndState(GameStateManager* stateManager) : BaseState(stateManager) {}

	// Destructor.
	~GameEndState() override {}

	// Called when the state is created.
	void OnCreate() override;

	// Called when the state is destroyed.
	void OnDestroy() override;

	// Add input callbacks for the state.
	void AddInputCallbacks() override;

	// Remove input callbacks for the state.
	void RemoveInputCallbacks() override;

	// Activate the state.
	void Activate() override;

	// Deactivate the state.
	void Deactivate() override;

	// Update method called during the game loop.
	void Update() override;

	// Tick method called based on elapsed time.
	void Tick(const sf::Time& time) override;

	// Draw method for rendering the state.
	void Draw() override;

	// Callback to navigate to the main menu.
	void GoToMainMenu(EventDetails* details);

private:
	// Callback for mouse click events.
	void MouseClick(EventDetails* details);

	// Text for displaying game end information.
	sf::Text text;

	// Size of buttons.
	sf::Vector2f buttonSize;

	// Position of buttons.
	sf::Vector2f buttonPos;

	// Padding between buttons.
	unsigned int buttonPadding;

	// Font used for text rendering.
	sf::Font font;

	// Rectangle shape for fading effect.
	sf::RectangleShape faderRect;

	// Rectangle shapes for buttons.
	sf::RectangleShape rects[3];

	// Text labels for buttons.
	sf::Text labels[3];
};
