#pragma once

#include "../stdafx.h"

namespace scripts
{
	void Update();

	namespace orbwalker
	{
		void IssueOrder();
		void Attack();
		void Update();
	}

	namespace recalls
	{
		void RemoveRecall(int index);
		int GetRecallListIndex(Object* obj);
		void Update();
	}
}
