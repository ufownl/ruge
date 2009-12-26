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
#include "CustomCtrl.h"
#include "Register.h"

CCustomCtrl::CCustomCtrl(int nID, LPCSTR lpcszPath)
	: RUGE::CControl(nID)
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

CCustomCtrl::~CCustomCtrl()
{
	if (m_luaState->GetGlobal("Deconstruct").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Deconstruct=m_luaState->GetGlobal("Deconstruct");

		Lua_Deconstruct(this);
	}
}

void CCustomCtrl::SetStatic(BOOL bStatic)
{
	m_bStatic=bStatic;
}

void CCustomCtrl::SetVisible(BOOL bVisible)
{
	m_bVisible=bVisible;
}

void CCustomCtrl::SetEnabled(BOOL bEnabled)
{
	m_bEnabled=bEnabled;
}

void CCustomCtrl::SetRect(RUGE::CRect *pRect)
{
	m_Rect=*pRect;
}

void CCustomCtrl::SetColor(DWORD dwColor)
{
	RUGE::CControl::SetColor(dwColor);
	if (m_luaState->GetGlobal("SetColor").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_SetColor=m_luaState->GetGlobal("SetColor");

		Lua_SetColor(this, dwColor);
	}
}

RUGE::CGUI* CCustomCtrl::GetGUI() const
{
	return m_pGUI;
}

int CCustomCtrl::GetID() const
{
	return m_nID;
}

BOOL CCustomCtrl::GetStatic() const
{
	return m_bStatic;
}

BOOL CCustomCtrl::GetVisible() const
{
	return m_bVisible;
}

BOOL CCustomCtrl::GetEnabled() const
{
	return m_bEnabled;
}

void CCustomCtrl::GetRect(RUGE::CRect *pRect) const
{
	*pRect=m_Rect;
}

DWORD CCustomCtrl::GetColor() const
{
	return m_dwColor;
}

LuaPlus::LuaState* CCustomCtrl::GetLua() const
{
	return m_luaState;
}

void CCustomCtrl::Render()
{
	if (m_luaState->GetGlobal("Render").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Render=m_luaState->GetGlobal("Render");

		Lua_Render(this);
	}
}

void CCustomCtrl::Update(float fDelta)
{
	if (m_luaState->GetGlobal("Update").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Update=m_luaState->GetGlobal("Update");

		Lua_Update(this, fDelta);
	}
}

void CCustomCtrl::Enter()
{
	if (m_luaState->GetGlobal("Enter").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Enter=m_luaState->GetGlobal("Enter");

		Lua_Enter(this);
	}
}

void CCustomCtrl::Exit()
{
	if (m_luaState->GetGlobal("Exit").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Exit=m_luaState->GetGlobal("Exit");

		Lua_Exit(this);
	}
}

void CCustomCtrl::Reset()
{
	if (m_luaState->GetGlobal("Reset").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Reset=m_luaState->GetGlobal("Reset");

		Lua_Reset(this);
	}
}

BOOL CCustomCtrl::IsDone()
{
	BOOL bRes=FALSE;

	if (m_luaState->GetGlobal("IsDone").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_IsDone=m_luaState->GetGlobal("IsDone");

		bRes=(BOOL)Lua_IsDone(this);
	}
	return bRes;
}

void CCustomCtrl::Focus(BOOL bFocused)
{
	if (m_luaState->GetGlobal("Focus").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_Focus=m_luaState->GetGlobal("Focus");

		Lua_Focus(this, bFocused ? true : false);
	}
}

void CCustomCtrl::MouseOver(BOOL bOver)
{
	if (m_luaState->GetGlobal("MouseOver").IsFunction())
	{
		LuaPlus::LuaFunction<void> Lua_MouseOver=m_luaState->GetGlobal("MouseOver");

		Lua_MouseOver(this, bOver ? true : false);
	}
}

BOOL CCustomCtrl::MouseMove(float x, float y)
{
	BOOL bRes=FALSE;

	if (m_luaState->GetGlobal("MouseMove").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_MouseMove=m_luaState->GetGlobal("MouseMove");

		bRes=(BOOL)Lua_MouseMove(this, x, y);
	}
	return bRes;
}

BOOL CCustomCtrl::MouseLBtn(BOOL bDown, float x, float y)
{
	BOOL bRes=FALSE;

	if (m_luaState->GetGlobal("MouseLBtn").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_MouseLBtn=m_luaState->GetGlobal("MouseLBtn");

		bRes=(BOOL)Lua_MouseLBtn(this, bDown ? true : false, x, y);
	}
	return bRes;
}

BOOL CCustomCtrl::MouseRBtn(BOOL bDown, float x, float y)
{
	BOOL bRes=FALSE;

	if (m_luaState->GetGlobal("MouseRBtn").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_MouseRBtn=m_luaState->GetGlobal("MouseRBtn");

		bRes=(BOOL)Lua_MouseRBtn(this, bDown ? true : false, x, y);
	}
	return bRes;
}

BOOL CCustomCtrl::MouseWheel(SHORT nWheel)
{
	BOOL bRes=FALSE;

	if (m_luaState->GetGlobal("MouseWheel").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_MouseWheel=m_luaState->GetGlobal("MouseWheel");

		bRes=(BOOL)Lua_MouseWheel(this, nWheel);
	}
	return bRes;
}

BOOL CCustomCtrl::KeyClick(int nVKey, char chChar)
{
	BOOL bRes=FALSE;

	if (m_luaState->GetGlobal("KeyClick").IsFunction())
	{
		LuaPlus::LuaFunction<bool> Lua_KeyClick=m_luaState->GetGlobal("KeyClick");

		bRes=(BOOL)Lua_KeyClick(this, nVKey, (int)chChar);
	}
	return bRes;
}
