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

CApplicationImpl *CApplicationImpl::m_pThis=NULL;

CApplicationImpl::CApplicationImpl()
	: m_uRefCount(0)
	, m_nWidth(800)
	, m_nHeight(600)
	, m_nMaxChannels(32)
	, m_bWindowed(TRUE)
	, m_bHideCursor(FALSE)
	, m_dwVSync(VSYNC_DEFAULT)
	, m_dwMagFilter(TEXF_NEAREST)
	, m_dwMinFilter(TEXF_NEAREST)
	, m_pEventHandler(NULL)
	, m_hWnd(NULL)
{
	assert(m_pThis==NULL);
	m_pThis=this;
	strcpy(m_szCaption, "RangerUFO's Game Engine");
	g_uDllLockCount++;
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

STDMETHODIMP CApplicationImpl::System_SetState(RUGEStringState State, LPCSTR lpcszVal)
{
	switch (State)
	{
	case RUGE_CAPTION:
		strcpy(m_szCaption, lpcszVal);
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CApplicationImpl::System_SetState(RUGEIntState State, int nVal)
{
	switch (State)
	{
	case RUGE_WIDTH:
		m_nWidth=nVal;
		break;
	case RUGE_HEIGHT:
		m_nHeight=nVal;
		break;
	case RUGE_MAXCHANNELS:
		m_nMaxChannels=nVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CApplicationImpl::System_SetState(RUGEBoolState State, BOOL bVal)
{
	switch (State)
	{
	case RUGE_WINDOWED:
		m_bWindowed=bVal;
		break;
	case RUGE_HIDECURSOR:
		m_bHideCursor=bVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CApplicationImpl::System_SetState(RUGEDwordState State, DWORD dwVal)
{
	switch (State)
	{
	case RUGE_VSYNC:
		m_dwVSync=dwVal;
		break;
	case RUGE_MAGFILTER:
		m_dwMagFilter=dwVal;
		break;
	case RUGE_MINFILTER:
		m_dwMinFilter=dwVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CApplicationImpl::System_SetState(RUGEEventHandlerState State, PAPPLICATIONEVENTHANDLER pVal)
{
	switch (State)
	{
	case RUGE_EVENTHANDLER:
		m_pEventHandler=pVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP_(LPCSTR) CApplicationImpl::System_GetState(RUGEStringState State)
{
	switch (State)
	{
	case RUGE_CAPTION:
		return m_szCaption;
	default:
		return NULL;
	}
}

STDMETHODIMP_(int) CApplicationImpl::System_GetState(RUGEIntState State)
{
	switch (State)
	{
	case RUGE_WIDTH:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_WIDTH);
		else return 0;
	case RUGE_HEIGHT:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_HEIGHT);
		else return 0;
	case RUGE_FPS:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_FPS);
		else return 0;
	case RUGE_MAXCHANNELS:
		return m_nMaxChannels;
	default:
		return 0;
	}
}

STDMETHODIMP_(BOOL) CApplicationImpl::System_GetState(RUGEBoolState State)
{
	switch (State)
	{
	case RUGE_WINDOWED:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_WINDOWED);
		else return 0;
	case RUGE_DEVICELOST:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_DEVICELOST);
		else return FALSE;
	case RUGE_FOCUS:
		return m_hWnd==GetFocus();
	case RUGE_HIDECURSOR:
		return m_bHideCursor;
	default:
		return FALSE;
	}
}

STDMETHODIMP_(DWORD) CApplicationImpl::System_GetState(RUGEDwordState State)
{
	switch (State)
	{
	case RUGE_VSYNC:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_VSYNC);
		else return 0;
	case RUGE_MAGFILTER:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_MAGFILTER);
		else return 0;
	case RUGE_MINFILTER:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_MINFILTER);
		else return 0;
	default:
		return 0;
	}
}

STDMETHODIMP_(PAPPLICATIONEVENTHANDLER) CApplicationImpl::System_GetState(RUGEEventHandlerState State)
{
	switch (State)
	{
	case RUGE_EVENTHANDLER:
		return m_pEventHandler;
	default:
		return NULL;
	}
}

STDMETHODIMP_(HANDLE) CApplicationImpl::System_GetState(RUGEHandleState State)
{
	switch (State)
	{
	case RUGE_DEVICE:
		if (m_pRenderer!=NULL) return m_pRenderer->GetState(RENDERER_DEVICE);
		else return NULL;
	case RUGE_MAINWINDOW:
		return (HANDLE)m_hWnd;
	default:
		return NULL;
	}
}

STDMETHODIMP CApplicationImpl::System_Initialize()
{
	HINSTANCE hInstance=GetModuleHandle(NULL);
	WNDCLASS wc;

	wc.style=CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc=WndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=NULL;
	wc.hCursor=NULL;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName="Application";
	RegisterClass(&wc);
	m_hWnd=CreateWindow("Application", m_szCaption, WS_CAPTION|WS_SYSMENU|WS_BORDER|WS_MINIMIZEBOX, CW_USEDEFAULT
		, CW_USEDEFAULT, m_nWidth+GetSystemMetrics(SM_CXFIXEDFRAME)*2, m_nHeight+GetSystemMetrics(SM_CYFIXEDFRAME)*2+GetSystemMetrics(SM_CYCAPTION)
		, NULL, NULL, hInstance, NULL);
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	HRESULT hr=m_pRenderer.CreateInstance(__uuidof(CRendererImpl));

	if (FAILED(hr)) return hr;
	m_pRenderer->SetState(RENDERER_WIDTH, m_nWidth);
	m_pRenderer->SetState(RENDERER_HEIGHT, m_nHeight);
	m_pRenderer->SetState(RENDERER_WINDOWED, m_bWindowed);
	m_pRenderer->SetState(RENDERER_VSYNC, m_dwVSync);
	m_pRenderer->SetState(RENDERER_MAGFILTER, m_dwMagFilter);
	m_pRenderer->SetState(RENDERER_MINFILTER, m_dwMinFilter);
	m_pRenderer->SetState(RENDERER_EVENTHANDLER, m_pEventHandler);
	hr=m_pRenderer->Initialize(m_hWnd);
	if (FAILED(hr)) return hr;

	hr=m_pAudio.CreateInstance(__uuidof(CAudioImpl));
	if (FAILED(hr)) return hr;
	hr=m_pAudio->Initialize(m_nMaxChannels);
	if (FAILED(hr)) return hr;

	hr=m_pInput.CreateInstance(__uuidof(CInputImpl));
	if (FAILED(hr)) return hr;
	hr=m_pTimer.CreateInstance(__uuidof(CTimerImpl));
	if (FAILED(hr)) return hr;

	if (m_pEventHandler!=NULL)
	{
		hr=m_pEventHandler->InitResource();
		if (FAILED(hr)) return hr;
	}
	return S_OK;
}

STDMETHODIMP CApplicationImpl::System_Run()
{
	MSG Msg;

	memset(&Msg, 0, sizeof(Msg));
	while (Msg.message!=WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		float fDelta=(float)m_pTimer->GetDelta()/1000;

		m_pTimer->Start();
		if (m_pEventHandler!=NULL)
		{
			if (m_pEventHandler->Frame(fDelta)) PostQuitMessage(0);
		}
		
		HRESULT hr=m_pRenderer->RendererLoop();

		if (FAILED(hr)) PostQuitMessage(hr);
		hr=m_pAudio->Update();
		if (FAILED(hr)) PostQuitMessage(hr);
	}
	if (m_pEventHandler!=NULL) m_pEventHandler->ReleaseResource();
	return (HRESULT)Msg.wParam;
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

STDMETHODIMP_(HFONTX) CApplicationImpl::Font_Create(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont)
{
	return m_pRenderer->Font_Create(nHeight, nWidth, nWeight, bItalic, lpcszFont);
}

STDMETHODIMP CApplicationImpl::Font_Free(HFONTX hFont)
{
	return m_pRenderer->Font_Free(hFont);
}

STDMETHODIMP_(int) CApplicationImpl::Font_DrawText(HFONTX hFont, LPCSTR lpcszText, LPRECT lpRect,
												   float z/* =0.0f */, DWORD dwFormat/* =DT_TOP|DT_LEFT */, DWORD dwColor/* =0xFFFFFFFF */)
{
	return m_pRenderer->Font_DrawText(hFont, lpcszText, lpRect, z, dwFormat, dwColor);
}

STDMETHODIMP_(BOOL) CApplicationImpl::Input_KeyDown(int nVKey)
{
	return m_pInput->KeyDown(nVKey);
}

STDMETHODIMP_(BOOL) CApplicationImpl::Input_KeyPress(int nVKey)
{
	return m_pInput->KeyPress(nVKey);
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

STDMETHODIMP_(SHORT) CApplicationImpl::Input_GetMouseWheel()
{
	return m_pInput->GetMouseWheel();
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

LRESULT CALLBACK CApplicationImpl::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_pThis!=NULL)
	{
		if (m_pThis->m_pInput!=NULL) m_pThis->m_pInput->OnWndEvent(uMsg, wParam, lParam);
		if (m_pThis->m_pEventHandler!=NULL) m_pThis->m_pEventHandler->WndEvent(uMsg, wParam, lParam);
		switch (uMsg)
		{
		case WM_SETCURSOR:
			if (m_pThis->m_bHideCursor) SetCursor(NULL);
			else SetCursor(LoadCursor(NULL, IDC_ARROW));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
