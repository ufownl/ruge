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

#ifndef _SCENE_H_
#define _SCENE_H_

class CSceneManager;

typedef struct IScene
{
	virtual BOOL EnterScene(WPARAM wParam, LPARAM lParam)=0;
	virtual void ExitScene()=0;
	virtual BOOL Update(CSceneManager *pSceneManager, float fDelta)=0;
	virtual void Render()=0;
} *PSCENE;

#endif  // _SCENE_H_