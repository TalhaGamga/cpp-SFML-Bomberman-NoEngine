#include "PlayState.h"
#include "Level_1.h"

void PlayState::OnCreate()
{
	AddInputCallbacks();
	levelManager.LoadLevel(new Level_1(stateManager->GetContext()));
}

void PlayState::OnDestroy()
{
	RemoveInputCallbacks();
}

void PlayState::AddInputCallbacks() {
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->AddCallback(StateType::Play, "Key_Escape", &PlayState::MainMenu, this);
	eventManager->AddCallback(StateType::Play, "Key_P", &PlayState::Pause, this);
}

void PlayState::RemoveInputCallbacks() {
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::Play, "Key_Escape");
	eventManager->RemoveCallback(StateType::Play, "Key_P");
}

void PlayState::Activate()
{
}

void PlayState::Deactivate()
{
}

void PlayState::Update()
{
	levelManager.Update();
}

void PlayState::Tick(const sf::Time& time)
{
	levelManager.Tick(time);
}

void PlayState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	levelManager.Render(window);
}

void PlayState::MainMenu(EventDetails* details)
{
	stateManager->SwitchTo(StateType::MainMenu);
}

void PlayState::Pause(EventDetails* details) {
	stateManager->SwitchTo(StateType::Paused);
}