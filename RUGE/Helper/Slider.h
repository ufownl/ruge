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

#ifndef _RUGE_SLIDER_H_
#define _RUGE_SLIDER_H_

#include "GUI.h"

#define SLIDER_BAR			0
#define SLIDER_BARRELATIVE	1
#define SLIDER_SLIDER		2

namespace RUGE
{

	class CSlider : public CControl
	{
	public:
		CSlider(int nID, float x, float y, float w, float h, HTEXTURE hTex, float tx, float ty, float sw, float sh, BOOL bVertical=FALSE);
		virtual ~CSlider();

		virtual void SetColor(DWORD dwColor);

		void SetMode(float fMin, float fMax, DWORD dwMode);
		void SetValue(float fVal);
		float GetValue() const;

	protected:
		virtual void Render();
		virtual BOOL MouseLBtn(BOOL bDown, float x, float y);
		virtual BOOL MouseMove(float x, float y);

	protected:
		BOOL m_bPressed, m_bVertical;
		DWORD m_dwMode;
		float m_fMin, m_fMax, m_fVal, m_fSliderWidth, m_fSliderHeight;
		CSprite *m_psprSlider;
	};

}

#endif  // _RUGE_SLIDER_H_