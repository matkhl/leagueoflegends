#pragma once

#include "../stdafx.h"

namespace scripts
{
	extern std::vector<std::pair<std::string, std::vector<std::string>>> settingsOrder;

	void AddSetting(std::string group, std::string key, settings::SettingValue value, settings::SettingValue min = 0, settings::SettingValue max = 1);
	void Init();
	void Update();

	namespace targetselector
	{
		bool ShouldChooseSelectedObject(Object* selectedObject, Object* checkObj);

		Object* GetEnemyChampionInRange(float range);

		void Init();
	}

	namespace orbwalker
	{
		namespace actions
		{
			bool CanDoAction();
			void Idle();
			void AttackObject(Object* obj);
		}

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

	namespace debug
	{
		void Init();
	}
}
