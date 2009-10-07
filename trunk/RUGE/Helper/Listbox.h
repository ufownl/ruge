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

#ifndef _RUGE_LISTBOX_H_
#define _RUGE_LISTBOX_H_

#include "GUI.h"

namespace RUGE
{

	typedef struct LISTBOXITEM
	{
		char szText[256];
		LISTBOXITEM *pNext;
	} *PLISTBOXITEM;

	class CListbox : public CControl
	{
	public:
		CListbox(int nID, float x, float y, float w, float h, HFONT hFont, DWORD dwTextColor, DWORD dwTextHLColor, DWORD dwHLColor);
		virtual ~CListbox();

		int AddItem(LPCSTR lpcszItem);
		void DelItem(int n);

		void SetSelected(int n);
		void SetTop(int n);
		void SetItemText(int n, LPCSTR lpcszItem);

		int GetSelected() const;
		int GetTop() const;
		LPCSTR GetItemText(int n) const;
		int GetNumItems() const;
		int GetNumRows() const;

		void Clear();

	protected:
		virtual void Render();
		virtual BOOL MouseLBtn(BOOL bDown, float x, float y);
		virtual void MouseOver(BOOL bOver);
		virtual BOOL MouseWheel(SHORT nWheel);
		virtual BOOL KeyClick(int nVKey, char chChar);

	protected:
		HFONT m_hFont;
		DWORD m_dwTextColor, m_dwTextHLColor, m_dwHLColor;
		int m_nItems, m_nSelected, m_nTop, m_nRowHeight, m_nRows, m_nWheel;
		CSprite *m_psprHighlight;
		PLISTBOXITEM m_pItemList;
	};

}

#endif  // _RUGE_LISTBOX_H_