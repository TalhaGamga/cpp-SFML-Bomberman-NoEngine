#include "Damageable.h"

// Set initial health points for the damageable object
void Damageable::SetHp(float initialHp)
{
    // Set the initial and current health points to the specified value
    this->initialHp = initialHp;
    currentHp = initialHp;
}

// Retrieve the initial health points of the damageable object
float Damageable::getInitialHp()
{
    // Return the initial health points
    return initialHp;
}

// Retrieve the current health points of the damageable object
float Damageable::getCurrentHp()
{
    // Return the current health points
    return currentHp;
}
