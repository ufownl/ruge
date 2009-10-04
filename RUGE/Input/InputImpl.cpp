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

#include "StdAfx.h"
#include "InputImpl.h"

#define WM_MOUSEWHEEL	0x020A
#define WHEEL_DELTA		120

LPCSTR CInputImpl::m_lpcszKeyNames[256]={
	"?", "Left Mouse Button", "Right Mouse Button", "?", "Middle Mouse Button",
	"?", "?", "?", "Backspace", "Tab", "?", "?", "?", "Enter", "?", "?",
	"Shift", "Ctrl", "Alt", "Pause", "Caps Lock", "?", "?", "?", "?", "?", "?",
	"Escape", "?", "?", "?", "?",
	"Space", "Page Up", "Page Down", "End", "Home",
	"Left Arrow", "Up Arrow", "Right Arrow", "Down Arrow",
	"?", "?", "?", "?", "Insert", "Delete", "?",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"?", "?", "?", "?", "?", "?", "?",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"Left Win", "Right Win", "Application", "?", "?",
	"NumPad 0", "NumPad 1", "NumPad 2", "NumPad 3", "NumPad 4",
	"NumPad 5", "NumPad 6", "NumPad 7", "NumPad 8", "NumPad 9",
	"Multiply", "Add", "?", "Subtract", "Decimal", "Divide",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"Num Lock", "Scroll Lock",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"Semicolon", "Equals", "Comma", "Minus", "Period", "Slash", "Grave",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?",
	"Left bracket", "Backslash", "Right bracket", "Apostrophe",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?"};

CInputImpl::CInputImpl()
	: m_uRefCount(0)
	, m_hWnd(NULL)
	, m_bMouseOver(FALSE)
	, m_fPosX(0)
	, m_fPosY(0)
	, m_nPosZ(0)
	, m_nVKLast(0)
	, m_chLast(0)
{
	memset(m_nKeyStates, 0, sizeof(m_nKeyStates));
	memset(m_nOldKeyStates, 0, sizeof(m_nOldKeyStates));
	g_uDllLockCount++;
}

CInputImpl::~CInputImpl()
{
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CInputImpl::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CInputImpl::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CInputImpl::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT hr=S_OK;

	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
	else if (InlineIsEqualGUID(riid, __uuidof(IInput))) *ppv=(IInput*)this;
	else hr=E_NOINTERFACE;
	if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
	return hr;
}

STDMETHODIMP CInputImpl::Initialize(HWND hWnd)
{
	m_hWnd=hWnd;

	POINT	point;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_fPosX=(float)point.x;
	m_fPosY=(float)point.y;

	return S_OK;
}

STDMETHODIMP_(BOOL) CInputImpl::KeyDown(int nVKey)
{
	if (GetFocus()!=m_hWnd) return FALSE;
	return m_nKeyStates[nVKey]<0 && m_nOldKeyStates[nVKey]>=0;
}

STDMETHODIMP_(BOOL) CInputImpl::KeyPressed(int nVKey)
{
	if (GetFocus()!=m_hWnd) return FALSE;
	return m_nKeyStates[nVKey]<0;
}

STDMETHODIMP_(BOOL) CInputImpl::KeyUp(int nVKey)
{
	if (GetFocus()!=m_hWnd) return FALSE;
	return m_nKeyStates[nVKey]>=0 && m_nOldKeyStates[nVKey]<0;
}

STDMETHODIMP_(int) CInputImpl::GetKey()
{
	return m_nVKLast;
}

STDMETHODIMP_(char) CInputImpl::GetChar()
{
	return m_chLast;
}

STDMETHODIMP_(LPCSTR) CInputImpl::GetKeyName(int nVKey)
{
	return m_lpcszKeyNames[nVKey];
}

STDMETHODIMP CInputImpl::GetMousePos(float *x, float *y)
{
	*x=m_fPosX;
	*y=m_fPosY;
	return S_OK;
}

STDMETHODIMP CInputImpl::SetMousePos(float x, float y)
{
	if (GetFocus()!=m_hWnd) return -1;

	POINT point={(LONG)x, (LONG)y};

	ClientToScreen(m_hWnd, &point);
	SetCursorPos(point.x, point.y);
	return S_OK;
}

STDMETHODIMP_(SHORT) CInputImpl::GetMouseWheel()
{
	return m_nPosZ;
}

STDMETHODIMP_(BOOL) CInputImpl::IsMouseOver()
{
	return m_bMouseOver;
}

STDMETHODIMP CInputImpl::Update()
{
	m_nVKLast=0;
	m_chLast=0;
	memcpy(m_nOldKeyStates, m_nKeyStates, sizeof(m_nKeyStates));
	for (int i=0; i<256; i++) m_nKeyStates[i]=GetKeyState(i);

	POINT	point;
	RECT	rect;

	GetCursorPos(&point);
	GetClientRect(m_hWnd, &rect);
	MapWindowPoints(m_hWnd, NULL, (LPPOINT)&rect, 2);
	m_bMouseOver=PtInRect(&rect, point) && WindowFromPoint(point)==m_hWnd;
	return S_OK;
}

STDMETHODIMP CInputImpl::OnWndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		m_nVKLast=(int)wParam;
		break;
	case WM_CHAR:
		m_chLast=(char)wParam;
		break;
	case WM_MOUSEMOVE:
		m_fPosX=LOWORD(lParam);
		m_fPosY=HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
		m_nPosZ+=(short)HIWORD(wParam)/WHEEL_DELTA;
		break;
	default:
		break;
	}
	return S_OK;
}
