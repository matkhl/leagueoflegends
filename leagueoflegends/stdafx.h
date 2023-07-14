#pragma once

#define WIN32_LEAN_AND_MEAN
#define GLFW_EXPOSE_NATIVE_WGL

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <Psapi.h>

#include <vector>
#include <map>
#include <variant>
#include <TlHelp32.h>
#include <directxmath.h>
#include <winternl.h>
#include <string>
#include <sstream>
#include <fstream>

#include <dxgi.h>
#include <d3d11.h>
#include <d3d10.h>
#include <d3d9.h>

#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "mem/mem.h"
#include "mem/spoof_call.h"
#include "global/strings.h"
#include "global/colors.h"
#include "global/offsets.h"
#include "global/structs.h"
#include "global/utils.h"
#include "classes/classes.h"
#include "global/functions.h"
#include "render/render.h"
#include "global/settings.h"
#include "global/globals.h"
#include "global/targetver.h"
#include "scripts/scripts.h"

#include "hooks/hooks.h"
#include "hooks/impl/impl.h"
#include "menu/menu.h"