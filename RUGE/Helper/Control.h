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

#ifndef _RUGE_CONTROL_H_
#define _RUGE_CONTROL_H_

#include "Rect.h"

namespace RUGE
{

	class CControl
	{
		friend class CGUI;

	public:
		CControl(int nID);
		virtual ~CControl();

		virtual void SetColor(DWORD dwColor);

	protected:
		CControl(const CControl&);
		CControl& operator = (const CControl&);

		virtual void Render()=0;
		virtual void Update(float fDelta);

		virtual void Enter();
		virtual void Exit();
		virtual void Reset();
		virtual BOOL IsDone();
		virtual void Focus(BOOL bFocused);
		virtual void MouseOver(BOOL bOver);

		virtual BOOL MouseMove(float x, float y);
		virtual BOOL MouseLBtn(BOOL bDown, float x, float y);
		virtual BOOL MouseRBtn(BOOL bDown, float x, float y);
		virtual BOOL MouseWheel(SHORT nWheel);
		virtual BOOL KeyClick(int nVKey, char chChar);

	protected:
		PAPPLICATION m_pApp;
		CGUI *m_pGUI;
		int m_nID;
		BOOL m_bStatic, m_bVisible, m_bEnabled, m_bManaged;
		CRect m_Rect;
		DWORD m_dwColor;
		CControl *m_pPrev, *m_pNext;
	};

}

#endif  // _RUGE_CONTROL_H_
