#pragma once
#include <vector>
#include <functional>

// Type alias for a vector of functions to be called when taking damage events occur.
using OnTakingDamage = std::vector<std::function<void()>>;

// Interface for objects that can take damage.
class Damageable
{
public:
	// Abstract method for taking damage.
	virtual void TakeDamage(float damage) = 0;

	// Sets the initial and current health points.
	void SetHp(float initialHp);

	// Flag indicating if the object has died.
	bool isDied = false;

	// Binds a member function to the taking damage event.
	template <typename T>
	void BindOnTakingDamage(T* instance, void (T::* method)()) {
		onTakingDamage.push_back(std::bind(method, instance));
	}

	// Gets the initial health points.
	float getInitialHp();

	// Gets the current health points.
	float getCurrentHp();

protected:
	// Initial health points.
	float initialHp;

	// Current health points.
	float currentHp;

	// Vector of functions to be called when taking damage events occur.
	OnTakingDamage onTakingDamage;
};
