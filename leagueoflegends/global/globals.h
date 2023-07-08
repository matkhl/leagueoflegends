#pragma once

#include "../stdafx.h"

namespace globals
{
	extern LPCWSTR processName;
	extern QWORD moduleBase;

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
		namespace recalls
		{
			extern std::vector<RecallInfo> recallList;
			extern float timeBuffer;
		}
	}
}