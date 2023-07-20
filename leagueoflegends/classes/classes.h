#pragma once

#include "../stdafx.h"

class AiManager
{
public:
    Vector3 GetTargetPosition();
    bool IsMoving();
    int GetCurrentSegment();
    Vector3 GetPathStart();
    Vector3 GetPathEnd();
    int GetSegmentsCount();
    float GetDashSpeed();
    bool IsDashing();
    Vector3 GetPosition();
public:
    Vector3 GetSegment(int index);
    std::vector<Vector3> GetFutureSegments();
};

class CharacterData
{
public:
    float GetSize();
    QWORD GetObjectTypeHash();
};

class SpellData
{
public:
	std::string GetName();
    float GetManaCostByLevel(int level);
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
    bool IsReady();
	std::string GetName();
    float GetManaCost();
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
    float GetMana();
    bool IsTargetable();
    int GetRecallState();
    float GetHealth();
    unsigned short GetActionState();
    float GetBonusAttackDamage();
    float GetAbilityPower();
    float GetBaseAttackDamage();
	float GetScale();
    float GetMovementSpeed();
	float GetArmor();
	float GetMagicResist();
    float GetAttackRange();
	std::string GetName();
    SpellCast* GetActiveSpellCast();
	Spell* GetSpellBySlotId(int slotId);
    CharacterData* GetCharacterData();
    AiManager* GetAiManager();
public:
    float GetBoundingRadius();
    float GetAttackDelay();
    float GetAttackWindup();
public:
    bool CanAttack();
    bool CanCast();
    bool CanMove();
    bool IsEnemy();
    bool IsValidTarget();
    bool IsHero();
    float GetAttackDamage();
    float GetEffectiveHealth(int damageType);
    float GetRealAttackRange();
    bool IsInRange(Vector3 pos, float radius);
    bool CanCastSpell(int slotId);
    Vector3 GetServerPosition();
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