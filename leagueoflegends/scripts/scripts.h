#pragma once

#include "../stdafx.h"

namespace scripts
{
	void Init();
	void Update();

	namespace orbwalker
	{
		void IssueMove();
		void Attack();
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
}
