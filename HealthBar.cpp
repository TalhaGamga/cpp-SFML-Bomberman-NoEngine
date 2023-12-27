#include "HealthBar.h"

HealthBar::HealthBar(Damageable* damageable) :
	bgSize(sf::Vector2f(50.0f, 8.0f)),
	fgSize(sf::Vector2f(48.0f, 6.0f)),
	fgOffset((bgSize.x - fgSize.x) / 2.0f)
{
	this->damageable = damageable;
	backgroundBarShape.setFillColor(sf::Color::White);
	foregroundBarShape.setFillColor(sf::Color(0, 220, 0));

	foregroundBarShape.setSize(fgSize);
	backgroundBarShape.setSize(bgSize);

	backgroundBarShape.setOrigin(sf::Vector2f(backgroundBarShape.getSize().x / 2.0f, backgroundBarShape.getSize().y / 2.0f));
	foregroundBarShape.setOrigin(sf::Vector2f(0, foregroundBarShape.getSize().y / 2.0f));

	damageable->BindOnTakingDamage(this, &HealthBar::SetHealthBar);
}

void HealthBar::Update()
{
	backgroundBarShape.setPosition(getPosition());
	foregroundBarShape.setPosition(sf::Vector2f(backgroundBarShape.getGlobalBounds().left + fgOffset, backgroundBarShape.getPosition().y));
	foregroundBarShape.setOrigin(sf::Vector2f(0, foregroundBarShape.getSize().y / 2.0f));
}

void HealthBar::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

void HealthBar::Tick(sf::Time& elapsed)
{}

void HealthBar::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(backgroundBarShape);
	window.draw(foregroundBarShape);
}

void HealthBar::SetHealthBar()
{
	sf::Vector2f nextSize = sf::Vector2f(fgSize.x * damageable->getCurrentHp() / damageable->getInitialHp(), fgSize.y);
	foregroundBarShape.setSize(nextSize);
}