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

#ifndef _RUGE_RENDERERIMPL_H_
#define _RUGE_RENDERERIMPL_H_

#include "Renderer.h"

namespace RUGE
{

	typedef struct TARGET
	{
		LPDIRECT3DTEXTURE9 lpD3DTex;
		LPDIRECT3DSURFACE9 lpD3DSurf, lpD3DSurfDepth;
		int nWidth, nHeight;
	} *PTARGET;

	typedef struct TEXTURELIST
	{
		LPDIRECT3DTEXTURE9 lpD3DTex;
		TEXTURELIST *pNext;
	} *PTEXTURELIST;

	typedef struct TARGETLIST
	{
		PTARGET pTarg;
		TARGETLIST *pNext;
	} *PTARGETLIST;

	typedef struct FONTLIST
	{
		LPD3DXFONT lpD3DFont;
		FONTLIST *pNext;
	} *PFONTLIST;

	class CRendererImpl : public IRenderer
	{
	public:
		CRendererImpl();
		virtual ~CRendererImpl();

		// IUnknown
		STDMETHOD_(ULONG, AddRef)();
		STDMETHOD_(ULONG, Release)();
		STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

		// IRenderer
		STDMETHOD(SetState)(RendererIntState State, int nVal);
		STDMETHOD(SetState)(RendererBoolState State, BOOL bVal);
		STDMETHOD(SetState)(RendererDwordState State, DWORD dwVal);
		STDMETHOD(SetState)(RendererEventHandlerState State, PRENDEREREVENTHANDLER pVal);

		STDMETHOD_(int, GetState)(RendererIntState State);
		STDMETHOD_(BOOL, GetState)(RendererBoolState State);
		STDMETHOD_(DWORD, GetState)(RendererDwordState State);
		STDMETHOD_(PRENDEREREVENTHANDLER, GetState)(RendererEventHandlerState State);
		STDMETHOD_(HANDLE, GetState)(RendererHandleState State);

		STDMETHOD(Initialize)(HWND hWnd);
		STDMETHOD(Shutdown)();
		STDMETHOD(RendererLoop)();

		STDMETHOD(BeginTarget)(HTARGET hTarg);
		STDMETHOD(EndTarget)();
		STDMETHOD(Clear)(DWORD dwColor=0);
		STDMETHOD(RenderLine)(PVERTEX pV1, PVERTEX pV2, DWORD dwBlend=BLEND_DEFAULT);
		STDMETHOD(RenderTriangle)(PTRIANGLE pTriangle);
		STDMETHOD(RenderQuad)(PQUAD pQuad);
		STDMETHOD(Shotsnap)(LPCSTR lpcszPath, DWORD dwIFF=IFF_BMP);

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

		STDMETHOD_(HFONT, Font_Create)(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont);
		STDMETHOD(Font_Free)(HFONT hFont);
		STDMETHOD_(int, Font_DrawText)(HFONT hFont, LPCSTR lpcszText, LPRECT lpRect,
			float z=0.0f, DWORD dwFormat=DT_TOP|DT_LEFT, DWORD dwColor=0xFFFFFFFF);

	protected:
		HRESULT InitLost();
		void SetBlendMode(DWORD dwBlend);
		void RenderBatch(BOOL bEndRender=FALSE);
		void BeginScene();
		void EndScene();
		void SetProjectionMatrix(int nWidth, int nHeight);
		HRESULT OnLostDevice();
		HRESULT OnResetDevice();
		HRESULT Restore();
		void Texture_Append(LPDIRECT3DTEXTURE9 lpD3DTex);
		void Texture_Remove(LPDIRECT3DTEXTURE9 lpD3DTex);
		void Texture_RemoveAll();
		void Target_Append(PTARGET pTarg);
		void Target_Remove(PTARGET pTarg);
		void Target_RemoveAll();
		void Font_Append(LPD3DXFONT lpD3DFont);
		void Font_Remove(LPD3DXFONT lpD3DFont);
		void Font_RemoveAll();

	protected:
		ULONG m_uRefCount;
		long m_lStyle;
		RECT m_rectPos;
		int m_nWidth, m_nHeight;
		BOOL m_bWindowed, m_bDeviceLost;
		DWORD m_dwVSync, m_dwMagFilter, m_dwMinFilter;
		PRENDEREREVENTHANDLER m_pEventHandler;
		LPDIRECT3D9 m_lpD3D;
		D3DPRESENT_PARAMETERS m_D3Dpp;
		LPDIRECT3DDEVICE9 m_lpD3DDevice;
		LPDIRECT3DSURFACE9 m_lpD3DSurfBack, m_lpD3DSurfDepth;
		D3DXMATRIX m_d3dxmatProj;
		LPD3DXSPRITE m_lpD3DSprite;
		LPDIRECT3DVERTEXBUFFER9 m_lpD3DVertexBuf;
		PVERTEX m_pVertexes;
		PTEXTURELIST m_pTexList;
		PTARGETLIST m_pTargList;
		PFONTLIST m_pFontList;
		DWORD m_dwCurPrim, m_dwCurBlend;
		HTEXTURE m_hCurTex;
		int m_nPrims;
	};

}

#endif  // _RENDERERIMPL_H_