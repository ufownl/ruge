#pragma once

#ifndef _RENDERERIMPL_H_
#define _RENDERERIMPL_H_

#include "Renderer.h"

typedef struct TEXTURELIST
{
	LPDIRECT3DTEXTURE9 lpD3DTex;
	TEXTURELIST *pNext;
} *PTEXTURELIST;

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

	STDMETHOD_(HFONTX, Font_Create)(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont);
	STDMETHOD(Font_Free)(HFONTX hFont);
	STDMETHOD_(int, Font_DrawText)(HFONTX hFont, LPCSTR lpcszText, LPRECT lpRect,
		float z=0.0f, DWORD dwFormat=DT_TOP|DT_LEFT, DWORD dwColor=0xFFFFFFFF);

protected:
	HRESULT InitLost();
	void SetBlendMode(DWORD dwBlend);
	void RenderBatch(bool bEndRender=false);
	void Texture_Append(LPDIRECT3DTEXTURE9 lpD3DTex);
	void Texture_Remove(LPDIRECT3DTEXTURE9 lpD3DTex);
	void Texture_RemoveAll();
	void Font_Append(LPD3DXFONT lpD3DFont);
	void Font_Remove(LPD3DXFONT lpD3DFont);
	void Font_RemoveAll();
	HRESULT Font_OnLostDevice();
	HRESULT Font_OnResetDevice();

protected:
	ULONG m_uRefCount;
	int m_nWidth, m_nHeight;
	BOOL m_bWindowed;
	DWORD m_dwVSync, m_dwMagFilter, m_dwMinFilter;
	LPDIRECT3D9 m_lpD3D;
	D3DDISPLAYMODE m_D3Ddm;
	D3DPRESENT_PARAMETERS m_D3Dpp;
	LPDIRECT3DDEVICE9 m_lpD3DDevice;
	LPD3DXSPRITE m_lpD3DSprite;
	ITimerPtr m_pTimer;
	BOOL m_bDeviceLost;
	PRENDEREREVENTHANDLER m_pEventHandler;
	LPDIRECT3DVERTEXBUFFER9 m_lpD3DVertexBuf;
	PVERTEX m_pVertexes;
	PTEXTURELIST m_pTexList;
	PFONTLIST m_pFontList;
	DWORD m_dwCurPrim, m_dwCurBlend;
	HTEXTURE m_hCurTex;
	int m_nPrims, m_nFPS;
};

#endif  // _RENDERERIMPL_H_