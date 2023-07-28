#pragma once

#include "../stdafx.h"

class Skillshot
{
private:
	int slotIndex;
	float range;
	float radius;
	float speed;
	float castTime;
	int type;
	std::vector<int> collidableWith;

public:
	Skillshot() : slotIndex(0), range(0.0f), radius(0.0f), speed(0.0f), castTime(0.0f), type(SkillshotType::SkillshotNone) {}

	Skillshot(float range, float radius, float speed, float castTime, int type, std::vector<int> collidableWith = {}) :
		slotIndex(0),
		range(range),
		radius(radius),
		speed(speed),
		castTime(castTime),
		type(type),
		collidableWith(collidableWith) {}

	void SetSlotIndex(int slotIndex);
	float GetRange();
	float GetRadius();
	float GetSpeed();
	float GetCastTime();
	int GetType();
	bool IsCollidableWith(int type);

public:
	float GetMaxRange();
	std::string GetName();
	bool IsCastable();
	int GetStacks();
};

class SkillshotManager
{
private:
	std::map<std::string, std::map<int, Skillshot>> spells;

	static SkillshotManager& GetInstance() {
		static SkillshotManager instance;
		return instance;
	}

	SkillshotManager() {}

public:
	static Skillshot RegisterSpell(const std::string& name, const int& slotIndex, Skillshot spell) {
		spell.SetSlotIndex(slotIndex);
		GetInstance().spells[name][slotIndex] = spell;
		return spell;
	}

	static bool GetSpell(const std::string& name, const int& slotIndex, Skillshot &out) {
		auto& instance = GetInstance();
		auto itName = instance.spells.find(name);
		if (itName != instance.spells.end()) {
			auto itSpellId = (*itName).second.find(slotIndex);
			if (itSpellId != (*itName).second.end()) {
				out = itSpellId->second;
				return true;
			}
		}
		return false;
	}
};