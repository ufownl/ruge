#include "StdAfx.h"
#include "TimerClassFactory.h"
#include "TimerImpl.h"

CTimerClassFactory::CTimerClassFactory()
	: m_uRefCount(0)
{
	g_uDllLockCount++;
}

CTimerClassFactory::~CTimerClassFactory()
{
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CTimerClassFactory::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CTimerClassFactory::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CTimerClassFactory::QueryInterface(REFIID riid, void** ppv)
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

STDMETHODIMP CTimerClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	HRESULT hr;
	CTimerImpl* pImpl;

	if (pUnkOuter!=NULL) return CLASS_E_NOAGGREGATION;
	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	pImpl=new CTimerImpl;
	hr=pImpl->QueryInterface(riid, ppv);
	if (FAILED(hr)) delete pImpl;
	return hr;
}

STDMETHODIMP CTimerClassFactory::LockServer (BOOL bLock)
{
	bLock ? g_uDllLockCount++ : g_uDllLockCount--;
	return S_OK;
}