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
#include "ApplicationImpl.h"

namespace RUGE
{

	CApplicationImpl *CApplicationImpl::m_pThis=NULL;

	CApplicationImpl::CApplicationImpl()
		: m_uRefCount(0)
		, m_lpcszCaption("RangerUFO's Game Engine")
		, m_lpcszIcon(NULL)
		, m_lpcszIniFile(NULL)
		, m_bHideCursor(FALSE)
		, m_bActive(FALSE)
		, m_bNotSuspend(FALSE)
		, m_pEventHandler(NULL)
		, m_hWnd(NULL)
		, m_fTime(0)
		, m_fDelta(0)
		, m_nFPS(0)
	{
		assert(m_pThis==NULL);
		m_pThis=this;
		g_uDllLockCount++;
		memset(m_szIniBuf, 0, sizeof(m_szIniBuf));
		m_pRenderer.CreateInstance(__uuidof(CRendererImpl));
		m_pAudio.CreateInstance(__uuidof(CAudioImpl));
		m_pInput.CreateInstance(__uuidof(CInputImpl));
		m_pTimer.CreateInstance(__uuidof(CTimerImpl));
		m_pRand.CreateInstance(__uuidof(CRandomImpl));
	}

	CApplicationImpl::~CApplicationImpl()
	{
		m_pThis=NULL;
		g_uDllLockCount--;
	}

	STDMETHODIMP_(ULONG) CApplicationImpl::AddRef()
	{
		return ++m_uRefCount;
	}

	STDMETHODIMP_(ULONG) CApplicationImpl::Release()
	{
		ULONG uRet=--m_uRefCount;

		if (m_uRefCount==0) delete this;
		return uRet;
	}

	STDMETHODIMP CApplicationImpl::QueryInterface(REFIID riid, void** ppv)
	{
		HRESULT hr=S_OK;

		if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
		*ppv=NULL;
		if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
		else if (InlineIsEqualGUID(riid, __uuidof(IApplication))) *ppv=(IApplication*)this;
		else hr=E_NOINTERFACE;
		if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
		return hr;
	}

