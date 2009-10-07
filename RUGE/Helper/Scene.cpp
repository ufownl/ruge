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
#include "Scene.h"

namespace RUGE
{

	CScene::CScene(int nID)
		: m_pApp(GetRUGE())
		, m_pSceneManager(NULL)
		, m_nID(nID)
		, m_bManaged(FALSE)
		, m_pNext(NULL)
	{
	}

	CScene::~CScene()
	{
		m_pApp->Release();
	}

	BOOL CScene::Update(float fDelta)
	{
		return FALSE;
	}

	BOOL CScene::Enter(WPARAM wParam, LPARAM lParam)
	{
		return TRUE;
	}

	void CScene::Exit()
	{
	}

}