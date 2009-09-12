#include "StdAfx.h"
#include "AudioComDef.h"
#include "AudioClassFactory.h"

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
	CAudioClassFactory* pFactory;

	if (!InlineIsEqualGUID(rclsid, __uuidof(CAudioImpl))) return CLASS_E_CLASSNOTAVAILABLE;
	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	pFactory=new CAudioClassFactory;
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
	TCHAR szClassDescription[]=_T("Audio class");
	TCHAR szThreadingModel[]=_T("Apartment");

	__try
	{
		lRet=RegCreateKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{09D26750-ECD1-4641-A767-3771A5838ADE}"),
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
	RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{09D26750-ECD1-4641-A767-3771A5838ADE}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{09D26750-ECD1-4641-A767-3771A5838ADE}"));
	return S_OK;
}