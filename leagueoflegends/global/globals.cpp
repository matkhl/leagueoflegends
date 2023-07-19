#include "../stdafx.h"

namespace globals
{
	const char* imguiFileName = SP_STRING("settings-metadata-window.ini");
	const char* settingsFileName = SP_STRING("settings-metadata.ini");
	const char* fontPath = SP_STRING("C:\\Windows\\Fonts\\Arial.ttf");

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
	ObjectManager* heroManager;
	ObjectManager* minionManager;

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