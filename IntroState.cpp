#include "IntroState.h"
void IntroState::OnCreate()
{
	timePassed = 0.0f;

	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();

	introTexture.loadFromFile("Assets/Sprites/intro.png");
	introSprite.setTexture(introTexture);
	introSprite.setOrigin(introTexture.getSize().x / 2.0f, introTexture.getSize().y / 2.0f);

	introSprite.setPosition(windowSize.x / 2.0f, 0);

	font.loadFromFile("Assets/Fonts/arial.ttf");
	text.setFont(font);
	text.setString({ "Press SPACE to continue" });
	text.setCharacterSize(15);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	AddInputCallbacks();
}

void IntroState::OnDestroy()
{
	RemoveInputCallbacks();
}

void IntroState::AddInputCallbacks()
{
	EventManager* eventManager = stateManager->GetContext()->eventManager;

	eventManager->AddCallback(StateType::Intro, "Intro_Continue", &IntroState::Continue, this);
}

void IntroState::RemoveInputCallbacks()
{
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void IntroState::Activate()
{
}

void IntroState::Deactivate()
{
}

void IntroState::Update()
{
}

void IntroState::Tick(const sf::Time& time)
{
	if (timePassed < 5.0f)
	{
		timePassed += time.asSeconds();
		introSprite.setPosition(introSprite.getPosition().x, introSprite.getPosition().y + (48 * time.asSeconds()));
	}
}

void IntroState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	window->draw(introSprite);
	if (timePassed >= 5.0f)
	{
		window->draw(text);
	}
}

void IntroState::Continue(EventDetails* details) {
	if (timePassed >= 5.0f)
	{
		stateManager->SwitchTo(StateType::MainMenu);
		stateManager->Remove(StateType::Intro);
	}
}