#pragma once

namespace menu
{
	void Init();
	void SaveSoon();
	void TextCentered(std::string text);
	void DrawMenu(std::pair<std::string, settings::SettingsGroup> group);
	void DynamicSettings();
	void Update();
}