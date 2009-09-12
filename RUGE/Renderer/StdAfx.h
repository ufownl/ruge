#pragma once

#define _RUGE_IMPL_

#include <windows.h>
#include <comdef.h>
#include <tchar.h>
#include <assert.h>

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif  // _DEBUG
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "..\\Timer\\Timer.h"

extern HINSTANCE g_hinstThisDll;
extern UINT g_uDllLockCount;