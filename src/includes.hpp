// windows / stl includes.
#include <Windows.h>
#include <WinUser.h>
#include <filesystem>
#include <string>
#include <tlhelp32.h>
#include <unordered_set>
#include <direct.h> // mkdir
#include <dwmapi.h> // DwmExtendFrameIntoClientArea


// features
#include "utils/utils.hpp"

#include "menu/menu.hpp"


// third-party
#include "../third-party/imgui/imgui.h"
#include "../third-party/imgui/impl/imgui_impl_win32.h"
#include "../third-party/imgui/impl/imgui_impl_dx11.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")