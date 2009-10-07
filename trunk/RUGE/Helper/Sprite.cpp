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
#include "Sprite.h"

namespace RUGE
{

	CSprite::CSprite(HTEXTURE hTex, float x, float y, float w, float h)
		: m_pApp(GetRUGE())
	{
		for (int i=0; i<4; i++)
		{
			m_quadTex.v[i].x=0.0f;
			m_quadTex.v[i].y=0.0f;
			m_quadTex.v[i].rhw=1.0f;
		}
		SetTexture(hTex);
		SetTextureRect(x, y, w, h);
		SetColor(0xFFFFFFFF);
		SetZ(0.5f);
		SetBlendMode(BLEND_DEFAULT);
		SetHotSpot(0.0f, 0.0f);
	}

	CSprite::CSprite(const CSprite &Spr)
		: m_pApp(GetRUGE())
		, m_quadTex(Spr.m_quadTex)
		, m_fLeft(Spr.m_fLeft)
		, m_fTop(Spr.m_fTop)
		, m_fWidth(Spr.m_fWidth)
		, m_fHeight(Spr.m_fHeight)
		, m_fHotx(Spr.m_fHotx)
		, m_fHoty(Spr.m_fHoty)
	{
	}

	CSprite::~CSprite()
	{
		m_pApp->Release();
	}

	CSprite& CSprite::operator = (const CSprite &Spr)
	{
		if (this!=&Spr)
		{
			m_quadTex=Spr.m_quadTex;
			m_fLeft=Spr.m_fLeft;
			m_fTop=Spr.m_fTop;
			m_fWidth=Spr.m_fWidth;
			m_fHeight=Spr.m_fHeight;
			m_fHotx=Spr.m_fHotx;
			m_fHoty=Spr.m_fHoty;
		}
		return *this;
	}

	void CSprite::Flip(BOOL bx, BOOL by, BOOL bHotSpot/* =FALSE */)
	{
		float fTemp;

		if (bx)
		{
			if (bHotSpot) m_fHotx=m_fWidth-m_fHotx;

			fTemp=m_quadTex.v[0].tu;
			m_quadTex.v[0].tu=m_quadTex.v[1].tu;
			m_quadTex.v[1].tu=fTemp;

			fTemp=m_quadTex.v[0].tv;
			m_quadTex.v[0].tv=m_quadTex.v[1].tv;
			m_quadTex.v[1].tv=fTemp;

			fTemp=m_quadTex.v[2].tu;
			m_quadTex.v[2].tu=m_quadTex.v[3].tu;
			m_quadTex.v[3].tu=fTemp;

			fTemp=m_quadTex.v[2].tv;
			m_quadTex.v[2].tv=m_quadTex.v[3].tv;
			m_quadTex.v[3].tv=fTemp;
		}
		if (by)
		{
			if (bHotSpot) m_fHoty=m_fHeight-m_fHoty;

			fTemp=m_quadTex.v[0].tu;
			m_quadTex.v[0].tu=m_quadTex.v[3].tu;
			m_quadTex.v[3].tu=fTemp;

			fTemp=m_quadTex.v[0].tv;
			m_quadTex.v[0].tv=m_quadTex.v[3].tv;
			m_quadTex.v[3].tv=fTemp;

			fTemp=m_quadTex.v[1].tu;
			m_quadTex.v[1].tu=m_quadTex.v[2].tu;
			m_quadTex.v[2].tu=fTemp;

			fTemp=m_quadTex.v[1].tv;
			m_quadTex.v[1].tv=m_quadTex.v[2].tv;
			m_quadTex.v[2].tv=fTemp;
		}
	}

