#pragma once

#ifndef _APPLICATIONIMPL_H_
#define _APPLICATIONIMPL_H_

#include "Application.h"

class CApplicationImpl : public IApplication
{
public:
	CApplicationImpl();
	virtual ~CApplicationImpl();

	// IUnknown
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	// IApplication
	STDMETHOD(System_SetState)(RUGEStringState State, LPCSTR lpcszVal);
	STDMETHOD(System_SetState)(RUGEIntState State, int nVal);
	STDMETHOD(System_SetState)(RUGEBoolState State, BOOL bVal);
	STDMETHOD(System_SetState)(RUGEDwordState State, DWORD dwVal);
	STDMETHOD(System_SetState)(RUGEEventHandlerState State, PAPPLICATIONEVENTHANDLER pVal);

	STDMETHOD_(LPCSTR, System_GetState)(RUGEStringState State);
	STDMETHOD_(int, System_GetState)(RUGEIntState State);
	STDMETHOD_(BOOL, System_GetState)(RUGEBoolState State);
	STDMETHOD_(DWORD, System_GetState)(RUGEDwordState State);
	STDMETHOD_(PAPPLICATIONEVENTHANDLER, System_GetState)(RUGEEventHandlerState State);
	STDMETHOD_(HANDLE, System_GetState)(RUGEHandleState State);

	STDMETHOD(System_Initialize)();
	STDMETHOD(System_Run)();

	STDMETHOD(Gfx_BeginTarget)(HTARGET hTarg);
	STDMETHOD(Gfx_EndTarget)();
	STDMETHOD(Gfx_Clear)(DWORD dwColor=0);
	STDMETHOD(Gfx_RenderLine)(PVERTEX pV1, PVERTEX pV2, DWORD dwBlend=BLEND_DEFAULT);
	STDMETHOD(Gfx_RenderTriangle)(PTRIANGLE pTriangle);
	STDMETHOD(Gfx_RenderQuad)(PQUAD pQuad);
	STDMETHOD(Gfx_Shotsnap)(LPCSTR lpcszPath, DWORD dwIFF=IFF_BMP);

	STDMETHOD_(HTEXTURE, Texture_Create)(int nWidth, int nHeight);
	STDMETHOD_(HTEXTURE, Texture_Load)(LPCSTR lpcszPath);
	STDMETHOD(Texture_Free)(HTEXTURE hTex);
	STDMETHOD_(void*, Texture_Lock)(HTEXTURE hTex, BOOL bReadOnly=TRUE, int x=0, int y=0, int w=0, int h=0);
	STDMETHOD(Texture_Unlock)(HTEXTURE hTex);
	STDMETHOD_(int, Texture_GetWidth)(HTEXTURE hTex);
	STDMETHOD_(int, Texture_GetHeight)(HTEXTURE hTex);

	STDMETHOD_(HTARGET, Target_Create)(int nWidth, int nHeight);
	STDMETHOD(Target_Free)(HTARGET hTarg);
	STDMETHOD_(HTEXTURE, Target_GetTexture)(HTARGET hTarg);

	STDMETHOD_(HFONTX, Font_Create)(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont);
	STDMETHOD(Font_Free)(HFONTX hFont);
	STDMETHOD_(int, Font_DrawText)(HFONTX hFont, LPCSTR lpcszText, LPRECT lpRect,
		float z=0.0f, DWORD dwFormat=DT_TOP|DT_LEFT, DWORD dwColor=0xFFFFFFFF);

	STDMETHOD_(BOOL, Input_KeyDown)(int nVKey);
	STDMETHOD_(BOOL, Input_KeyPress)(int nVKey);
	STDMETHOD_(BOOL, Input_KeyUp)(int nVKey);
	STDMETHOD_(int, Input_GetKey)();
	STDMETHOD_(char, Input_GetChar)();
	STDMETHOD_(LPCSTR, Input_GetKeyName)(int nVKey);

	STDMETHOD(Input_GetMousePos)(float *x, float *y);
	STDMETHOD_(SHORT, Input_GetMouseWheel)();

	STDMETHOD_(HAUDIO, Effect_Load)(LPCSTR lpcszPath);
	STDMETHOD_(HCHANNEL, Effect_Play)(HAUDIO hAudio, int nVolume=100, int nPan=0, float fPitch=1.0f, BOOL bLoop=FALSE);

	STDMETHOD_(HAUDIO, Music_Load)(LPCSTR lpcszPath);
	STDMETHOD_(HCHANNEL, Music_Play)(HAUDIO hAudio, int nVolume=100, float fStart=0.0f, BOOL bLoop=TRUE);

	STDMETHOD_(float, Audio_GetLength)(HAUDIO hAudio);
	STDMETHOD(Audio_Free)(HAUDIO hAudio);

	STDMETHOD(Channel_Pause)(HCHANNEL hChannel);
	STDMETHOD(Channel_Resume)(HCHANNEL hChannel);
	STDMETHOD(Channel_Stop)(HCHANNEL hChannel);
	STDMETHOD_(BOOL, Channel_IsPlaying)(HCHANNEL hChannel);

	STDMETHOD(Channel_SetVolume)(HCHANNEL hChannel, int nVolume);
	STDMETHOD(Channel_SetPan)(HCHANNEL hChannel, int nPan);
	STDMETHOD(Channel_SetPitch)(HCHANNEL hChannel, float fPitch);
	STDMETHOD(Channel_SetPosition)(HCHANNEL hChannel, float fPos);

	STDMETHOD_(int, Channel_GetVolume)(HCHANNEL hChannel);
	STDMETHOD_(int, Channel_GetPan)(HCHANNEL hChannel);
	STDMETHOD_(float, Channel_GetPosition)(HCHANNEL hChannel);

protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	static CApplicationImpl *m_pThis;
	ULONG m_uRefCount;
	char m_szCaption[MAX_PATH];
	int m_nWidth, m_nHeight, m_nMaxChannels;
	BOOL m_bWindowed, m_bHideCursor, m_bFocus;
	DWORD m_dwVSync, m_dwMagFilter, m_dwMinFilter;
	PAPPLICATIONEVENTHANDLER m_pEventHandler;
	HWND m_hWnd;
	IRendererPtr m_pRenderer;
	IAudioPtr m_pAudio;
	IInputPtr m_pInput;
	ITimerPtr m_pTimer;
};

#endif  // _APPLICATIONIMPL_H_