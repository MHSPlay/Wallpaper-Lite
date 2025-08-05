// windows / stl includes.
#include <Windows.h>
#include <WinUser.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <tlhelp32.h>
#include <thread>
#include <shlobj.h>
#include <direct.h> // mkdir
#include <dwmapi.h> // DwmExtendFrameIntoClientArea

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

// third-party
#define IMGUI_ENABLE_VIEWPORTS
#include "../third-party/imgui/imgui.h"
#include "../third-party/imgui/impl/imgui_impl_win32.h"
#include "../third-party/imgui/impl/imgui_impl_dx11.h"

static ID3D11Device*			g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static bool                     g_SwapChainOccluded = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

// features
#include "utils/utils.hpp"

#include "menu/menu.hpp"

