/*
RUGE GameMaker Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE GameMaker.

RUGE GameMaker is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE GameMaker is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE GameMaker.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "RugeLuaListbox.h"
#include <Listbox.h>

int Lua_Listbox_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nID=0;
	float x=0, y=0, w=0, h=0;
	RUGE::HFONT hFont=NULL;
	DWORD dwTextColor=0, dwTextHLColor=0, dwHLColor=0;

	if (args.Count()==9)
	{
		if (args[1].IsInteger()) nID=args[1].GetInteger();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		if (args[4].IsNumber()) w=args[4].GetFloat();
		if (args[5].IsNumber()) h=args[5].GetFloat();
		if (args[6].IsLightUserData()) hFont=args[6].GetLightUserData();
		if (args[7].IsInteger()) dwTextColor=args[7].GetInteger();
		if (args[8].IsInteger()) dwTextHLColor=args[8].GetInteger();
		if (args[9].IsInteger()) dwHLColor=args[9].GetInteger();
	}

	lua->PushLightUserData(new RUGE::CListbox(nID, x, y, w, h, hFont, dwTextColor, dwTextHLColor, dwHLColor));
	return 1;
}

void Listbox_Free(HLISTBOX hListbox)
{
	delete (RUGE::CListbox*)hListbox;
}

void Listbox_SetColor(HLISTBOX hListbox, int nColor)
{
	((RUGE::CListbox*)hListbox)->SetColor(nColor);
}

int Listbox_AddItem(HLISTBOX hListbox, LPCSTR lpcszItem)
{
	return ((RUGE::CListbox*)hListbox)->AddItem(lpcszItem);
}

void Listbox_DelItem(HLISTBOX hListbox, int n)
{
	((RUGE::CListbox*)hListbox)->DelItem(n);
}

void Listbox_SetSelected(HLISTBOX hListbox, int n)
{
	((RUGE::CListbox*)hListbox)->SetSelected(n);
}

void Listbox_SetTop(HLISTBOX hListbox, int n)
{
	((RUGE::CListbox*)hListbox)->SetTop(n);
}

void Listbox_SetItemText(HLISTBOX hListbox, int n, LPCSTR lpcszItem)
{
	((RUGE::CListbox*)hListbox)->SetItemText(n, lpcszItem);
}

int Listbox_GetSelected(HLISTBOX hListbox)
{
	return ((RUGE::CListbox*)hListbox)->GetSelected();
}

int Listbox_GetTop(HLISTBOX hListbox)
{
	return ((RUGE::CListbox*)hListbox)->GetTop();
}

LPCSTR Listbox_GetItemText(HLISTBOX hListbox, int n)
{
	return ((RUGE::CListbox*)hListbox)->GetItemText(n);
}

int Listbox_GetNumItems(HLISTBOX hListbox)
{
	return ((RUGE::CListbox*)hListbox)->GetNumItems();
}

int Listbox_GetNumRows(HLISTBOX hListbox)
{
	return ((RUGE::CListbox*)hListbox)->GetNumRows();
}

void Listbox_Clear(HLISTBOX hListbox)
{
	((RUGE::CListbox*)hListbox)->Clear();
}