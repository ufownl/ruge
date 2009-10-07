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

#ifndef _RUGE_SPRITE_H_
#define _RUGE_SPRITE_H_

#include "Rect.h"

namespace RUGE
{

	class CSprite
	{
	public:
		CSprite(HTEXTURE hTex, float x, float y, float w, float h);
		CSprite(const CSprite &Spr);
		virtual ~CSprite();

		CSprite& operator = (const CSprite &Spr);

		void Flip(BOOL bx, BOOL by, BOOL bHotSpot=FALSE);
		void Render(float x, float y);
		void RenderEx(float x, float y, float fRot=0.0f, float fHScale=1.0f, float fVScale=0.0f);
		void RenderStretch(float x1, float y1, float x2, float y2);
		void Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);

		void SetTexture(HTEXTURE hTex);
		void SetTextureRect(float x, float y, float w, float h);
		void SetColor(DWORD dwColor, int nIndex=-1);
		void SetZ(float z, int nIndex=-1);
		void SetBlendMode(DWORD dwBlend);
		void SetHotSpot(float x, float y);

		HTEXTURE GetTexture() const;
		void GetTextureRect(float *x, float *y, float *w, float *h) const;
		DWORD GetColor(int nIndex=0) const;
		float GetZ(int nIndex=0) const;
		DWORD GetBlendMode() const;
		void GetHotSpot(float *x, float *y) const;
		float GetWidth() const;
		float GetHeight() const;
		void GetBoundingBox(float x, float y, CRect *pRect) const;
		void GetBoundingBox(float x, float y, float fRot, float fHScale, float fVScale, CRect *pRect) const;

	protected:
		PAPPLICATION m_pApp;
		QUAD m_quadTex;
		float m_fLeft, m_fTop, m_fWidth, m_fHeight, m_fHotx, m_fHoty;
	};

}

#endif  // _RUGE_SPRITE_H_
