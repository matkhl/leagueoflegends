#include "../stdafx.h"

int Spell::GetLevel()
{
	return *(int*)((QWORD)this + oSpellLevel);
}

float Spell::GetCooldownTimer()
{
	return *(float*)((QWORD)this + oSpellCooldown);
}

float Spell::GetCooldown()
{
	float cooldownTimer = this->GetCooldownTimer();
	if (cooldownTimer == 0.0f) return cooldownTimer;
	return max(cooldownTimer - functions::GetGameTime(), 0.0f);
}

float Spell::GetTotalCooldown()
{
	return *(float*)((QWORD)this + oSpellTotalCooldown);
}

float Spell::GetRelativeCooldown()
{
	if (!this->GetLevel()) return 1.0f;
	if (this->GetLevel() && this->GetCooldownTimer() < 1.0f) return 0.0f;
	return min(this->GetCooldown() / this->GetTotalCooldown(), 1.0f);
}

int Object::GetTeam()
{
	return *(int*)((QWORD)this + oObjTeam);
}

Vector3 Object::GetPosition()
{
	return functions::ReadVector3((QWORD)this + oObjPosition);
}

std::string Object::GetName()
{
	return std::string((char*)((QWORD)this + oObjName));
}

bool Object::IsEnemy()
{
	return this->GetTeam() != globals::localPlayer->GetTeam();
}

bool Object::IsAlive()
{
	return !(*(int*)((QWORD)this + oObjAlive) % 2);
}

bool Object::IsVisible()
{
	return *(bool*)((QWORD)this + oObjVisible);
}

int Object::GetRecallState()
{
	return *(int*)((QWORD)this + oObjRecallState);
}

Spell* Object::GetSpellById(int id)
{
	return *(Spell**)((QWORD)this + oObjSpells + id * 0x8);
}

int HeroManager::GetListSize()
{
	return *(int*)((QWORD)this + oManagerListSize);
}

Object* HeroManager::GetIndex(int index)
{
	index = min(index, this->GetListSize());
	return *(Object**)(*(QWORD*)((QWORD)this + oManagerList) + 0x8 * index);
}