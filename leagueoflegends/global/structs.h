#pragma once

#include "../stdafx.h"

struct Vector3
{
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    bool IsValid() const
    {
        return !(this->x == 0.0f && this->y == 0.0f && this->z == 0.0f) && (this->x > (-1000000)) && (this->y > (-1000000)) && (this->z > (-1000000)) && (this->x < (1000000)) && (this->y < (1000000)) && (this->z < (1000000));
    }

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

    bool operator==(const Vector3& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

    Vector3 Extend(const Vector3& to, float distance) const
    {
        const auto from = *this;
        const auto result = from + (to - from).Normalized() * distance;
        return result;
    }

    float Distance(const Vector3& to) const
    {
        return sqrtf(powf(to.x - x, 2) + powf(to.z - z, 2) + powf(to.y - y, 2));
    }

    float Length() const
    {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    float DotProduct(const Vector3& other) const
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3 Normalized() const
    {
        auto const length = this->Length();
        if (length != 0)
        {
            auto const inv = 1.0f / length;
            return { this->x * inv, this->y * inv, this->z * inv };
        }

        return *this;
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

    bool operator==(const Vector2& rhs) const
    {
        return x == rhs.x && y == rhs.y;
	}

    ImVec2 ToImVec() const
    {
        return ImVec2(x, y);
    }
};

enum OrbwalkState
{
    Off,
    Attack,
    Clear,
    Harass
};

enum RecallState
{
    Recalling,
    Teleporting,
    RecallingFinished,
    TeleportingFinished,
};

struct RecallInfo
{
    int state;
    std::string name;
    float startTime;
    RecallInfo() { state = RecallState::Recalling; name = ""; startTime = 0.0f; }
    RecallInfo(int _state, std::string _name, float _startTime) { state = _state; name = _name; startTime = _startTime; }
};

enum DamageType
{
	Physical,
	Magical,
	True
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

enum SpellState
{
    Ready = 0,
    DoesNotExist = 2,
    NotAvailable = 4,
    NotLearned = 12,
    Processing = 24,
    Cooldown = 32,
    NoMana = 64
};

enum CharacterState : unsigned short
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
    NoRender = 32768
};

enum ObjectType : unsigned long long
{
    Champion = 7957694998179309635,
    Special = 2336349411965497427,
    Ward = 5989923982968774999,
    Minion_Lane = 8944270284747073869,
    Minion_Lane_Siege = 7306920423476651374,
    Minion_Lane_Ranged = 7306930284704785774,
    Minion_Lane_Melee = 7306365152824092014,
    Minion_Lane_Super = 8243118342183806318,
    Monster = 2338042707385937741,
    Monster_Epic = 2340781521963538015,
    Monster_Dragon = 2336927746459059295,
    Special_Void = 2340781521963538015,
    Structure_Turret = 4294967297,
    UNKNOWN = 5980780305148018688,
    Less = 126939457912832
};

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

enum SkillshotType
{
    SkillshotNone,
    SkillshotLine,
    SkillshotCircle,
    SkillshotCone
};

enum CollidableObjects
{
    Objects,
    Walls
};