	STDMETHODIMP CApplicationImpl::System_SetState(AppStringState State, LPCSTR lpcszVal)
	{
		switch (State)
		{
		case APP_CAPTION:
			m_lpcszCaption=lpcszVal;
			if (m_hWnd!=NULL) SetWindowText(m_hWnd, m_lpcszCaption);
			break;
		case APP_ICON:
			m_lpcszIcon=lpcszVal;
			if (m_hWnd!=NULL) SetClassLong(m_hWnd, GCL_HICON, (LONG)(LONG_PTR)LoadIcon(GetModuleHandle(NULL), m_lpcszIcon));
			break;
		case APP_INIFILE:
			m_lpcszIniFile=lpcszVal;
			break;
		}
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::System_SetState(AppIntState State, int nVal)
	{
		switch (State)
		{
		case APP_WIDTH:
			return m_pRenderer->SetState(RENDERER_WIDTH, nVal);
		case APP_HEIGHT:
			return m_pRenderer->SetState(RENDERER_HEIGHT, nVal);
		case APP_MAXCHANNELS:
			return m_pAudio->SetState(AUDIO_MAXCHANNELS, nVal);
		}
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::System_SetState(AppBoolState State, BOOL bVal)
	{
		switch (State)
		{
		case APP_WINDOWED:
			return m_pRenderer->SetState(RENDERER_WINDOWED, bVal);
		case APP_HIDECURSOR:
			m_bHideCursor=bVal;
			break;
		case APP_NOTSUSPEND:
			m_bNotSuspend=bVal;
			break;
		}
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::System_SetState(AppDwordState State, DWORD dwVal)
	{
		switch (State)
		{
		case APP_VSYNC:
			return m_pRenderer->SetState(RENDERER_VSYNC, dwVal);
		case APP_MAGFILTER:
			return m_pRenderer->SetState(RENDERER_MAGFILTER, dwVal);
		case APP_MINFILTER:
			return m_pRenderer->SetState(RENDERER_MINFILTER, dwVal);
		}
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::System_SetState(AppEventHandlerState State, PAPPLICATIONEVENTHANDLER pVal)
	{
		switch (State)
		{
		case APP_EVENTHANDLER:
			if (m_pEventHandler==NULL)
			{
				m_pEventHandler=pVal;
				m_pRenderer->SetState(RENDERER_EVENTHANDLER, m_pEventHandler);
			}
			break;
		}
		return S_OK;
	}

	STDMETHODIMP_(LPCSTR) CApplicationImpl::System_GetState(AppStringState State)
	{
		switch (State)
		{
		case APP_CAPTION:
			return m_lpcszCaption;
		case APP_ICON:
			return m_lpcszIcon;
		case APP_INIFILE:
			return m_lpcszIniFile;
		}
		return NULL;
	}

	STDMETHODIMP_(int) CApplicationImpl::System_GetState(AppIntState State)
	{
		switch (State)
		{
		case APP_WIDTH:
			return m_pRenderer->GetState(RENDERER_WIDTH);
		case APP_HEIGHT:
			return m_pRenderer->GetState(RENDERER_HEIGHT);
		case APP_MAXCHANNELS:
			return m_pAudio->GetState(AUDIO_MAXCHANNELS);
		}
		return 0;
	}

	STDMETHODIMP_(BOOL) CApplicationImpl::System_GetState(AppBoolState State)
	{
		switch (State)
		{
		case APP_WINDOWED:
			return m_pRenderer->GetState(RENDERER_WINDOWED);
		case APP_DEVICELOST:
			return m_pRenderer->GetState(RENDERER_DEVICELOST);
		case APP_ACTIVE:
			return m_bActive;
		case APP_HIDECURSOR:
			return m_bHideCursor;
		case APP_NOTSUSPEND:
			return m_bNotSuspend;
		}
		return FALSE;
	}

	STDMETHODIMP_(DWORD) CApplicationImpl::System_GetState(AppDwordState State)
	{
		switch (State)
		{
		case APP_VSYNC:
			return m_pRenderer->GetState(RENDERER_VSYNC);
		case APP_MAGFILTER:
			return m_pRenderer->GetState(RENDERER_MAGFILTER);
		case APP_MINFILTER:
			return m_pRenderer->GetState(RENDERER_MINFILTER);
		}
		return 0;
	}

	STDMETHODIMP_(PAPPLICATIONEVENTHANDLER) CApplicationImpl::System_GetState(AppEventHandlerState State)
	{
		switch (State)
		{
		case APP_EVENTHANDLER:
			return m_pEventHandler;
		}
		return NULL;
	}

	STDMETHODIMP_(HANDLE) CApplicationImpl::System_GetState(AppHandleState State)
	{
		switch (State)
		{
		case APP_DEVICE:
			return m_pRenderer->GetState(RENDERER_DEVICE);
		case APP_MAINWINDOW:
			return m_hWnd;
		}
		return NULL;
	}

	STDMETHODIMP CApplicationImpl::System_Initialize()
	{
		SYSTEMTIME		SysTime;
		OSVERSIONINFO	OSVer;
		MEMORYSTATUS	MemStatus;

		fprintf(stderr, "RUGE Started..\n\nRUGE Version: 2.7\n");
		GetLocalTime(&SysTime);
		fprintf(stderr, "Date: %02d-%02d-%02d, %02d:%02d:%02d\n\n", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
		fprintf(stderr, "Application: %s\n", m_lpcszCaption);
		OSVer.dwOSVersionInfoSize=sizeof(OSVer);
		GetVersionEx(&OSVer);
		fprintf(stderr, "OS: Windows %u.%u.%u\n", OSVer.dwMajorVersion, OSVer.dwMinorVersion, OSVer.dwBuildNumber);
		GlobalMemoryStatus(&MemStatus);
		fprintf(stderr, "Memory: %uKB Total, %uKB Free\n\n", MemStatus.dwTotalPhys/1024, MemStatus.dwAvailPhys/1024);

		HINSTANCE hInstance=GetModuleHandle(NULL);
		int nWidth=m_pRenderer->GetState(RENDERER_WIDTH), nHeight=m_pRenderer->GetState(RENDERER_HEIGHT);
		WNDCLASS wc;

		wc.style=CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
		wc.lpfnWndProc=WndProc;
		wc.cbClsExtra=0;
		wc.cbWndExtra=0;
		wc.hInstance=hInstance;
		wc.hIcon=LoadIcon(hInstance, m_lpcszIcon);
		wc.hCursor=NULL;
		wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName=NULL;
		wc.lpszClassName="Application";
		if (!RegisterClass(&wc))
		{
			fprintf(stderr, "Can't register window class.\n");
			return -1;
		}
		m_hWnd=CreateWindow("Application", m_lpcszCaption, WS_CAPTION|WS_SYSMENU|WS_BORDER|WS_MINIMIZEBOX, CW_USEDEFAULT
			, CW_USEDEFAULT, nWidth+GetSystemMetrics(SM_CXFIXEDFRAME)*2, nHeight+GetSystemMetrics(SM_CYFIXEDFRAME)*2+GetSystemMetrics(SM_CYCAPTION)
			, NULL, NULL, hInstance, NULL);
		if (m_hWnd==NULL)
		{
			fprintf(stderr, "Can't create window.\n");
			return -1;
		}
		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);

		HRESULT hr=m_pRenderer->Initialize(m_hWnd);

		if (FAILED(hr)) return hr;
		hr=m_pAudio->Initialize();
		if (FAILED(hr)) return hr;
		hr=m_pInput->Initialize(m_hWnd);
		if (FAILED(hr)) return hr;
		if (m_pEventHandler!=NULL)
		{
			hr=m_pEventHandler->InitResource();
			if (FAILED(hr)) return hr;
		}
		fprintf(stderr, "Init done.\n\n");
		m_pTimer->Start();
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::System_Run()
	{
		MSG Msg;

		do
		{
			if (m_bActive || m_bNotSuspend)
			{
				if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
				else
				{
					static float fElapsed=0;
					static int nFrames=0;
					DWORD dwDelta;

					do
					{
						dwDelta=m_pTimer->GetDelta();
					} while (dwDelta==0);
					m_pTimer->Start();
					m_fDelta=(float)dwDelta/1000;
					m_fTime+=m_fDelta;
					fElapsed+=m_fDelta;
					nFrames++;
					if (fElapsed>=1)
					{
						m_nFPS=nFrames;
						fElapsed=0;
						nFrames=0;
					}
					if (m_pEventHandler!=NULL)
					{
						if (m_pEventHandler->Frame(m_fDelta)) PostQuitMessage(0);
					}

					HRESULT hr=m_pRenderer->RendererLoop();

					if (FAILED(hr)) PostQuitMessage(hr);
					hr=m_pAudio->Update();
					if (FAILED(hr)) PostQuitMessage(hr);
					hr=m_pInput->Update();
					if (FAILED(hr)) PostQuitMessage(hr);
				}
			}
			else
			{
				GetMessage(&Msg, NULL, 0, 0);
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
				m_pTimer->Start();
			}
		} while (Msg.message!=WM_QUIT);
		fprintf(stderr, "\nFinishing..\n");
		if (m_pEventHandler!=NULL) m_pEventHandler->ReleaseResource();
		fprintf(stderr, "The End.\n");
		return (HRESULT)Msg.wParam;
	}

	STDMETHODIMP CApplicationImpl::Ini_SetInt(LPCSTR lpcszSection, LPCSTR lpcszName, int nVal)
	{
		if (m_lpcszIniFile==NULL) return E_POINTER;
		sprintf(m_szIniBuf, "%d", nVal);
		if (!WritePrivateProfileString(lpcszSection, lpcszName, m_szIniBuf, m_lpcszIniFile)) return -1;
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::Ini_SetFloat(LPCSTR lpcszSection, LPCSTR lpcszName, float fVal)
	{
		if (m_lpcszIniFile==NULL) return E_POINTER;
		sprintf(m_szIniBuf, "%f", fVal);
		if (!WritePrivateProfileString(lpcszSection, lpcszName, m_szIniBuf, m_lpcszIniFile)) return -1;
		return S_OK;
	}

	STDMETHODIMP CApplicationImpl::Ini_SetString(LPCSTR lpcszSection, LPCSTR lpcszName, LPCSTR lpcszVal)
	{
		if (m_lpcszIniFile==NULL) return E_POINTER;
		if (!WritePrivateProfileString(lpcszSection, lpcszName, lpcszVal, m_lpcszIniFile)) return -1;
		return S_OK;
	}

	STDMETHODIMP_(int) CApplicationImpl::Ini_GetInt(LPCSTR lpcszSection, LPCSTR lpcszName, int nDef/* =0 */)
	{
		if (m_lpcszIniFile!=NULL && GetPrivateProfileString(lpcszSection, lpcszName,
			NULL, m_szIniBuf, sizeof(m_szIniBuf), m_lpcszIniFile)) return atoi(m_szIniBuf);
		return nDef;
	}

	STDMETHODIMP_(float) CApplicationImpl::Ini_GetFloat(LPCSTR lpcszSection, LPCSTR lpcszName, float fDef/* =0 */)
	{
		if (m_lpcszIniFile!=NULL && GetPrivateProfileString(lpcszSection, lpcszName,
			NULL, m_szIniBuf, sizeof(m_szIniBuf), m_lpcszIniFile)) return (float)atof(m_szIniBuf);
		return fDef;
	}

	STDMETHODIMP_(LPCSTR) CApplicationImpl::Ini_GetString(LPCSTR lpcszSection, LPCSTR lpcszName, LPCSTR lpcszDef/* =NULL */)
	{
		if (m_lpcszIniFile!=NULL && GetPrivateProfileString(lpcszSection, lpcszName,
			NULL, m_szIniBuf, sizeof(m_szIniBuf), m_lpcszIniFile)) return m_szIniBuf;
		return lpcszDef;
	}

	STDMETHODIMP CApplicationImpl::Gfx_BeginTarget(HTARGET hTarg)
	{
		return m_pRenderer->BeginTarget(hTarg);
	}

	STDMETHODIMP CApplicationImpl::Gfx_EndTarget()
	{
		return m_pRenderer->EndTarget();
	}

	STDMETHODIMP CApplicationImpl::Gfx_Clear(DWORD dwColor/* =0 */)
	{
		return m_pRenderer->Clear(dwColor);
	}

	STDMETHODIMP CApplicationImpl::Gfx_RenderLine(PVERTEX pV1, PVERTEX pV2, DWORD dwBlend/* =BLEND_DEFAULT */)
	{
		return m_pRenderer->RenderLine(pV1, pV2, dwBlend);
	}

	STDMETHODIMP CApplicationImpl::Gfx_RenderTriangle(PTRIANGLE pTriangle)
	{
		return m_pRenderer->RenderTriangle(pTriangle);
	}

	STDMETHODIMP CApplicationImpl::Gfx_RenderQuad(PQUAD pQuad)
	{
		return m_pRenderer->RenderQuad(pQuad);
	}

	STDMETHODIMP CApplicationImpl::Gfx_Shotsnap(LPCSTR lpcszPath, DWORD dwIFF/* =IFF_BMP */)
	{
		return m_pRenderer->Shotsnap(lpcszPath, dwIFF);
	}

	STDMETHODIMP_(HTEXTURE) CApplicationImpl::Texture_Create(int nWidth, int nHeight)
	{
		return m_pRenderer->Texture_Create(nWidth, nHeight);
	}

	STDMETHODIMP_(HTEXTURE) CApplicationImpl::Texture_Load(LPCSTR lpcszPath)
	{
		return m_pRenderer->Texture_Load(lpcszPath);
	}

	STDMETHODIMP CApplicationImpl::Texture_Free(HTEXTURE hTex)
	{
		return m_pRenderer->Texture_Free(hTex);
	}

	STDMETHODIMP_(void*) CApplicationImpl::Texture_Lock(HTEXTURE hTex, BOOL bReadOnly/* =TRUE */,
		int x/* =0 */, int y/* =0 */, int w/* =0 */, int h/* =0 */)
	{
		return m_pRenderer->Texture_Lock(hTex, bReadOnly, x, y, w, h);
	}

	STDMETHODIMP CApplicationImpl::Texture_Unlock(HTEXTURE hTex)
	{
		return m_pRenderer->Texture_Unlock(hTex);
	}

	STDMETHODIMP_(int) CApplicationImpl::Texture_GetWidth(HTEXTURE hTex)
	{
		return m_pRenderer->Texture_GetWidth(hTex);
	}

	STDMETHODIMP_(int) CApplicationImpl::Texture_GetHeight(HTEXTURE hTex)
	{
		return m_pRenderer->Texture_GetHeight(hTex);
	}

	STDMETHODIMP_(HTARGET) CApplicationImpl::Target_Create(int nWidth, int nHeight)
	{
		return m_pRenderer->Target_Create(nWidth, nHeight);
	}

	STDMETHODIMP CApplicationImpl::Target_Free(HTARGET hTarg)
	{
		return m_pRenderer->Target_Free(hTarg);
	}

	STDMETHODIMP_(HTEXTURE) CApplicationImpl::Target_GetTexture(HTARGET hTarg)
	{
		return m_pRenderer->Target_GetTexture(hTarg);
	}

	STDMETHODIMP_(HFONT) CApplicationImpl::Font_Create(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont)
	{
		return m_pRenderer->Font_Create(nHeight, nWidth, nWeight, bItalic, lpcszFont);
	}

	STDMETHODIMP CApplicationImpl::Font_Free(HFONT hFont)
	{
		return m_pRenderer->Font_Free(hFont);
	}

	STDMETHODIMP_(int) CApplicationImpl::Font_DrawText(HFONT hFont, LPCSTR lpcszText, LPRECT lpRect,
		float z/* =0.0f */, DWORD dwFormat/* =DT_TOP|DT_LEFT */, DWORD dwColor/* =0xFFFFFFFF */)
	{
		return m_pRenderer->Font_DrawText(hFont, lpcszText, lpRect, z, dwFormat, dwColor);
	}

	STDMETHODIMP_(BOOL) CApplicationImpl::Input_KeyDown(int nVKey)
	{
		return m_pInput->KeyDown(nVKey);
	}

	STDMETHODIMP_(BOOL) CApplicationImpl::Input_KeyPressed(int nVKey)
	{
		return m_pInput->KeyPressed(nVKey);
	}

	STDMETHODIMP_(BOOL) CApplicationImpl::Input_KeyUp(int nVKey)
	{
		return m_pInput->KeyUp(nVKey);
	}

	STDMETHODIMP_(int) CApplicationImpl::Input_GetKey()
	{
		return m_pInput->GetKey();
	}

	STDMETHODIMP_(char) CApplicationImpl::Input_GetChar()
	{
		return m_pInput->GetChar();
	}

	STDMETHODIMP_(LPCSTR) CApplicationImpl::Input_GetKeyName(int nVKey)
	{
		return m_pInput->GetKeyName(nVKey);
	}

	STDMETHODIMP CApplicationImpl::Input_GetMousePos(float *x, float *y)
	{
		return m_pInput->GetMousePos(x, y);
	}

	STDMETHODIMP CApplicationImpl::Input_SetMousePos(float x, float y)
	{
		return m_pInput->SetMousePos(x, y);
	}

	STDMETHODIMP_(SHORT) CApplicationImpl::Input_GetMouseWheel()
	{
		return m_pInput->GetMouseWheel();
	}

	STDMETHODIMP_(BOOL) CApplicationImpl::Input_IsMouseOver()
	{
		return m_pInput->IsMouseOver();
	}

	STDMETHODIMP_(HAUDIO) CApplicationImpl::Effect_Load(LPCSTR lpcszPath)
	{
		return m_pAudio->Effect_Load(lpcszPath);
	}

	STDMETHODIMP_(HCHANNEL) CApplicationImpl::Effect_Play(HAUDIO hAudio, int nVolume/* =100 */, int nPan/* =0 */,
		float fPitch/* =1.0f */, BOOL bLoop/* =FALSE */)
	{
		return m_pAudio->Effect_Play(hAudio, nVolume, nPan, fPitch, bLoop);
	}

	STDMETHODIMP_(HAUDIO) CApplicationImpl::Music_Load(LPCSTR lpcszPath)
	{
		return m_pAudio->Music_Load(lpcszPath);
	}

	STDMETHODIMP_(HCHANNEL) CApplicationImpl::Music_Play(HAUDIO hAudio, int nVolume/* =100 */, float fStart/* =0.0f */, BOOL bLoop/* =TRUE */)
	{
		return m_pAudio->Music_Play(hAudio, nVolume, fStart, bLoop);
	}

	STDMETHODIMP_(float) CApplicationImpl::Audio_GetLength(HAUDIO hAudio)
	{
		return m_pAudio->Audio_GetLength(hAudio);
	}

	STDMETHODIMP CApplicationImpl::Audio_Free(HAUDIO hAudio)
	{
		return m_pAudio->Audio_Free(hAudio);
	}

	STDMETHODIMP CApplicationImpl::Channel_Pause(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_Pause(hChannel);
	}

	STDMETHODIMP CApplicationImpl::Channel_Resume(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_Resume(hChannel);
	}

	STDMETHODIMP CApplicationImpl::Channel_Stop(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_Stop(hChannel);
	}

	STDMETHODIMP_(BOOL) CApplicationImpl::Channel_IsPlaying(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_IsPlaying(hChannel);
	}

	STDMETHODIMP CApplicationImpl::Channel_SetVolume(HCHANNEL hChannel, int nVolume)
	{
		return m_pAudio->Channel_SetVolume(hChannel, nVolume);
	}

	STDMETHODIMP CApplicationImpl::Channel_SetPan(HCHANNEL hChannel, int nPan)
	{
		return m_pAudio->Channel_SetPan(hChannel, nPan);
	}

	STDMETHODIMP CApplicationImpl::Channel_SetPitch(HCHANNEL hChannel, float fPitch)
	{
		return m_pAudio->Channel_SetPitch(hChannel, fPitch);
	}

	STDMETHODIMP CApplicationImpl::Channel_SetPosition(HCHANNEL hChannel, float fPos)
	{
		return m_pAudio->Channel_SetPosition(hChannel, fPos);
	}

	STDMETHODIMP_(int) CApplicationImpl::Channel_GetVolume(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_GetVolume(hChannel);
	}

	STDMETHODIMP_(int) CApplicationImpl::Channel_GetPan(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_GetPan(hChannel);
	}

	STDMETHODIMP_(float) CApplicationImpl::Channel_GetPosition(HCHANNEL hChannel)
	{
		return m_pAudio->Channel_GetPosition(hChannel);
	}

	STDMETHODIMP CApplicationImpl::Random_Seed(DWORD dwSeed)
	{
		return m_pRand->Randomize(dwSeed);
	}

	STDMETHODIMP_(int) CApplicationImpl::Random_Int(int nMin, int nMax)
	{
		return m_pRand->Integer(nMin, nMax);
	}

	STDMETHODIMP_(float) CApplicationImpl::Random_Float(float fMin, float fMax)
	{
		return m_pRand->Float(fMin, fMax);
	}

	STDMETHODIMP_(float) CApplicationImpl::Timer_GetTime()
	{
		return m_fTime;
	}

	STDMETHODIMP_(float) CApplicationImpl::Timer_GetDelta()
	{
		return m_fDelta;
	}

	STDMETHODIMP_(int) CApplicationImpl::Timer_GetFPS()
	{
		return m_nFPS;
	}

	LRESULT CALLBACK CApplicationImpl::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (m_pThis!=NULL)
		{
			if (m_pThis->m_pInput!=NULL) m_pThis->m_pInput->OnWndEvent(uMsg, wParam, lParam);
			if (m_pThis->m_pEventHandler!=NULL) m_pThis->m_pEventHandler->WndEvent(uMsg, wParam, lParam);
			switch (uMsg)
			{
			case WM_ACTIVATE:
				m_pThis->m_bActive=LOWORD(wParam)!=WA_INACTIVE && HIWORD(wParam)==0;
				break;
			case WM_SETCURSOR:
				if (m_pThis->m_bHideCursor) SetCursor(NULL);
				else SetCursor(LoadCursor(NULL, IDC_ARROW));
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

}