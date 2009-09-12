#pragma once

#ifndef _INPUTCLASSFACTORY_H_
#define _INPUTCLASSFACTORY_H_

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

#endif  // _INPUTCLASSFACTORY_H_
