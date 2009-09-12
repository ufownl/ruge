#pragma once

#ifndef _TIMERIMPL_H_
#define _TIMERIMPL_H_

#include "Timer.h"

class CTimerImpl : public ITimer
{
public:
	CTimerImpl();
	virtual ~CTimerImpl();

	// IUnknown
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	// ITimer
	STDMETHOD_(DWORD, Start)();
	STDMETHOD_(DWORD, GetDelta)();

protected:
	ULONG m_uRefCount;
	DWORD m_dwTicks;
};

#endif  // _TIMERIMPL_H_