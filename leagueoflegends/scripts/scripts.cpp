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
		cooldowns::Init();
		recalls::Init();
		orbwalker::Init();
		debug::Init();
	}

	void Update()
	{
		if (settings::GetBool("orbwalker", "enabled")) orbwalker::Update();
		if (settings::GetBool("recalls", "enabled")) recalls::Update();
	}

	namespace orbwalker
	{
		float lastActionTime = 0.0f;
		float lastAttackTime = 0.0f;
		QWORD lastSpellCastAddress = 0;

		float gameTime = 0.0f;

		namespace actions
		{
			bool CanDoAction()
			{
				if (!lastActionTime) lastActionTime = gameTime;
				if (gameTime < lastActionTime + settings::GetFloat("orbwalker", "clickdelay")) return false;
				lastActionTime = gameTime;
				return true;
			}

			void Idle()
			{
				if (!CanDoAction()) return;
				functions::MoveToMousePos();
			}

			void AttackObject(Object* obj)
			{
				if (!CanDoAction()) return;
				functions::AttackObject(obj);
			}
		}

		namespace states
		{
			void Attack()
			{
				if (Object* obj = targetselector::GetEnemyChampionInRange(globals::localPlayer->GetRealAttackRange()))
				{
					actions::AttackObject(obj);
					return;
				}
				actions::Idle();
			}
		}

		bool StopOrbwalk()
		{
			return (
				!functions::CanSendInput() ||
				gameTime < lastAttackTime + globals::localPlayer->GetAttackWindup() + settings::GetFloat("orbwalker", "windupbuffer")
			);
		}

		bool IsReloading()
		{
			return gameTime < lastAttackTime + globals::localPlayer->GetAttackDelay() - settings::GetFloat("orbwalker", "attack before can attack");
		}

		void CheckActiveAttack()
		{
			auto spellCast = globals::localPlayer->GetActiveSpellCast();
			if (spellCast)
			{
				if ((spellCast->IsAutoAttack() ||
					functions::stringcheck::IsAttackWindupSpell(spellCast->GetSpellInfo()->GetSpellData()->GetName())) &&
					(QWORD)spellCast != lastSpellCastAddress)
				{
					lastAttackTime = gameTime;
				}
			}
			lastSpellCastAddress = (QWORD)spellCast;
		}

		void Init()
		{
			AddSetting("orbwalker", "enabled", true);
			AddSetting("orbwalker", "clickdelay", 0.05f, 0.03f, 1.0f);
			AddSetting("orbwalker", "windupbuffer", 0.03f, 0.01f, 0.2f);
			AddSetting("orbwalker", "attack before can attack", 0.01f, 0.0f, 0.2f);
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
			case OrbwalkState::ATTACK:
				states::Attack();
				break;
			}
		}
	}

	namespace cooldowns
	{
		void Init()
		{
			AddSetting("cooldowns", "enabled", true);
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
			AddSetting("recalls", "enabled", true);
		}

		void Update()
		{
			float gameTime = functions::GetGameTime();

			for (int i = 0; i < recallList.size(); i++)
			{
				RecallInfo recallInfo = recallList[i];
				switch (recallInfo.state)
				{
				case RecallState::RECALLING:
					if (gameTime > recallInfo.startTime + 8.0f - timeBuffer)
					{
						recallList[i].state = RecallState::RECALLING_FINISHED;
					}
					break;
				case RecallState::TELEPORTING:
					if (gameTime > recallInfo.startTime + 4.0f - timeBuffer) recallList[i].state = RecallState::TELEPORTING_FINISHED;
					break;
				case RecallState::RECALLING_FINISHED:
					if (gameTime > recallInfo.startTime + 11.0f) RemoveRecall(i);
					break;
				case RecallState::TELEPORTING_FINISHED:
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
					recallList.push_back(RecallInfo((state == 6) ? RecallState::RECALLING : RecallState::TELEPORTING, obj->GetName(), gameTime));
					continue;
				}
				if (isInList && (state != 6 && state != 8) &&
					(recallList[recallIndex].state != RecallState::RECALLING_FINISHED && recallList[recallIndex].state != RecallState::TELEPORTING_FINISHED))
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
			AddSetting("debug", "draw object data", false);
			AddSetting("debug", "draw bounding radius", false);
		}
	}
}