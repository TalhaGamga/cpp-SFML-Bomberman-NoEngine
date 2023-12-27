#pragma once
#include <vector>
#include <functional>

using OnTakingDamage = std::vector<std::function<void()>>;

class Damageable
{
public:
	virtual void TakeDamage(float damage) = 0;
	void SetHp(float initialHp);
	bool isDied = false;

	template <typename T>
	void BindOnTakingDamage(T* instance, void (T::* method)()) {
		onTakingDamage.push_back(std::bind(method, instance));
	}

	float getInitialHp();
	float getCurrentHp();

protected:
	float initialHp;
	float currentHp;

	OnTakingDamage onTakingDamage;
};

