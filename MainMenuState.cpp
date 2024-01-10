#include "MainMenuState.h"

void MainMenuState::OnCreate()
{
	// Load font from file
	font.loadFromFile("Assets/Fonts/arial.ttf");

	// Set up main menu text
	text.setFont(font);
	text.setString(sf::String("MAIN MENU:"));
	text.setCharacterSize(18);

	// Set the origin of the text to the center for proper positioning
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	// Get window size
	float windowSizeX = GetStateManager()->GetContext()->window->GetWindowSize().x;
	float windowSizeY = GetStateManager()->GetContext()->window->GetWindowSize().y;

	// Position the text at the top
	text.setPosition(windowSizeX / 2, 100);

	// Set up button properties
	buttonSize = sf::Vector2f(500.0f, 64.0f);
	buttonPos = sf::Vector2f(windowSizeX / 2, windowSizeY / 2);
	buttonPadding = 4;

	// Define button labels
	std::string str[2];
	str[0] = "PLAY";
	str[1] = "EXIT";

	// Create buttons
	for (int i = 0; i < 2; ++i) {
		sf::Vector2f buttonPosition(buttonPos.x, buttonPos.y + (i * (buttonSize.y + buttonPadding)));

		rects[i].setSize(buttonSize);
		rects[i].setFillColor(sf::Color::Red);

		rects[i].setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		rects[i].setPosition(buttonPosition);

		labels[i].setFont(font);
		labels[i].setString(sf::String(str[i]));
		labels[i].setCharacterSize(12);

		sf::FloatRect rect = labels[i].getLocalBounds();
		labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

		labels[i].setPosition(buttonPosition);
	}

	// Add input callbacks for mouse clicks
	AddInputCallbacks();
}

void MainMenuState::OnDestroy()
{
	// Remove input callbacks when the state is destroyed
	RemoveInputCallbacks();
}

void MainMenuState::AddInputCallbacks()
{
	// Add input callback for mouse click events
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->AddCallback(StateType::MainMenu, "Mouse_Left", &MainMenuState::MouseClick, this);
}

void MainMenuState::RemoveInputCallbacks()
{
	// Remove input callback for mouse click events
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void MainMenuState::Activate()
{
	// If Play state exists and the label is "PLAY", update the label to "RESUME"
	if (stateManager->HasState(StateType::Play) && labels[0].getString() == "PLAY")
	{
		labels[0].setString(sf::String("RESUME"));
		sf::FloatRect rect = labels[0].getLocalBounds();
		labels[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	}
}

void MainMenuState::Deactivate()
{
	// No specific actions on deactivation
}

void MainMenuState::Update()
{
	// No specific update logic for the main menu
}

void MainMenuState::Tick(const sf::Time& time)
{
	// No specific tick logic for the main menu
}

void MainMenuState::Draw()
{
	// Draw main menu elements, including buttons
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	window->draw(text);
	for (int i = 0; i < 2; ++i)
	{
		window->draw(rects[i]);
		window->draw(labels[i]);
	}
}

void MainMenuState::MouseClick(EventDetails* details)
{
	// Handle mouse click events for button interactions
	sf::Vector2i mousePos = details->mouse;

	float halfX = buttonSize.x / 2.0f;
	float halfY = buttonSize.y / 2.0f;

	for (int i = 0; i < 3; ++i)
	{
		if ((mousePos.x >= rects[i].getPosition().x - halfX && mousePos.x <= rects[i].getPosition().x + halfX)
			&&
			(mousePos.y >= rects[i].getPosition().y - halfY && mousePos.y <= rects[i].getPosition().y + halfY))
		{
			if (i == 0)
			{
				// Switch to Play state on "PLAY" button click
				stateManager->SwitchTo(StateType::Play);
			}
			else if (i == 1)
			{
				// Close the window on "EXIT" button click
				stateManager->GetContext()->window->Close();
			}
		}
	}
}
