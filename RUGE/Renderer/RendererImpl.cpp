#include "StdAfx.h"
#include "RendererImpl.h"

#define VERTEX_BUFFER_SIZE	6000L

CRendererImpl::CRendererImpl()
	: m_uRefCount(0)
	, m_nWidth(800)
	, m_nHeight(600)
	, m_bWindowed(TRUE)
	, m_dwVSync(VSYNC_DEFAULT)
	, m_dwMagFilter(TEXF_NEAREST)
	, m_dwMinFilter(TEXF_NEAREST)
	, m_lpD3D(NULL)
	, m_lpD3DDevice(NULL)
	, m_bDeviceLost(FALSE)
	, m_pEventHandler(NULL)
	, m_lpD3DVertexBuf(NULL)
	, m_pVertexes(NULL)
	, m_pTexList(NULL)
	, m_pFontList(NULL)
	, m_dwCurPrim(PRIM_LINE)
	, m_dwCurBlend(BLEND_DEFAULT)
	, m_hCurTex(NULL)
	, m_nPrims(0)
	, m_nFPS(0)
{
	g_uDllLockCount++;
}

CRendererImpl::~CRendererImpl()
{
	Shutdown();
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CRendererImpl::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CRendererImpl::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CRendererImpl::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT hr=S_OK;

	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
	else if (InlineIsEqualGUID(riid, __uuidof(IRenderer))) *ppv=(IRenderer*)this;
	else hr=E_NOINTERFACE;
	if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
	return hr;
}

