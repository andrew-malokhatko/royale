#pragma once

#include "nlohmann/json.hpp"
#include "Component.hpp"
#include "HealthStrategy.hpp"
#include <memory>

namespace royale
{
	using json = nlohmann::json;

	class HealthComponent : public Component
	{
		int mMaxHealth;
		int mHealth;
		HealthStrategy* mStrategy;

	public:
		HealthComponent(int health, int maxHealth, HealthStrategy* healthStrategy);
		~HealthComponent();

		void update(GameObject& gameObject) override;
		std::unique_ptr<Component> clone() const override;

		void takeDamage(int damage);
		void heal(int health);
		double getHealth() const;

		static std::unique_ptr<HealthComponent> fromJson(json& data);
	};
}