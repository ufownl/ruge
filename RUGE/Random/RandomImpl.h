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

#ifndef _RUGE_RANDOMIMPL_H_
#define _RUGE_RANDOMIMPL_H_

#include "Random.h"

namespace RUGE
{

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

}

#endif  // _RANDOMIMPL_H_