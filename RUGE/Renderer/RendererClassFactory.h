#pragma once

#ifndef _RENDERERCLASSFACTORY_H_
#define _RENDERERCLASSFACTORY_H_

class CRendererClassFactory : public IClassFactory
{
public:
	CRendererClassFactory();
	virtual ~CRendererClassFactory();

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

#endif  // _RENDERERCLASSFACTORY_H_
