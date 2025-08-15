#pragma once


#include <nlohmann/json.hpp>
#include <vector>
#include "vector2.hpp"
#include "CardType.hpp"
#include "EntityType.hpp"
#include "Rarity.hpp"
#include "TargetType.hpp"
#include "ResourceType.hpp"
#include "PlacementType.hpp"


namespace royale
{
	//
	//	Stores information about entity(ies) a card can spawn, as well as offset from the placement position(s)
	//
	struct EntitySpawnInfo
	{
		EntityType type;
		Vector2 offset;
	};

	//
	//	Stores general information about card (Type, rarity, cost)
	//	But also instructions on construction (entities)
	//
	class Card
	{
		CardType mType {};
		Rarity mRarity{};
		PlacementType mPlacement{};
		int mCost{};

		std::vector<EntitySpawnInfo> mEntitySpawnInfo{};
			
	public:

		bool operator ==(const Card& other)
		{
			return other.mType == mType;
		}

		Card() = default;
		Card(CardType type, Rarity rarity, PlacementType placement, int cost, std::vector<EntitySpawnInfo> entities);

		CardType getCard() const;
		Rarity getRarity() const;
		PlacementType getPlacement() const;
		int getCost() const;

		const std::vector<EntitySpawnInfo> getEntitySpawnInfo() const;
	};
}
