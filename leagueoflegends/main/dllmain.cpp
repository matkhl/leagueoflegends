#include "../stdafx.h"

//#define CONSOLE_ENABLED

HMODULE hLocalModule;

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
	Sleep(100);
	FreeLibraryAndExitThread(hLocalModule, 0);

	return 0;
}

DWORD __stdcall OnInject(LPVOID lpReserved)
{
#ifdef CONSOLE_ENABLED
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
#endif

	std::cout << SP_STRING("Injected") << std::endl;

	globals::moduleBase = (uintptr_t)GetModuleHandle(nullptr);
	if (!GetModuleInformation(GetCurrentProcess(), (HMODULE)globals::moduleBase, &globals::moduleInfo, sizeof(MODULEINFO)))
	{
		std::cout << SP_STRING("Failed to get module information.") << std::endl;
		return 0;
	}

	while (true)
	{
		float* gameTimePtr = (float*)(globals::moduleBase + oGameTime);
		if (IsValidPtr(gameTimePtr) && *gameTimePtr > 3.0f) break;
		Sleep(300);
	}

	int hooked = 2;
	do
		hooked = hooks::Init();
	while (hooked == 2);

	Sleep(1000);

	if (!globals::hookResponse && hooked == 1)
		std::cout << SP_STRING("Hook function not called by process\n(press detach key)") << std::endl;

	while (!globals::eject)
	{
		Sleep(5);
		if (!globals::hookResponse && GetAsyncKeyState(VK_DELETE))
			globals::eject = true;
	}
#ifdef CONSOLE_ENABLED
	fclose(f);
	FreeConsole();
#endif

	CreateThread(nullptr, 0, EjectThread, nullptr, 0, nullptr);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hLocalModule = hModule;
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, OnInject, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}