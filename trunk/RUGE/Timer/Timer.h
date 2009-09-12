#pragma once

#ifndef _TIMER_H_
#define _TIMER_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL_
#include "TimerComDef.h"

typedef struct ITimer : public IUnknown
{
	STDMETHOD_(DWORD, Start)() PURE;
	STDMETHOD_(DWORD, GetDelta)() PURE;
} *PITIMER;

_COM_SMARTPTR_TYPEDEF(ITimer, __uuidof(ITimer));

#endif  // _TIMER_H_