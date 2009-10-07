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
#include "Slider.h"

namespace RUGE
{

	CSlider::CSlider(int nID, float x, float y, float w, float h, HTEXTURE hTex, float tx, float ty, float sw, float sh, BOOL bVertical/* =FALSE */)
		: CControl(nID)
		, m_bPressed(FALSE)
		, m_bVertical(bVertical)
		, m_dwMode(SLIDER_BAR)
		, m_fMin(0)
		, m_fMax(100)
		, m_fVal(50)
		, m_fSliderWidth(sw)
		, m_fSliderHeight(sh)
		, m_psprSlider(new CSprite(hTex, tx, ty, sw, sh))
	{
		m_bStatic=FALSE;
		m_bVisible=TRUE;
		m_bEnabled=TRUE;
		m_Rect.Set(x, y, x+w, y+h);

		m_psprSlider->SetColor(m_dwColor);
	}

	CSlider::~CSlider()
	{
		delete m_psprSlider;
	}

	void CSlider::SetColor(DWORD dwColor)
	{
		CControl::SetColor(dwColor);

		m_psprSlider->SetColor(m_dwColor);
	}

	void CSlider::SetMode(float fMin, float fMax, DWORD dwMode)
	{
		m_fMin=fMin;
		m_fMax=fMax;
		m_dwMode=dwMode;
	}

	void CSlider::SetValue(float fVal)
	{
		if (fVal<m_fMin) m_fVal=m_fMin;
		else if (fVal>m_fMax) m_fVal=m_fMax;
		else m_fVal=fVal;
	}

	float CSlider::GetValue() const
	{
		return m_fVal;
	}

	void CSlider::Render()
	{
		float x, y, x1, y1, x2, y2;

		x=m_Rect.x1+(m_Rect.x2-m_Rect.x1)*(m_fVal-m_fMin)/(m_fMax-m_fMin);
		y=m_Rect.y1+(m_Rect.y2-m_Rect.y1)*(m_fVal-m_fMin)/(m_fMax-m_fMin);

		if (m_bVertical)
		{
			switch (m_dwMode)
			{
			case SLIDER_BAR:
				x1=m_Rect.x1;
				y1=m_Rect.y1;
				x2=m_Rect.x2;
				y2=y;
				break;
			case SLIDER_BARRELATIVE:
				x1=m_Rect.x1;
				y1=(m_Rect.y1+m_Rect.y2)/2;
				x2=m_Rect.x2;
				y2=y;
				break;
			case SLIDER_SLIDER:
				x1=(m_Rect.x1+m_Rect.x2-m_fSliderWidth)/2;
				y1=y-m_fSliderHeight/2;
				x2=(m_Rect.x1+m_Rect.x2+m_fSliderWidth)/2;
				y2=y+m_fSliderHeight/2;
				break;
			}
		}
		else
		{
			switch (m_dwMode)
			{
			case SLIDER_BAR:
				x1=m_Rect.x1;
				y1=m_Rect.y1;
				x2=x;
				y2=m_Rect.y2;
				break;
			case SLIDER_BARRELATIVE:
				x1=(m_Rect.x1+m_Rect.x2)/2;
				y1=m_Rect.y1;
				x2=x;
				y2=m_Rect.y2;
				break;
			case SLIDER_SLIDER:
				x1=x-m_fSliderWidth/2;
				y1=(m_Rect.y1+m_Rect.y2-m_fSliderHeight)/2;
				x2=x+m_fSliderWidth/2;
				y2=(m_Rect.y1+m_Rect.y2+m_fSliderHeight)/2;
				break;
			}
		}

		m_psprSlider->RenderStretch(x1, y1, x2, y2);
	}

	BOOL CSlider::MouseLBtn(BOOL bDown, float x, float y)
	{
		m_bPressed=bDown;
		return MouseMove(x, y);
	}

	BOOL CSlider::MouseMove(float x, float y)
	{
		if (m_bPressed)
		{
			if(m_bVertical) SetValue(m_fMin+(m_fMax-m_fMin)*y/(m_Rect.y2-m_Rect.y1));
			else SetValue(m_fMin+(m_fMax-m_fMin)*x/(m_Rect.x2-m_Rect.x1));
			return TRUE;
		}
		return FALSE;
	}

}