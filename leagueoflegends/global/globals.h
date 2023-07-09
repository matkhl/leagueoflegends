#pragma once

#include "../stdafx.h"

namespace globals
{
	extern QWORD moduleBase;
	extern MODULEINFO moduleInfo;

	extern float windowWidth;
	extern float windowHeight;

	extern bool eject;
	extern const char* renderType;
	extern bool hookResponse;
	extern ImVec2 menuSize;

	extern Object* localPlayer;
	extern HeroManager* heroManager;
	extern std::vector<Object*> heroes;

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