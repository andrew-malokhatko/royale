#pragma once

#include <nlohmann/json.hpp>
#include "Component.hpp"
#include "MovementStrategy.hpp"
#include <memory>

namespace royale
{
	using json = nlohmann::json;

	class MovementComponent : public Component
	{
		double mSpeed;
		MovementStrategy* mStrategy;

	public:
		MovementComponent(double speed, MovementStrategy* movementStrategy);
		~MovementComponent();

		void update(GameObject& gameObject) override;
		std::unique_ptr<Component> clone() const override;

		double getSpeed() const;
		void setSpeed(double speed);

		static std::unique_ptr<MovementComponent> fromJson(json& data);
	};
}