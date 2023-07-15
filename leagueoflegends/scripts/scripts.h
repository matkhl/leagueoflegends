#pragma once

#include "../stdafx.h"

namespace scripts
{
	static std::vector<std::string> settingsOrder = {
		"orbwalker",
		"cooldowns",
		"recalls",
		"debug"
	};

	void Init();
	void Update();

	namespace targetselector
	{
		Object* GetEnemyChampionInRange(float range);
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
