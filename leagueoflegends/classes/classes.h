#pragma once

#include "../stdafx.h"

class Spell
{
public:
	int GetLevel();
	float GetCooldownTimer();
	float GetCooldown();
	float GetTotalCooldown();
	float GetRelativeCooldown();
};

class Object
{
public:
	int GetTeam();
	Vector3 GetPosition();
	bool IsEnemy();
	bool IsAlive();
	bool IsVisible();
	std::string GetName();
	int GetRecallState();
	Spell* GetSpellById(int id);
};

class HeroManager
{
public:
	int GetListSize();
	Object* GetIndex(int index);
};