STDMETHODIMP CRendererImpl::SetState(RendererIntState State, int nVal)
{
	switch (State)
	{
	case RENDERER_WIDTH:
		m_nWidth=nVal;
		break;
	case RENDERER_HEIGHT:
		m_nHeight=nVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CRendererImpl::SetState(RendererBoolState State, int bVal)
{
	switch (State)
	{
	case RENDERER_WINDOWED:
		m_bWindowed=bVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CRendererImpl::SetState(RendererDwordState State, DWORD dwVal)
{
	switch (State)
	{
	case RENDERER_VSYNC:
		m_dwVSync=dwVal;
		break;
	case RENDERER_MAGFILTER:
		m_dwMagFilter=dwVal;
		break;
	case RENDERER_MINFILTER:
		m_dwMinFilter=dwVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CRendererImpl::SetState(RendererEventHandlerState State, PRENDEREREVENTHANDLER pVal)
{
	switch (State)
	{
	case RENDERER_EVENTHANDLER:
		m_pEventHandler=pVal;
		break;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP_(int) CRendererImpl::GetState(RendererIntState State)
{
	switch (State)
	{
	case RENDERER_WIDTH:
		return m_nWidth;
	case RENDERER_HEIGHT:
		return m_nHeight;
	case RENDERER_FPS:
		return m_nFPS;
	default:
		return 0;
	}
}

STDMETHODIMP_(BOOL) CRendererImpl::GetState(RendererBoolState State)
{
	switch (State)
	{
	case RENDERER_WINDOWED:
		return m_bWindowed;
	case RENDERER_DEVICELOST:
		return m_bDeviceLost;
	default:
		return FALSE;
	}
}

STDMETHODIMP_(DWORD) CRendererImpl::GetState(RendererDwordState State)
{
	switch (State)
	{
	case RENDERER_VSYNC:
		return m_dwVSync;
	case RENDERER_MAGFILTER:
		return m_dwMagFilter;
	case RENDERER_MINFILTER:
		return m_dwMinFilter;
	default:
		return 0;
	}
}

STDMETHODIMP_(PRENDEREREVENTHANDLER) CRendererImpl::GetState(RendererEventHandlerState State)
{
	switch (State)
	{
	case RENDERER_EVENTHANDLER:
		return m_pEventHandler;
	default:
		return NULL;
	}
}

STDMETHODIMP_(HANDLE) CRendererImpl::GetState(RendererHandleState State)
{
	switch (State)
	{
	case RENDERER_DEVICE:
		return (HANDLE)m_lpD3DDevice;
	default:
		return NULL;
	}
}

STDMETHODIMP CRendererImpl::Initialize(HWND hWnd)
{
	assert(m_lpD3D==NULL && m_lpD3DDevice==NULL);
	m_lpD3D=Direct3DCreate9(D3D_SDK_VERSION);  // 创建D3D对象
	if (m_lpD3D==NULL) return -1;
	memset(&m_D3Ddm, 0, sizeof(m_D3Ddm));

	HRESULT hr=m_lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_D3Ddm);

	if (FAILED(hr)) return hr;
	memset(&m_D3Dpp, 0, sizeof(m_D3Dpp));
	m_D3Dpp.BackBufferWidth=m_nWidth;
	m_D3Dpp.BackBufferHeight=m_nHeight;
	m_D3Dpp.BackBufferFormat=m_D3Ddm.Format;
	m_D3Dpp.BackBufferCount=1;
	m_D3Dpp.SwapEffect=D3DSWAPEFFECT_FLIP;
	m_D3Dpp.hDeviceWindow=hWnd;
	m_D3Dpp.Windowed=m_bWindowed;
	m_D3Dpp.EnableAutoDepthStencil=true;
	m_D3Dpp.AutoDepthStencilFormat=D3DFMT_D16;
	m_D3Dpp.Flags=D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	m_D3Dpp.PresentationInterval=m_dwVSync;
	hr=m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3Dpp, &m_lpD3DDevice);
	if (FAILED(hr)) return hr;
	hr=D3DXCreateSprite(m_lpD3DDevice, &m_lpD3DSprite);
	if (FAILED(hr)) return hr;
	hr=m_pTimer.CreateInstance(__uuidof(CTimerImpl));
	if (FAILED(hr)) return hr;
	return InitLost();
}

STDMETHODIMP CRendererImpl::Shutdown()
{
	Font_RemoveAll();
	Texture_RemoveAll();
	if (m_lpD3DVertexBuf!=NULL)
	{
		m_lpD3DVertexBuf->Release();
		m_lpD3DVertexBuf=NULL;
	}
	if (m_pTimer!=NULL) m_pTimer.Release();
	if (m_lpD3DSprite!=NULL)
	{
		m_lpD3DSprite->Release();
		m_lpD3DSprite=NULL;
	}
	if (m_lpD3DDevice!=NULL)
	{
		m_lpD3DDevice->Release();
		m_lpD3DDevice=NULL;
	}
	if (m_lpD3D!=NULL)
	{
		m_lpD3D->Release();
		m_lpD3D=NULL;
	}
	return S_OK;
}

STDMETHODIMP CRendererImpl::RendererLoop()
{
	assert(m_lpD3DDevice!=NULL);
	switch (m_lpD3DDevice->TestCooperativeLevel())
	{
	case D3D_OK:
		{
			static int nFrames=0;

			if (nFrames==0) m_pTimer->Start();
			if (m_pTimer->GetDelta()>=1000)
			{
				m_nFPS=nFrames;
				nFrames=0;
			}
			else nFrames++;
			m_lpD3DDevice->BeginScene();
			if (m_pEventHandler!=NULL) m_pEventHandler->Render();
			else Clear();
			RenderBatch(true);
			m_lpD3DDevice->EndScene();

			LPDIRECT3DSURFACE9 lpD3DSurface;

			if (m_pEventHandler!=NULL && SUCCEEDED(m_lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpD3DSurface)))
			{
				D3DLOCKED_RECT D3Dlr;

				lpD3DSurface->LockRect(&D3Dlr, NULL, 0);
				m_pEventHandler->Pretreat(D3Dlr.Pitch, D3Dlr.pBits);
				lpD3DSurface->UnlockRect();
				lpD3DSurface->Release();
			}
			m_lpD3DDevice->Present(NULL, NULL, NULL, NULL);
		}
		break;
	case D3DERR_DEVICELOST:
		m_bDeviceLost=true;
		break;
	case D3DERR_DEVICENOTRESET:
		{
			m_lpD3DVertexBuf->Release();
			m_lpD3DVertexBuf=NULL;

			HRESULT hr=Font_OnLostDevice();

			if (FAILED(hr)) return hr;
			hr=m_lpD3DDevice->Reset(&m_D3Dpp);
			if (FAILED(hr)) return hr;
			hr=InitLost();
			if (FAILED(hr)) return hr;
			hr=Font_OnResetDevice();
			if (FAILED(hr)) return hr;
			m_bDeviceLost=false;
		}
		break;
	case D3DERR_DRIVERINTERNALERROR:
		return D3DERR_DRIVERINTERNALERROR;
	default:
		break;
	}
	return S_OK;
}

STDMETHODIMP CRendererImpl::Clear(DWORD dwColor/* =0 */)
{
	assert(m_lpD3DDevice!=NULL);
	return m_lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, dwColor, 1.0f, 0);
}

STDMETHODIMP CRendererImpl::RenderLine(PVERTEX pV1, PVERTEX pV2, DWORD dwBlend/* =BLEND_DEFAULT */)
{
	assert(m_lpD3DDevice!=NULL && m_lpD3DVertexBuf!=NULL);
	if (m_pVertexes==NULL) m_lpD3DVertexBuf->Lock(0, 0, (void**)&m_pVertexes, 0);
	if(m_dwCurPrim!=PRIM_LINE || m_nPrims>=VERTEX_BUFFER_SIZE/PRIM_LINE || m_dwCurBlend!=dwBlend)
	{
		RenderBatch();
		m_dwCurPrim=PRIM_LINE;
		SetBlendMode(dwBlend);
		m_dwCurBlend=dwBlend;
		m_lpD3DDevice->SetTexture(0, NULL);
		m_hCurTex=NULL;
	}

	int nIndex=m_nPrims*PRIM_LINE;

	m_pVertexes[nIndex]=*pV1;
	m_pVertexes[nIndex+1]=*pV2;
	m_nPrims++;
	return S_OK;
}

STDMETHODIMP CRendererImpl::RenderTriangle(PTRIANGLE pTriangle)
{
	if (pTriangle==NULL) return E_POINTER;
	assert(m_lpD3DDevice!=NULL && m_lpD3DVertexBuf!=NULL);
	if (m_pVertexes==NULL) m_lpD3DVertexBuf->Lock(0, 0, (void**)&m_pVertexes, 0);
	if(m_dwCurPrim!=PRIM_TRIANGLE || m_nPrims>=VERTEX_BUFFER_SIZE/PRIM_TRIANGLE
		|| m_dwCurBlend!=pTriangle->dwBlend || m_hCurTex!=pTriangle->hTex)
	{
		RenderBatch();
		m_dwCurPrim=PRIM_TRIANGLE;
		SetBlendMode(pTriangle->dwBlend);
		m_dwCurBlend=pTriangle->dwBlend;
		m_lpD3DDevice->SetTexture(0, (LPDIRECT3DTEXTURE9)pTriangle->hTex);
		m_hCurTex=pTriangle->hTex;
	}

	int nIndex=m_nPrims*PRIM_TRIANGLE;

	m_pVertexes[nIndex]=pTriangle->v[0];
	m_pVertexes[nIndex+1]=pTriangle->v[1];
	m_pVertexes[nIndex+2]=pTriangle->v[2];
	m_nPrims++;

	return S_OK;
}

STDMETHODIMP CRendererImpl::RenderQuad(PQUAD pQuad)
{
	if (pQuad==NULL) return E_POINTER;
	assert(m_lpD3DDevice!=NULL && m_lpD3DVertexBuf!=NULL);
	if (m_pVertexes==NULL) m_lpD3DVertexBuf->Lock(0, 0, (void**)&m_pVertexes, 0);
	if(m_dwCurPrim!=PRIM_QUAD || m_nPrims>=VERTEX_BUFFER_SIZE/PRIM_QUAD
		|| m_dwCurBlend!=pQuad->dwBlend || m_hCurTex!=pQuad->hTex)
	{
		RenderBatch();
		m_dwCurPrim=PRIM_QUAD;
		SetBlendMode(pQuad->dwBlend);
		m_dwCurBlend=pQuad->dwBlend;
		m_lpD3DDevice->SetTexture(0, (LPDIRECT3DTEXTURE9)pQuad->hTex);
		m_hCurTex=pQuad->hTex;
	}

	int nIndex=m_nPrims*PRIM_QUAD;

	m_pVertexes[nIndex]=pQuad->v[0];
	m_pVertexes[nIndex+1]=pQuad->v[1];
	m_pVertexes[nIndex+2]=pQuad->v[2];
	m_pVertexes[nIndex+3]=pQuad->v[2];
	m_pVertexes[nIndex+4]=pQuad->v[3];
	m_pVertexes[nIndex+5]=pQuad->v[0];
	m_nPrims++;
	return S_OK;
}

STDMETHODIMP CRendererImpl::Shotsnap(LPCSTR lpcszPath, DWORD dwIFF/* =IFF_BMP */)
{
	assert(m_lpD3DDevice!=NULL);

	
	LPDIRECT3DSURFACE9 lpD3DSurface;
	HRESULT hr=m_lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpD3DSurface);

	if (FAILED(hr)) return hr;
	hr=D3DXSaveSurfaceToFile(lpcszPath, (D3DXIMAGE_FILEFORMAT)dwIFF, lpD3DSurface, NULL, NULL);
	lpD3DSurface->Release();
	return hr;
}

STDMETHODIMP_(HTEXTURE) CRendererImpl::Texture_Create(int nWidth, int nHeight)
{
	assert(m_lpD3DDevice!=NULL);

	LPDIRECT3DTEXTURE9 lpD3DTex;

	if (FAILED(D3DXCreateTexture(m_lpD3DDevice, nWidth, nHeight, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &lpD3DTex))) return NULL;
	Texture_Append(lpD3DTex);
	return (HTEXTURE)lpD3DTex;
}

STDMETHODIMP_(HTEXTURE) CRendererImpl::Texture_Load(LPCSTR lpcszPath)
{
	assert(m_lpD3DDevice!=NULL);

	LPDIRECT3DTEXTURE9 lpD3DTex;

	if (FAILED(D3DXCreateTextureFromFile(m_lpD3DDevice, lpcszPath, &lpD3DTex))) return NULL;
	Texture_Append(lpD3DTex);
	return (HTEXTURE)lpD3DTex;
}

STDMETHODIMP CRendererImpl::Texture_Free(HTEXTURE hTex)
{
	if (hTex==NULL) return E_HANDLE;
	Texture_Remove((LPDIRECT3DTEXTURE9)hTex);
	return S_OK;
}

STDMETHODIMP_(void*) CRendererImpl::Texture_Lock(HTEXTURE hTex, BOOL bReadOnly/* =TRUE */,
												 int x/* =0 */, int y/* =0 */, int w/* =0 */, int h/* =0 */)
{
	if (hTex==NULL) return NULL;

	D3DSURFACE_DESC D3Dsd;
	DWORD dwFlags=0;
	RECT rectRegion;
	LPRECT lpRect=NULL;
	D3DLOCKED_RECT D3Dlr;

	if (FAILED(((LPDIRECT3DTEXTURE9)hTex)->GetLevelDesc(0, &D3Dsd))) return NULL;
	if (D3Dsd.Format!=D3DFMT_X8R8G8B8 && D3Dsd.Format!=D3DFMT_A8R8G8B8) return NULL;
	if (bReadOnly) dwFlags=D3DLOCK_READONLY;
	if (w!=0 && h!=0)
	{
		rectRegion.left=x;
		rectRegion.top=y;
		rectRegion.right=x+w;
		rectRegion.bottom=y+h;
		lpRect=&rectRegion;
	}
	if (FAILED(((LPDIRECT3DTEXTURE9)hTex)->LockRect(0, &D3Dlr, lpRect, dwFlags))) return NULL;
	return D3Dlr.pBits;
}

STDMETHODIMP CRendererImpl::Texture_Unlock(HTEXTURE hTex)
{
	if (hTex==NULL) return E_HANDLE;
	((LPDIRECT3DTEXTURE9)hTex)->UnlockRect(0);
	return S_OK;
}

STDMETHODIMP_(int) CRendererImpl::Texture_GetWidth(HTEXTURE hTex)
{
	if (hTex==NULL) return 0;

	D3DSURFACE_DESC D3Dsd;

	if(FAILED(((LPDIRECT3DTEXTURE9)hTex)->GetLevelDesc(0, &D3Dsd))) return 0;
	return D3Dsd.Width;
}

STDMETHODIMP_(int) CRendererImpl::Texture_GetHeight(HTEXTURE hTex)
{
	if (hTex==NULL) return 0;

	D3DSURFACE_DESC D3Dsd;

	if(FAILED(((LPDIRECT3DTEXTURE9)hTex)->GetLevelDesc(0, &D3Dsd))) return 0;
	return D3Dsd.Height;
}

STDMETHODIMP_(HFONTX) CRendererImpl::Font_Create(int nHeight, int nWidth, int nWeight, BOOL bItalic, LPCSTR lpcszFont)
{
	assert(m_lpD3DDevice!=NULL);

	LPD3DXFONT lpD3DFont;

	if (FAILED(D3DXCreateFont(m_lpD3DDevice, nHeight, nWidth, nWeight, 1, bItalic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		lpcszFont, &lpD3DFont))) return NULL;
	Font_Append(lpD3DFont);
	return (HFONTX)lpD3DFont;
}

STDMETHODIMP CRendererImpl::Font_Free(HFONTX hFont)
{
	if (hFont==NULL) return E_HANDLE;
	Font_Remove((LPD3DXFONT)hFont);
	return S_OK;
}

STDMETHODIMP_(int) CRendererImpl::Font_DrawText(HFONTX hFont, LPCSTR lpcszText, LPRECT lpRect, float z/* =0.0f */,
									   DWORD dwFormat/* =DT_TOP|DT_LEFT */, DWORD dwColor/* =0xFFFFFFFF */)
{
	if (hFont==NULL) return 0;

	D3DXMATRIX matrix;
	int nRes;

	m_lpD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixIdentity(&matrix);
	D3DXMatrixTranslation(&matrix, 0.0f, 0.0f, z);
	m_lpD3DSprite->SetTransform(&matrix);
	nRes=((LPD3DXFONT)hFont)->DrawText(m_lpD3DSprite, lpcszText, -1, lpRect, dwFormat, dwColor);
	m_lpD3DSprite->End();
	return nRes;
}

HRESULT CRendererImpl::InitLost()
{
	assert(m_lpD3DVertexBuf==NULL);
	
	HRESULT hr=m_lpD3DDevice->CreateVertexBuffer(sizeof(VERTEX)*VERTEX_BUFFER_SIZE,
		D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1, D3DPOOL_DEFAULT, &m_lpD3DVertexBuf, NULL);

	if (FAILED(hr)) return hr;
	m_lpD3DDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	m_lpD3DDevice->SetStreamSource(0, m_lpD3DVertexBuf, 0, sizeof(VERTEX));

	// 设置公共渲染状态
	m_lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_lpD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_lpD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_lpD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x01);
	m_lpD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	m_lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	m_lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, m_dwMagFilter);
	m_lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, m_dwMinFilter);

	m_nPrims=0;
	m_dwCurPrim=PRIM_QUAD;
	m_dwCurBlend=BLEND_DEFAULT;
	m_hCurTex=NULL;

	return S_OK;
}

