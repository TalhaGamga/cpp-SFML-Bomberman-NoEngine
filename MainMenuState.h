#pragma once
#include "BaseState.h"
#include "GameStateManager.h"

class MainMenuState : public BaseState {
public:
	MainMenuState(GameStateManager* stateManager) : BaseState(stateManager) {}

	void OnCreate() override;
	void OnDestroy() override;


	void AddInputCallbacks() override;
	void RemoveInputCallbacks() override;

	void Activate() override;
	void Deactivate() override;

	void  Update() override;
	void  Tick(const sf::Time& time) override;

	void Draw() override;
	void MouseClick(EventDetails* details);

private:
	sf::Text text;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	unsigned int buttonPadding;

	sf::RectangleShape rects[2];
	sf::Text labels[2];
	sf::Font font;
};