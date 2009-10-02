/*
RUGE Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE.

RUGE is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "Control.h"

CControl::CControl(int nID)
	: m_pApp(GetRUGE())
	, m_pGUI(NULL)
	, m_nID(nID)
	, m_bStatic(FALSE)
	, m_bVisible(TRUE)
	, m_bEnabled(TRUE)
	, m_bManaged(FALSE)
	, m_dwColor(0xFFFFFFFF)
	, m_pPrev(NULL)
	, m_pNext(NULL)
{
}

CControl::~CControl()
{
	m_pApp->Release();
}

void CControl::Update(float fDelta)
{
}

void CControl::Enter()
{
}

void CControl::Exit()
{
}

void CControl::Reset()
{
}

BOOL CControl::IsDone()
{
	return TRUE;
}

void CControl::Focus(BOOL bFocused)
{
}

void CControl::MouseOver(BOOL bOver)
{
}

BOOL CControl::MouseMove(float x, float y)
{
	return FALSE;
}

BOOL CControl::MouseLBtn(BOOL bDown)
{
	return FALSE;
}

BOOL CControl::MouseRBtn(BOOL bDown)
{
	return FALSE;
}

BOOL CControl::MouseWheel(SHORT nWheel)
{
	return FALSE;
}

BOOL CControl::KeyClick(int nVKey, char chChar)
{
	return FALSE;
}

void CControl::SetColor(DWORD dwColor)
{
	m_dwColor=dwColor;
}