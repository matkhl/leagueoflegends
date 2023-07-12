﻿#include "../../stdafx.h"

namespace hooks
{
	namespace impl
	{
		typedef unsigned int UINT;

		bool _init = false;

		void Inits()
		{
			globals::localPlayer = *(Object**)(globals::moduleBase + oLocalPlayer);
			globals::heroManager = *(HeroManager**)(globals::moduleBase + oHeroManager);

			functions::Init();
			render::Init();
			menu::Init();

			RECT windowRect;
			if (GetWindowRect(windowDX, &windowRect))
			{
				globals::windowWidth = abs(windowRect.right - windowRect.left);
				globals::windowHeight = abs(windowRect.bottom - windowRect.top);
			}

			globals::hookResponse = true;
		}

		void Updates()
		{
			functions::RefreshArrays();
			scripts::Update();
			render::Update();
			menu::Update();
		}

		typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

		HWND windowDX = nullptr;
		WNDPROC o_wndProcDX;

		LRESULT __stdcall wndProcDX(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

			if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
				return true;

			return CallWindowProc(o_wndProcDX, hWnd, uMsg, wParam, lParam);
		}

		typedef long(__stdcall* ResetFn)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
		static ResetFn o_resetDX9 = NULL;

		typedef long(__stdcall* EndSceneFn)(LPDIRECT3DDEVICE9);
		static EndSceneFn o_endSceneDX9 = NULL;

		HRESULT __stdcall Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			HRESULT result = o_resetDX9(pDevice, pPresentationParameters);
			ImGui_ImplDX9_CreateDeviceObjects();

			return result;
		}

		HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice)
		{
			if (globals::eject) return o_endSceneDX9(pDevice);

			if (!_init)
			{
				D3DDEVICE_CREATION_PARAMETERS params;
				pDevice->GetCreationParameters(&params);
				windowDX = params.hFocusWindow;
				o_wndProcDX = (WNDPROC)SetWindowLongPtr(windowDX, GWLP_WNDPROC, (LONG_PTR)wndProcDX);

				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

				ImGui_ImplWin32_Init(windowDX);
				ImGui_ImplDX9_Init(pDevice);

				Inits();

				std::cout << globals::renderType << " hooked and ImGui initialized" << std::endl;

				_init = true;
			}

			if (functions::IsGameFocused())
			{
				if (GetAsyncKeyState(settings::detachKey) & 1)
				{
					SetWindowLongPtr(windowDX, GWLP_WNDPROC, (LONG_PTR)o_wndProcDX);

					ImGui_ImplDX9_Shutdown();
					ImGui_ImplWin32_Shutdown();
					ImGui::DestroyContext();

					HRESULT result = o_endSceneDX9(pDevice);
					
					kiero::shutdown();
					pDevice->Release();

					globals::eject = true;

					return result;
				}

				if (GetAsyncKeyState(settings::openMenuKey) & 1)
				{
					settings::isMenuOpen = !settings::isMenuOpen;
					functions::SaveSettings();
				}

				globals::scripts::orbwalker::orbwalkState = OrbwalkState::OFF;
				if (GetAsyncKeyState(VK_SPACE))
					globals::scripts::orbwalker::orbwalkState = OrbwalkState::ATTACK;
			}

			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			Updates();

			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

			return o_endSceneDX9(pDevice);
		}

		void Init()
		{
			//hook methods in /kiero/METHODSTABLE.txt
			if (globals::renderType == "D3D9")
			{
				if (kiero::bind(16, (void**)&o_resetDX9, Reset) != kiero::Status::Success) std::cout << globals::renderType << " bind failed" << std::endl;
				if (kiero::bind(42, (void**)&o_endSceneDX9, EndScene) != kiero::Status::Success) std::cout << globals::renderType << " bind failed" << std::endl;
			}
		}
	}
}