#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

class PausedState : public BaseState {
public:
	PausedState(GameStateManager* stateManager) : BaseState(stateManager) {
	}

	void OnCreate() override;
	void OnDestroy() override;

	void AddInputCallbacks() override;
	void RemoveInputCallbacks() override;

	void Activate() override;	
	void Deactivate() override;

	void  Update() override;
	void  Tick(const sf::Time& time) override;

	void Draw() override;
	void Unpause(EventDetails* details);

private:
	sf::Text text;
	sf::RectangleShape rect;
	sf::Font font;
};