void CRendererImpl::SetBlendMode(DWORD dwBlend)
{
	assert(m_lpD3DDevice!=NULL);
	if(dwBlend & BLEND_COLORADD) m_lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
	else m_lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	if(dwBlend & BLEND_ALPHABLEND) m_lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	else m_lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	if(dwBlend & BLEND_ZWRITE) m_lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	else m_lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void CRendererImpl::RenderBatch(bool bEndRender/* =false */)
{
	if (m_pVertexes==NULL) return;
	assert(m_lpD3DDevice!=NULL && m_lpD3DVertexBuf!=NULL);
	m_lpD3DVertexBuf->Unlock();
	m_pVertexes=NULL;
	if (m_nPrims>0)
	{
		switch (m_dwCurPrim)
		{
		case PRIM_LINE:
			m_lpD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nPrims);
			break;
		case PRIM_TRIANGLE:
			m_lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nPrims);
			break;
		case PRIM_QUAD:
			
			m_lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nPrims*2);
			break;
		}
		m_nPrims=0;
	}
	if (!bEndRender) m_lpD3DVertexBuf->Lock(0, 0, (void**)&m_pVertexes, 0);
}

void CRendererImpl::Texture_Append(LPDIRECT3DTEXTURE9 lpD3DTex)
{
	PTEXTURELIST pNode=new TEXTURELIST;

	pNode->lpD3DTex=lpD3DTex;
	pNode->pNext=m_pTexList;
	m_pTexList=pNode;
}

