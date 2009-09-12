#pragma once

#ifndef _APPLICATIONCLASSFACTORY_H_
#define _APPLICATIONCLASSFACTORY_H_

class CApplicationClassFactory : public IClassFactory
{
public:
	CApplicationClassFactory();
	virtual ~CApplicationClassFactory();

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

#endif  // _APPLICATIONCLASSFACTORY_H_
