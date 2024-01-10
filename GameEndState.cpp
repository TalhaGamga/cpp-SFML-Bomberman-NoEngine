#include "GameEndState.h"

void GameEndState::OnCreate()
{
    SetTransparent(true); // Set our transparency flag

    font.loadFromFile("Assets/Fonts/arial.ttf");
    text.setFont(font);
    text.setString(sf::String("GAME END"));
    text.setCharacterSize(60);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    float windowSizeX = GetStateManager()->GetContext()->window->GetWindowSize().x;
    float windowSizeY = GetStateManager()->GetContext()->window->GetWindowSize().y;

    text.setPosition(windowSizeX / 2, 100);

    buttonSize = sf::Vector2f(500.0f, 64.0f);
    buttonPos = sf::Vector2f(windowSizeX / 2, windowSizeY / 2);
    buttonPadding = 4;

    std::string str[2];

    str[0] = "CREDITS";
    str[1] = "EXIT";

    faderRect.setSize(sf::Vector2f(windowSizeX, windowSizeY));
    faderRect.setPosition(0, 0);
    faderRect.setFillColor(sf::Color(0, 0, 0, 100));

    for (int i = 0; i < 2; i++)
    {
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

    rects[2] = faderRect;

    AddInputCallbacks();
}

void GameEndState::OnDestroy()
{
    RemoveInputCallbacks();
}

void GameEndState::AddInputCallbacks()
{
    EventManager* eventManager = stateManager->GetContext()->eventManager;
    eventManager->AddCallback(StateType::GameEnd, "Mouse_Left", &GameEndState::MouseClick, this);
}

void GameEndState::RemoveInputCallbacks()
{
    EventManager* eventManager = stateManager->GetContext()->eventManager;
    eventManager->RemoveCallback(StateType::GameEnd, "Mouse_Left");
}

void GameEndState::Activate()
{
}

void GameEndState::Deactivate()
{
}

void GameEndState::Update()
{
}

void GameEndState::Tick(const sf::Time& time)
{
}

void GameEndState::Draw()
{
    sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();

    window->draw(text);

    for (int i = 0; i < 3; ++i)
    {
        window->draw(rects[i]);
        window->draw(labels[i]);
    }
}

void GameEndState::GoToMainMenu(EventDetails* details)
{
    // Implement if needed
}

void GameEndState::MouseClick(EventDetails* details)
{
    sf::Vector2i mousePos = details->mouse;

    float halfX = buttonSize.x / 2.0f;
    float halfY = buttonSize.y / 2.0f;

    for (int i = 0; i < 2; ++i)
    {
        if ((mousePos.x >= rects[i].getPosition().x - halfX && mousePos.x <= rects[i].getPosition().x + halfX) &&
            (mousePos.y >= rects[i].getPosition().y - halfY && mousePos.y <= rects[i].getPosition().y + halfY))
        {
            if (i == 0)
            {
                stateManager->SwitchTo(StateType::Credits);
            }
            else if (i == 1)
            {
                stateManager->GetContext()->window->Close();
            }
        }
    }
}
