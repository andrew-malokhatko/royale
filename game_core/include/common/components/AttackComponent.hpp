#pragma once

#include "nlohmann/json.hpp"
#include "Component.hpp"
#include "AttackStrategy.hpp"
#include "TargetType.hpp"
#include <memory>

namespace royale
{
	using json = nlohmann::json;

	class AttackComponent : public Component
	{
		int mDamage;
		double mSpeed;
		double mRange;
		GameObject* mTarget {};

		TargetType mTargetType;
		AttackStrategy* mStrategy;

	public:
		AttackComponent(int damage, double speed, double range, TargetType targetType, AttackStrategy* attackStrategy);
		~AttackComponent();

		void update(GameObject& gameObject) override;
		std::unique_ptr<Component> clone() const override;

		static std::unique_ptr<AttackComponent> fromJson(json& data);
	};
}