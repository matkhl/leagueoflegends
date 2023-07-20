#include "../stdafx.h"

namespace scripts
{
	std::vector<std::pair<std::string, std::vector<std::string>>> settingsOrder = {};

	void AddSetting(std::string group, std::string key, settings::SettingValue value, settings::SettingValue min, settings::SettingValue max)
	{
		std::pair<std::string, std::vector<std::string>>* groupData = nullptr;
		for (auto& pair : settingsOrder)
			if (pair.first == group)
				groupData = &pair;

		if (groupData) {
			groupData->second.push_back(key);
		} else {
			settingsOrder.push_back({ group, {key} });
		}

		settings::Get(group, key, value);

		if (std::holds_alternative<int>(value))
			settings::AddBounds(group, key, std::get<int>(min), std::get<int>(max));
		if (std::holds_alternative<float>(value))
			settings::AddBounds(group, key, std::get<float>(min), std::get<float>(max));
	}

	void Init()
	{
		srand(static_cast <unsigned> (time(0)));

		cooldowns::Init();
		recalls::Init();
		orbwalker::Init();
		targetselector::Init();
		debug::Init();
		champions::Init();
	}

	void Update()
	{
		champions::Update();
		if (SETTINGS_BOOL("orbwalker", "enabled")) orbwalker::Update();
		if (SETTINGS_BOOL("recalls", "enabled")) recalls::Update();
	}

	namespace orbwalker
	{
		float lastActionTime = 0.0f;
		float lastAttackTime = 0.0f;
		QWORD lastSpellCastAddress = 0;

		float gameTime = 0.0f;

		float nextRngBuffer = 0.0f;

		namespace actions
		{
			bool CanDoAction()
			{
				if (!lastActionTime) lastActionTime = gameTime;
				if (gameTime < lastActionTime + SETTINGS_FLOAT("orbwalker", "clickdelay") + nextRngBuffer) return false;
				lastActionTime = gameTime;
				return true;
			}

			void Idle()
			{
				if (!(CanDoAction() && globals::localPlayer->CanMove())) return;
				functions::MoveToMousePos();
				RefreshBuffer();
			}

			void AttackObject(Object* obj)
			{
				if (!CanDoAction()) return;
				functions::AttackObject(obj);
				RefreshBuffer();
			}
		}

		namespace states
		{
			void Attack()
			{
				if (globals::localPlayer->CanAttack()) {
					if (auto obj = targetselector::GetEnemyChampionInRange(globals::localPlayer->GetRealAttackRange()))
					{
						actions::AttackObject(obj);
						return;
					}
				}
				actions::Idle();
			}
		}

		bool StopOrbwalk()
		{
			return (
				!functions::CanSendInput() || 
				gameTime < lastAttackTime + globals::localPlayer->GetAttackWindup() + SETTINGS_FLOAT("orbwalker", "windupbuffer")
			);
		}

		bool IsReloading()
		{
			return gameTime < lastAttackTime + globals::localPlayer->GetAttackDelay() - SETTINGS_FLOAT("orbwalker", "attack before can attack");
		}

		void RefreshBuffer()
		{
			if (!SETTINGS_BOOL("orbwalker", "random click delay"))
			{
				nextRngBuffer = 0.0f;
				return;
			}
			nextRngBuffer = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.01f);
		}

		void CheckActiveAttack()
		{
			auto spellCast = globals::localPlayer->GetActiveSpellCast();
			if (spellCast)
			{
				if ((spellCast->IsAutoAttack() ||
					functions::IsAttackWindupSpell(spellCast->GetSpellId())) &&
					(QWORD)spellCast != lastSpellCastAddress)
				{
					lastAttackTime = gameTime;
				}
			}
			lastSpellCastAddress = (QWORD)spellCast;
		}

