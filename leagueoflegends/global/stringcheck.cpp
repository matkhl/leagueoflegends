#include "../stdafx.h"

namespace functions::stringcheck
{
	static std::vector<std::string> jungleMonsterObjects = {
		JUNGLE_MONSTER_GROMP,
		JUNGLE_MONSTER_WOLF,
		JUNGLE_MONSTER_WOLF_MINI,
		JUNGLE_MONSTER_RAPTOR,
		JUNGLE_MONSTER_RAPTOR_MINI,
		JUNGLE_MONSTER_KRUG,
		JUNGLE_MONSTER_KRUG_MINI,
		JUNGLE_MONSTER_KRUG_MINI_MINI,
		JUNGLE_MONSTER_CRAB,
		JUNGLE_MONSTER_BLUE,
		JUNGLE_MONSTER_RED,
		JUNGLE_MONSTER_BARON,
		JUNGLE_MONSTER_HERALD,
		JUNGLE_MONSTER_DRAGON_INFERNAL,
		JUNGLE_MONSTER_DRAGON_OCEAN,
		JUNGLE_MONSTER_DRAGON_MOUNTAIN,
		JUNGLE_MONSTER_DRAGON_CLOUD,
		JUNGLE_MONSTER_DRAGON_HEXTECH,
		JUNGLE_MONSTER_DRAGON_CHEMTECH,
		JUNGLE_MONSTER_DRAGON_ELDER
	};

	static std::vector<std::string> minionObjects = {
		MINION_MELEE_BLUE,
		MINION_MELEE_RED,
		MINION_RANGED_BLUE,
		MINION_RANGED_RED,
		MINION_CANNON_BLUE,
		MINION_CANNON_RED,
		MINION_SUPER_BLUE,
		MINION_SUPER_RED
	};

	bool VectorContains(std::vector<std::string> vector, std::string string)
	{
		return std::find(vector.begin(), vector.end(), string) != vector.end();
	}

	bool IsJungleMonsterObject(std::string objectName)
	{
		return VectorContains(jungleMonsterObjects, objectName);
	}

	bool IsMinionObject(std::string objectName)
	{
		return VectorContains(minionObjects, objectName);
	}
}