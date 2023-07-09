#pragma once

#include "../stdafx.h"

namespace settings
{
	extern DWORD openMenuKey;
	extern DWORD detachKey;

	extern bool isMenuOpen;

	namespace scripts
	{
		namespace orbwalker
		{
			extern bool enabled;
			extern float clickDelay;
		}

		extern bool cooldowns;
		extern bool recalls;
	}
}