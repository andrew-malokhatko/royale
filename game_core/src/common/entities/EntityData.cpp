#include "EntityData.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <cassert>
#include "CardData.hpp"

// components
#include "AttackComponent.hpp"
#include "HealthComponent.hpp"
#include "MovementComponent.hpp"


namespace royale
{
	using json = nlohmann::json;

	std::unordered_map<EntityType, std::string> initStringFromEntity() noexcept
	{
		std::unordered_map<EntityType, std::string> paths = {};

		// entities
		paths[EntityType::None] = "none";
		paths[EntityType::Archer] = "archer";
		paths[EntityType::Goblin] = "goblin";
		paths[EntityType::Giant] = "giant";
		paths[EntityType::Prince] = "prince";
		paths[EntityType::Bomber] = "bomber";
		paths[EntityType::Knight] = "knight";
		paths[EntityType::Golem] = "golem";
		paths[EntityType::Princess] = "princess";
		paths[EntityType::Arrows] = "arrows";
		paths[EntityType::XBow] = "x_bow";

		// towers
		paths[EntityType::ArcherTower] = "archer_tower";
		paths[EntityType::KingTower] = "king_tower";

		assert(paths.size() == static_cast<size_t>(EntityType::COUNT));
		return paths;
	}

	std::unordered_map<std::string, EntityType> initEntityFromString()
	{
		std::unordered_map<std::string, EntityType> map{};
		map.reserve(STRING_FROM_ENTITY.size());

		for (auto& [key, value] : STRING_FROM_ENTITY)
		{
			map[value] = key;
		}

		return map;
	}

	auto parseComponents(json& j) noexcept
	{
		std::vector<std::unique_ptr<Component>> components{};

		if (j.contains("health"))       components.emplace_back(HealthComponent::fromJson(j["health"]));
		if (j.contains("attack"))       components.emplace_back(AttackComponent::fromJson(j["attack"]));
		if (j.contains("movement"))     components.emplace_back(MovementComponent::fromJson(j["movement"]));

		return components;
	}

	std::unordered_map<EntityType, EntityData> loadEntityData() noexcept
	{
		std::unordered_map<EntityType, EntityData> result;
		result.reserve(STRING_FROM_ENTITY.size());

		for (auto& [type, str] : STRING_FROM_ENTITY)
		{
			std::string fileName = std::format("entities/{}.json", str);
			std::ifstream f(fileName);
			json data = json::parse(f);

			EntityData entity;
			entity.name = data["name"];
			entity.components = std::move(parseComponents(data));

			result[type] = std::move(entity);
		}

		return result;
	}

	/*
	* Move in to archer_tower, but now it just kills itself
	* 
	//"attack": {
	//	"damage": 50,
	//	"speed": 2,
	//	"range": 5,
	//	"target": "any",
	//	"strategy": "arrow"
	//}


	// Same with king tower

	  //"attack": {
	  //  "damage": 70,
	  //  "speed": 1.5,
	  //  "range": 6,
	  //  "target": "any",
	  //  "strategy": "arrow"
	  //}
	
	
	*/

	// function definitions
	const std::unordered_map<EntityType, std::string> STRING_FROM_ENTITY = initStringFromEntity();
	const std::unordered_map<std::string, EntityType> ENTITY_FROM_STRING = initEntityFromString();
	const std::unordered_map<EntityType, EntityData> ENTITY_DATA = loadEntityData();

	// function definitions
	const std::unordered_map<CardType, std::string_view> STRING_FROM_CARD = initStringFromCard();
	const std::unordered_map<std::string_view, CardType> CARD_FROM_STRING = initCardFromString();
	const std::unordered_map<CardType, Card> CARD_DATA = loadCardData();
}