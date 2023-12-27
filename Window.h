#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw(); // Clear the window
	void EndDraw(); // Display the changes

	void Update();

	bool IsDone();
	bool IsFullScreen();

	sf::Vector2u GetWindowSize();
	EventManager* GetEventManager();

	bool IsFocused();

	void ToggleFullScreen(EventDetails* details);
	void Close(EventDetails* details = nullptr);

	sf::RenderWindow* GetRenderWindow();

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Destroy();
	void Create();

	EventManager eventManager;

	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;

	bool isDone;
	bool isFullScreen;
	bool isFocused;
};

