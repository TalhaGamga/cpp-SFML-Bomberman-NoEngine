#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

class GameOverState : public BaseState {
public:
	GameOverState(GameStateManager* stateManager) : BaseState(stateManager) {
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
private:
	sf::Text text;
	sf::RectangleShape rect;
	sf::Font font;
};