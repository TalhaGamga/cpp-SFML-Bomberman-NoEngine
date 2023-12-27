#include "Damageable.h"

void Damageable::SetHp(float initialHp)
{
	this->initialHp = initialHp;
	currentHp = initialHp;
}

float Damageable::getInitialHp()
{
	return initialHp;
}

float Damageable::getCurrentHp()
{
	return currentHp;
}
