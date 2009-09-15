/*
RUGE Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE.

RUGE is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "ApplicationComDef.h"
#include "ApplicationClassFactory.h"

HINSTANCE g_hinstThisDll=NULL;
UINT g_uDllLockCount=0;

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		g_hinstThisDll=hModule;
		DisableThreadLibraryCalls(hModule);
		break;
	default:
		break;
	}
	return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	CApplicationClassFactory* pFactory;

	if (!InlineIsEqualGUID(rclsid, __uuidof(CApplicationImpl))) return CLASS_E_CLASSNOTAVAILABLE;
	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	pFactory=new CApplicationClassFactory;
	pFactory->AddRef();
	hr=pFactory->QueryInterface(riid, ppv);
	pFactory->Release();
	return hr;
}

STDAPI DllCanUnloadNow()
{
	return g_uDllLockCount>0 ? S_FALSE : S_OK;
}

STDAPI DllRegisterServer()
{
	HKEY hCLSIDKey=NULL, hInProcSvrKey=NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[]=_T("Application class");
	TCHAR szThreadingModel[]=_T("Apartment");

	__try
	{
		lRet=RegCreateKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{B6B25D5F-96D1-41ba-B587-34596A6D38D7}"),
			0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY,
			NULL, &hCLSIDKey, NULL);
		if (lRet!=ERROR_SUCCESS) return HRESULT_FROM_WIN32(lRet);

		lRet=RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*)szClassDescription,
			sizeof(szClassDescription));
		if (lRet!=ERROR_SUCCESS) return HRESULT_FROM_WIN32(lRet);

		lRet = RegCreateKeyEx ( hCLSIDKey, _T("InProcServer32"), 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_SET_VALUE, NULL, &hInProcSvrKey, NULL );
		if (lRet!=ERROR_SUCCESS) return HRESULT_FROM_WIN32(lRet);

		GetModuleFileName ( g_hinstThisDll, szModulePath, MAX_PATH );

		lRet=RegSetValueEx(hInProcSvrKey, NULL, 0, REG_SZ, (const BYTE*)szModulePath, 
			sizeof(TCHAR)*(lstrlen(szModulePath)+1));
		if (lRet!=ERROR_SUCCESS) return HRESULT_FROM_WIN32(lRet);

		lRet=RegSetValueEx (hInProcSvrKey, _T("ThreadingModel"), 0, REG_SZ,
			(const BYTE*)szThreadingModel, sizeof(szThreadingModel));
		if (lRet!=ERROR_SUCCESS) return HRESULT_FROM_WIN32(lRet);
	}   
	__finally
	{
		if (hCLSIDKey!=NULL) RegCloseKey(hCLSIDKey);
		if (hInProcSvrKey!=NULL) RegCloseKey(hInProcSvrKey);
	}
	return S_OK;
}

STDAPI DllUnregisterServer()
{
	RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{B6B25D5F-96D1-41ba-B587-34596A6D38D7}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{B6B25D5F-96D1-41ba-B587-34596A6D38D7}"));
	return S_OK;
}