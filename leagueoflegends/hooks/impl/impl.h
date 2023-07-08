#pragma once

namespace hooks
{
	namespace impl
	{
		extern HWND windowDX;
		void Init();
	}
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);