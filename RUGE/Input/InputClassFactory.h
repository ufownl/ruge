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

#ifndef _RUGE_INPUTCLASSFACTORY_H_
#define _RUGE_INPUTCLASSFACTORY_H_

namespace RUGE
{

	class CInputClassFactory : public IClassFactory
	{
	public:
		CInputClassFactory();
		virtual ~CInputClassFactory();

		// IUnknown
		STDMETHOD_(ULONG, AddRef)();
		STDMETHOD_(ULONG, Release)();
		STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

		// IClassFactory
		STDMETHOD(CreateInstance)(IUnknown* pUnkOuter, REFIID riid, void** ppv);
		STDMETHOD(LockServer)(BOOL fLock);

	protected:
		ULONG m_uRefCount;
	};

}

#endif  // _RUGE_INPUTCLASSFACTORY_H_
