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