#pragma once
#include <SFML/Graphics.hpp>
#include "IClickable.h"

class Button : public sf::Drawable, public IClickable
{
public:
	Button(sf::Vector2f size, sf::Vector2f position, std::string text) : size(size), position(position) {
		rect.setSize(this->size);
		rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(sf::Vector2f(500.0f, 500.0f));

		font.loadFromFile("Assets/Fonts/arial.ttf");

		label.setFont(font);
		label.setString(sf::String(text));
		label.setCharacterSize(12);

		sf::FloatRect rect = label.getLocalBounds();
		label.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		label.setPosition(rect.getPosition());
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnClick(EventDetails* details);

private:
	sf::RectangleShape rect;
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Font font;
	sf::Text label;
};