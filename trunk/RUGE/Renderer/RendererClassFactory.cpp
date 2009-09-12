#include "StdAfx.h"
#include "RendererClassFactory.h"
#include "RendererImpl.h"

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