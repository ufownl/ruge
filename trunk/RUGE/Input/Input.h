#pragma once

#ifndef _INPUT_H_
#define _INPUT_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL
#include "InputComDef.h"

typedef struct IInput : public IUnknown
{
	STDMETHOD_(BOOL, KeyDown)(int nVKey) PURE;
	STDMETHOD_(BOOL, KeyPress)(int nVKey) PURE;
	STDMETHOD_(BOOL, KeyUp)(int nVKey) PURE;
	STDMETHOD_(int, GetKey)() PURE;
	STDMETHOD_(char, GetChar)() PURE;
	STDMETHOD_(LPCSTR, GetKeyName)(int nVKey) PURE;

	STDMETHOD(GetMousePos)(float *x, float *y) PURE;
	STDMETHOD_(SHORT, GetMouseWheel)() PURE;

	STDMETHOD(OnWndEvent)(UINT uMsg, WPARAM wParam, LPARAM lParam) PURE;
} *PINPUT;

_COM_SMARTPTR_TYPEDEF(IInput, __uuidof(IInput));

#endif  // _INPUT_H_