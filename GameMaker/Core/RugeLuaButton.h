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

typedef HANDLE HBUTTON;

int Lua_Button_Create(LuaPlus::LuaState *lua);
void Button_Free(HBUTTON hBtn);

void Button_SetColor(HBUTTON hBtn, int nColor);

void Button_SetMode(HBUTTON hBtn, bool bTrigger);
void Button_SetState(HBUTTON hBtn, bool bPressed);
bool Button_GetState(HBUTTON hBtn);