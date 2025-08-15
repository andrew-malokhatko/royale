#pragma once

#include <memory>

namespace royale
{
	// forward delcare GameObject
	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		//
		//	This function applies component logic to the object
		//
		virtual void update(GameObject& object) = 0;

		//
		//	Clones this component and returns unique_ptr to it
		//
		virtual std::unique_ptr<Component> clone() const = 0;
	};
}