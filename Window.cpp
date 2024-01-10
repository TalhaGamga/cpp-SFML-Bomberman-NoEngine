#include "Window.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Default constructor for the Window class, calls the Setup function with default values
Window::Window() {
	Setup("Window", sf::Vector2u(1080, 720));
}

// Overloaded constructor for the Window class, calls the Setup function with specified values
Window::Window(const std::string& title, const sf::Vector2u& size) {
	Setup(title, size);
}

// Destructor for the Window class, calls the Destroy function
Window::~Window() {
	Destroy();
}

// Setup function to initialize window properties and event callbacks
void Window::Setup(const std::string& title, const sf::Vector2u& size) {
	windowTitle = title;
	windowSize = size;
	isFullScreen = false;
	isDone = false;
	isFocused = true; // Default value for focused flag

	bgColor = new sf::Color(50, 50, 50);

	// Add event callbacks for fullscreen toggle and window close
	eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullScreen, this);
	eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);

	// Create the window
	Create();
}

// Create the SFML window based on the current properties
void Window::Create() {

	auto style = (isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);

	window.create({ windowSize.x,windowSize.y }, windowTitle, style);
}

// Close the SFML window
void Window::Destroy() {
	window.close();
}

// Handle events, update the EventManager, and adjust focus state
void Window::Update() {
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			isFocused = false;
		}

		else if (event.type == sf::Event::GainedFocus)
		{
			isFocused = true;
		}

		eventManager.HandleEvent(event);
	}

	eventManager.Update();
}

// Clear the window for drawing
void Window::BeginDraw() {
	window.clear(*bgColor);
	window.draw(bgSprite);
}

// Display the contents of the window
void Window::EndDraw() {
	window.display();
}

// Check if the window is flagged as done
bool Window::IsDone() {
	return isDone;
}

// Check if the window is in fullscreen mode
bool Window::IsFullScreen() {
	return isFullScreen;
}

// Get the size of the window
sf::Vector2u Window::GetWindowSize() {
	return windowSize;
}

// Get the EventManager associated with the window
EventManager* Window::GetEventManager()
{
	return &eventManager;
}

// Check if the window is focused
bool Window::IsFocused()
{
	return isFocused;
}

// Get the SFML RenderWindow object associated with the window
sf::RenderWindow* Window::GetRenderWindow()
{
	return &window;
}

// Close the window in response to the "Window_close" event
void Window::Close(EventDetails* details)
{
	isDone = true;
}

// Toggle fullscreen mode in response to the "Fullscreen_toggle" event
void Window::ToggleFullScreen(EventDetails* details) {
	isFullScreen = !isFullScreen;

	Destroy();
	Create();
}
