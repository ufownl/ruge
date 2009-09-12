#include "StdAfx.h"

#define RUGE_EXPORT _declspec(dllexport)
#include "RUGE.h"

PAPPLICATION pApp;

PAPPLICATION GetRUGE(DWORD dwVer)
{
	if (dwVer!=RUGE_VERSION) return NULL;
	if (pApp==NULL)
	{
		if (FAILED(CoCreateInstance(__uuidof(CApplicationImpl), NULL, CLSCTX_ALL,
			__uuidof(IApplication), (void**)&pApp))) return NULL;
	}
	else pApp->AddRef();
	return pApp;
}