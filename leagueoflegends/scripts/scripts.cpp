#include "../stdafx.h"

namespace scripts
{
	void Init()
	{
		cooldowns::Init();
		recalls::Init();
		orbwalker::Init();
		debug::Init();
	}

	void Update()
	{
		if (settings::GetBool("orbwalker", "enabled", true)) orbwalker::Update();
		if (settings::GetBool("recalls", "enabled", true)) recalls::Update();
	}

	namespace orbwalker
	{
		float lastMoveTime = 0.0f;
		float lastAttackTime = 0.0f;

		float gameTime = 0.0f;

		namespace actions
		{
			void Idle()
			{
				if (!lastMoveTime) lastMoveTime = gameTime;
				if (gameTime < lastMoveTime + settings::GetFloat("orbwalker", "clickdelay", 0.05f)) return;
				lastMoveTime = gameTime;

				functions::MoveToMousePos();
			}

			void AttackObject(Object* obj)
			{

			}
		}

		namespace states
		{
			void Attack()
			{
				actions::Idle();
			}
		}

		bool StopOrbwalk()
		{
			return (
				!functions::CanSendInput() ||
				gameTime < lastAttackTime + globals::localPlayer->GetAttackWindup()
			);
		}

		void CheckActiveAttack()
		{
			if (auto spellCast = globals::localPlayer->GetActiveSpellCast())
				if (spellCast->IsAutoAttack())
					lastAttackTime = spellCast->GetStartTime();
		}

		void Init()
		{
			settings::GetFloat("orbwalker", "clickdelay", 0.05f);
			settings::AddBounds("orbwalker", "clickdelay", 0.03f, 1.0f);
			settings::GetBool("orbwalker", "enabled", true);
		}

		void Update()
		{
			gameTime = functions::GetGameTime();
			CheckActiveAttack();

			if (StopOrbwalk()) return;

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
			settings::GetBool("cooldowns", "enabled", true);
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
			settings::GetBool("recalls", "enabled", true);
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
			settings::GetBool("debug", "draw object data", false);
		}
	}
}