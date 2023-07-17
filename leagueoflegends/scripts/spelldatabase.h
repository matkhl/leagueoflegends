#pragma once

#include "../stdafx.h"

class ChampionSpell
{
private:
	float range;
	float speed;
	float castTime;

public:
	float GetRange();
	float GetSpeed();
	float GetCastTime();
};

class ChampionSpellManager
{
public:
	static void RegisterSpell(const std::string& name, const int& spellId, ChampionSpell* spell) {
		GetInstance().spells[name][spellId] = spell;
	}

	static ChampionSpell* GetSpell(const std::string& name, const int& spellId) {
		auto& instance = GetInstance();
		auto itName = instance.spells.find(name);
		if (itName != instance.spells.end()) {
			auto itSpellId = (*itName).second.find(spellId);
			if (itSpellId != (*itName).second.end()) {
				return itSpellId->second;
			}
		}
		return nullptr;
	}

private:
	std::map<std::string, std::map<int, ChampionSpell*>> spells;

	static ChampionSpellManager& GetInstance() {
		static ChampionSpellManager instance;
		return instance;
	}

	ChampionSpellManager() {}
};