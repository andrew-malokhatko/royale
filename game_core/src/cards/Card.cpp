#include "Card.hpp"

namespace royale
{
	Card::Card(CardType type, Rarity rarity, PlacementType placement, int cost, std::vector<EntitySpawnInfo> spawnInfo)
		:
		mType{ type },
		mRarity{ rarity },
		mPlacement{ placement },
		mCost{ cost },
		mEntitySpawnInfo{ spawnInfo }
	{
	}

	CardType Card::getCard() const
	{
		return mType;
	}

	Rarity Card::getRarity() const
	{
		return mRarity;
	}

	int Card::getCost() const
	{
		return mCost;
	}

	PlacementType Card::getPlacement() const
	{
		return mPlacement;
	}

	const std::vector<EntitySpawnInfo> Card::getEntitySpawnInfo() const
	{
		return mEntitySpawnInfo;
	}
}