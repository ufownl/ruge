/*
RUGE Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE.

RUGE is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	STDMETHOD(Initialize)(HWND hWnd) PURE;

	STDMETHOD_(BOOL, KeyDown)(int nVKey) PURE;
	STDMETHOD_(BOOL, KeyPressed)(int nVKey) PURE;
	STDMETHOD_(BOOL, KeyUp)(int nVKey) PURE;
	STDMETHOD_(int, GetKey)() PURE;
	STDMETHOD_(char, GetChar)() PURE;
	STDMETHOD_(LPCSTR, GetKeyName)(int nVKey) PURE;

	STDMETHOD(GetMousePos)(float *x, float *y) PURE;
	STDMETHOD(SetMousePos)(float x, float y) PURE;
	STDMETHOD_(SHORT, GetMouseWheel)() PURE;
	STDMETHOD_(BOOL, IsMouseOver)() PURE;

	STDMETHOD(Update)() PURE;
	STDMETHOD(OnWndEvent)(UINT uMsg, WPARAM wParam, LPARAM lParam) PURE;
} *PINPUT;

_COM_SMARTPTR_TYPEDEF(IInput, __uuidof(IInput));

#endif  // _INPUT_H_