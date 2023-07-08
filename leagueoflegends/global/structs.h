#pragma once

#include "../stdafx.h"

struct Vector3
{
	float x, y, z;
	Vector3() { x = 0.0f; y = 0.0f; z = 0.0f; }
	Vector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};

struct Vector2
{
	float x, y;
	Vector2() { x = 0.0f; y = 0.0f; }
	Vector2(float _x, float _y) { x = _x; y = _y; }
	ImVec2 ToImVec() { return ImVec2(x, y); }
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