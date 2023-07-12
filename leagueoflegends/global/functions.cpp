#include "../stdafx.h"

namespace functions
{
	float lastRefreshTime = 0.0f;
	
	void* spoof_trampoline = 0x0;

	void Init()
	{
		spoof_trampoline = (void*)mem::ScanModInternal((char*)"\xFF\x23", (char*)"xx", (char*)globals::moduleBase);

		LoadSettings();
	}

	void SaveSettings()
	{
		std::ofstream settings;
		settings.open("settings-metadata.ini");
		settings.clear();

		std::string connChar = "=";

		settings << "isMenuOpen" << connChar << settings::isMenuOpen << std::endl;
		settings << "scripts::orbwalker::enabled" << connChar << settings::scripts::orbwalker::enabled << std::endl;
		settings << "scripts::cooldowns" << connChar << settings::scripts::cooldowns << std::endl;
		settings << "scripts::recalls" << connChar << settings::scripts::recalls << std::endl;

		settings.close();
	}

	void LoadSettings()
	{
		std::ifstream settings;
		settings.open("settings-metadata.ini");
		if (settings.fail()) {
			SaveSettings();
			return;
		}

		std::string connChar = "=";
		std::string line;
		while (std::getline(settings, line))
		{
			std::size_t connCharIndex = line.find(connChar);
			std::string name = line.substr(0, connCharIndex);
			std::string value = line.substr(connCharIndex + 1);
			bool boolValue = std::atoi(value.c_str());

			if (name == "isMenuOpen")
				settings::isMenuOpen = boolValue;
			else if (name == "scripts::orbwalker::enabled")
				settings::scripts::orbwalker::enabled = boolValue;
			else if (name == "scripts::cooldowns")
				settings::scripts::cooldowns = boolValue;
			else if (name == "scripts::recalls")
				settings::scripts::recalls = boolValue;
		}

		settings.close();
	}

	void RefreshArrays()
	{
		float gameTime = GetGameTime();
		if (gameTime < lastRefreshTime + 0.1f) return;
		lastRefreshTime = gameTime;

		globals::heroes.clear();

		for (int i = 0; i < globals::heroManager->GetListSize(); i++)
		{
			Object* obj = globals::heroManager->GetIndex(i);
			if (!IsValidPtr(obj)) continue;
			globals::heroes.push_back(obj);
		}
	}

	bool IsGameFocused()
	{
		return GetActiveWindow() == hooks::impl::windowDX;
	}

	float GetGameTime()
	{
		return *(float*)(globals::moduleBase + oGameTime);
	}

	Vector3 ReadVector3(QWORD offset)
	{
		Vector3 result;
		result.x = *(float*)(offset);
		result.y = *(float*)(offset + 0x4);
		result.z = *(float*)(offset + 0x8);
		return result;
	}

	Vector2 GetMousePos()
	{
		if (!IsGameFocused()) return Vector2();
		POINT curMouse;
		bool getMouse = GetCursorPos(&curMouse);
		return Vector2(curMouse.x, curMouse.y);
	}

	Vector3 GetBaseDrawPosition(Object* obj)
	{
		typedef bool(__fastcall* fnGetBaseDrawPosition)(QWORD* obj, Vector3* out);
		fnGetBaseDrawPosition _fnGetBaseDrawPosition = (fnGetBaseDrawPosition)(globals::moduleBase + oGetBaseDrawPosition);
		Vector3 out;
		_fnGetBaseDrawPosition((QWORD*)obj, &out);
		return out;
	}

	Vector2 WorldToScreen(Vector3 in)
	{
		typedef bool(__fastcall* fnWorldToScreen)(QWORD* viewport, Vector3* in, Vector3* out);
		fnWorldToScreen _fnWorldToScreen = (fnWorldToScreen)(globals::moduleBase + oWorldToScreen);
		QWORD* viewport = *(QWORD**)(globals::moduleBase + oViewport);
		Vector3 out;
		_fnWorldToScreen((QWORD*)((QWORD)viewport + (QWORD)oViewportW2S), &in, &out);
		return Vector2(out.x, out.y);
	}

	void IssueOrder()
	{
		Vector2 mousePos = GetMousePos();

		typedef bool(__fastcall* fnTryRightClick)(QWORD* player, unsigned int* params);
		fnTryRightClick _fnTryRightClick = (fnTryRightClick)(globals::moduleBase + oTryRightClick);

		unsigned int* params = new unsigned int[20];
		params[17] = (int)mousePos.x;
		params[18] = (int)mousePos.y;
		params[19] = 2;

		spoof_call(spoof_trampoline, _fnTryRightClick, (QWORD*)globals::localPlayer, params);
	}

	void IssueMove()
	{
		Vector2 mousePos = GetMousePos();

		typedef bool(__fastcall* fnIssueMove)(QWORD* oHudInput, int screenX, int screenY, bool isAttackMove, int zeroOrOne, int order);
		fnIssueMove _fnIssueMove = (fnIssueMove)(globals::moduleBase + oIssueMove);

		spoof_call(spoof_trampoline, _fnIssueMove, (QWORD*)(*(QWORD*)(*(QWORD*)(globals::moduleBase + oHudInstance) + oHudInstanceHudInputOffset)), (int)mousePos.x, (int)mousePos.y, false, 0, 0);
	}
}