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

#include "RugeLuaRect.h"

typedef HANDLE HCONTROL;
typedef HANDLE HGUI;

int Lua_Control_Create(LuaPlus::LuaState *lua);
void Control_Free(HCONTROL hCtrl);

void Control_SetStatic(HCONTROL hCtrl, bool bStatic);
void Control_SetVisible(HCONTROL hCtrl, bool bVisible);
void Control_SetEnabled(HCONTROL hCtrl, bool bEnabled);
int Lua_Control_SetRect(LuaPlus::LuaState *lua);
void Control_SetColor(HCONTROL hCtrl, int nColor);
int Lua_Control_SetAttribute(LuaPlus::LuaState *lua);

HGUI Control_GetGUI(HCONTROL hCtrl);
int Control_GetID(HCONTROL hCtrl);
bool Control_GetStatic(HCONTROL hCtrl);
bool Control_GetVisible(HCONTROL hCtrl);
bool Control_GetEnabled(HCONTROL hCtrl);
int Lua_Control_GetRect(LuaPlus::LuaState *lua);
int Control_GetColor(HCONTROL hCtrl);
int Lua_Control_GetAttribute(LuaPlus::LuaState *lua);