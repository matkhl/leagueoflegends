#pragma once

#include "../stdafx.h"

namespace globals
{
	extern QWORD moduleBase;
	extern MODULEINFO moduleInfo;

	extern bool eject;
	extern const char* renderType;
	extern bool hookResponse;
	extern ImVec2 menuSize;
	extern bool menuOpen;

	extern float windowWidth;
	extern float windowHeight;

	extern Object* localPlayer;
	extern ObjectManager* heroManager;
	extern ObjectManager* minionManager;

	namespace scripts
	{
		namespace orbwalker
		{
			extern OrbwalkState orbwalkState;
		}

		namespace recalls
		{
			extern std::vector<RecallInfo> recallList;
			extern float timeBuffer;
		}
	}
}