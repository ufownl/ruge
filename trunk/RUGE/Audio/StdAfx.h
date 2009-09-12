#pragma once

#define _RUGE_IMPL_

#include <windows.h>
#include <comdef.h>
#include <tchar.h>
#include <assert.h>

#include <Fmod.hpp>
#pragma comment(lib, "fmodex_vc.lib")

extern HINSTANCE g_hinstThisDll;
extern UINT g_uDllLockCount;