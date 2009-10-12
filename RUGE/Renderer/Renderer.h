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

#ifndef _RUGE_RENDERER_H_
#define _RUGE_RENDERER_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL_
#include "RendererComDef.h"
#include "RendererEventHandler.h"

#define ARGB(a, r, g, b) ((DWORD(a)<<24)+(DWORD(r)<<16)+(DWORD(g)<<8)+DWORD(b))
#define XRGB(r, g, b) ARGB(0xFF, r, g, b)
#define GETA(col) ((col)>>24)
#define GETR(col) (((col)>>16)&0xFF)
#define GETG(col) (((col)>>8)&0xFF)
#define GETB(col) ((col)&0xFF)
#define SETA(col, a) (((col)&0x00FFFFFF)+(DWORD(a)<<24))
#define SETR(col, r) (((col)&0xFF00FFFF)+(DWORD(r)<<16))
#define SETG(col, g) (((col)&0xFFFF00FF)+(DWORD(g)<<8))
#define SETB(col, b) (((col)&0xFFFFFF00)+DWORD(b))

#define VSYNC_DEFAULT	0x00000000L
#define VSYNC_ONE		0x00000001L
#define VSYNC_TWO		0x00000002L
#define VSYNC_THREE		0x00000004L
#define VSYNC_FOUR		0x00000008L
#define VSYNC_IMMEDIATE	0x80000000L

#define TEXF_NEAREST	1L
#define TEXF_LINEAR		2L

#define PRIM_LINE		2L
#define PRIM_TRIANGLE	3L
#define PRIM_QUAD		6L

#define BLEND_COLORADD		1L
#define BLEND_COLORMUL		0L
#define BLEND_ALPHABLEND	2L
#define BLEND_ALPHAADD		0L
#define BLEND_ZWRITE		4L
#define BLEND_NOZWRITE		0L
#define BLEND_DEFAULT		(BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_NOZWRITE)

#define IFF_BMP	0L
#define IFF_JPG	1L
#define IFF_TGA	2L
#define IFF_PNG	3L
#define IFF_DDS	4L
#define IFF_PPM	5L
#define IFF_DIB	6L
#define IFF_HDR	7L
#define IFF_PFM	8L

namespace RUGE
{

	typedef HANDLE HDEVICE;
	typedef HANDLE HTEXTURE;
	typedef HANDLE HTARGET;
	typedef HANDLE HFONT;

	typedef struct VERTEX
	{
		float x, y, z;
		DWORD dwColor;
		float tu, tv;
	} *PVERTEX;

	typedef struct TRIANGLE
	{
		VERTEX v[3];
		HTEXTURE hTex;
		DWORD dwBlend;
	} *PTRIANGLE;

	typedef struct QUAD
	{
		VERTEX v[4];
		HTEXTURE hTex;
		DWORD dwBlend;
	} *PQUAD;

	enum RendererIntState
	{
		RENDERER_WIDTH,
		RENDERER_HEIGHT,
	};

	enum RendererBoolState
	{
		RENDERER_WINDOWED,
		RENDERER_DEVICELOST,
	};

	enum RendererDwordState
	{
		RENDERER_VSYNC,
		RENDERER_MAGFILTER,
		RENDERER_MINFILTER
	};

	enum RendererEventHandlerState
	{
		RENDERER_EVENTHANDLER
	};

	enum RendererHandleState
	{
		RENDERER_DEVICE
	};

	typedef struct IRenderer : public IUnknown
	{
		// IRenderer
		STDMETHOD(SetState)(RendererIntState State, int nVal) PURE;
		STDMETHOD(SetState)(RendererBoolState State, BOOL bVal) PURE;
		STDMETHOD(SetState)(RendererDwordState State, DWORD dwVal) PURE;
		STDMETHOD(SetState)(RendererEventHandlerState State, PRENDEREREVENTHANDLER pVal) PURE;

		STDMETHOD_(int, GetState)(RendererIntState State) PURE;
		STDMETHOD_(BOOL, GetState)(RendererBoolState State) PURE;
		STDMETHOD_(DWORD, GetState)(RendererDwordState State) PURE;
		STDMETHOD_(PRENDEREREVENTHANDLER, GetState)(RendererEventHandlerState State) PURE;
		STDMETHOD_(HANDLE, GetState)(RendererHandleState State) PURE;

		STDMETHOD(Initialize)(HWND hWnd) PURE;
		STDMETHOD(Shutdown)() PURE;
		STDMETHOD(RendererLoop)() PURE;

		STDMETHOD(BeginTarget)(HTARGET hTarg) PURE;
		STDMETHOD(EndTarget)() PURE;
		STDMETHOD(Clear)(DWORD dwColor=0) PURE;
		STDMETHOD(RenderLine)(PVERTEX pV1, PVERTEX pV2, DWORD dwBlend=BLEND_DEFAULT) PURE;
		STDMETHOD(RenderTriangle)(PTRIANGLE pTriangle) PURE;
		STDMETHOD(RenderQuad)(PQUAD pQuad) PURE;
		STDMETHOD(Shotsnap)(LPCSTR lpcszPath, DWORD dwIFF=IFF_BMP) PURE;

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
	} *PRENDERER;

	_COM_SMARTPTR_TYPEDEF(IRenderer, __uuidof(IRenderer));

}

#endif  // _RUGE_RENDERER_H_