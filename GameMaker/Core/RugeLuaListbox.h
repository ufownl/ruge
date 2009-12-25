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

#pragma once

typedef HANDLE HLISTBOX;

int Lua_Listbox_Create(LuaPlus::LuaState *lua);
void Listbox_Free(HLISTBOX hListbox);

void Listbox_SetColor(HLISTBOX hListbox, int nColor);

int Listbox_AddItem(HLISTBOX hListbox, LPCSTR lpcszItem);
void Listbox_DelItem(HLISTBOX hListbox, int n);

void Listbox_SetSelected(HLISTBOX hListbox, int n);
void Listbox_SetTop(HLISTBOX hListbox, int n);
void Listbox_SetItemText(HLISTBOX hListbox, int n, LPCSTR lpcszItem);

int Listbox_GetSelected(HLISTBOX hListbox);
int Listbox_GetTop(HLISTBOX hListbox);
LPCSTR Listbox_GetItemText(HLISTBOX hListbox, int n);
int Listbox_GetNumItems(HLISTBOX hListbox);
int Listbox_GetNumRows(HLISTBOX hListbox);

void Listbox_Clear(HLISTBOX hListbox);