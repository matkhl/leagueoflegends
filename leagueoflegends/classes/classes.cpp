#include "../stdafx.h"

void CharacterDataStack::Update(bool change)
{
	typedef void(__thiscall* fnUpdate)(QWORD, bool);
	fnUpdate _update = (fnUpdate)(globals::moduleBase + oCharacterDataStackUpdate);
	spoof_call(functions::spoof_trampoline, _update, (QWORD)this, change);
}

Vector3 AiManager::GetTargetPosition()
{
	return functions::ReadVector3((QWORD)this + oObjAiManagerManagerTargetPosition);
}

bool AiManager::IsMoving()
{
	return *(bool*)((QWORD)this + oObjAiManagerManagerIsMoving);
}

int AiManager::GetCurrentSegment()
{
	return *(int*)((QWORD)this + oObjAiManagerManagerCurrentSegment);
}

Vector3 AiManager::GetPathStart()
{
	return functions::ReadVector3((QWORD)this + oObjAiManagerManagerPathStart);
}

Vector3 AiManager::GetPathEnd()
{
	return functions::ReadVector3((QWORD)this + oObjAiManagerManagerPathEnd);
}

int AiManager::GetSegmentsCount()
{
	return *(int*)((QWORD)this + oObjAiManagerManagerSegmentsCount);
}

float AiManager::GetDashSpeed()
{
	return *(float*)((QWORD)this + oObjAiManagerManagerDashSpeed);
}

bool AiManager::IsDashing()
{
	return *(bool*)((QWORD)this + oObjAiManagerManagerIsDashing);
}

Vector3 AiManager::GetPosition()
{
	return functions::ReadVector3((QWORD)this + oObjAiManagerManagerPosition);
}

Vector3 AiManager::GetSegment(int index)
{
	return functions::ReadVector3(*(QWORD*)((QWORD)this + oObjAiManagerManagerSegments) + (min(index, this->GetSegmentsCount() - 1) * sizeof(Vector3)));
}

std::vector<Vector3> AiManager::GetFutureSegments()
{
	std::vector<Vector3> segments = {};
	int segmentsCount = this->GetSegmentsCount();
	for (int i = this->GetCurrentSegment(); i < segmentsCount; i++)
	{
		segments.push_back(this->GetSegment(i));
	}
	return segments;
}

float CharacterData::GetSize()
{
	return *(float*)((QWORD)this + oObjCharDataDataSize);
}

QWORD CharacterData::GetObjectTypeHash()
{
	return *(QWORD*)(*(QWORD*)((QWORD)this + oObjCharDataDataObjType));
}

QWORD CharacterData::GetObjectTypeHashDetailed()
{
	return *(QWORD*)(*(QWORD*)((QWORD)this + oObjCharDataDataObjType) + oObjCharDataDataObjTypeDetailed);
}

std::string SpellData::GetName()
{
	return *(char**)((QWORD)this + oSpellDataSpellName);
}

float SpellData::GetManaCostByLevel(int level)
{
	return *(float*)((QWORD)this + oSpellDataManaCost + ((level - 1) * sizeof(float)));
}

SpellData* SpellInfo::GetSpellData()
{
	return *(SpellData**)((QWORD)this + oSpellInfoSpellData);
}

int Spell::GetLevel()
{
	return *(int*)((QWORD)this + oSpellSlotLevel);
}

float Spell::GetCooldownTimer()
{
	return *(float*)((QWORD)this + oSpellSlotCooldown);
}

float Spell::GetCooldown()
{
	float cooldownTimer = this->GetCooldownTimer();
	if (cooldownTimer == 0.0f) return cooldownTimer;
	return max(cooldownTimer - functions::GetGameTime(), 0.0f);
}

int Spell::GetStacks()
{
	return *(int*)((QWORD)this + oSpellSlotStacks);
}

float Spell::GetTotalCooldown()
{
	return *(float*)((QWORD)this + oSpellSlotTotalCooldown);
}

float Spell::GetRelativeCooldown()
{
	if (!this->GetLevel()) return 1.0f;
	if (this->GetLevel() && this->GetCooldownTimer() < 1.0f) return 0.0f;
	return this->GetTotalCooldown() ? min(this->GetCooldown() / this->GetTotalCooldown(), 1.0f) : 0.0f;
}

SpellInput* Spell::GetSpellInput()
{
	return *(SpellInput**)((QWORD)this + oSpellSlotSpellInput);
}

SpellInfo* Spell::GetSpellInfo()
{
	return *(SpellInfo**)((QWORD)this + oSpellSlotSpellInfo);
}

bool Spell::IsReady()
{
	return this->GetRelativeCooldown() == 0.0f;
};

std::string Spell::GetName()
{
	return this->GetSpellInfo()->GetSpellData()->GetName();
}

