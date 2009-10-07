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
#include "Button.h"

namespace RUGE
{

	CButton::CButton(int nID, float x, float y, float w, float h, HTEXTURE hTex, float tx, float ty)
		: CControl(nID)
		, m_bTrigger(FALSE)
		, m_bPressed(FALSE)
		, m_bOldState(FALSE)
		, m_psprUp(new CSprite(hTex, tx, ty, w, h))
		, m_psprDown(new CSprite(hTex, tx+w, ty, w, h))
	{
		m_bStatic=FALSE;
		m_bVisible=TRUE;
		m_bEnabled=TRUE;
		m_Rect.Set(x, y, x+w, y+h);

		m_psprUp->SetColor(m_dwColor);
		m_psprDown->SetColor(m_dwColor);
	}

	CButton::~CButton()
	{
		delete m_psprDown;
		delete m_psprUp;
	}

	void CButton::SetColor(DWORD dwColor)
	{
		CControl::SetColor(dwColor);

		m_psprUp->SetColor(m_dwColor);
		m_psprDown->SetColor(m_dwColor);
	}

	void CButton::SetMode(BOOL bTrigger)
	{
		m_bTrigger=bTrigger;
	}

	void CButton::SetState(BOOL bPressed)
	{
		m_bPressed=bPressed;
	}

	BOOL CButton::GetState() const
	{
		return m_bPressed;
	}

	void CButton::Render()
	{
		if (m_bPressed) m_psprDown->Render(m_Rect.x1, m_Rect.y1);
		else m_psprUp->Render(m_Rect.x1, m_Rect.y1);
	}

	BOOL CButton::MouseLBtn(BOOL bDown, float x, float y)
	{
		if(bDown)
		{
			m_bOldState=m_bPressed;
			m_bPressed=TRUE;
			return FALSE;
		}
		else
		{
			if(m_bTrigger) m_bPressed=!m_bOldState;
			else m_bPressed=FALSE;
			return TRUE;
		}
	}

}