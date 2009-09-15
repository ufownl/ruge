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