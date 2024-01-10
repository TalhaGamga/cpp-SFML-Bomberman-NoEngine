#include "CreditsState.h"

void CreditsState::OnCreate()
{
	// Load font and set up text for the credits heading.
	font.loadFromFile("Assets/Fonts/arial.ttf");
	text.setFont(font);
	text.setString(sf::String("CREDITS"));
	text.setCharacterSize(60);

	// Set the origin and position of the text.
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	float windowSizeX = GetStateManager()->GetContext()->window->GetWindowSize().x;
	float windowSizeY = GetStateManager()->GetContext()->window->GetWindowSize().y;
	text.setPosition(windowSizeX / 2, 50);

	// Set up parameters for clickable rectangles displaying credits information.
	rectSize = sf::Vector2f(500.0f, 64.0f);
	rectPos = sf::Vector2f(windowSizeX / 2, 200);
	rectPadding = 4;

	// Array of strings containing credits information.
	std::string str[6];
	str[0] = "TALHA GAMGA - BODYBUILDER";
	str[1] = "MUHAMMED FATIH ASAN - ACTOR";
	str[2] = "BUGRA BILDIREN - DOCTOR";
	str[3] = "MURATHAN KARAKAYA - WARRIOR";
	str[4] = "SELCUK USTUN - USTUNBUS CEO";
	str[5] = "EXIT";

	// Loop to create and position rectangles and labels for each credit entry.
	for (int i = 0; i < 6; i++)
	{
		sf::Vector2f rectPosition(rectPos.x, rectPos.y + (i * (rectSize.y + rectPadding)));

		rects[i].setSize(rectSize);
		rects[i].setFillColor(sf::Color::Red);
		rects[i].setOrigin(rectSize.x / 2.0f, rectSize.y / 2.0f);
		rects[i].setPosition(rectPosition);

		labels[i].setFont(font);
		labels[i].setString(sf::String(str[i]));
		labels[i].setCharacterSize(30);

		sf::FloatRect rect = labels[i].getLocalBounds();
		labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		labels[i].setPosition(rectPosition);
	}

	// Add input callbacks for mouse clicks.
	AddInputCallbacks();
}

void CreditsState::OnDestroy()
{
	// Remove input callbacks when destroying the state.
	RemoveInputCallbacks();
}

void CreditsState::AddInputCallbacks()
{
	// Add callback for mouse click event.
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->AddCallback(StateType::Credits, "Mouse_Left", &CreditsState::MouseClick, this);
}

void CreditsState::RemoveInputCallbacks()
{
	// Remove callback for mouse click event.
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::Credits, "Mouse_Left");
}

void CreditsState::Activate()
{
	// No specific activation behavior for the CreditsState.
}

void CreditsState::Deactivate()
{
	// No specific deactivation behavior for the CreditsState.
}

void CreditsState::Update()
{
	// No regular update behavior for the CreditsState.
}

void CreditsState::Tick(const sf::Time& time)
{
	// No regular tick behavior for the CreditsState.
}

void CreditsState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	// Draw the credits heading.
	window->draw(text);

	// Draw rectangles and labels for each credit entry.
	for (int i = 0; i < 6; ++i)
	{
		window->draw(rects[i]);
		window->draw(labels[i]);
	}
}

void CreditsState::MouseClick(EventDetails* details)
{
	// Handle mouse click events on the rectangles.
	sf::Vector2i mousePos = details->mouse;
	float halfX = rectSize.x / 2.0f;
	float halfY = rectSize.y / 2.0f;

	// Check if the mouse position is within the boundaries of each rectangle.
	for (int i = 0; i < 6; ++i)
	{
		if ((mousePos.x >= rects[i].getPosition().x - halfX && mousePos.x <= rects[i].getPosition().x + halfX) &&
			(mousePos.y >= rects[i].getPosition().y - halfY && mousePos.y <= rects[i].getPosition().y + halfY))
		{
			// Execute specific actions based on the clicked rectangle.
			if (i == 5) {
				stateManager->GetContext()->window->Close();
			}
		}
	}
}
