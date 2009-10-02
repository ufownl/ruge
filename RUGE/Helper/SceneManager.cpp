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
#include "SceneManager.h"

CSceneManager::CSceneManager()
	: m_pScene(NULL)
{
}

CSceneManager::CSceneManager(PSCENE pScene)
	: m_pScene(NULL)
{
	SwitchScene(pScene);
}

CSceneManager::~CSceneManager()
{
	if (m_pScene!=NULL) m_pScene->ExitScene();
}

CSceneManager& CSceneManager::operator = (PSCENE pScene)
{
	SwitchScene(pScene);
	return *this;
}

BOOL CSceneManager::SwitchScene(PSCENE pScene, WPARAM wParam/* =0 */, LPARAM lParam/* =0 */)
{
	if (m_pScene!=NULL) m_pScene->ExitScene();
	m_pScene=pScene;
	if (m_pScene!=NULL) return m_pScene->EnterScene(wParam, lParam);
	return TRUE;
}

BOOL CSceneManager::Update(float fDelta)
{
	if (m_pScene!=NULL) return m_pScene->Update(this, fDelta);
	return FALSE;
}

void CSceneManager::Render()
{
	if (m_pScene!=NULL) m_pScene->Render();
}
