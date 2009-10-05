/*
RUGE Copyright (C) 2009 ����UFO

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

#pragma once

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "Scene.h"

class CSceneManager
{
public:
	CSceneManager();
	virtual ~CSceneManager();

	void AddScene(CScene *pScene, BOOL bManaged=TRUE);
	void DelScene(int nID);
	CScene* GetScene(int nID) const;
	CScene* Switch(int nID, WPARAM wParam=0, LPARAM lParam=0);

	BOOL Update(float fDelta);
	void Render();

protected:
	CSceneManager(const CSceneManager &SceneManager);
	CSceneManager& operator = (const CSceneManager &SceneManager);

protected:
	CScene *m_pSceneList, *m_pScene;
};

#endif  // _SCENEMANAGER_H_
