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

enum OrbwalkState
{
    OFF,
    ATTACK,
    CLEAR,
    HARASS
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

namespace spellstate
{
    enum SpellState
    {
        Ready = 0,
        DoesNotExist = 2,
        NotAvailable = 4,
        Supressed = 8,
        NotLearned = 12,
        Frozen = 16,
        Processing = 24,
        Stasis = 28,
        Cooldown = 32,
        InZhonyas = 48,
        NoMana = 64
    };
}

namespace characterstate
{
    enum CharacterState
    {
        CanAttack = 1,
        CanCast = 2,
        CanMove = 4,
        Immovable = 8,
        Unknownz = 16,
        IsStealth = 32,
        Taunted = 64,
        Feared = 128,
        Fleeing = 256,
        Supressed = 512,
        Asleep = 1024,
        NearSight = 2048,
        Ghosted = 4096,
        HasGhost = 8192,
        Charmed = 16384,
        NoRender = 32768,
        DodgePiercing = 131072,
        DisableAmbientGold = 262144,
        DisableAmbientXP = 524288,
        ForceRenderParticles = 65536,
        IsCombatEnchanced = 1048576,
        IsSelectable = 16777216
    };
}

enum CollisionFlags
{
    None = 0,
    Grass = 1,
    Wall = 2,
    Building = 64,
    Tower = 70,
    Prop = 128,
    GlobalVision = 256
};