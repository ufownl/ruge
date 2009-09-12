#pragma once

#ifndef _RANDOMIMPL_H_
#define _RANDOMIMPL_H_

#include "Random.h"

class CRandomImpl : public IRandom
{
public:
	CRandomImpl();
	virtual ~CRandomImpl();

	// IUnknown
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	// IRandom
	STDMETHOD(Randomize)(DWORD dwSeed);
	STDMETHOD_(int, Integer)(int nMin, int nMax);
	STDMETHOD_(float, Float)(float fMin, float fMax);

protected:
	ULONG m_uRefCount;
	DWORD m_dwSeed;
};

#endif  // _RANDOMIMPL_H_