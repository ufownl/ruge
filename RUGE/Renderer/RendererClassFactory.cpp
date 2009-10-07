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

#include "StdAfx.h"
#include "RendererClassFactory.h"
#include "RendererImpl.h"

namespace RUGE
{

	CRendererClassFactory::CRendererClassFactory()
		: m_uRefCount(0)
	{
		g_uDllLockCount++;
	}

	CRendererClassFactory::~CRendererClassFactory()
	{
		g_uDllLockCount--;
	}

	STDMETHODIMP_(ULONG) CRendererClassFactory::AddRef()
	{
		return ++m_uRefCount;
	}

	STDMETHODIMP_(ULONG) CRendererClassFactory::Release()
	{
		ULONG uRet=--m_uRefCount;

		if (m_uRefCount==0) delete this;
		return uRet;
	}

	STDMETHODIMP CRendererClassFactory::QueryInterface(REFIID riid, void** ppv)
	{
		HRESULT hr=S_OK;

		if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
		*ppv=NULL;
		if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
		else if (InlineIsEqualGUID(riid, IID_IClassFactory)) *ppv=(IClassFactory*)this;
		else hr=E_NOINTERFACE;
		if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
		return hr;
	}

	STDMETHODIMP CRendererClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
	{
		HRESULT hr;
		CRendererImpl* pImpl;

		if (pUnkOuter!=NULL) return CLASS_E_NOAGGREGATION;
		if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
		*ppv=NULL;
		pImpl=new CRendererImpl;
		hr=pImpl->QueryInterface(riid, ppv);
		if (FAILED(hr)) delete pImpl;
		return hr;
	}

	STDMETHODIMP CRendererClassFactory::LockServer (BOOL bLock)
	{
		bLock ? g_uDllLockCount++ : g_uDllLockCount--;
		return S_OK;
	}

}