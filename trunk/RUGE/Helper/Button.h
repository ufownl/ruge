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

#ifndef _RUGE_BUTTON_H_
#define _RUGE_BUTTON_H_

#include "GUI.h"

namespace RUGE
{

	class CButton : public CControl
	{
	public:
		CButton(int nID, float x, float y, float w, float h, HTEXTURE hTex, float tx, float ty);
		virtual ~CButton();

		virtual void SetColor(DWORD dwColor);

		void SetMode(BOOL bTrigger);
		void SetState(BOOL bPressed);
		BOOL GetState() const;

	protected:
		virtual void Render();
		virtual BOOL MouseLBtn(BOOL bDown, float x, float y);

	protected:
		BOOL m_bTrigger, m_bPressed, m_bOldState;
		CSprite *m_psprUp, *m_psprDown;
	};

}

#endif  // _RUGE_BUTTON_H_