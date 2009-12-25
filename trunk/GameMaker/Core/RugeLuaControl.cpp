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
#include "RugeLuaControl.h"
#include "CustomCtrl.h"
#include "Table.h"

int Lua_Control_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nID=0;
	LPCSTR lpcszPath=NULL;
	CCustomCtrl *pCtrl=NULL;
	
	if (args.Count()>=2)
	{
		if (args[1].IsInteger()) nID=args[1].GetInteger();
		if (args[2].IsString()) lpcszPath=args[2].GetString();
		pCtrl=new CCustomCtrl(nID, lpcszPath);
		if (args.Count()>=3 && args[3].IsTable()) TableCopy(&pCtrl->GetLua()->GetGlobals().CreateTable("Attribute"), &args[3]);
	}
	if (pCtrl->GetLua()->GetGlobal("Construct").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Construct=pCtrl->GetLua()->GetGlobal("Construct");

		Lua_Construct(pCtrl);
	}

	lua->PushLightUserData(pCtrl);
	return 1;
}

void Control_Free(HCONTROL hCtrl)
{
	delete (CCustomCtrl*)hCtrl;
}

void Control_SetStatic(HCONTROL hCtrl, bool bStatic)
{
	((CCustomCtrl*)hCtrl)->SetStatic((BOOL)bStatic);
}

void Control_SetVisible(HCONTROL hCtrl, bool bVisible)
{
	((CCustomCtrl*)hCtrl)->SetVisible((BOOL)bVisible);
}

void Control_SetEnabled(HCONTROL hCtrl, bool bEnabled)
{
	((CCustomCtrl*)hCtrl)->SetEnabled((BOOL)bEnabled);
}

int Lua_Control_SetRect(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	CCustomCtrl *pCtrl=NULL;
	float fLeft=0, fTop=0, fRight=0, fBottom=0;

	if (args.Count()==2)
	{
		if (args[1].IsLightUserData()) pCtrl=(CCustomCtrl*)args[1].GetLightUserData();
		if (args[2].IsTable())
		{
			if (args[2]["Left"].IsNumber()) fLeft=args[2]["Left"].GetFloat();
			if (args[2]["Top"].IsNumber()) fTop=args[2]["Top"].GetFloat();
			if (args[2]["Right"].IsNumber()) fRight=args[2]["Right"].GetFloat();
			if (args[2]["Bottom"].IsNumber()) fBottom=args[2]["Bottom"].GetFloat();
		}
	}

	RUGE::CRect rect(fLeft, fTop, fRight, fBottom);

	pCtrl->SetRect(&rect);
	return 0;
}

void Control_SetColor(HCONTROL hCtrl, int nColor)
{
	((CCustomCtrl*)hCtrl)->SetColor(nColor);
}

int Lua_Control_SetAttribute(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	CCustomCtrl *pCtrl=NULL;
	LuaPlus::LuaStackObject Attr;

	if (args.Count()==2)
	{
		if (args[1].IsLightUserData()) pCtrl=(CCustomCtrl*)args[1].GetLightUserData();
		if (args[2].IsTable()) Attr=args[2];
	}
	TableCopy(&pCtrl->GetLua()->GetGlobal("Attribute"), &Attr);
	return 0;
}

HGUI Control_GetGUI(HCONTROL hCtrl)
{
	return (HGUI)((CCustomCtrl*)hCtrl)->GetGUI();
}

int Control_GetID(HCONTROL hCtrl)
{
	return ((CCustomCtrl*)hCtrl)->GetID();
}

bool Control_GetStatic(HCONTROL hCtrl)
{
	return ((CCustomCtrl*)hCtrl)->GetStatic() ? true : false;
}

bool Control_GetVisible(HCONTROL hCtrl)
{
	return ((CCustomCtrl*)hCtrl)->GetVisible() ? true : false;
}

bool Control_GetEnabled(HCONTROL hCtrl)
{
	return ((CCustomCtrl*)hCtrl)->GetEnabled() ? true : false;
}

int Lua_Control_GetRect(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	CCustomCtrl *pCtrl=NULL;

	if (args.Count()==1 && args[1].IsLightUserData()) pCtrl=(CCustomCtrl*)args[1].GetLightUserData();

	RUGE::CRect rect;

	pCtrl->GetRect(&rect);

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("Left", rect.x1);
	table.SetNumber("Top", rect.y1);
	table.SetNumber("Right", rect.x2);
	table.SetNumber("Bottom", rect.y2);
	return 1;
}

int Control_GetColor(HCONTROL hCtrl)
{
	return ((CCustomCtrl*)hCtrl)->GetColor();
}

int Lua_Control_GetAttribute(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	CCustomCtrl *pCtrl=NULL;

	if (args.Count()==1 && args[1].IsLightUserData()) pCtrl=(CCustomCtrl*)args[1].GetLightUserData();

	TableCopy(&lua->CreateTable(), &pCtrl->GetLua()->GetGlobal("Attribute"));
	return 1;
}