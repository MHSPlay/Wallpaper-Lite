#pragma once

// windows / stl includes.
#include <Windows.h>
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <functional>
#include <map>
#include <shlobj.h>
#include <filesystem>
#include <streambuf>
#include <dwmapi.h>
#include <direct.h> 
#include <tlhelp32.h>
#include <WinUser.h>
#include <optional>
#include <shlwapi.h>
#include <shobjidl.h>
#include <comdef.h>
#pragma comment(lib, "shlwapi.lib")

using namespace std;

// imgui includes.
#define IMGUI_DEFINE_MATH_OPERATORS
#include "..\dependencies\imgui\imgui.h"
#include "..\dependencies\imgui\backends\imgui_impl_dx11.h"
#include "..\dependencies\imgui\backends\imgui_impl_win32.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// other includes.
#include "..\dependencies\stb_image.h"
#include "utils\utils.h"
#include "gui\gui.h"