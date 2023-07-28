#include "../stdafx.h"

namespace settings
{
	inline std::ostream& operator<<(std::ostream& os, const SettingValue& value) {
		if (std::holds_alternative<int>(value)) {
			os << std::get<int>(value);
		}
		else if (std::holds_alternative<float>(value)) {
			os << std::get<float>(value);
		}
		else if (std::holds_alternative<bool>(value)) {
			os << std::boolalpha << std::get<bool>(value);
		}
		return os;
	}

	SettingsData data = {};
	SettingsBounds bounds = {};

	void Save()
	{
		std::ofstream file("ionia.ini");
		if (file.is_open()) {
			for (const auto& group : data) {
				file << "[" << group.first << "]\n";
				for (const auto& setting : group.second) {
					file << setting.first << "=" << setting.second << "\n";
				}
				file << "\n";
			}
			file.close();
		}
	}

	void Load()
	{
		std::ifstream file("ionia.ini");
		if (file.is_open())
		{
			std::string line;
			std::string currentGroup;
			while (std::getline(file, line)) {
				if (line.empty() || line[0] == '#'){
					continue;
				}
				if (line[0] == '[' && line.back() == ']') {
					currentGroup = line.substr(1, line.size() - 2);
				}
				else {
					auto delimiterPos = line.find('=');
					if (delimiterPos != std::string::npos) {
						std::string key = line.substr(0, delimiterPos);
						std::string valueStr = line.substr(delimiterPos + 1);

						SettingValue value;
						if (valueStr == SP_STRING("true")) {
							value = true;
						}
						else if (valueStr == SP_STRING("false")) {
							value = false;
						}
						else if (std::isdigit(valueStr[0])) {
							try {
								size_t parsedChars;
								int intValue = std::stoi(valueStr, &parsedChars);
								if (parsedChars == valueStr.size()) {
									value = intValue;
								}
								else {
									float floatValue = std::stof(valueStr);
									value = floatValue;
								}
							}
							catch (...) {}
						}

						auto groupIt = data.find(currentGroup);
						if (groupIt != data.end()) {
							auto keyIt = groupIt->second.find(key);
							if (keyIt != groupIt->second.end()) {
								data[currentGroup][key] = value;
							}
						}
					}
				}
			}
			file.close();
		}
	}

	SettingValue Get(std::string group, std::string key, SettingValue defaultValue)
	{
		auto groupIt = data.find(group);
		if (groupIt != data.end()) {
			auto keyIt = groupIt->second.find(key);
			if (keyIt != groupIt->second.end()) {
				return keyIt->second;
			}
		}
		Set(group, key, defaultValue);
		return defaultValue;
	}

	bool GetBool(std::string group, std::string key)
	{
		return std::get<bool>(Get(group, key, false));
	}

	int GetInt(std::string group, std::string key)
	{
		return std::get<int>(Get(group, key, 0));
	}

	float GetFloat(std::string group, std::string key)
	{
		return std::get<float>(Get(group, key, 0.0f));
	}

	void Set(std::string group, std::string key, SettingValue value)
	{
		data[group][key] = value;
	}

	SettingBoundsValue GetBounds(std::string group, std::string key, SettingBoundsValue defaultValue)
	{
		auto groupIt = bounds.find(group);
		if (groupIt != bounds.end()) {
			auto keyIt = groupIt->second.find(key);
			if (keyIt != groupIt->second.end()) {
				return keyIt->second;
			}
		}
		return defaultValue;
	}

	std::pair<int, int> GetBoundsInt(std::string group, std::string key, std::pair<int, int> defaultValue)
	{
		return std::get<std::pair<int, int>>(GetBounds(group, key, defaultValue));
	}

	std::pair<float, float> GetBoundsFloat(std::string group, std::string key, std::pair<float, float> defaultValue)
	{
		return std::get<std::pair<float, float>>(GetBounds(group, key, defaultValue));
	}

	void AddBounds(std::string group, std::string key, int min, int max)
	{
		bounds[group][key] = std::pair<int, int>(min, max);
	}

	void AddBounds(std::string group, std::string key, float min, float max)
	{
		bounds[group][key] = std::pair<float, float>(min, max);
	}
}