#pragma once

namespace menu
{
	void Init();
	void SaveSoon();
	void TextCentered(std::string text);
	bool CustomCheckbox(const char* label, bool* v);
	void DrawMenu(std::pair<std::string, settings::SettingsGroup> group, std::pair<std::string, std::vector<std::string>> groupOrder);
	void DynamicSettings();
	void Update();
}