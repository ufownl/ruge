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
