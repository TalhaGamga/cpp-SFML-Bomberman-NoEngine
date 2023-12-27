#pragma once
#include "BaseState.h"
#include "GameStateManager.h"
#include "LevelManager.h"

class PlayState : public BaseState {
public:
	PlayState(GameStateManager* stateManager) : BaseState(stateManager) {
	}

	~PlayState() override {}

	void OnCreate() override;
	void OnDestroy() override;

	void AddInputCallbacks() override;
	void RemoveInputCallbacks() override;

	void Activate() override;
	void Deactivate() override;

	void  Update() override;
	void  Tick(const sf::Time& time) override;

	void Draw() override;

	void MainMenu(EventDetails* details);
	void Pause(EventDetails* details);

private:
	LevelManager levelManager;
};