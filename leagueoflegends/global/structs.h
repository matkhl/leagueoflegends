#pragma once

#include "../stdafx.h"

struct Vector3
{
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3& rhs) const
    {
        return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector3 operator-(const Vector3& rhs) const
    {
        return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector3 operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
};

struct Vector2
{
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    Vector2 operator+(const Vector2& rhs) const
    {
        return Vector2(x + rhs.x, y + rhs.y);
    }

    Vector2 operator-(const Vector2& rhs) const
    {
        return Vector2(x - rhs.x, y - rhs.y);
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    ImVec2 ToImVec() const
    {
        return ImVec2(x, y);
    }
};


enum RecallState
{
	RECALLING,
	TELEPORTING,
	RECALLING_FINISHED,
	TELEPORTING_FINISHED
};

struct RecallInfo
{
	int state;
	std::string name;
	float startTime;
	RecallInfo() { state = RecallState::RECALLING; name = ""; startTime = 0.0f; }
	RecallInfo(int _state, std::string _name, float _startTime) { state = _state; name = _name; startTime = _startTime; }
};

enum SpellIndex
{
	Q,
	W,
	E,
	R,
	D,
	F,
	Item1,
	Item2,
	Item3,
	Item4,
	Item5,
	Item6,
	Trinket,
	Recall
};

enum OrbwalkState
{
	OFF,
	ATTACK,
	CLEAR,
	HARASS
};