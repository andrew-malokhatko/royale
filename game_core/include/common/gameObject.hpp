#pragma once

#include <stdexcept>
#include <vector>
#include <memory>
#include "vector2.hpp"
#include "Component.hpp"

namespace royale
{
	// forward declare the game
	// this allows to pass Game as a context to the GameObject
	class Game;

	class GameObject
	{
		Game& mContext;
		std::vector<std::unique_ptr<Component>> mComponents;

	protected:
		Vector2 mPosition;
		Vector2 mSize;

	public:
		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(Vector2 position, Vector2 size, Game& context);

		const Vector2& getPosition();
		const Vector2& getSize();

		bool collides(Vector2 point);
		bool collides(GameObject other);

		void update();
		Game& getContext();

		void addComponent(std::unique_ptr<Component> component)
		{
			mComponents.emplace_back(std::move(component));
		}

		template<typename T> requires std::is_base_of_v<Component, T>
		T& getComponent()
		{
			for (auto& component : mComponents)
			{
				//Component* ptr = dynamic_cast<T*>(component.get());
				Component* ptr = nullptr;
				if (ptr != nullptr)
				{
					return *ptr;
				}
			}

			throw std::exception("Component not found");
		}

		//template<typename T> requires std::is_base_of_v<Component, T>
		//bool hasComponent()
		//{
		//	for (auto component : mComponents)
		//	{
		//		auto target = dynamic_cast<T*>(component);
		//		if (target != nullptr)
		//		{
		//			return true;
		//		}
		//	}
		//	return false;
		//}
	};
}