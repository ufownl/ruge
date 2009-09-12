#pragma once

#ifndef _TIMERCLASSFACTORY_H_
#define _TIMERCLASSFACTORY_H_

class CTimerClassFactory : public IClassFactory
{
public:
	CTimerClassFactory();
	virtual ~CTimerClassFactory();

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

#endif  // _TIMERCLASSFACTORY_H_
