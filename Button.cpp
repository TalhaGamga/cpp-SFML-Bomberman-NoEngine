#include "Button.h"

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	printf("Button Draw\n");
	target.draw(rect, states);
}

bool Button::OnClick(EventDetails* details)
{
	sf::Vector2i mousePos = details->mouse;

	float halfX = size.x / 2.0f;
	float halfY = size.y / 2.0f;
	return false;
}