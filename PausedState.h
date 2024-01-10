#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

// Class representing the paused state of the game.
class PausedState : public BaseState {
public:
	// Constructor taking a pointer to the game state manager.
	PausedState(GameStateManager* stateManager) : BaseState(stateManager) {}

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

	// Callback for unpausing the game.
	void Unpause(EventDetails* details);

private:
	// Text for displaying pause information.
	sf::Text text;

	// Rectangle shape for visual representation of the paused state.
	sf::RectangleShape rect;

	// Font used for text rendering.
	sf::Font font;
};
