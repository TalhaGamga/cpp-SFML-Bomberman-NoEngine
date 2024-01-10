#include "PlayState.h"
#include "Level_1.h"

void PlayState::OnCreate()
{
	// Add input callbacks and load the initial level
	AddInputCallbacks();
	levelManager.LoadLevel(new Level_1(stateManager->GetContext()));
}

void PlayState::OnDestroy()
{
	// Remove input callbacks when the play state is destroyed
	RemoveInputCallbacks();
}

void PlayState::AddInputCallbacks() {
	// Add input callbacks for handling key events during gameplay
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->AddCallback(StateType::Play, "Key_Escape", &PlayState::MainMenu, this);
	eventManager->AddCallback(StateType::Play, "Key_P", &PlayState::Pause, this);
}

void PlayState::RemoveInputCallbacks() {
	// Remove input callbacks when the play state is deactivated or destroyed
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::Play, "Key_Escape");
	eventManager->RemoveCallback(StateType::Play, "Key_P");
}

void PlayState::Activate()
{
	// Activate the play state
}

void PlayState::Deactivate()
{
	// Deactivate the play state
}

void PlayState::Update()
{
	// Update the current level manager during the play state
	levelManager.Update();
}

void PlayState::Tick(const sf::Time& time)
{
	// Perform tick operations on the current level manager
	levelManager.Tick(time);
}

void PlayState::Draw()
{
	// Draw the current level manager to the window
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	levelManager.Render(window);
}

void PlayState::MainMenu(EventDetails* details)
{
	// Switch to the main menu state when the escape key is pressed
	stateManager->SwitchTo(StateType::MainMenu);
}

void PlayState::Pause(EventDetails* details) {
	// Switch to the paused state when the 'P' key is pressed
	stateManager->SwitchTo(StateType::Paused);
}

// Additional comments have been added to explain the purpose of each function and section.
