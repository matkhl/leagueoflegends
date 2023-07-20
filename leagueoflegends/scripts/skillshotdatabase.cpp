#include "../stdafx.h"

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
	return this->castTime;
}

float Skillshot::GetCastTime()
{
	return this->castTime;
}

int Skillshot::GetType()
{
	return this->type;
}

float Skillshot::IsCollidableWith(int type)
{
	return std::find(this->collidableWith.begin(), this->collidableWith.end(), type) != this->collidableWith.end();
}

float Skillshot::GetMaxRange()
{
	return (this->type == SkillshotType::SkillshotCircle) ? this->range + this->radius : this->range;
}