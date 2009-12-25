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

#include "RugeLuaControl.h"
#include "RugeLuaButton.h"
#include "RugeLuaListbox.h"
#include "RugeLuaSlider.h"
#include "RugeLuaText.h"
#include "RugeLuaSprite.h"

#define NAV_NONAVKEYS	0
#define NAV_LEFTRIGHT	1
#define NAV_UPDOWN		2
#define NAV_CYCLED		4

HGUI GUI_Create();
void GUI_Free(HGUI hGUI);

int Lua_GUI_AddCtrl(LuaPlus::LuaState *lua);
void GUI_DelCtrl(HGUI hGUI, int nID);
HCONTROL GUI_GetCtrl(HGUI hGUI, int nID);
HCONTROL GUI_MoveCtrl(HGUI hGUI, int nID, float x, float y);
int Lua_GUI_ShowCtrl(LuaPlus::LuaState *lua);
int Lua_GUI_EnableCtrl(LuaPlus::LuaState *lua);

void GUI_SetNavMode(HGUI hGUI, int nNavMode);
void GUI_SetCursor(HGUI hGUI, HSPRITE hsprCursor);
void GUI_SetColor(HGUI hGUI, int nColor);
void GUI_SetFocus(HGUI hGUI, int nID);
int GUI_GetFocus(HGUI hGUI);

void GUI_Enter(HGUI hGUI);
void GUI_Exit(HGUI hGUI);
void GUI_Reset(HGUI hGUI);
void GUI_Move(HGUI hGUI, float dx, float dy);

int GUI_Update(HGUI hGUI, float fDelta);
void GUI_Render(HGUI hGUI);