#include "../stdafx.h"

namespace scripts
{
	void Update()
	{
		if (settings::scripts::recalls) recalls::Update();
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

			for (int i = 0; i < globals::heroes.size(); i++)
			{
				Object* obj = globals::heroes[i];
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
}