#pragma once

#define _RUGE_IMPL_

#include <windows.h>
#include <comdef.h>
#include <tchar.h>
#include <assert.h>

#include "..\\Renderer\\Renderer.h"
#include "..\\Audio\\Audio.h"
#include "..\\Input\\Input.h"
#include "..\\Timer\\Timer.h"

extern HINSTANCE g_hinstThisDll;
extern UINT g_uDllLockCount;