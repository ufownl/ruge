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
#include "CustomScene.h"
#include "Register.h"

CCustomScene::CCustomScene(int nID, LPCSTR lpcszPath)
	: RUGE::CScene(nID)
	, m_luaState(true)
{
	RegisterAPI(m_luaState);
	m_luaState->CheckStack(LUA_STACKSIZE);
	if (m_luaState->DoFile(lpcszPath))
	{
		printf("Error: %sΩ≈±æ¥ÌŒÛ\n", lpcszPath);
		system("pause");
	}
}

CCustomScene::~CCustomScene()
{
}

int CCustomScene::GetID() const
{
	return m_nID;
}

RUGE::CSceneManager* CCustomScene::GetManager() const
{
	return m_pSceneManager;
}

LuaPlus::LuaState* CCustomScene::GetLua() const
{
	return m_luaState;
}

void CCustomScene::Render()
{
	if (m_luaState->GetGlobal("Render").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Render=m_luaState->GetGlobal("Render");

		Lua_Render(this);
	}
}

BOOL CCustomScene::Update(float fDelta)
{
	if (m_luaState->GetGlobal("Update").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_Update=m_luaState->GetGlobal("Update");

		return (BOOL)Lua_Update(this, fDelta);
	}
	return FALSE;
}

void CCustomScene::Exit()
{
	if (m_luaState->GetGlobal("Exit").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Exit=m_luaState->GetGlobal("Exit");

		Lua_Exit(this);
	}
}