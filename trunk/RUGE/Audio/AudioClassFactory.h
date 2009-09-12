#pragma once

#ifndef _AUDIOCLASSFACTORY_H_
#define _AUDIOCLASSFACTORY_H_

class CAudioClassFactory : public IClassFactory
{
public:
	CAudioClassFactory();
	virtual ~CAudioClassFactory();

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

#endif  // _AUDIOCLASSFACTORY_H_
