#include "Window.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Window::Window() {
	Setup("Window", sf::Vector2u(1080, 720));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
	Setup(title, size);
}

Window::~Window() {
	Destroy();
}

void Window::Setup(const std::string& title, const sf::Vector2u& size) {
	windowTitle = title;
	windowSize = size;
	isFullScreen = false;
	isDone = false;
	isFocused = true; // Default value for focused flag

	bgColor = new sf::Color(128, 100, 70);

	//if (bgTexture.loadFromFile("Assets/Sprites/ground_03.png"))
	//{
	//	bgSprite.setTexture(bgTexture);
	//}

	eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullScreen, this);
	eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);

	Create();
}

void Window::Create() {

	auto style = (isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);

	window.create({ windowSize.x,windowSize.y }, windowTitle, style);
}

void Window::Destroy() {
	window.close();
}

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

void Window::BeginDraw() {
	window.clear(sf::Color::Black);
	window.draw(bgSprite);
}

void Window::EndDraw() {
	window.display();
}

bool Window::IsDone() {
	return isDone;
}

bool Window::IsFullScreen() {
	return isFullScreen;
}

sf::Vector2u Window::GetWindowSize() {
	return windowSize;
}

EventManager* Window::GetEventManager()
{
	return &eventManager;
}

bool Window::IsFocused()
{
	return isFocused;
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &window;
}

void Window::Close(EventDetails* details)
{
	isDone = true;
}

void Window::ToggleFullScreen(EventDetails* details) {
	isFullScreen = !isFullScreen;

	Destroy();
	Create();
}