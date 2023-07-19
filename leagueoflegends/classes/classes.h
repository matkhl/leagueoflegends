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

class SpellCast
{
public:
    SpellInfo* GetSpellInfo();
    int GetSpellId();
public:
    bool IsAutoAttack();
};

class Object
{
public:
	unsigned int GetNetId();
	int GetTeam();
    Vector3 GetPosition();
    bool IsVisible();
	bool IsAlive();
    bool IsTargetable();
    int GetRecallState();
    float GetHealth();
	float GetScale();
	float GetArmor();
	float GetMagicResist();
    float GetAttackRange();
	std::string GetName();
    SpellCast* GetActiveSpellCast();
	Spell* GetSpellById(int id);
    QWORD GetCharacterData();
public:
    float GetBoundingRadius();
    float GetAttackDelay();
    float GetAttackWindup();
public:
    unsigned short GetActionState();
    bool CanAttack();
    bool CanCast();
    bool CanMove();
    bool IsEnemy();
    bool IsValidTarget();
    float GetRealAttackRange();
    bool IsInRange(Vector3 pos, float radius);
};

class ObjectManager
{
public:
    int GetListSize();
    Object* GetIndex(int index);
public:
    class iterator
    {
    private:
        ObjectManager* objectManager;
        int index;

    public:
        iterator(ObjectManager* _objectManager, int _index)
            : objectManager(_objectManager), index(_index) {}

        iterator& operator++()
        {
            index++;
            return *this;
        }

        bool operator!=(const iterator& other) const
        {
            return index != other.index;
        }

        Object* operator*()
        {
            return objectManager->GetIndex(index);
        }
    };

    iterator begin()
    {
        return iterator(this, 0);
    }

    iterator end()
    {
        return iterator(this, GetListSize());
    }
};