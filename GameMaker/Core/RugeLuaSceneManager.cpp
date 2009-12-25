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
#include "RugeLuaSceneManager.h"
#include "CustomScene.h"
#include "Table.h"
#include <SceneManager.h>


HSCENEMANAGER SceneManager_Create()
{
	return new RUGE::CSceneManager();
}

void SceneManager_Free(HSCENEMANAGER hSceneManager)
{
	delete (RUGE::CSceneManager*)hSceneManager;
}

int Lua_SceneManager_AddScene(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSceneManager *pSceneManager=NULL;
	RUGE::CScene *pScene=NULL;
	BOOL bManaged=TRUE;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsBoolean()) bManaged=(BOOL)args[3].GetBoolean();
	case 2:
		if (args[1].IsLightUserData()) pSceneManager=(RUGE::CSceneManager*)args[1].GetLightUserData();
		if (args[2].IsLightUserData()) pScene=(RUGE::CScene*)args[2].GetLightUserData();
		break;
	}
	pSceneManager->AddScene(pScene, bManaged);
	return 0;
}

void SceneManager_DelScene(HSCENEMANAGER hSceneManager, int nID)
{
	((RUGE::CSceneManager*)hSceneManager)->DelScene(nID);
}

HSCENE SceneManager_GetScene(HSCENEMANAGER hSceneManager, int nID)
{
	return ((RUGE::CSceneManager*)hSceneManager)->GetScene(nID);
}

int Lua_SceneManager_Switch(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSceneManager *pSceneManager=NULL;
	int nID=0;

	switch (args.Count())
	{
	case 3:
	case 2:
		if (args[1].IsLightUserData()) pSceneManager=(RUGE::CSceneManager*)args[1].GetLightUserData();
		if (args[2].IsInteger()) nID=args[2].GetInteger();
		break;
	}
	
	CCustomScene *pScene=(CCustomScene*)pSceneManager->Switch(nID);
	
	if (pScene!=NULL)
	{
		if (pScene->GetLua()->GetGlobal("Enter").IsFunction())
		{
			LuaPlus::LuaFunction<bool> Lua_Enter=pScene->GetLua()->GetGlobal("Enter");
			bool bRes=false;

			if (args.Count()==3 && args[3].IsTable())
			{
				LuaPlus::LuaStackObject Param=pScene->GetLua()->CreateTable();

				TableCopy(&Param, &args[3]);
				bRes=Lua_Enter(pScene, Param);
			}
			else bRes=Lua_Enter(pScene);
			if (!bRes) pScene=(CCustomScene*)pSceneManager->Switch(-1);
		}
	}
	lua->PushLightUserData(pScene);
	return 1;
}

bool SceneManager_Update(HSCENEMANAGER hSceneManager, float fDelta)
{
	return ((RUGE::CSceneManager*)hSceneManager)->Update(fDelta) ? true : false;
}

void SceneManager_Render(HSCENEMANAGER hSceneManager)
{
	((RUGE::CSceneManager*)hSceneManager)->Render();
}