	void CSprite::Render(float x, float y)
	{
		float x1, y1, x2, y2;

		x1=x-m_fHotx;
		y1=y-m_fHoty;
		x2=x+m_fWidth-m_fHotx;
		y2=y+m_fHeight-m_fHoty;

		m_quadTex.v[0].x=x1;
		m_quadTex.v[0].y=y1;
		m_quadTex.v[1].x=x2;
		m_quadTex.v[1].y=y1;
		m_quadTex.v[2].x=x2;
		m_quadTex.v[2].y=y2;
		m_quadTex.v[3].x=x1;
		m_quadTex.v[3].y=y2;

		m_pApp->Gfx_RenderQuad(&m_quadTex);
	}

	void CSprite::RenderEx(float x, float y, float fRot/* =0.0f */, float fHScale/* =1.0f */, float fVScale/* =0.0f */)
	{
		if (fVScale==0) fVScale=fHScale;

		float tx1=(-m_fHotx)*fHScale, ty1=(-m_fHoty)*fVScale, tx2=(m_fWidth-m_fHotx)*fHScale
			, ty2=(m_fHeight-m_fHoty)*fVScale;

		if (fRot!=0.0f)
		{
			float fCost=cosf(fRot), fSint=sinf(fRot);

			m_quadTex.v[0].x=tx1*fCost-ty1*fSint+x;
			m_quadTex.v[0].y=tx1*fSint+ty1*fCost+y;
			m_quadTex.v[1].x=tx2*fCost-ty1*fSint+x;
			m_quadTex.v[1].y=tx2*fSint+ty1*fCost+y;
			m_quadTex.v[2].x=tx2*fCost-ty2*fSint+x;
			m_quadTex.v[2].y=tx2*fSint+ty2*fCost+y;
			m_quadTex.v[3].x=tx1*fCost-ty2*fSint+x;
			m_quadTex.v[3].y=tx1*fSint+ty2*fCost+y;
		}
		else
		{
			m_quadTex.v[0].x=tx1+x;
			m_quadTex.v[0].y=ty1+y;
			m_quadTex.v[1].x=tx2+x;
			m_quadTex.v[1].y=ty1+y;
			m_quadTex.v[2].x=tx2+x;
			m_quadTex.v[2].y=ty2+y;
			m_quadTex.v[3].x=tx1+x;
			m_quadTex.v[3].y=ty2+y;
		}
		m_pApp->Gfx_RenderQuad(&m_quadTex);
	}

	void CSprite::RenderStretch(float x1, float y1, float x2, float y2)
	{
		m_quadTex.v[0].x=x1;
		m_quadTex.v[0].y=y1;
		m_quadTex.v[1].x=x2;
		m_quadTex.v[1].y=y1;
		m_quadTex.v[2].x=x2;
		m_quadTex.v[2].y=y2;
		m_quadTex.v[3].x=x1;
		m_quadTex.v[3].y=y2;
		m_pApp->Gfx_RenderQuad(&m_quadTex);
	}

	void CSprite::Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
	{
		m_quadTex.v[0].x=x0;
		m_quadTex.v[0].y=y0;
		m_quadTex.v[1].x=x1;
		m_quadTex.v[1].y=y1;
		m_quadTex.v[2].x=x2;
		m_quadTex.v[2].y=y2;
		m_quadTex.v[3].x=x3;
		m_quadTex.v[3].y=y3;
		m_pApp->Gfx_RenderQuad(&m_quadTex);
	}

	void CSprite::SetTexture(HTEXTURE hTex)
	{
		m_quadTex.hTex=hTex;
	}

	void CSprite::SetTextureRect(float x, float y, float w, float h)
	{
		m_fLeft=x;
		m_fTop=y;
		m_fWidth=w;
		m_fHeight=h;

		float tu1=0.0f, tv1=0.0f, tu2=1.0f, tv2=1.0f;

		if (m_quadTex.hTex!=NULL)
		{
			int nTexWidth=m_pApp->Texture_GetWidth(m_quadTex.hTex),
				nTexHeight=m_pApp->Texture_GetHeight(m_quadTex.hTex);

			tu1=x/nTexWidth;
			tv1=y/nTexHeight;
			tu2=(x+w)/nTexWidth;
			tv2=(y+h)/nTexHeight;
		}
		m_quadTex.v[0].tu=tu1;
		m_quadTex.v[0].tv=tv1;
		m_quadTex.v[1].tu=tu2;
		m_quadTex.v[1].tv=tv1;
		m_quadTex.v[2].tu=tu2;
		m_quadTex.v[2].tv=tv2;
		m_quadTex.v[3].tu=tu1;
		m_quadTex.v[3].tv=tv2;
	}

