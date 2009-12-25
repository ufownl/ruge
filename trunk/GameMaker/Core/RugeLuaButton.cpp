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
#include "RugeLuaButton.h"
#include <Button.h>

int Lua_Button_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nID=0;
	float x=0, y=0, w=0, h=0;
	RUGE::HTEXTURE hTex=NULL;
	float tx=0, ty=0;

	if (args.Count()==8)
	{
		if (args[1].IsInteger()) nID=args[1].GetInteger();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		if (args[4].IsNumber()) w=args[4].GetFloat();
		if (args[5].IsNumber()) h=args[5].GetFloat();
		if (args[6].IsLightUserData()) hTex=args[6].GetLightUserData();
		if (args[7].IsNumber()) tx=args[7].GetFloat();
		if (args[8].IsNumber()) ty=args[8].GetFloat();
	}

	lua->PushLightUserData(new RUGE::CButton(nID, x, y, w, h, hTex, tx, ty));
	return 1;
}

void Button_Free(HBUTTON hBtn)
{
	delete (RUGE::CButton*)hBtn;
}

void Button_SetColor(HBUTTON hBtn, int nColor)
{
	((RUGE::CButton*)hBtn)->SetColor(nColor);
}

void Button_SetMode(HBUTTON hBtn, bool bTrigger)
{
	((RUGE::CButton*)hBtn)->SetMode((BOOL)bTrigger);
}

void Button_SetState(HBUTTON hBtn, bool bPressed)
{
	((RUGE::CButton*)hBtn)->SetState((BOOL)bPressed);
}

bool Button_GetState(HBUTTON hBtn)
{
	return ((RUGE::CButton*)hBtn)->GetState() ? true : false;
}