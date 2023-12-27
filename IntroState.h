#pragma once

#include "BaseState.h"
#include "GameStateManager.h"

class IntroState : public BaseState {

public:
	IntroState(GameStateManager* stateManager) : BaseState(stateManager) {}

	void OnCreate() override;
	void OnDestroy() override;

	void AddInputCallbacks() override;
	void RemoveInputCallbacks() override;

	void Activate() override;
	void Deactivate() override;

	void  Update() override;
	void  Tick(const sf::Time& time) override;

	void Draw() override;

	void Continue(EventDetails* details);

private:
	sf::Texture introTexture;
	sf::Sprite introSprite;
	sf::Font font;
	sf::Text text;
	float timePassed;
};