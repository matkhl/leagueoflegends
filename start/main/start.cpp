#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

#include <shlwapi.h>
#include <cwchar>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <clocale>

#include <vector>
#include <string>

#include "Injection.h"

#define NAMED_PIPE 1

DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
	return procId;
}

int main()
{
	std::cout << "Checking files" << std::endl;

	HINSTANCE hInjectionMod = LoadLibrary(GH_INJ_MOD_NAME);

	auto InjectA = (f_InjectA)GetProcAddress(hInjectionMod, "InjectA");
	auto GetSymbolState = (f_GetSymbolState)GetProcAddress(hInjectionMod, "GetSymbolState");
	auto GetImportState = (f_GetSymbolState)GetProcAddress(hInjectionMod, "GetImportState");
	auto StartDownload = (f_StartDownload)GetProcAddress(hInjectionMod, "StartDownload");

	StartDownload();

	while (GetSymbolState() != 0)
	{
		Sleep(10);
	}

	while (GetImportState() != 0)
	{
		Sleep(10);
	}

	DWORD TargetProcessId = 0;

	std::cout << "Waiting for process" << std::endl;

	while (!TargetProcessId)
	{
		TargetProcessId = GetProcId(L"League of Legends.exe");
		Sleep(500);
	}

	std::cout << "Process found" << std::endl;

	Sleep(1000);

	std::vector<wchar_t> pathBuf;
	DWORD copied = 0;
	do {
		pathBuf.resize(pathBuf.size() + MAX_PATH);
		copied = GetModuleFileName(0, &pathBuf.at(0), pathBuf.size());
	} while (copied >= pathBuf.size());

	pathBuf.resize(copied);
	std::string path(pathBuf.begin(), pathBuf.end() - 0x9);

#if NAMED_PIPE
	setlocale(LC_CTYPE, ".OCP");
	std::wstring wPath(path.begin(), path.end());
	std::cout << "Launching named pipe server" << std::endl;

	try
	{
		const intptr_t result = reinterpret_cast<intptr_t>(ShellExecuteW(NULL, L"open", L"\"NamedPipeConsole.exe\"", NULL, wPath.c_str(), SW_SHOWNORMAL));
		if (result < 33) {
			std::cout << "Launching pipe server failed" << std::endl;
		}
	}
	catch (...) {};
#endif

	INJECTIONDATAA data =
	{
		"",
		TargetProcessId,
		INJECTION_MODE::IM_LoadLibraryExW,
		LAUNCH_METHOD::LM_FakeVEH,
		NULL,
		3000,
		NULL,
		NULL,
		true
	};

	strcpy_s(data.szDllPath, (path + "leagueoflegends.dll").c_str());

	Sleep(500);

	InjectA(&data);
}