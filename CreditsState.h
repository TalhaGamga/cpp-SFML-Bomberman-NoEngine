#pragma once
#include "BaseState.h"
#include "GameStateManager.h"
class CreditsState : public BaseState
{
public:
	CreditsState(GameStateManager* stateManager) : BaseState(stateManager) {}

	~CreditsState() override {}

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
	void MouseClick(EventDetails* details);

	sf::Text text;
	sf::Vector2f rectSize;
	sf::Vector2f rectPos;
	unsigned int rectPadding;

	sf::Font font;

	sf::RectangleShape rects[6];
	sf::Text labels[6];
};