float Spell::GetManaCost()
{
	return this->GetSpellInfo()->GetSpellData()->GetManaCostByLevel(this->GetLevel());
}

SpellInfo* SpellCast::GetSpellInfo()
{
	return *(SpellInfo**)((QWORD)this + oActiveSpellCastSpellInfo);
}

int SpellCast::GetSpellId()
{
	return *(int*)((QWORD)this + oActiveSpellCastSpellId);
}

bool SpellCast::IsAutoAttack()
{
	return *(int*)((QWORD)this + oActiveSpellCastSpellType) == -1;
}

std::string Buff::GetName()
{
	QWORD* namePtr = (QWORD*)(*(QWORD*)((QWORD)this + oBuffNamePtr));
	if (!IsValidPtr(namePtr)) return "";
	return (char*)((QWORD)namePtr + oBuffNamePtrName);
}

float Buff::GetStartTime()
{
	return *(float*)((QWORD)this + oBuffStartTime);
}

float Buff::GetEndTime()
{
	return *(float*)((QWORD)this + oBuffEndTime);
}

int Buff::GetStacksAlt()
{
	return *(int*)((QWORD)this + oBuffStacksAlt);
}

int Buff::GetStacks()
{
	return *(int*)((QWORD)this + oBuffStacks);
}

int Buff::GetMaxStacks()
{
	return max(this->GetStacksAlt(), this->GetStacks());
}

Buff* BuffEntry::GetBuff()
{
	Buff* buff = (Buff*)(*(QWORD*)((QWORD)this + oBuffEntryBuff));
	if (!IsValidPtr(buff)) return nullptr;
	return buff;
}

BuffEntry* BuffManager::GetBuffEntryByIndex(int index)
{
	BuffEntry* address = (BuffEntry*)(*(QWORD*)((QWORD)this + (sizeof(QWORD) * index)));
	if (!IsValidPtr(address)) return nullptr;
	return address;
}

unsigned int Object::GetNetId()
{
	return *(int*)((QWORD)this + oObjNetId);
}

int Object::GetTeam()
{
	return *(int*)((QWORD)this + oObjTeam);
}

Vector3 Object::GetPosition()
{
	return functions::ReadVector3((QWORD)this + oObjPosition);
}

bool Object::IsVisible()
{
	return *(bool*)((QWORD)this + oObjVisible);
}

bool Object::IsAlive()
{
	return !(*(int*)((QWORD)this + oObjAlive) % 2);
}

float Object::GetMana()
{
	return *(float*)((QWORD)this + oObjMana);
}

bool Object::IsTargetable()
{
	return *(bool*)((QWORD)this + oObjTargetable);
}

int Object::GetRecallState()
{
	return *(int*)((QWORD)this + oObjRecallState);
}

float Object::GetHealth()
{
	return *(float*)((QWORD)this + oObjHealth);
}

float Object::GetMaxHealth()
{
	return *(float*)((QWORD)this + oObjMaxHealth);
}

unsigned short Object::GetActionState()
{
	return *(unsigned short*)((QWORD)this + oObjActionState);
}

float Object::GetBaseAttackDamage()
{
	return *(float*)((QWORD)this + oObjBaseAttackDamage);
}

float Object::GetAbilityPower()
{
	return *(float*)((QWORD)this + oObjAbilityPower);
}

float Object::GetBonusAttackDamage()
{
	return *(float*)((QWORD)this + oObjBonusAttackDamage);
}

float Object::GetScale()
{
	return *(float*)((QWORD)this + oObjScale);
}

float Object::GetMovementSpeed()
{
	return *(float*)((QWORD)this + oObjMovementSpeed);
}

float Object::GetArmor()
{
	return *(float*)((QWORD)this + oObjArmor);
}

float Object::GetMagicResist()
{
	return *(float*)((QWORD)this + oObjMagicResist);
}

float Object::GetAttackRange()
{
	return *(float*)((QWORD)this + oObjAttackRange);
}

std::string Object::GetName()
{
	return *(char**)((QWORD)this + oObjName);
}

BuffManager* Object::GetBuffManager()
{
	return (BuffManager*)(*(QWORD*)((QWORD)this + oObjBuffManager));
}

QWORD* Object::GetBuffManagerEntriesEnd()
{
	return *(QWORD**)((QWORD)this + oObjBuffManager + oObjBuffManagerEntriesEnd);
}

SpellCast* Object::GetActiveSpellCast()
{
	QWORD* activeSpellCastOffset = *(QWORD**)((QWORD)this + oObjActiveSpellCast);
	if (!IsValidPtr(activeSpellCastOffset)) return nullptr;
	return (SpellCast*)activeSpellCastOffset;
}

CharacterData* Object::GetCharacterData()
{
	return (CharacterData*)(*(QWORD*)(*(QWORD*)((QWORD)this + oObjCharData) + oObjCharDataData));
}

