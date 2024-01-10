#include "PausedState.h"

void PausedState::OnCreate()
{
    SetTransparent(true); // Set our transparency flag

    // Load font and set up the paused text
    font.loadFromFile("Assets/Fonts/arial.ttf");
    text.setFont(font);
    text.setString(sf::String("PAUSED"));
    text.setCharacterSize(14);
    text.setStyle(sf::Text::Bold);

    // Position the paused text at the center of the window
    sf::Vector2u windowSize = stateManager->GetContext()->window->GetRenderWindow()->getSize();
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    // Create a semi-transparent background rectangle covering the entire window
    rect.setSize(sf::Vector2f(windowSize));
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color(0, 0, 0, 150));

    // Register input callback for unpausing
    AddInputCallbacks();
}

void PausedState::OnDestroy()
{
    // Remove input callbacks when the state is destroyed
    RemoveInputCallbacks();
}

void PausedState::AddInputCallbacks()
{
    // Add input callback for unpausing when 'P' key is pressed
    EventManager* eventManager = stateManager->GetContext()->eventManager;
    eventManager->AddCallback(StateType::Paused, "Key_P", &PausedState::Unpause, this);
}

void PausedState::RemoveInputCallbacks()
{
    // Remove input callback when the state is deactivated or destroyed
    EventManager* eventManager = stateManager->GetContext()->eventManager;
    eventManager->RemoveCallback(StateType::Paused, "Key_P");
}

void PausedState::Activate()
{
    // Additional activation logic, if needed
}

void PausedState::Deactivate()
{
    // Additional deactivation logic, if needed
}

void PausedState::Update()
{
    // Additional update logic, if needed
}

void PausedState::Tick(const sf::Time& time)
{
    // Additional tick logic, if needed
}

void PausedState::Draw()
{
    // Draw the semi-transparent background and the paused text
    sf::RenderWindow* window = stateManager->GetContext()->window->GetRenderWindow();
    window->draw(rect);
    window->draw(text);
}

void PausedState::Unpause(EventDetails* details)
{
    // Switch back to the Play state when 'P' key is pressed
    stateManager->SwitchTo(StateType::Play);
}
