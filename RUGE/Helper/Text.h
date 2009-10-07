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

#ifndef _RUGE_TEXT_H_
#define _RUGE_TEXT_H_

#include "GUI.h"

namespace RUGE
{

	class CText : public CControl
	{
	public:
		CText(int nID, float x, float y, float w, float h, HFONT hFont);
		virtual ~CText();

		void SetMode(DWORD dwMode);
		void SetText(LPCSTR lpcszText);

	protected:
		virtual void Render();

	protected:
		HFONT m_hFont;
		DWORD m_dwMode;
		char m_szText[256];
	};

}

#endif  // _RUGE_TEXT_H_