		void Init()
		{
			ADD_SETTING("orbwalker", "enabled", true);
			ADD_SETTING_RANGE("orbwalker", "clickdelay", 0.05f, 0.03f, 1.0f);
			ADD_SETTING("orbwalker", "random click delay", true);
			ADD_SETTING_RANGE("orbwalker", "windupbuffer", 0.03f, 0.01f, 0.2f);
			ADD_SETTING_RANGE("orbwalker", "attack before can attack", 0.01f, 0.0f, 0.2f);
		}

		void Update()
		{
			gameTime = functions::GetGameTime();
			CheckActiveAttack();

			if (StopOrbwalk()) return;

			if (globals::scripts::orbwalker::orbwalkState && IsReloading())
			{
				actions::Idle();
				return;
			}

			switch (globals::scripts::orbwalker::orbwalkState)
			{
			case OrbwalkState::Attack:
				states::Attack();
				break;
			}
		}
	}

	namespace cooldowns
	{
		void Init()
		{
			ADD_SETTING("cooldowns", "enabled", true);
		}
	}

	namespace recalls
	{
		using namespace globals::scripts::recalls;

		void RemoveRecall(int index)
		{
			recallList.erase(recallList.begin() + index);
		}

		int GetRecallListIndex(Object* obj)
		{
			for (int i = 0; i < recallList.size(); i++)
			{
				if (recallList[i].name == obj->GetName()) return i;
			}
			return 999;
		}

		void Init()
		{
			ADD_SETTING("recalls", "enabled", true);
		}

		void Update()
		{
			float gameTime = functions::GetGameTime();

			for (int i = 0; i < recallList.size(); i++)
			{
				RecallInfo recallInfo = recallList[i];
				switch (recallInfo.state)
				{
				case RecallState::Recalling:
					if (gameTime > recallInfo.startTime + 8.0f - timeBuffer)
					{
						recallList[i].state = RecallState::RecallingFinished;
					}
					break;
				case RecallState::Teleporting:
					if (gameTime > recallInfo.startTime + 4.0f - timeBuffer) recallList[i].state = RecallState::TeleportingFinished;
					break;
				case RecallState::RecallingFinished:
					if (gameTime > recallInfo.startTime + 11.0f) RemoveRecall(i);
					break;
				case RecallState::TeleportingFinished:
					if (gameTime > recallInfo.startTime + 7.0f) RemoveRecall(i);
					break;
				}
			}

			for (int i = 0; i < globals::heroManager->GetListSize(); i++)
			{
				Object* obj = globals::heroManager->GetIndex(i);
				if (!IsValidPtr(obj)) continue;
				if (!obj->IsEnemy()) continue;
				int state = obj->GetRecallState();
				int recallIndex = GetRecallListIndex(obj);
				bool isInList = recallIndex != 999;
				if (!isInList && (state == 6 || state == 8))
				{
					recallList.push_back(RecallInfo((state == 6) ? RecallState::Recalling : RecallState::Teleporting, obj->GetName(), gameTime));
					continue;
				}
				if (isInList && (state != 6 && state != 8) &&
					(recallList[recallIndex].state != RecallState::RecallingFinished && recallList[recallIndex].state != RecallState::TeleportingFinished))
				{
					RemoveRecall(recallIndex);
					continue;
				}
			}
		}
	}

	namespace debug
	{
		void Init()
		{
			ADD_SETTING("debug", "draw object data", false);
			ADD_SETTING("debug", "draw bounding radius", false);
			ADD_SETTING("debug", "draw cursor world", false);
			ADD_SETTING("debug", "draw player paths", false);
		}
	}

	namespace champions
	{
		static ChampionModule* activeChampModule = nullptr;

		void Init()
		{
			activeChampModule = ChampionModuleManager::GetModule(globals::localPlayer->GetName());
			if (!activeChampModule) return;

			activeChampModule->Init();
		}

		void Update()
		{
			if (!activeChampModule) return;

			activeChampModule->Update();

			switch (globals::scripts::orbwalker::orbwalkState)
			{
			case OrbwalkState::Attack:
				activeChampModule->Attack();
				break;
			}
		}
	}
}