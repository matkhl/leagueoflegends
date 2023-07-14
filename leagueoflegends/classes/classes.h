#pragma once

#include "../stdafx.h"

class SpellData
{
public:
	std::string GetName();
};

class SpellInfo
{
public:
	SpellData* GetSpellData();
};

class SpellInput
{
public:
};

class Spell
{
public:
	int GetLevel();
	float GetCooldownTimer();
	float GetCooldown();
	float GetTotalCooldown();
	float GetRelativeCooldown();
	SpellInput* GetSpellInput();
	SpellInfo* GetSpellInfo();
public:
	std::string GetName();
};

class Object
{
public:
	int GetNetId();
	int GetTeam();
	Vector3 GetPosition();
	bool IsEnemy();
	bool IsAlive();
	bool IsVisible();
	float GetScale();
	std::string GetName();
	int GetRecallState();
	QWORD GetCharacterData();
	Spell* GetSpellById(int id);
};

class HeroManager
{
public:
	int GetListSize();
	Object* GetIndex(int index);
};