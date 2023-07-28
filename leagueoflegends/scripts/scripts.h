#pragma once

#include "../stdafx.h"

#define ADD_SETTING(group, key, value) AddSetting(SP_STRING(group), SP_STRING(key), value)
#define ADD_SETTING_RANGE(group, key, value, min, max) AddSetting(SP_STRING(group), SP_STRING(key), value, min, max)

namespace scripts
{
	extern float gameTime;

	extern std::vector<std::pair<std::string, std::vector<std::string>>> settingsOrder;

	void AddSetting(std::string group, std::string key, settings::SettingValue value, settings::SettingValue min = 0, settings::SettingValue max = 1);
	void RefreshBuffer();
	void Init();
	void Update();

	namespace targetselector
	{
		bool ChooseSelectedObject(Object* selectedObject, Object* checkObj);

		Object* GetEnemyChampionInRange(float range);
		Object* GetEnemyChampionInRange(float range, Skillshot skillshot);
		Object* GetEnemyChampionInRange(float range, int damageType, Skillshot skillshot);
		Object* GetObjectInRange(float range, std::string name = "", std::vector<QWORD> includefilterTypeHashes = {}, std::vector<QWORD> excludeFilterTypeHashesDetailed = {}, bool isSpecial = false);

		void Init();
	}

	namespace prediction
	{
		struct PredictionOutput
		{
			Vector3 position;
			float hitChance = 100.0f;
		};

		bool CheckCollision(Vector3 sourcePos, Vector3 targetPos, Object* sourceObject, Object* targetObject, Skillshot& skillshot);
		bool IsSpecificObjectInWay(Vector3 sourcePos, Vector3 targetPos, Object* collisionObject, float projectileRadius);
		bool IsAnyObjectInWay(Vector3 sourcePos, Vector3 targetPos, Object* sourceObject, Object* targetObject, float projectileRadius);

		Vector3 GetObjectPositionAfterTime(Object* obj, float time, float distanceBuffer = 0.0f);

		bool GetPrediction(Skillshot &spell, PredictionOutput& out);
		bool GetPrediction(Object* sourceObj, Object* targetObj, Skillshot &spell, PredictionOutput &out);
	}

	namespace actions
	{
		extern float lastActionTime;

		bool CanDoAction();
		void Idle();
		void AttackObject(Object* obj);
		void CastSpell(int spellId, Object* target);
		void CastSpell(int spellId, Vector3 pos);
	}

	namespace orbwalker
	{

		extern float lastAttackTime;

		namespace states
		{
			void Attack();
		}

		bool StopOrbwalk();
		bool IsReloading();
		void CheckActiveAttack();
		void Init();
		void Update();
	}

	namespace cooldowns
	{
		void Init();
	}

	namespace recalls
	{
		void RemoveRecall(int index);
		int GetRecallListIndex(Object* obj);
		void Init();
		void Update();
	}

	namespace skinchanger
	{
		void Init();
		void Update();
	}

	namespace debug
	{
		void Init();
	}

	namespace champions
	{
		void Init();
		void Update();
		void RenderUpdate();
	}
}
