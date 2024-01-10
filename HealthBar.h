#pragma once
#include "Damageable.h"
#include "MapObject.h"

#ifndef HEALTHBAR
#define HEALTHBAR

// Class representing a health bar associated with a damageable entity.
class HealthBar : public sf::Drawable, public  sf::Transformable
{
public:
	// Constructor taking a pointer to a damageable entity.
	HealthBar(Damageable* damageable);

	// Update method called during the game loop.
	void Update();

	// Render method for rendering the health bar.
	void Render(sf::RenderWindow* window);

	// Tick method called based on elapsed time.
	void Tick(sf::Time& elapsed);

	// Abstract method for drawing the health bar.
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

private:
	// Pointer to the associated damageable entity.
	Damageable* damageable;

	// Shape representing the background of the health bar.
	sf::RectangleShape backgroundBarShape;

	// Shape representing the foreground of the health bar.
	sf::RectangleShape foregroundBarShape;

	// Size of the foreground and background bars.
	sf::Vector2f fgSize;
	sf::Vector2f bgSize;

	// Offset between the background and foreground bars.
	float fgOffset; // bg - fg

	// Set the size and position of the health bar.
	void SetHealthBar();
};

#endif
