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

namespace RUGE
{

	CSceneManager::CSceneManager()
		: m_pSceneList(NULL)
		, m_pScene(NULL)
	{
	}

	CSceneManager::~CSceneManager()
	{
		if (m_pScene!=NULL) m_pScene->Exit();
		while (m_pSceneList!=NULL)
		{
			CScene *pScene=m_pSceneList;

			m_pSceneList=m_pSceneList->m_pNext;
			if (pScene->m_bManaged) delete pScene;
		}
	}

	void CSceneManager::AddScene(CScene *pScene, BOOL bManaged/* =TRUE */)
	{
		pScene->m_pSceneManager=this;
		pScene->m_bManaged=bManaged;
		pScene->m_pNext=m_pSceneList;
		m_pSceneList=pScene;
	}

	void CSceneManager::DelScene(int nID)
	{
		if (m_pSceneList->m_nID==nID)
		{
			CScene *pScene=m_pSceneList;

			m_pSceneList=m_pSceneList->m_pNext;
			if (pScene->m_bManaged) delete pScene;
		}
		else
		{
			for (CScene *p=m_pSceneList; p->m_pNext!=NULL; p=p->m_pNext)
			{
				if (p->m_pNext->m_nID==nID)
				{
					CScene *pScene=p->m_pNext;

					p->m_pNext=pScene->m_pNext;
					if (pScene->m_bManaged) delete pScene;
					break;
				}
			}
		}
	}

	CScene* CSceneManager::GetScene(int nID) const
	{
		for (CScene *p=m_pSceneList; p!=NULL; p=p->m_pNext)
		{
			if (p->m_nID==nID) return p;
		}
		return NULL;
	}

	CScene* CSceneManager::Switch(int nID, WPARAM wParam/* =0 */, LPARAM lParam/* =0 */)
	{
		CScene *pScene=GetScene(nID);

		if (pScene==NULL) return NULL;
		if (m_pScene!=NULL) m_pScene->Exit();
		if (pScene->Enter(wParam, lParam)) m_pScene=pScene;
		else m_pScene=NULL;
		return m_pScene;
	}

	BOOL CSceneManager::Update(float fDelta)
	{
		if (m_pScene!=NULL) return m_pScene->Update(fDelta);
		return FALSE;
	}

	void CSceneManager::Render()
	{
		if (m_pScene!=NULL) m_pScene->Render();
	}

}