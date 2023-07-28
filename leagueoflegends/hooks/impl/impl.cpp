#include "../../stdafx.h"

namespace hooks
{
	namespace impl
	{
		typedef unsigned int UINT;

		bool _init = false;

		void Inits()
		{
			globals::localPlayer = *(Object**)(globals::moduleBase + oLocalPlayer);
			globals::heroManager = *(ObjectManager**)(globals::moduleBase + oHeroManager);
			globals::minionManager = *(ObjectManager**)(globals::moduleBase + oMinionManager);

			functions::Init();
			render::Init();
			scripts::Init();
			settings::Load();
			menu::Init();

			RECT windowRect;
			if (GetWindowRect(windowDX, &windowRect))
			{
				globals::windowWidth = (float)abs(windowRect.right - windowRect.left);
				globals::windowHeight = (float)abs(windowRect.bottom - windowRect.top);
			}

			functions::PrintChat(CHAT_COLOR("#72ff72", "Loaded"));

			globals::hookResponse = true;

			LOG("%s hooked", globals::renderType);
		}

		void Updates()
		{
			scripts::Update();
			render::Update();
			menu::Update();
		}

		bool KeyChecks()
		{
			if (GetAsyncKeyState(VK_DELETE) & 1)
			{
				settings::Save();
				globals::eject = true;

				functions::PrintChat(CHAT_COLOR("#ff5b5b", "Ejected"));

				return true;
			}

			if (GetAsyncKeyState(VK_SHIFT)) {
				globals::menuOpen = true;
			} else {
				globals::menuOpen = false;
			}

			globals::scripts::orbwalker::orbwalkState = OrbwalkState::Off;
			if (GetAsyncKeyState(VK_SPACE))
				globals::scripts::orbwalker::orbwalkState = OrbwalkState::Attack;

			return false;
		}

		//DX
		typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		static Present o_presentDX;

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

		//DX9
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
				io.IniFilename = "window.ini";
				io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
				io.Fonts->AddFontFromFileTTF(SP_STRING("C:\\Windows\\Fonts\\Arial.ttf"), 14);

				ImGui_ImplWin32_Init(windowDX);
				ImGui_ImplDX9_Init(pDevice);

				Inits();

				_init = true;
			}

			if (functions::IsGameFocused())
			{
				if (KeyChecks())
				{
					SetWindowLongPtr(windowDX, GWLP_WNDPROC, (LONG_PTR)o_wndProcDX);

					ImGui_ImplDX9_Shutdown();
					ImGui_ImplWin32_Shutdown();
					ImGui::DestroyContext();

					HRESULT result = o_endSceneDX9(pDevice);

					kiero::shutdown();
					pDevice->Release();

					return result;
				}
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

		//DX11
		ID3D11Device* pDeviceDX11 = nullptr;
		ID3D11DeviceContext* pContextDX11 = nullptr;
		ID3D11RenderTargetView* mainRenderTargetViewDX11;

		HRESULT __stdcall presentDX11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
		{
			if (!_init)
			{
				if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDeviceDX11)))
				{
					pDeviceDX11->GetImmediateContext(&pContextDX11);
					DXGI_SWAP_CHAIN_DESC sd;
					pSwapChain->GetDesc(&sd);
					windowDX = sd.OutputWindow;
					ID3D11Texture2D* pBackBuffer;
					pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
					if (!pBackBuffer) return o_presentDX(pSwapChain, SyncInterval, Flags);
					pDeviceDX11->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewDX11);
					pBackBuffer->Release();
					o_wndProcDX = (WNDPROC)SetWindowLongPtr(windowDX, GWLP_WNDPROC, (LONG_PTR)wndProcDX);

					IMGUI_CHECKVERSION();
					ImGui::CreateContext();
					ImGuiIO& io = ImGui::GetIO(); (void)io;
					io.IniFilename = "window.ini";
					io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
					io.Fonts->AddFontFromFileTTF(SP_STRING("C:\\Windows\\Fonts\\Arial.ttf"), 14);

					DXGI_SWAP_CHAIN_DESC desc;
					pSwapChain->GetDesc(&desc);

					ID3D11Device* device;
					pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device);

					ID3D11DeviceContext* context;
					device->GetImmediateContext(&context);

					ImGui_ImplWin32_Init(windowDX);
					ImGui_ImplDX11_Init(device, context);

					Inits();

					_init = true;
				}
				else
					return o_presentDX(pSwapChain, SyncInterval, Flags);
			}

			if (functions::IsGameFocused())
			{
				if (KeyChecks())
				{
					SetWindowLongPtr(windowDX, GWLP_WNDPROC, (LONG_PTR)o_wndProcDX);

					ImGui_ImplDX11_Shutdown();
					ImGui_ImplWin32_Shutdown();
					ImGui::DestroyContext();

					HRESULT result = o_presentDX(pSwapChain, SyncInterval, Flags);

					kiero::shutdown();
					pDeviceDX11->Release();

					globals::eject = true;

					return result;
				}
			}

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			Updates();

			ImGui::EndFrame();
			ImGui::Render();
			pContextDX11->OMSetRenderTargets(1, &mainRenderTargetViewDX11, NULL);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			return o_presentDX(pSwapChain, SyncInterval, Flags);
		}

		void Init()
		{
			if (globals::renderType == "D3D9")
			{
				kiero::bind(16, (void**)&o_resetDX9, Reset);
				kiero::bind(42, (void**)&o_endSceneDX9, EndScene);
			}
			else if (globals::renderType == "D3D11")
			{
				kiero::bind(8, (void**)&o_presentDX, presentDX11);
			}
		}
	}
}