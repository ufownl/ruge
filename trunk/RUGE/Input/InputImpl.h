/*
RUGE Copyright (C) 2009 ����UFO

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

#ifndef _RUGE_INPUTIMPL_H_
#define _RUGE_INPUTIMPL_H_

#include "Input.h"

namespace RUGE
{

	class CInputImpl : public IInput
	{
	public:
		CInputImpl();
		virtual ~CInputImpl();

		// IUnknown
		STDMETHOD_(ULONG, AddRef)();
		STDMETHOD_(ULONG, Release)();
		STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

		// IInput
		STDMETHOD(Initialize)(HWND hWnd);

		STDMETHOD_(BOOL, KeyDown)(int nVKey);
		STDMETHOD_(BOOL, KeyPressed)(int nVKey);
		STDMETHOD_(BOOL, KeyUp)(int nVKey);
		STDMETHOD_(int, GetKey)();
		STDMETHOD_(char, GetChar)();
		STDMETHOD_(LPCSTR, GetKeyName)(int nVKey);

		STDMETHOD(GetMousePos)(float *x, float *y);
		STDMETHOD(SetMousePos)(float x, float y);
		STDMETHOD_(SHORT, GetMouseWheel)();
		STDMETHOD_(BOOL, IsMouseOver)();

		STDMETHOD(Update)();
		STDMETHOD(OnWndEvent)(UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		ULONG m_uRefCount;
		static LPCSTR m_lpcszKeyNames[256];
		HWND m_hWnd;
		SHORT m_nKeyStates[256], m_nOldKeyStates[256];
		BOOL m_bMouseOver;
		float m_fPosX, m_fPosY;
		SHORT m_nPosZ;
		int m_nVKLast;
		char m_chLast;
	};

}

#endif  // _RUGE_INPUTIMPL_H_