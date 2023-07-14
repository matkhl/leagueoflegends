#pragma once

#include "../stdafx.h"

namespace settings
{
	typedef std::variant<bool, int, float> SettingValue;
	typedef std::map<std::string, SettingValue> SettingsGroup;
	typedef std::map<std::string, SettingsGroup> SettingsData;

	typedef std::variant<std::pair<int, int>, std::pair<float, float>> SettingBoundsValue;
	typedef std::map<std::string, SettingBoundsValue> SettingsBoundsGroup;
	typedef std::map<std::string, SettingsBoundsGroup> SettingsBounds;

	extern SettingsData data;

	void Load();
	void Save();

	SettingValue Get(std::string group, std::string key, SettingValue defaultValue);
	bool GetBool(std::string group, std::string key, SettingValue defaultValue);
	int GetInt(std::string group, std::string key, SettingValue defaultValue);
	float GetFloat(std::string group, std::string key, SettingValue defaultValue);
	void Set(std::string group, std::string key, SettingValue value);

	SettingBoundsValue GetBounds(std::string group, std::string key, SettingBoundsValue defaultValue);
	std::pair<int, int> GetBoundsInt(std::string group, std::string key, std::pair<int, int> defaultValue);
	std::pair<float, float> GetBoundsFloat(std::string group, std::string key, std::pair<float, float> defaultValue);
	void AddBounds(std::string group, std::string key, int min, int max);
	void AddBounds(std::string group, std::string key, float min, float max);
}