#include "CardData.hpp"

#include "EntityData.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <cassert>
#include <vector>

namespace royale
{
	using json = nlohmann::json;

	std::unordered_map<CardType, std::string_view> initStringFromCard() noexcept
	{
		std::unordered_map<CardType, std::string_view> paths = {};

		paths[CardType::None] = "none";
		paths[CardType::Archers] = "archers";
		paths[CardType::Goblins] = "goblins";
		paths[CardType::Giant] = "giant";
		paths[CardType::Prince] = "prince";
		paths[CardType::Bomber] = "bomber";
		paths[CardType::Knight] = "knight";
		paths[CardType::Golem] = "golem";
		paths[CardType::Princess] = "princess";
		paths[CardType::Arrows] = "arrows";
		paths[CardType::XBow] = "x_bow";

		assert(paths.size() == static_cast<size_t>(EntityType::COUNT));
		return paths;
	}

	std::unordered_map<std::string_view, CardType> initCardFromString() noexcept
	{
		std::unordered_map<std::string_view, CardType> map{};
		map.reserve(STRING_FROM_CARD.size());

		for (auto& [key, value] : STRING_FROM_CARD)
		{
			map[value] = key;
		}

		return map;
	}

	auto loadCardEntities(const json& data) noexcept
	{
		std::vector<EntitySpawnInfo> info{};
		info.reserve(data.size());

		for (const auto& item : data)
		{
			EntitySpawnInfo spawnInfo;
			std::string name = item.at("entity_name").get<std::string>();

			spawnInfo.type = ENTITY_FROM_STRING.at(name);
			spawnInfo.offset.x = item.at("position").at("x").get<double>();
			spawnInfo.offset.y = item.at("position").at("y").get<double>();

			info.push_back(spawnInfo);
		}

		return info;
	}

	std::unordered_map<CardType, Card> loadCardData() noexcept
	{
		std::unordered_map<CardType, Card> result = {};

		for (auto& [type, str] : STRING_FROM_CARD)
		{
			std::string fileName = std::format("cards/{}.json", str);
			std::ifstream f(fileName);
			json data = json::parse(f);

			CardType type = CARD_FROM_STRING.at(data["name"]);
			Rarity rarity = rarityFromString(data["rarity"]);
			PlacementType placement = placementFromString(data["placement"]);
			int cost = data["cost"];
			std::vector<EntitySpawnInfo> spawnInfo = loadCardEntities(data["entities"]);

			result[type] = Card{ type, rarity, placement, cost, std::move(spawnInfo) };
		}

		return result;
	}

	// function definitions
	const std::unordered_map<CardType, std::string_view> STRING_FROM_CARD = initStringFromCard();
	const std::unordered_map<std::string_view, CardType> CARD_FROM_STRING = initCardFromString();
	const std::unordered_map<CardType, Card> CARD_DATA = loadCardData();
}