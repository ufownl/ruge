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
#include "RugeLuaGUI.h"
#include <GUI.h>

HGUI GUI_Create()
{
	return new RUGE::CGUI();
}

void GUI_Free(HGUI hGUI)
{
	delete (RUGE::CGUI*)hGUI;
}

int Lua_GUI_AddCtrl(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CGUI *pGUI=NULL;
	RUGE::CControl *pCtrl=NULL;
	BOOL bManaged=TRUE;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsBoolean()) bManaged=(BOOL)args[3].GetBoolean();
	case 2:
		if (args[1].IsLightUserData()) pGUI=(RUGE::CGUI*)args[1].GetLightUserData();
		if (args[2].IsLightUserData()) pCtrl=(RUGE::CControl*)args[2].GetLightUserData();
		break;
	}
	pGUI->AddCtrl(pCtrl, bManaged);
	return 0;
}

void GUI_DelCtrl(HGUI hGUI, int nID)
{
	((RUGE::CGUI*)hGUI)->DelCtrl(nID);
}

HCONTROL GUI_GetCtrl(HGUI hGUI, int nID)
{
	return ((RUGE::CGUI*)hGUI)->GetCtrl(nID);
}

HCONTROL GUI_MoveCtrl(HGUI hGUI, int nID, float x, float y)
{
	return ((RUGE::CGUI*)hGUI)->MoveCtrl(nID, x, y);
}

int Lua_GUI_ShowCtrl(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CGUI *pGUI=NULL;
	int nID=0;
	BOOL bVisible=TRUE;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsBoolean()) bVisible=(BOOL)args[3].GetBoolean();
	case 2:
		if (args[1].IsLightUserData()) pGUI=(RUGE::CGUI*)args[1].GetLightUserData();
		if (args[2].IsInteger()) nID=args[2].GetInteger();
		break;
	}

	lua->PushLightUserData(pGUI->ShowCtrl(nID, bVisible));
	return 1;
}

int Lua_GUI_EnableCtrl(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CGUI *pGUI=NULL;
	int nID=0;
	BOOL bEnabled=TRUE;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsBoolean()) bEnabled=(BOOL)args[3].GetBoolean();
	case 2:
		if (args[1].IsLightUserData()) pGUI=(RUGE::CGUI*)args[1].GetLightUserData();
		if (args[2].IsInteger()) nID=args[2].GetInteger();
		break;
	}

	lua->PushLightUserData(pGUI->EnableCtrl(nID, bEnabled));
	return 1;
}

void GUI_SetNavMode(HGUI hGUI, int nNavMode)
{
	((RUGE::CGUI*)hGUI)->SetNavMode(nNavMode);
}

void GUI_SetCursor(HGUI hGUI, HSPRITE hsprCursor)
{
	((RUGE::CGUI*)hGUI)->SetCursor((RUGE::CSprite*)hsprCursor);
}

void GUI_SetColor(HGUI hGUI, int nColor)
{
	((RUGE::CGUI*)hGUI)->SetColor(nColor);
}

void GUI_SetFocus(HGUI hGUI, int nID)
{
	((RUGE::CGUI*)hGUI)->SetFocus(nID);
}

int GUI_GetFocus(HGUI hGUI)
{
	return ((RUGE::CGUI*)hGUI)->GetFocus();
}

void GUI_Enter(HGUI hGUI)
{
	((RUGE::CGUI*)hGUI)->Enter();
}

void GUI_Exit(HGUI hGUI)
{
	((RUGE::CGUI*)hGUI)->Exit();
}

void GUI_Reset(HGUI hGUI)
{
	((RUGE::CGUI*)hGUI)->Reset();
}

void GUI_Move(HGUI hGUI, float dx, float dy)
{
	((RUGE::CGUI*)hGUI)->Move(dx, dy);
}

int GUI_Update(HGUI hGUI, float fDelta)
{
	return ((RUGE::CGUI*)hGUI)->Update(fDelta);
}

void GUI_Render(HGUI hGUI)
{
	((RUGE::CGUI*)hGUI)->Render();
}