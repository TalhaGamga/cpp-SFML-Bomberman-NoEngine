#pragma once
#include "Damageable.h"
#include "MapObject.h"

#ifndef HEALTHBAR
#define HEALTHBAR

class HealthBar : public sf::Drawable, public  sf::Transformable
{
public:
	HealthBar(Damageable* damageable);
	void Update();
	void Render(sf::RenderWindow* window);
	void Tick(sf::Time& elapsed);

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;


private:
	Damageable* damageable;

	sf::RectangleShape backgroundBarShape;
	sf::RectangleShape foregroundBarShape;

	sf::Vector2f fgSize;
	sf::Vector2f bgSize;

	float fgOffset; // bg - fg

	void SetHealthBar();
};

#endif