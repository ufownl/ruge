#include "StdAfx.h"
#include "AudioClassFactory.h"
#include "AudioImpl.h"

CAudioClassFactory::CAudioClassFactory()
	: m_uRefCount(0)
{
	g_uDllLockCount++;
}

CAudioClassFactory::~CAudioClassFactory()
{
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CAudioClassFactory::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CAudioClassFactory::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CAudioClassFactory::QueryInterface(REFIID riid, void** ppv)
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

STDMETHODIMP CAudioClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	HRESULT hr;
	CAudioImpl* pImpl;

	if (pUnkOuter!=NULL) return CLASS_E_NOAGGREGATION;
	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	pImpl=new CAudioImpl;
	hr=pImpl->QueryInterface(riid, ppv);
	if (FAILED(hr)) delete pImpl;
	return hr;
}

STDMETHODIMP CAudioClassFactory::LockServer (BOOL bLock)
{
	bLock ? g_uDllLockCount++ : g_uDllLockCount--;
	return S_OK;
}