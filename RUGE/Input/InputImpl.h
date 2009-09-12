#pragma once

#ifndef _INPUTIMPL_H_
#define _INPUTIMPL_H_

#include "Input.h"

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
	STDMETHOD_(BOOL, KeyDown)(int nVKey);
	STDMETHOD_(BOOL, KeyPress)(int nVKey);
	STDMETHOD_(BOOL, KeyUp)(int nVKey);
	STDMETHOD_(int, GetKey)();
	STDMETHOD_(char, GetChar)();
	STDMETHOD_(LPCSTR, GetKeyName)(int nVKey);

	STDMETHOD(GetMousePos)(float *x, float *y);
	STDMETHOD_(SHORT, GetMouseWheel)();

	STDMETHOD(OnWndEvent)(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	ULONG m_uRefCount;
	static LPCSTR m_lpcszKeyNames[256];
	SHORT m_nOldKeyStates[256];
	float m_fPosX, m_fPosY;
	SHORT m_nPosZ;
	int m_nVKLast;
	char m_chLast;
};

#endif  // _INPUTIMPL_H_