#pragma once

#include "movement/GroundMovementStrategy.hpp"
#include "GameContext.hpp"
#include "MovementComponent.hpp"
#include "AttackComponent.hpp"

namespace royale
{
	void GroundMovementStrategy::move(GameObject& gameObject, MovementComponent& comp)
	{
		const GameContext& context = gameObject.getContext();
		double dt = context.getDeltaTime();

		auto& attackComp = gameObject.getComponent<AttackComponent>();
		auto* target = attackComp.mTarget;

		if (!target)
		{
			return;
		}

		if (gameObject.getDistance(*target) <= attackComp.mRange ||
			gameObject.collides(*target))
		{
			return;
		}

		if (target != nullptr)
		{
			Vector2 thisPos = gameObject.getPosition();
			Vector2 targetPos = target->getPosition();

			double difX = targetPos.x - thisPos.x;
			double difY = targetPos.y - thisPos.y;

			Vector2 movement = { difX, difY };
			movement.normalize();
			movement.scale(comp.getSpeed());
			movement.scale(dt);

			gameObject.setPosition(thisPos + movement);
		}

	}
}