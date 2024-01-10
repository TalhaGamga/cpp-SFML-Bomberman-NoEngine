#include "IntroState.h"

// OnCreate method for initializing the IntroState
void IntroState::OnCreate()
{
	timePassed = 0.0f;

	// Set up the intro texture and sprite
	sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();
	introTexture.loadFromFile("Assets/Sprites/intro.png");
	introSprite.setTexture(introTexture);
	introSprite.setOrigin(introTexture.getSize().x / 2.0f, introTexture.getSize().y / 2.0f);
	introSprite.setPosition(windowSize.x / 2.0f, 0);

	// Set up the text for prompting user input
	font.loadFromFile("Assets/Fonts/arial.ttf");
	text.setFont(font);
	text.setString({ "Press SPACE to continue" });
	text.setCharacterSize(15);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	// Add input callbacks for the SPACE key
	AddInputCallbacks();
}

// OnDestroy method for cleaning up resources when IntroState is destroyed
void IntroState::OnDestroy()
{
	// Remove input callbacks to avoid unwanted interactions
	RemoveInputCallbacks();
}

// AddInputCallbacks method to register input callbacks for IntroState
void IntroState::AddInputCallbacks()
{
	EventManager* eventManager = stateManager->GetContext()->eventManager;

	// Add a callback for the SPACE key to trigger the Continue method
	eventManager->AddCallback(StateType::Intro, "Intro_Continue", &IntroState::Continue, this);
}

// RemoveInputCallbacks method to unregister input callbacks for IntroState
void IntroState::RemoveInputCallbacks()
{
	EventManager* eventManager = stateManager->GetContext()->eventManager;

	// Remove the callback for the SPACE key
	eventManager->RemoveCallback(StateType::Intro, "Intro_Continue");
}

// Activate method called when IntroState becomes the active state
void IntroState::Activate()
{
}

// Deactivate method called when IntroState is no longer the active state
void IntroState::Deactivate()
{
}

// Update method for handling general state updates (unused in this case)
void IntroState::Update()
{
}

// Tick method for handling time-based updates in IntroState
void IntroState::Tick(const sf::Time& time)
{
	// Move the intro sprite downward for the first 5 seconds
	if (timePassed < 5.0f)
	{
		timePassed += time.asSeconds();
		introSprite.setPosition(introSprite.getPosition().x, introSprite.getPosition().y + (48 * time.asSeconds()));
	}
}

// Draw method for rendering the contents of IntroState
void IntroState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	// Draw the intro sprite
	window->draw(introSprite);

	// Display the prompt text after 5 seconds
	if (timePassed >= 5.0f)
	{
		window->draw(text);
	}
}

// Continue method triggered by the SPACE key, switches to MainMenuState
void IntroState::Continue(EventDetails* details)
{
	if (timePassed >= 5.0f)
	{
		stateManager->SwitchTo(StateType::MainMenu);
		stateManager->Remove(StateType::Intro);
	}
}
