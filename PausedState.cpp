#include "PausedState.h"

void PausedState::OnCreate()
{
	SetTransparent(true); // Set our transparency flag
	font.loadFromFile("Assets/Fonts/arial.ttf");
	text.setFont(font);
	text.setString(sf::String("PAUSED"));
	text.setCharacterSize(14);
	text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	rect.setSize(sf::Vector2f(windowSize));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(0, 0, 0, 150));

	AddInputCallbacks();
}


void PausedState::OnDestroy()
{
	RemoveInputCallbacks();
}

void PausedState::AddInputCallbacks() {
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->AddCallback(StateType::Paused, "Key_P", &PausedState::Unpause, this);
}

void PausedState::RemoveInputCallbacks() {
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::Paused, "Key_P");
}


void PausedState::Activate()
{
}

void PausedState::Deactivate()
{
}

void PausedState::Update()
{
}

void PausedState::Tick(const sf::Time& time)
{
}

void PausedState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
	window->draw(rect);
	window->draw(text);
}

void PausedState::Unpause(EventDetails* details)
{
	stateManager->SwitchTo(StateType::Play);
}
