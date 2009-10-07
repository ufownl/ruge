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
#include "Text.h"

namespace RUGE
{

	CText::CText(int nID, float x, float y, float w, float h, HFONT hFont)
		: CControl(nID)
		, m_hFont(hFont)
		, m_dwMode(DT_TOP|DT_LEFT)
	{
		m_bStatic=TRUE;
		m_bVisible=TRUE;
		m_bEnabled=TRUE;
		m_Rect.Set(x, y, x+w, y+h);

		memset(m_szText, 0, sizeof(m_szText));
	}

	CText::~CText()
	{
	}

	void CText::SetMode(DWORD dwMode)
	{
		m_dwMode=dwMode;
	}

	void CText::SetText(LPCSTR lpcszText)
	{
		strcpy(m_szText, lpcszText);
	}

	void CText::Render()
	{
		RECT rect={(LONG)m_Rect.x1, (LONG)m_Rect.y1, (LONG)m_Rect.x2, (LONG)m_Rect.y2};

		m_pApp->Font_DrawText(m_hFont, m_szText, &rect, 0, m_dwMode, m_dwColor);
	}

}