	void CSprite::SetColor(DWORD dwColor, int nIndex/* =-1 */)
	{
		if (0<=nIndex && nIndex<=3) m_quadTex.v[nIndex].dwColor=dwColor;
		else
		{
			for (int i=0; i<4; i++) m_quadTex.v[i].dwColor=dwColor;
		}
	}

	void CSprite::SetZ(float z, int nIndex/* =-1 */)
	{
		if (0<=nIndex && nIndex<=3) m_quadTex.v[nIndex].z=z;
		else
		{
			for (int i=0; i<4; i++) m_quadTex.v[i].z=z;
		}
	}

	void CSprite::SetBlendMode(DWORD dwBlend)
	{
		m_quadTex.dwBlend=dwBlend;
	}

	void CSprite::SetHotSpot(float x, float y)
	{
		m_fHotx=x;
		m_fHoty=y;
	}

	HTEXTURE CSprite::GetTexture() const
	{
		return m_quadTex.hTex;
	}

	void CSprite::GetTextureRect(float *x, float *y, float *w, float *h) const
	{
		*x=m_fLeft;
		*y=m_fTop;
		*w=m_fWidth;
		*h=m_fHeight;
	}

	DWORD CSprite::GetColor(int nIndex/* =0 */) const
	{
		return m_quadTex.v[nIndex].dwColor;
	}

	float CSprite::GetZ(int nIndex/* =0 */) const
	{
		return m_quadTex.v[nIndex].z;
	}

	DWORD CSprite::GetBlendMode() const
	{
		return m_quadTex.dwBlend;
	}

	void CSprite::GetHotSpot(float *x, float *y) const
	{
		*x=m_fHotx;
		*y=m_fHoty;
	}

	float CSprite::GetWidth() const
	{
		return m_fWidth;
	}

	float CSprite::GetHeight() const
	{
		return m_fHeight;
	}

	void CSprite::GetBoundingBox(float x, float y, CRect *pRect) const
	{
		pRect->Set(x-m_fHotx, y-m_fHoty, x-m_fHotx+m_fWidth, y-m_fHoty+m_fHeight);
	}

	void CSprite::GetBoundingBox(float x, float y, float fRot, float fHScale, float fVScale, CRect *pRect) const
	{
		pRect->Clear();
		if (fVScale==0) fVScale=fHScale;

		float tx1=(-m_fHotx)*fHScale, ty1=(-m_fHoty)*fVScale, tx2=(m_fWidth-m_fHotx)*fHScale
			, ty2=(m_fHeight-m_fHoty)*fVScale;

		if (fRot!=0.0f)
		{
			float fCost=cosf(fRot), fSint=sinf(fRot);

			pRect->Encapsulate(tx1*fCost-ty1*fSint+x, tx1*fSint+ty1*fCost+y);
			pRect->Encapsulate(tx2*fCost-ty1*fSint+x, tx2*fSint+ty1*fCost+y);
			pRect->Encapsulate(tx2*fCost-ty2*fSint+x, tx2*fSint+ty2*fCost+y);
			pRect->Encapsulate(tx1*fCost-ty2*fSint+x, tx1*fSint+ty2*fCost+y);
		}
		else
		{
			pRect->Encapsulate(tx1+x, ty1+y);
			pRect->Encapsulate(tx2+x, ty1+y);
			pRect->Encapsulate(tx2+x, ty2+y);
			pRect->Encapsulate(tx1+x, ty2+y);
		}
	}

}