#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

// Class representing the intro state of the game.
class IntroState : public BaseState {

public:
	// Constructor taking a pointer to the game state manager.
	IntroState(GameStateManager* stateManager) : BaseState(stateManager) {}

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

	// Continue to the next state.
	void Continue(EventDetails* details);

private:
	// Texture for the intro background.
	sf::Texture introTexture;

	// Sprite for displaying the intro background.
	sf::Sprite introSprite;

	// Font for text rendering.
	sf::Font font;

	// Text displaying information during the intro.
	sf::Text text;

	// Time passed during the intro.
	float timePassed;
};