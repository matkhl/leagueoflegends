#pragma once

namespace menu
{
	void Init();
	void TextCentered(std::string text);
	void DynamicSettings();
	void Update();

	namespace log
	{
		extern ImGuiTextBuffer logBuffer;
		extern bool scrollToBottom;

		void Log(const char* message);
		void Log(int number);
		void Log(double decimal);
		void Log(uint64_t address);
		void Log(void* pointer);
	}
}