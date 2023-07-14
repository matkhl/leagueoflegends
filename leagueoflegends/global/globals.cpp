#include "../stdafx.h"

namespace globals
{
	QWORD moduleBase;
	MODULEINFO moduleInfo;

	bool eject = false;
	const char* renderType;
	bool hookResponse = false;
	ImVec2 menuSize;
	bool menuOpen = false;

	float windowWidth = 0.0f;
	float windowHeight = 0.0f;

	Object* localPlayer;
	HeroManager* heroManager;
	std::vector<Object*> heroes;

	namespace scripts
	{
		namespace orbwalker
		{
			OrbwalkState orbwalkState;
		}

		namespace recalls
		{
			std::vector<RecallInfo> recallList = {};
			float timeBuffer = 0.035f;
		}
	}
}