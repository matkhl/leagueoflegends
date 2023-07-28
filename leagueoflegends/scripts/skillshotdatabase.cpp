#include "../stdafx.h"

void Skillshot::SetSlotIndex(int slotId)
{
	this->slotIndex = slotId;
}

float Skillshot::GetRange()
{
	return this->range;
}

float Skillshot::GetRadius()
{
	return this->radius;
}

float Skillshot::GetSpeed()
{
	return this->speed;
}

float Skillshot::GetCastTime()
{
	return this->castTime;
}

int Skillshot::GetType()
{
	return this->type;
}

bool Skillshot::IsCollidableWith(int type)
{
	return std::find(this->collidableWith.begin(), this->collidableWith.end(), type) != this->collidableWith.end();
}

float Skillshot::GetMaxRange()
{
	return (this->type == SkillshotType::SkillshotCircle) ? this->range + (this->radius - min(this->radius, 70.0f)) : this->range;
}

std::string Skillshot::GetName()
{
	return globals::localPlayer->GetSpellBySlotId(this->slotIndex)->GetName();
}

bool Skillshot::IsCastable()
{
	return globals::localPlayer->CanCastSpell(this->slotIndex);
}

int Skillshot::GetStacks()
{
	return globals::localPlayer->GetSpellBySlotId(this->slotIndex)->GetStacks();
}