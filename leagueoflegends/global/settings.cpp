#include "../stdafx.h"

namespace settings
{
	DWORD openMenuKey = VK_NUMPAD0;
	DWORD detachKey = VK_DELETE;

	bool isMenuOpen = false;

	namespace scripts
	{
		bool cooldowns = true;
		bool recalls = true;
	}
}