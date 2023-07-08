#include "../stdafx.h"

namespace functions
{
	float lastRefreshTime = 0.0f;

	void SaveSettings()
	{
		std::ofstream settings;
		settings.open("settings-metadata.ini");
		settings.clear();

		std::string connChar = "=";

		settings << "isMenuOpen" << connChar << settings::isMenuOpen << std::endl;
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
			else if (name == "scripts::cooldowns")
				settings::scripts::cooldowns = boolValue;
			else if (name == "scripts::recalls")
				settings::scripts::recalls = boolValue;
		}

		settings.close();
	}

	Vector3 ReadVector3(QWORD offset)
	{
		Vector3 result;
		result.x = *(float*)(offset);
		result.y = *(float*)(offset + 0x4);
		result.z = *(float*)(offset + 0x8);
		return result;
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

	bool IsGameFocused()
	{
		return GetActiveWindow() == hooks::impl::windowDX;
	}

	float GetGameTime()
	{
		return *(float*)(globals::moduleBase + oGameTime);
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
}