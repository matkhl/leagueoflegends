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

class SpellCast
{
public:
    float GetStartTime();
public:
    bool IsAutoAttack();
};

class Object
{
public:
	int GetNetId();
	int GetTeam();
	Vector3 GetPosition();
	bool IsAlive();
	bool IsVisible();
    int GetRecallState();
	float GetScale();
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
    bool IsEnemy();
    float GetRealAttackRange();
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