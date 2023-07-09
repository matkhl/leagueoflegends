#include "../stdafx.h"

namespace menu
{
	static bool no_titlebar = true;
	static bool no_border = true;
	static bool no_resize = true;
	static bool auto_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = true;
	static bool no_menu = true;
	static bool start_pos_set = false;

	ImGuiWindowFlags window_flags;

	void Init()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(5.0f, 5.0f);
		style->WindowRounding = 0.0f;
		style->FramePadding = ImVec2(4.0f, 4.0f);
		style->FrameRounding = 0.0f;
		style->ItemSpacing = ImVec2(4.0f, 3.0f);
		style->ItemInnerSpacing = ImVec2(4.0f, 3.0f);
		style->IndentSpacing = 6.0f;
		style->ScrollbarSize = 12.0f;
		style->ScrollbarRounding = 2.0f;
		style->GrabMinSize = 4.0f;
		style->GrabRounding = 0.0f;
		style->WindowBorderSize = 0.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.50f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
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

		globals::menuSize = ImVec2(220.0f, 350.0f);

		ImGui::SetNextWindowSize(globals::menuSize, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(25, 25));

		ImGui::GetIO().MouseDrawCursor = false;

		std::cout << "Menu initialized" << std::endl;
	}

	void TextCentered(std::string text) {
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(text.c_str());
	}

	void Update()
	{
		ImGui::SetNextWindowSize(globals::menuSize, ImGuiCond_FirstUseEver);

		if (settings::isMenuOpen)
		{
			ImGui::Begin("menu", &settings::isMenuOpen, window_flags);

			TextCentered(std::string("Menu by Matkhl"));
			ImGui::Spacing();
			ImGui::Checkbox("Orbwalker", &settings::scripts::orbwalker::enabled);
			ImGui::Spacing();
			ImGui::Checkbox("Track cooldowns", &settings::scripts::cooldowns);
			ImGui::Checkbox("Track recalls", &settings::scripts::recalls);
			ImGui::Spacing();
			if (ImGui::Button("Save")) functions::SaveSettings();

			const float logHeight = ImGui::GetContentRegionAvail().y - ImGui::GetTextLineHeightWithSpacing();
			ImGui::BeginChild("Log", ImVec2(-1, logHeight), true, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::TextUnformatted(log::logBuffer.begin(), log::logBuffer.end());
			if (log::scrollToBottom)
				ImGui::SetScrollHereY(1.0f);
			log::scrollToBottom = false;
			ImGui::EndChild();

			ImGui::End();
		}
	}

	namespace log
	{
		static ImGuiTextBuffer logBuffer;
		static bool scrollToBottom = true;

		void Log(const char* message)
		{
			std::string newline = message + std::string("\n");
			logBuffer.appendf(newline.c_str());
		}

		void Log(int number)
		{
			char buffer[sizeof(number) * CHAR_BIT / 2] = "";
			sprintf_s(buffer, "%i", number);
			Log(buffer);
		}

		void Log(double decimal)
		{
			char buffer[(sizeof(decimal) * CHAR_BIT / 4) + 2] = "";
			sprintf_s(buffer, "%.2f", decimal);
			Log(buffer);
		}

		void Log(uint64_t address)
		{
			char buffer[32] = "";
			sprintf_s(buffer, "%llx", address);
			Log(buffer);
		}

		void Log(void* pointer)
		{
			char buffer[32] = "";
			sprintf_s(buffer, "%p", pointer);
			Log(buffer);
		}
	}
}