AiManager* Object::GetAiManager()
{
	LeagueObfuscation<QWORD> aiManagerObf = *(LeagueObfuscation<QWORD>*)((QWORD)this + oObjAiManager);
	return (AiManager*)(*(QWORD*)(Decrypt(aiManagerObf) + 0x10));
}

Spell* Object::GetSpellBySlotId(int slotId)
{
	return *(Spell**)((QWORD)this + oObjSpellBook + oObjSpellBookSpellSlot + (sizeof(QWORD) * slotId));
}

float Object::GetBoundingRadius()
{
	typedef float(__fastcall* fnGetBoundingRadius)(Object* obj);
	fnGetBoundingRadius _fnGetBoundingRadius = (fnGetBoundingRadius)(globals::moduleBase + oGetBoundingRadius);
	return _fnGetBoundingRadius(this);
}

float Object::GetAttackDelay()
{
	typedef float(__cdecl* fnGetAttackDelay)(Object* obj);
	fnGetAttackDelay _fnGetAttackDelay = (fnGetAttackDelay)(globals::moduleBase + oGetAttackDelay);
	return _fnGetAttackDelay(this);
}

float Object::GetAttackWindup()
{
	typedef float(__cdecl* fnGetAttackWindup)(Object* obj, int flags);
	fnGetAttackWindup _fnGetAttackWindup = (fnGetAttackWindup)(globals::moduleBase + oGetAttackWindup);
	return _fnGetAttackWindup(this, 0x40);
}

bool Object::CanAttack()
{
	return this->GetActionState() & CharacterState::CanAttack;
}

bool Object::CanCast()
{
	return this->GetActionState() & CharacterState::CanCast;
}

bool Object::CanMove()
{
	return this->GetActionState() & CharacterState::CanMove;
}

bool Object::IsEnemy()
{
	return this->GetTeam() != globals::localPlayer->GetTeam();
}

bool Object::IsValidTarget()
{
	return this->IsVisible() && this->IsAlive() && this->IsEnemy() && this->IsTargetable();
}

bool Object::IsHero()
{
	return this->GetCharacterData()->GetObjectTypeHash() == ObjectType::Champion;
}

float Object::GetAttackDamage()
{
	return this->GetBaseAttackDamage() + this->GetBonusAttackDamage();
}

float Object::GetEffectiveHealth(int damageType)
{
	if (damageType == DamageType::True) return this->GetHealth();
	return this->GetHealth() * (1 + (damageType == DamageType::Physical ? this->GetArmor() : this->GetAbilityPower()) / 100);
}

float Object::GetRealAttackRange()
{
	return this->GetAttackRange() + this->GetBoundingRadius();
}

float Object::GetDistanceTo(Object* obj)
{
	return this->GetPosition().Distance(obj->GetPosition());
}

bool Object::IsInRange(Vector3 pos, float radius)
{
	return radius + this->GetBoundingRadius() >= render::Distance(pos, this->GetPosition());
}

bool Object::CanCastSpell(int slotId)
{
	auto spell = this->GetSpellBySlotId(slotId);
	return this->CanCast() && spell->IsReady() && spell->GetManaCost() <= this->GetMana();
}

Vector3 Object::GetServerPosition()
{
	if (this->IsHero())
	{
		auto pos = this->GetAiManager()->GetPosition();
		if (pos.IsValid()) return pos;
	}

	return this->GetPosition();
}

int Object::GetBuffListSize()
{
	return (int)((QWORD)this->GetBuffManagerEntriesEnd() - (QWORD)this->GetBuffManager()) / (int)sizeof(QWORD);
}

Buff* Object::GetBuffByName(std::string name)
{
	for (int i = 0; i < this->GetBuffListSize(); i++)
	{
		auto buffEntry = this->GetBuffManager()->GetBuffEntryByIndex(i);
		if (!buffEntry) return nullptr;
		auto buff = buffEntry->GetBuff();
		if (buff && buff->GetEndTime() >= functions::GetGameTime() && buff->GetName() == name) return buff;
	}
	return nullptr;
}

CharacterDataStack* Object::GetCharacterDataStack()
{
	return (CharacterDataStack*)((QWORD)this + oObjCharacterDataStack);
}

void Object::ChangeSkin(int skinId)
{
	const auto stack{ this->GetCharacterDataStack() };
	stack->base_skin.skin = skinId;

	stack->Update(true);
}

int ObjectManager::GetListSize()
{
	return *(int*)((QWORD)this + oManagerListSize);
}

Object* ObjectManager::GetIndex(int index)
{
	index = min(index, this->GetListSize());
	return *(Object**)(*(QWORD*)((QWORD)this + oManagerList) + (sizeof(QWORD) * index));
}