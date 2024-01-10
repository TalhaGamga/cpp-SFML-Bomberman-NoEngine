#pragma once
#include "BaseState.h"
#include "GameStateManager.h"
#include "LevelManager.h"

// Class representing the play state of the game.
class PlayState : public BaseState {
public:
	// Constructor taking a pointer to the game state manager.
	PlayState(GameStateManager* stateManager) : BaseState(stateManager) {}

	// Destructor.
	~PlayState() override {}

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

	// Callback for returning to the main menu.
	void MainMenu(EventDetails* details);

	// Callback for pausing the game.
	void Pause(EventDetails* details);

private:
	// Manager for handling game levels.
	LevelManager levelManager;
};
