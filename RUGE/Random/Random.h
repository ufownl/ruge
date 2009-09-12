#pragma once

#ifndef _RANDOM_H_
#define _RANDOM_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL_
#include "RandomComDef.h"

typedef struct IRandom : public IUnknown
{
	STDMETHOD(Randomize)(DWORD dwSeed) PURE;
	STDMETHOD_(int, Integer)(int nMin, int nMax) PURE;
	STDMETHOD_(float, Float)(float fMin, float fMax) PURE;
} *PRANDOM;

_COM_SMARTPTR_TYPEDEF(IRandom, __uuidof(IRandom));

#endif  // _RANDOM_H_