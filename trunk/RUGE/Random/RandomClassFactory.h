#pragma once

#ifndef _RANDOMCLASSFACTORY_H_
#define _RANDOMCLASSFACTORY_H_

class CRandomClassFactory : public IClassFactory
{
public:
	CRandomClassFactory();
	virtual ~CRandomClassFactory();

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

#endif  // _RANDOMCLASSFACTORY_H_
