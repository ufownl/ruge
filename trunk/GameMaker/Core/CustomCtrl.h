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

#include <GUI.h>

class CCustomCtrl : public RUGE::CControl
{
public:
	CCustomCtrl(int nID, LPCSTR lpcszPath);
	virtual ~CCustomCtrl();

	void SetStatic(BOOL bStatic);
	void SetVisible(BOOL bVisible);
	void SetEnabled(BOOL bEnabled);
	void SetRect(RUGE::CRect *pRect);
	virtual void SetColor(DWORD dwColor);

	RUGE::CGUI* GetGUI() const;
	int GetID() const;
	BOOL GetStatic() const;
	BOOL GetVisible() const;
	BOOL GetEnabled() const;
	void GetRect(RUGE::CRect *pRect) const;
	DWORD GetColor() const;
	LuaPlus::LuaState* GetLua() const;

protected:
	virtual void Render();
	virtual void Update(float fDelta);

	virtual void Enter();
	virtual void Exit();
	virtual void Reset();
	virtual BOOL IsDone();
	virtual void Focus(BOOL bFocused);
	virtual void MouseOver(BOOL bOver);

	virtual BOOL MouseMove(float x, float y);
	virtual BOOL MouseLBtn(BOOL bDown, float x, float y);
	virtual BOOL MouseRBtn(BOOL bDown, float x, float y);
	virtual BOOL MouseWheel(SHORT nWheel);
	virtual BOOL KeyClick(int nVKey, char chChar);

protected:
	LuaPlus::LuaStateOwner m_luaState;
};
