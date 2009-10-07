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

#ifndef _RUGE_GUI_H_
#define _RUGE_GUI_H_

#include "Control.h"
#include "Sprite.h"

#define NAV_NONAVKEYS	0
#define NAV_LEFTRIGHT	1
#define NAV_UPDOWN		2
#define NAV_CYCLED		4

namespace RUGE
{

	class CGUI
	{
	public:
		CGUI();
		virtual ~CGUI();

		void AddCtrl(CControl *pCtrl, BOOL bManaged=TRUE);
		void DelCtrl(int nID);
		CControl* GetCtrl(int nID) const;
		CControl* MoveCtrl(int nID, float x, float y);
		CControl* ShowCtrl(int nID, BOOL bVisible=TRUE);
		CControl* EnableCtrl(int nID, BOOL bEnabled=TRUE);

		void SetNavMode(DWORD dwNavMode);
		void SetCursor(CSprite *psprCursor);
		void SetColor(DWORD dwColor);
		void SetFocus(int nID);
		int GetFocus() const;

		void Enter();
		void Exit();
		void Reset();
		void Move(float dx, float dy);

		int Update(float fDelta);
		void Render();

	protected:
		CGUI(const CGUI&);
		CGUI& operator = (const CGUI&);

		BOOL ProcessCtrl(CControl *pCtrl);

	protected:
		PAPPLICATION m_pApp;
		CControl *m_pCtrlList, *m_pCtrlLock, *m_pCtrlFocus, *m_pCtrlOver;
		DWORD m_dwNavMode;
		int m_nEnterExit;
		CSprite *m_psprCursor;
		float m_fCurX, m_fCurY, m_fOldX, m_fOldY;
		SHORT m_nWheel, m_nWheelOld;
		BOOL m_bLPressed, m_bLReleased, m_bRPressed, m_bRReleased;
	};

}

#endif  // _RUGE_GUI_H_
