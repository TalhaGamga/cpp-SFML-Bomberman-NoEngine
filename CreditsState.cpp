#include "CreditsState.h"

void CreditsState::OnCreate()
{
	font.loadFromFile("Assets/Fonts/arial.ttf");
	text.setFont(font);
	text.setString(sf::String("CREDITS"));
	text.setCharacterSize(60);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	float windowSizeX = GetStateManager()->GetContext()->window->GetWindowSize().x;
	float windowSizeY = GetStateManager()->GetContext()->window->GetWindowSize().y;

	text.setPosition(windowSizeX / 2, 50);

	rectSize = sf::Vector2f(500.0f, 64.0f);
	rectPos = sf::Vector2f(windowSizeX / 2, 200);
	rectPadding = 4;

	std::string str[6];

	str[0] = "TALHA GAMGA - BODYBUÝLDER";
	str[1] = "MUHAMMED FATÝH ASAN - AKTÖR";
	str[2] = "BUÐRA BÝLDÝREN - DOKTOR";
	str[3] = "MURATHAN KARAKAYA - SAVAÞÇI";
	str[4] = "SELÇUK ÜSTÜN - ÜSTÜN BUS CEO";
	str[5] = "EXIT";

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

	AddInputCallbacks();
}

void CreditsState::OnDestroy()
{
	RemoveInputCallbacks();
}

void CreditsState::AddInputCallbacks()
{
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->AddCallback(StateType::Credits, "Mouse_Left", &CreditsState::MouseClick, this);

}

void CreditsState::RemoveInputCallbacks()
{
	EventManager* eventManager = stateManager->GetContext()->eventManager;
	eventManager->RemoveCallback(StateType::Credits, "Mouse_Left");

}

void CreditsState::Activate()
{
}

void CreditsState::Deactivate()
{
}

void CreditsState::Update()
{
}

void CreditsState::Tick(const sf::Time& time)
{
}

void CreditsState::Draw()
{
	sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

	window->draw(text);

	for (int i = 0; i < 6; ++i)
	{
		window->draw(rects[i]);
		window->draw(labels[i]);
	}

}

void CreditsState::MouseClick(EventDetails* details)
{
	printf("Mouse click");
	sf::Vector2i mousePos = details->mouse;

	float halfX = rectSize.x / 2.0f;
	float halfY = rectSize.y / 2.0f;

	for (int i = 0; i < 6; ++i)
	{
		if ((mousePos.x >= rects[i].getPosition().x - halfX && mousePos.x <= rects[i].getPosition().x + halfX)
			&&
			(mousePos.y >= rects[i].getPosition().y - halfY && mousePos.y <= rects[i].getPosition().y + halfY))
		{
			if (i == 5) {
				stateManager->GetContext()->window->Close();
			}
		}
	}

}
