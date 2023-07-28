#include "../stdafx.h"

namespace menu
{
	static bool no_titlebar = true;
	static bool no_border = true;
	static bool no_resize = true;
	static bool auto_resize = true;
	static bool no_move = false;
	static bool no_scrollbar = true;
	static bool no_collapse = true;
	static bool no_menu = true;
	static bool start_pos_set = false;

	ImGuiWindowFlags window_flags;

	float nextSaveTime = 0.0f;

	void Init()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(12.0f, 14.0f);
		style->WindowRounding = 0.0f;
		style->FramePadding = ImVec2(10.0f, 4.0f);
		style->FrameRounding = 0.0f;
		style->ItemSpacing = ImVec2(12.0f, 16.0f);
		style->ItemInnerSpacing = ImVec2(14.0f, 4.0f);
		style->IndentSpacing = 0.0f;
		style->ScrollbarSize = 12.0f;
		style->ScrollbarRounding = 2.0f;
		style->GrabMinSize = 4.0f;
		style->GrabRounding = 0.0f;
		style->WindowBorderSize = 0.0f;
		style->PopupBorderSize = 1.0f;
		style->GrabMinSize = 14.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.88f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.70f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.80f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.60f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.61f, 0.61f, 0.61f, 0.54f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.85f, 0.85f, 0.85f, 0.54f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 0.75f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.42f, 1.0f, 0.93f, 0.75f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 1.0f, 0.93f, 0.92f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

		window_flags = 0;
		if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
		if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
		if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
		if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;

		globals::menuSize = ImVec2(150.0f, 140.0f);

		ImGui::SetNextWindowSize(globals::menuSize, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(25, 25));

		ImGui::GetIO().MouseDrawCursor = false;

		LOG("Menu initialized");
	}

	void SaveSoon()
	{
		nextSaveTime = functions::GetGameTime() + 1.0f;
	}

	void TextCentered(std::string text)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(text.c_str());
	}

	bool CustomCheckbox(const char* label, bool* isChecked)
	{
		ImGuiWindow* currentWindow = ImGui::GetCurrentWindow();
		if (currentWindow->SkipItems)
			return false;

		ImGuiContext& context = *GImGui;
		const ImGuiStyle& style = context.Style;
		const ImGuiID id = currentWindow->GetID(label);

		ImVec2 labelSize = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 valueSize = ImGui::CalcTextSize(SP_STRING("Off"), NULL, true);

		const float minWidgetWidth = 180.0f;
		const float widgetWidth = ImMax(ImMax(minWidgetWidth, labelSize.x + valueSize.x + 60.0f), ImGui::GetWindowSize().x);

		const float widgetHeight = ImMax(labelSize.y, valueSize.y);

		ImRect totalBoundingBox(currentWindow->DC.CursorPos, currentWindow->DC.CursorPos + ImVec2(widgetWidth, widgetHeight));

		if (!ImGui::ItemAdd(totalBoundingBox, id))
		{
			ImGui::TextColored(ImVec4(0.41f, 1.0f, 0.93f, 1.0f), std::to_string(id).c_str());
			return false;
		}

		bool isPressed = ImGui::InvisibleButton(label, ImVec2(widgetWidth - 25.0f, widgetHeight));
		if (isPressed)
			*isChecked = !(*isChecked);

		ImVec2 textPosition = totalBoundingBox.Min;
		ImGui::RenderText(textPosition, label);

		textPosition.x += widgetWidth - valueSize.x - 30.0f - ((*isChecked) ? 18.0f : 0.0f) + ((widgetWidth == ImGui::GetWindowSize().x) ? 1.0f : 0.0f);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(*isChecked ? 0.2f : 8.0f, *isChecked ? 8.0f : 0.2f, 0.2f, 1.0f));
		ImGui::RenderText(textPosition, *isChecked ? SP_STRING("On") : SP_STRING("Off"));
		ImGui::PopStyleColor();

		if (*isChecked) {
			textPosition.x += valueSize.x + 5.0f;
			ImGui::RenderCheckMark(currentWindow->DrawList, textPosition, COLOR_GREEN, labelSize.y);
		}

		return isPressed;
	}

	void DrawMenu(std::pair<std::string, settings::SettingsGroup> group, std::pair<std::string, std::vector<std::string>> groupOrder)
	{
		std::string groupName = functions::CapitalizeFirstLetter(group.first);
		if (ImGui::BeginMenu(groupName.c_str()))
		{
			int id = 0;
			for (const auto& key : groupOrder.second)
			{
				auto it = group.second.find(key);
				if (it != group.second.end())
				{
					std::pair<std::string, settings::SettingValue> setting = *it;

					const std::string& key = setting.first;
					const settings::SettingValue& value = setting.second;

					if (std::holds_alternative<bool>(value))
					{
						bool boolValue = std::get<bool>(value);
						if (CustomCheckbox(key.c_str(), &boolValue)) SaveSoon();
						settings::Set(group.first, setting.first, boolValue);
					}
					else if (std::holds_alternative<int>(value))
					{
						int intValue = std::get<int>(value);
						const auto bounds = settings::GetBoundsInt(group.first, key, std::pair<int, int>(0, 1));

						if (key == SP_STRING("skin id"))
						{
							char* items[50] = {};

							for (int i = 0; i < 50; i++) {
								std::string str;
								if (!i)
									str = SP_STRING("Off");
								else
									str = std::to_string(i);
								items[i] = new char[str.length() + 1];
								std::strcpy(items[i], str.c_str());
							}

							if (ImGui::Combo(key.c_str(), &intValue, items, 50, 5))
							{
								globals::localPlayer->ChangeSkin(intValue);
								SaveSoon();
							}

							for (int i = 0; i < 50; i++)
								delete[] items[i];
						}
						else
						{
							if (ImGui::SliderInt(("##" + key).c_str(), &intValue, bounds.first, bounds.second, key.c_str())) SaveSoon();
							ImGui::SameLine();
							ImGui::Text("%.3f", intValue);
						}

						settings::Set(group.first, setting.first, intValue);
					}
					else if (std::holds_alternative<float>(value))
					{
						float floatValue = std::get<float>(value);
						const auto bounds = settings::GetBoundsFloat(group.first, key, std::pair<float, float>(0.0f, 1.0f));

						if (ImGui::SliderFloat(("##" + key).c_str(), &floatValue, bounds.first, bounds.second, key.c_str())) SaveSoon();
						ImGui::SameLine();
						ImGui::Text("%.3f", floatValue);

						settings::Set(group.first, setting.first, floatValue);
					}

					if (!id && groupOrder.second.size() > 1 && key == SP_STRING("enabled"))
					{
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2.0f);
						ImGui::Separator();
					}

					++id;
				}
			}

			ImGui::EndMenu();
		}
		if (groupName == SP_STRING("Debug"))
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1.0f);
			ImGui::Separator();
		}
	}

	void DynamicSettings()
	{
		for (const auto& group : scripts::settingsOrder) {
			auto it = settings::data.find(group.first);
			if (it != settings::data.end()) {
				DrawMenu(*it, group);
			}
		}
	}

	void Update()
	{
		ImGui::SetNextWindowSize(globals::menuSize, ImGuiCond_FirstUseEver);

		if (globals::menuOpen)
		{
			ImGui::Begin("menu", &globals::menuOpen, window_flags);

			DynamicSettings();

			ImGui::End();
		}

		if (nextSaveTime && functions::GetGameTime() >= nextSaveTime)
		{
			settings::Save();
			nextSaveTime = 0.0f;
			LOG("Saved");
		}
	}
}