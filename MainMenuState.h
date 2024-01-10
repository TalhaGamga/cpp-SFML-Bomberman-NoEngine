#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

// Class representing the main menu state of the game.
class MainMenuState : public BaseState {
public:
	// Constructor taking a pointer to the game state manager.
	MainMenuState(GameStateManager* stateManager) : BaseState(stateManager) {}

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
	void  Update() override;

	// Tick method called based on elapsed time.
	void  Tick(const sf::Time& time) override;

	// Draw method for rendering the state.
	void Draw() override;

	// Callback for mouse click events.
	void MouseClick(EventDetails* details);

private:
	// Text for displaying menu options.
	sf::Text text;

	// Size of buttons.
	sf::Vector2f buttonSize;

	// Position of buttons.
	sf::Vector2f buttonPos;

	// Padding between buttons.
	unsigned int buttonPadding;

	// Rectangle shapes for buttons.
	sf::RectangleShape rects[2];

	// Text labels for buttons.
	sf::Text labels[2];

	// Font used for text rendering.
	sf::Font font;
};
