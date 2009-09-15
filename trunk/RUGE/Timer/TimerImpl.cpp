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

#include "StdAfx.h"
#include "TimerImpl.h"

CTimerImpl::CTimerImpl()
	: m_uRefCount(0)
	, m_dwTicks(0xFFFFFFFF)
{
	g_uDllLockCount++;
}

CTimerImpl::~CTimerImpl()
{
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CTimerImpl::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CTimerImpl::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CTimerImpl::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT hr=S_OK;

	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
	else if (InlineIsEqualGUID(riid, __uuidof(ITimer))) *ppv=(ITimer*)this;
	else hr=E_NOINTERFACE;
	if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
	return hr;
}

STDMETHODIMP_(DWORD) CTimerImpl::Start()
{
	m_dwTicks=GetTickCount();
	return m_dwTicks;
}

STDMETHODIMP_(DWORD) CTimerImpl::GetDelta()
{
	if (m_dwTicks==0xFFFFFFFF) Start();
	return GetTickCount()-m_dwTicks;
}
