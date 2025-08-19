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
	class GameContext;

	using GameObjectId = size_t;

	class GameObject
	{
		inline static GameObjectId IdGenerator = 0;

		const GameObjectId ID;
		GameContext& mContext;
		std::vector<std::unique_ptr<Component>> mComponents;

	protected:
		Vector2 mPosition;
		Vector2 mSize;

	public:
		//GameObject() = default;
		GameObject(Vector2 position, Vector2 size, GameContext& context);
		GameObject(GameObject&& other) noexcept;
		virtual ~GameObject() = default;

		const Vector2& getPosition() const;
		const Vector2& getSize() const;
		void setPosition(const Vector2& position);
		void setSize(const Vector2& size);

		GameObjectId getId() const;

		Vector2 getCenter() const;
		bool collides(Vector2 point) const;
		bool collides(const GameObject& other) const;
		double getDistance(Vector2 point) const;
		double getDistance(const GameObject& other) const;

		void update();
		GameContext& getContext();

		GameObject& operator=(GameObject&& other) noexcept;

		// Components

		void addComponent(std::unique_ptr<Component> component)
		{
			mComponents.emplace_back(std::move(component));
		}

		template<typename T> requires std::is_base_of_v<Component, T>
		T& getComponent()
		{
			for (auto& component : mComponents)
			{
				T* ptr = dynamic_cast<T*>(component.get());
				if (ptr != nullptr)
				{
					return *ptr;
				}
			}

			throw std::exception("Component not found");
		}
	};
}