#pragma once

#include "EntityType.hpp"
#include "Component.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>



namespace royale
{
	//
	//  Stores data needed to initialize the entity
	//
	struct EntityData
	{
		std::string name;
		std::vector<std::unique_ptr<Component>> components;
	};

	//
	//	Converts EntityType to string (also indicates filepath to the entity)
	//
	extern const std::unordered_map<EntityType, std::string> STRING_FROM_ENTITY;

	//
	//	Converts string to CardType (mainly used to deserialize from json)
	//
	extern const std::unordered_map<std::string, EntityType> ENTITY_FROM_STRING;

	//
	//	Holds data about all entities in the game
	//
	extern const std::unordered_map<EntityType, EntityData> ENTITY_DATA;
}