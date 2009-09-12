#include "StdAfx.h"
#include "RandomImpl.h"

CRandomImpl::CRandomImpl()
	: m_uRefCount(0)
	, m_dwSeed(0)
{
	g_uDllLockCount++;
}

CRandomImpl::~CRandomImpl()
{
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CRandomImpl::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CRandomImpl::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CRandomImpl::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT hr=S_OK;

	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
	else if (InlineIsEqualGUID(riid, __uuidof(IRandom))) *ppv=(IRandom*)this;
	else hr=E_NOINTERFACE;
	if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
	return hr;
}

STDMETHODIMP CRandomImpl::Randomize(DWORD dwSeed)
{
	m_dwSeed=dwSeed;
	return S_OK;
}

STDMETHODIMP_(int) CRandomImpl::Integer(int nMin, int nMax)
{
	m_dwSeed=214013*m_dwSeed+2531011;
	return nMin+(m_dwSeed^m_dwSeed>>15)%(nMax-nMin+1);
}

STDMETHODIMP_(float) CRandomImpl::Float(float fMin, float fMax)
{
	m_dwSeed=214013*m_dwSeed+2531011;
	return fMin+(m_dwSeed>>16)*(1.0f/65535.0f)*(fMax-fMin);
}