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

#pragma once

#ifndef _RUGE_SCENE_H_
#define _RUGE_SCENE_H_

namespace RUGE
{

	class CScene
	{
		friend class CSceneManager;

	public:
		CScene(int nID);
		virtual ~CScene();

	protected:
		virtual void Render()=0;
		virtual BOOL Update(float fDelta);

		virtual BOOL Enter(WPARAM wParam, LPARAM lParam);
		virtual void Exit();

	protected:
		PAPPLICATION m_pApp;
		CSceneManager *m_pSceneManager;
		int m_nID;
		BOOL m_bManaged;
		CScene *m_pNext;
	};

}

#endif  // _RUGE_SCENE_H_