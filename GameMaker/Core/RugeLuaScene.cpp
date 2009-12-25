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
#include "RugeLuaScene.h"
#include "CustomScene.h"
#include "Table.h"

int Lua_Scene_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nID=0;
	LPCSTR lpcszPath=NULL;
	CCustomScene *pScene=NULL;
	
	if (args.Count()>=2)
	{
		if (args[1].IsInteger()) nID=args[1].GetInteger();
		if (args[2].IsString()) lpcszPath=args[2].GetString();
		pScene=new CCustomScene(nID, lpcszPath);
		if (args.Count()>=3 && args[3].IsTable()) TableCopy(&pScene->GetLua()->GetGlobals().CreateTable("Attribute"), &args[3]);
	}
	if (pScene->GetLua()->GetGlobal("Construct").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Construct=pScene->GetLua()->GetGlobal("Construct");

		Lua_Construct(pScene);
	}

	lua->PushLightUserData(pScene);
	return 1;
}

void Scene_Free(HSCENE hScene)
{
	delete (CCustomScene*)hScene;
}

int Lua_Scene_SetAttribute(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	CCustomScene *pScene=NULL;
	LuaPlus::LuaStackObject Attr;

	if (args.Count()==2)
	{
		if (args[1].IsLightUserData()) pScene=(CCustomScene*)args[1].GetLightUserData();
		if (args[2].IsTable()) Attr=args[2];
	}
	TableCopy(&pScene->GetLua()->GetGlobal("Attribute"), &Attr);
	return 0;
}

int Scene_GetID(HSCENE hScene)
{
	return ((CCustomScene*)hScene)->GetID();
}

HSCENEMANAGER Scene_GetManager(HSCENE hScene)
{
	return ((CCustomScene*)hScene)->GetManager();
}

int Lua_Scene_GetAttribute(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	CCustomScene *pScene=NULL;

	if (args.Count()==1 && args[1].IsLightUserData()) pScene=(CCustomScene*)args[1].GetLightUserData();

	TableCopy(&lua->CreateTable(), &pScene->GetLua()->GetGlobal("Attribute"));
	return 1;
}