void CRendererImpl::Texture_Remove(LPDIRECT3DTEXTURE9 lpD3DTex)
{
	assert(m_pTexList!=NULL);
	if (m_pTexList->lpD3DTex==lpD3DTex)
	{
		PTEXTURELIST pNode=m_pTexList;

		m_pTexList=m_pTexList->pNext;
		lpD3DTex->Release();
		delete pNode;
	}
	else
	{
		for (PTEXTURELIST p=m_pTexList; p->pNext!=NULL; p=p->pNext)
		{
			if (p->pNext->lpD3DTex==lpD3DTex)
			{
				PTEXTURELIST pNode=p->pNext;

				p->pNext=pNode->pNext;
				lpD3DTex->Release();
				delete pNode;
				break;
			}
		}
	}
}

void CRendererImpl::Texture_RemoveAll()
{
	while (m_pTexList!=NULL)
	{
		PTEXTURELIST pNode=m_pTexList;

		m_pTexList=m_pTexList->pNext;
		pNode->lpD3DTex->Release();
		delete pNode;
	}
}

void CRendererImpl::Font_Append(LPD3DXFONT lpD3DFont)
{
	PFONTLIST pNode=new FONTLIST;

	pNode->lpD3DFont=lpD3DFont;
	pNode->pNext=m_pFontList;
	m_pFontList=pNode;
}

