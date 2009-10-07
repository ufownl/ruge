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

#pragma once

#ifndef _RUGE_APPLICATION_H_
#define _RUGE_APPLICATION_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL_
#include "ApplicationComDef.h"
#include "ApplicationEventHandler.h"

#ifndef M_PI
#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f
#define M_PI_4	0.785398163397448309616f
#define M_1_PI	0.318309886183790671538f
#define M_2_PI	0.636619772367581343076f
#endif

namespace RUGE
{

	enum AppStringState
	{
		APP_CAPTION,
		APP_ICON
	};

	enum AppIntState
	{
		APP_WIDTH,
		APP_HEIGHT,
		APP_MAXCHANNELS
	};

	enum AppBoolState
	{
		APP_WINDOWED,
		APP_DEVICELOST,
		APP_ACTIVE,
		APP_HIDECURSOR,
		APP_NOTSUSPEND
	};

	enum AppDwordState
	{
		APP_VSYNC,
		APP_MAGFILTER,
		APP_MINFILTER
	};

	enum AppEventHandlerState
	{
		APP_EVENTHANDLER
	};

	enum AppHandleState
	{
		APP_DEVICE,
		APP_MAINWINDOW
	};

	typedef struct IApplication : public IUnknown
	{
		STDMETHOD(System_SetState)(AppStringState State, LPCSTR lpcszVal) PURE;
		STDMETHOD(System_SetState)(AppIntState State, int nVal) PURE;
		STDMETHOD(System_SetState)(AppBoolState State, BOOL bVal) PURE;
		STDMETHOD(System_SetState)(AppDwordState State, DWORD dwVal) PURE;
		STDMETHOD(System_SetState)(AppEventHandlerState State, PAPPLICATIONEVENTHANDLER pVal) PURE;

		STDMETHOD_(LPCSTR, System_GetState)(AppStringState State) PURE;
		STDMETHOD_(int, System_GetState)(AppIntState State) PURE;
		STDMETHOD_(BOOL, System_GetState)(AppBoolState State) PURE;
		STDMETHOD_(DWORD, System_GetState)(AppDwordState State) PURE;
		STDMETHOD_(PAPPLICATIONEVENTHANDLER, System_GetState)(AppEventHandlerState State) PURE;
		STDMETHOD_(HANDLE, System_GetState)(AppHandleState State) PURE;

		STDMETHOD(System_Initialize)() PURE;
		STDMETHOD(System_Run)() PURE;

		STDMETHOD(Gfx_BeginTarget)(HTARGET hTarg) PURE;
		STDMETHOD(Gfx_EndTarget)() PURE;
		STDMETHOD(Gfx_Clear)(DWORD dwColor=0) PURE;
		STDMETHOD(Gfx_RenderLine)(PVERTEX pV1, PVERTEX pV2, DWORD dwBlend=BLEND_DEFAULT) PURE;
		STDMETHOD(Gfx_RenderTriangle)(PTRIANGLE pTriangle) PURE;
		STDMETHOD(Gfx_RenderQuad)(PQUAD pQuad) PURE;
		STDMETHOD(Gfx_Shotsnap)(LPCSTR lpcszPath, DWORD dwIFF=IFF_BMP) PURE;

		STDMETHOD_(HTEXTURE, Texture_Create)(int nWidth, int nHeight) PURE;
		STDMETHOD_(HTEXTURE, Texture_Load)(LPCSTR lpcszPath) PURE;
		STDMETHOD(Texture_Free)(HTEXTURE hTex) PURE;
		STDMETHOD_(void*, Texture_Lock)(HTEXTURE hTex, BOOL bReadOnly=TRUE, int x=0, int y=0, int w=0, int h=0) PURE;
		STDMETHOD(Texture_Unlock)(HTEXTURE hTex) PURE;
		STDMETHOD_(int, Texture_GetWidth)(HTEXTURE hTex) PURE;
		STDMETHOD_(int, Texture_GetHeight)(HTEXTURE hTex) PURE;

		STDMETHOD_(HTARGET, Target_Create)(int nWidth, int nHeight) PURE;
		STDMETHOD(Target_Free)(HTARGET hTarg) PURE;
		STDMETHOD_(HTEXTURE, Target_GetTexture)(HTARGET hTarg) PURE;

		STDMETHOD_(HFONT, Font_Create)(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont) PURE;
		STDMETHOD(Font_Free)(HFONT hFont) PURE;
		STDMETHOD_(int, Font_DrawText)(HFONT hFont, LPCSTR lpcszText, LPRECT lpRect,
			float z=0.0f, DWORD dwFormat=DT_TOP|DT_LEFT, DWORD dwColor=0xFFFFFFFF) PURE;

		STDMETHOD_(BOOL, Input_KeyDown)(int nVKey) PURE;
		STDMETHOD_(BOOL, Input_KeyPressed)(int nVKey) PURE;
		STDMETHOD_(BOOL, Input_KeyUp)(int nVKey) PURE;
		STDMETHOD_(int, Input_GetKey)() PURE;
		STDMETHOD_(char, Input_GetChar)() PURE;
		STDMETHOD_(LPCSTR, Input_GetKeyName)(int nVKey) PURE;

		STDMETHOD(Input_GetMousePos)(float *x, float *y) PURE;
		STDMETHOD(Input_SetMousePos)(float x, float y) PURE;
		STDMETHOD_(SHORT, Input_GetMouseWheel)() PURE;
		STDMETHOD_(BOOL, Input_IsMouseOver)() PURE;

		STDMETHOD_(HAUDIO, Effect_Load)(LPCSTR lpcszPath) PURE;
		STDMETHOD_(HCHANNEL, Effect_Play)(HAUDIO hAudio, int nVolume=100, int nPan=0, float fPitch=1.0f, BOOL bLoop=FALSE) PURE;

		STDMETHOD_(HAUDIO, Music_Load)(LPCSTR lpcszPath) PURE;
		STDMETHOD_(HCHANNEL, Music_Play)(HAUDIO hAudio, int nVolume=100, float fStart=0.0f, BOOL bLoop=TRUE) PURE;

		STDMETHOD_(float, Audio_GetLength)(HAUDIO hAudio) PURE;
		STDMETHOD(Audio_Free)(HAUDIO hAudio) PURE;

		STDMETHOD(Channel_Pause)(HCHANNEL hChannel) PURE;
		STDMETHOD(Channel_Resume)(HCHANNEL hChannel) PURE;
		STDMETHOD(Channel_Stop)(HCHANNEL hChannel) PURE;
		STDMETHOD_(BOOL, Channel_IsPlaying)(HCHANNEL hChannel) PURE;

		STDMETHOD(Channel_SetVolume)(HCHANNEL hChannel, int nVolume) PURE;
		STDMETHOD(Channel_SetPan)(HCHANNEL hChannel, int nPan) PURE;
		STDMETHOD(Channel_SetPitch)(HCHANNEL hChannel, float fPitch) PURE;
		STDMETHOD(Channel_SetPosition)(HCHANNEL hChannel, float fPos) PURE;

		STDMETHOD_(int, Channel_GetVolume)(HCHANNEL hChannel) PURE;
		STDMETHOD_(int, Channel_GetPan)(HCHANNEL hChannel) PURE;
		STDMETHOD_(float, Channel_GetPosition)(HCHANNEL hChannel) PURE;

		STDMETHOD(Random_Seed)(DWORD dwSeed) PURE;
		STDMETHOD_(int, Random_Int)(int nMax, int nMin) PURE;
		STDMETHOD_(float, Random_Float)(float fMax, float fMin) PURE;

		STDMETHOD_(float, Timer_GetTime)() PURE;
		STDMETHOD_(float, Timer_GetDelta)() PURE;
		STDMETHOD_(int, Timer_GetFPS)() PURE;
	} *PAPPLICATION;

	_COM_SMARTPTR_TYPEDEF(IApplication, __uuidof(IApplication));

}

#endif  // _RUGE_APPLICATION_H_