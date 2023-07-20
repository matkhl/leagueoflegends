#pragma once

#include "../stdafx.h"

class Skillshot
{
public:
	float range;
	float radius;
	float speed;
	float castTime;
	int type;
	std::vector<int> collidableWith;

public:
	Skillshot() : range(0), radius(0), speed(0), castTime(0), type(SkillshotType::SkillshotLine) {}

	Skillshot(float range, float radius, float speed, float castTime, int type, std::vector<int> collidableWith) :
		range(range),
		radius(radius),
		speed(speed),
		castTime(castTime),
		type(type),
		collidableWith(collidableWith) {}

	float GetRange();
	float GetRadius();
	float GetSpeed();
	float GetCastTime();
	int GetType();
	float IsCollidableWith(int type);

public:
	float GetMaxRange();
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
	static Skillshot RegisterSpell(const std::string& name, const int& spellId, Skillshot spell) {
		GetInstance().spells[name][spellId] = spell;
		return spell;
	}

	static bool GetSpell(const std::string& name, const int& spellId, Skillshot &out) {
		auto& instance = GetInstance();
		auto itName = instance.spells.find(name);
		if (itName != instance.spells.end()) {
			auto itSpellId = (*itName).second.find(spellId);
			if (itSpellId != (*itName).second.end()) {
				out = itSpellId->second;
				return true;
			}
		}
		return false;
	}
};