void CRendererImpl::Font_Remove(LPD3DXFONT lpD3DFont)
{
	assert(m_pFontList!=NULL);
	if (m_pFontList->lpD3DFont==lpD3DFont)
	{
		PFONTLIST pNode=m_pFontList;

		m_pFontList=m_pFontList->pNext;
		lpD3DFont->Release();
		delete pNode;
	}
	else
	{
		for (PFONTLIST p=m_pFontList; p->pNext!=NULL; p=p->pNext)
		{
			if (p->pNext->lpD3DFont==lpD3DFont)
			{
				PFONTLIST pNode=p->pNext;

				p->pNext=pNode->pNext;
				lpD3DFont->Release();
				delete pNode;
				break;
			}
		}
	}
}

void CRendererImpl::Font_RemoveAll()
{
	while (m_pFontList!=NULL)
	{
		PFONTLIST pNode=m_pFontList;

		m_pFontList=m_pFontList->pNext;
		pNode->lpD3DFont->Release();
		delete pNode;
	}
}

HRESULT CRendererImpl::Font_OnLostDevice()
{
	for (PFONTLIST p=m_pFontList; p!=NULL; p=p->pNext)
	{
		HRESULT hr=p->lpD3DFont->OnLostDevice();

		if (FAILED(hr)) return hr;
	}
	return m_lpD3DSprite->OnLostDevice();
}

HRESULT CRendererImpl::Font_OnResetDevice()
{
	for (PFONTLIST p=m_pFontList; p!=NULL; p=p->pNext)
	{
		HRESULT hr=p->lpD3DFont->OnResetDevice();

		if (FAILED(hr)) return hr;
	}
	return m_lpD3DSprite->OnResetDevice();
}
