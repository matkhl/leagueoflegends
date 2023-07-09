#include "../stdafx.h"

namespace settings
{
	DWORD openMenuKey = VK_NUMPAD0;
	DWORD detachKey = VK_DELETE;

	bool isMenuOpen = false;

	namespace scripts
	{
		namespace orbwalker
		{
			bool enabled = true;
			float clickDelay = 0.03f;
		}

		bool cooldowns = true;
		bool recalls = true;
	}
}