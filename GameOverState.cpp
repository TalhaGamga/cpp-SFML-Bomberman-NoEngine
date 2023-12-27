#include "GameOverState.h"

void GameOverState::OnCreate()
{
	font.loadFromFile("Assets/Fonts/arial.ttf");
	text.setFont(font);
	text.setString(sf::String("GAME OVER"));
	text.setCharacterSize(40);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	float windowSizeX = GetStateManager()->GetContext()->window->GetWindowSize().x;
	float windowSizeY = GetStateManager()->GetContext()->window->GetWindowSize().y;

	text.setPosition(windowSizeX / 2, 100);

}

void GameOverState::OnDestroy()
{
}

void GameOverState::AddInputCallbacks()
{
}

void GameOverState::RemoveInputCallbacks()
{
}

void GameOverState::Activate()
{
}

void GameOverState::Deactivate()
{
}

void GameOverState::Update()
{
}

void GameOverState::Tick(const sf::Time& time)
{
}

void GameOverState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	window->draw(text);
}
