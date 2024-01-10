#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"

// Class representing the game window.
class Window {
public:
	// Default constructor.
	Window();

	// Constructor taking title and size parameters.
	Window(const std::string& title, const sf::Vector2u& size);

	// Destructor.
	~Window();

	// Begin drawing by clearing the window.
	void BeginDraw();

	// End drawing and display the changes.
	void EndDraw();

	// Update method for handling window events.
	void Update();

	// Check if the window is closed.
	bool IsDone();

	// Check if the window is in full-screen mode.
	bool IsFullScreen();

	// Get the size of the window.
	sf::Vector2u GetWindowSize();

	// Get the event manager associated with the window.
	EventManager* GetEventManager();

	// Check if the window is currently focused.
	bool IsFocused();

	// Toggle full-screen mode.
	void ToggleFullScreen(EventDetails* details);

	// Close the window.
	void Close(EventDetails* details = nullptr);

	// Get the underlying SFML RenderWindow.
	sf::RenderWindow* GetRenderWindow();

private:
	// Setup method for initializing the window.
	void Setup(const std::string& title, const sf::Vector2u& size);

	// Destroy method for cleaning up resources.
	void Destroy();

	// Create method for creating the window.
	void Create();

	// Event manager for handling window events.
	EventManager eventManager;

	// SFML RenderWindow object.
	sf::RenderWindow window;

	// Size of the window.
	sf::Vector2u windowSize;

	// Title of the window.
	std::string windowTitle;

	// Background color.
	sf::Color* bgColor;

	// Texture for background.
	sf::Texture bgTexture;

	// Sprite for background.
	sf::Sprite bgSprite;

	// Flag indicating if the window is closed.
	bool isDone;

	// Flag indicating if the window is in full-screen mode.
	bool isFullScreen;

	// Flag indicating if the window is focused.
	bool isFocused;
};
