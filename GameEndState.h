#pragma once
#include "BaseState.h"
#include "GameStateManager.h"
class GameEndState : public BaseState
{
public:
	GameEndState(GameStateManager* stateManager) : BaseState(stateManager) {}

	~GameEndState() override {}

	void OnCreate() override;
	void OnDestroy() override;

	void AddInputCallbacks() override;
	void RemoveInputCallbacks() override;

	void Activate() override;
	void Deactivate() override;

	void  Update() override;
	void  Tick(const sf::Time& time) override;

	void Draw() override;

	void GoToMainMenu(EventDetails* details);


private:
	void MouseClick(EventDetails* details);

	sf::Text text;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	unsigned int buttonPadding;

	sf::Font font;

	sf::RectangleShape faderRect;

	sf::RectangleShape rects[3];
	sf::Text labels[3];
};

