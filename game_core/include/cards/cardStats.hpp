#pragma once

#include <array>
#include <card.hpp>

namespace royale
{
	struct UnitStats {
		Vector2 size;
		int health;
		int damage;
		//double attackCooldown;
	};

	struct SpellStats {
		Vector2 size;
		int damage;
		double duration;
		double cooldown;
	};

	struct StructureStats {
		int damage;
		int health;
		int healthDecrement;
	};

	static std::array<UnitStats, CARD_COUNT> initUnitStats()
	{
		std::array<UnitStats, CARD_COUNT> stats{};
		
		stats[toIndex(Card::Bomber)] =	{Vector2{1.2, 1.2}, 10,  5};
		stats[toIndex(Card::Giant)] =	{ Vector2{2, 2}, 199,  10 };
		stats[toIndex(Card::Goblins)] =	{ Vector2{0.6, 0.6}, 10,  3 };
		stats[toIndex(Card::Golem)] =	{ Vector2{2.5, 2.5}, 246, 23 };
		stats[toIndex(Card::Knight)] =	{ Vector2{1, 1}, 124,  12 };
		stats[toIndex(Card::Prince)] =	{ Vector2{1, 1}, 93,  20 };
		stats[toIndex(Card::Princess)] =	{ Vector2{0.6, 0.6}, 20,  50 };

		return stats;
	}

	static std::array<SpellStats, CARD_COUNT> initSpellStats()
	{
		std::array<SpellStats, CARD_COUNT> stats{};

		stats[toIndex(Card::Arrows)] = {Vector2{0.6, 0.6}, 20,  50, 10};

		return stats;
	}

	static std::array<StructureStats, CARD_COUNT> initStructureStats()
	{
		std::array<StructureStats, CARD_COUNT> stats{};

		stats[toIndex(Card::XBow)] = { 10, 20,  50 };

		return stats;
	}

	static std::array<CardType, CARD_COUNT> initCardTypes()
	{
		std::array<CardType, CARD_COUNT> types{};

		// Set unit types
		for (int i = toIndex(Card::None); i <= toIndex(Card::Princess); i++)
		{
			types[i] = CardType::Unit;
		}

		// Set Spell types
		for (int i = toIndex(Card::Arrows); i <= toIndex(Card::Arrows); i++)
		{
			types[i] = CardType::Spell;
		}

		// Set Structure types
		for (int i = toIndex(Card::XBow); i <= toIndex(Card::XBow); i++)
		{
			types[i] = CardType::Structure;
		}

		return types;
	}

	// used to determine in which array is needed stats placed
	static inline const std::array<CardType, CARD_COUNT> cardTypes = initCardTypes();

	// Keep all of the arrays of size unit count (3x memory usage then needed)
	// This allows to access stats by Card::Knight, etc
	static inline const std::array<UnitStats, CARD_COUNT> unitStats = initUnitStats();
	static inline const std::array<SpellStats, CARD_COUNT> spellStats = initSpellStats();
	static inline const std::array<StructureStats, CARD_COUNT> structureStats = initStructureStats();
}
