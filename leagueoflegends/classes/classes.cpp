#include "../stdafx.h"

float CharacterData::GetSize()
{
	return *(float*)((QWORD)this + oObjCharDataDataSize);
}

QWORD CharacterData::GetObjectTypeHash()
{
	return *(QWORD*)(*(QWORD*)((QWORD)this + oObjCharDataDataObjType));
}

std::string SpellData::GetName()
{
	return *(char**)((QWORD)this + oSpellDataSpellName);
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

float Spell::GetTotalCooldown()
{
	return *(float*)((QWORD)this + oSpellSlotTotalCooldown);
}

float Spell::GetRelativeCooldown()
{
	if (!this->GetLevel()) return 1.0f;
	if (this->GetLevel() && this->GetCooldownTimer() < 1.0f) return 0.0f;
	return min(this->GetCooldown() / this->GetTotalCooldown(), 1.0f);
}

SpellInput* Spell::GetSpellInput()
{
	return *(SpellInput**)((QWORD)this + oSpellSlotSpellInput);
}

SpellInfo* Spell::GetSpellInfo()
{
	return *(SpellInfo**)((QWORD)this + oSpellSlotSpellInfo);
}

std::string Spell::GetName()
{
	return this->GetSpellInfo()->GetSpellData()->GetName();
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

float Object::GetScale()
{
	return *(float*)((QWORD)this + oObjScale);
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

SpellCast* Object::GetActiveSpellCast()
{
	QWORD* activeSpellCastOffset = (QWORD*)((QWORD)this + oObjActiveSpellCast);
	if (!IsValidPtr(activeSpellCastOffset)) return 0;
	return *(SpellCast**)(activeSpellCastOffset);
}

CharacterData* Object::GetCharacterData()
{
	return (CharacterData*)(*(QWORD*)(*(QWORD*)((QWORD)this + oObjCharData) + oObjCharDataData));
}

AiManager* Object::GetAiManager()
{
	LeagueObfuscation<QWORD> aiManagerObf = *(LeagueObfuscation<QWORD>*)((QWORD)this + oObjAiManager);
	return (AiManager*)Decrypt(aiManagerObf);
}

Spell* Object::GetSpellById(int id)
{
	return *(Spell**)((QWORD)this + oObjSpellBook + oObjSpellBookSpellSlot + id * 0x8);
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

unsigned short Object::GetActionState()
{
	return *(unsigned short*)((QWORD)this + oObjActionState);
}

bool Object::CanAttack()
{
	return this->GetActionState() & object::CanAttack;
}

bool Object::CanCast()
{
	return this->GetActionState() & object::CanCast;
}

bool Object::CanMove()
{
	return this->GetActionState() & object::CanMove;
}

bool Object::IsEnemy()
{
	return this->GetTeam() != globals::localPlayer->GetTeam();
}

bool Object::IsValidTarget()
{
	return this->IsVisible() && this->IsAlive() && this->IsEnemy() && this->IsTargetable();
}

float Object::GetRealAttackRange()
{
	return this->GetAttackRange() + this->GetBoundingRadius();
}

bool Object::IsInRange(Vector3 pos, float radius)
{
	return radius + this->GetBoundingRadius() >= render::Distance(pos, this->GetPosition());
}

int ObjectManager::GetListSize()
{
	return *(int*)((QWORD)this + oManagerListSize);
}

Object* ObjectManager::GetIndex(int index)
{
	index = min(index, this->GetListSize());
	return *(Object**)(*(QWORD*)((QWORD)this + oManagerList) + 0x8 * index);
}