#pragma once

#include "../stdafx.h"

class CharacterStackData
{
public:
    const char* model;
    char pad1[0x18];
    int skin;
    char pad2[0x60];
    char gear;
    char pad3[0x7];
};

class CharacterDataStack
{
public:
    std::vector<CharacterStackData> stack;
    CharacterStackData base_skin;

    void Update(bool change);
};

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
    QWORD GetObjectTypeHashDetailed();
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
    int GetStacks();
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

class Buff
{
public:
    std::string GetName();
    float GetStartTime();
    float GetEndTime();
    int GetStacksAlt();
    int GetStacks();
public:
    int GetMaxStacks();
};

class BuffEntry
{
public:
    Buff* GetBuff();
};

class BuffManager
{
public:
    BuffEntry* GetBuffEntryByIndex(int index);
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
    float GetMaxHealth();
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
    BuffManager* GetBuffManager();
    QWORD* GetBuffManagerEntriesEnd();
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
    float GetDistanceTo(Object* obj);
    bool IsInRange(Vector3 pos, float radius);
    bool CanCastSpell(int slotId);
    Vector3 GetServerPosition();
    int GetBuffListSize();
    Buff* GetBuffByName(std::string name);
public:
    CharacterDataStack* GetCharacterDataStack();
    void ChangeSkin(int skinId);
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