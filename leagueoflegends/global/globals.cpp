#include "../stdafx.h"

namespace globals
{
	LPCWSTR processName;
	QWORD moduleBase;

	float windowWidth = 0.0f;
	float windowHeight = 0.0f;

	bool eject = false;
	const char* renderType;
	bool hookResponse = false;
	ImVec2 menuSize;

	Object* localPlayer;
	HeroManager* heroManager;
	std::vector<Object*> heroes;

	namespace scripts
	{
		namespace recalls
		{
			std::vector<RecallInfo> recallList = {};
			float timeBuffer = 0.035f;
		}
	}
}