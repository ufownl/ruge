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

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "sprite.h"

#define ANIM_FWD		0L
#define ANIM_REV		1L
#define ANIM_PINGPONG	2L
#define ANIM_NOPINGPONG	0L
#define ANIM_LOOP		4L
#define ANIM_NOLOOP		0L
#define ANIM_DEFAULT	(ANIM_FWD|ANIM_LOOP)

class CAnimation : public CSprite
{
public:
	CAnimation(HTEXTURE hTex, int nFrames, float FPS, float x, float y, float w, float h);
	CAnimation(const CAnimation &Anim);
	virtual ~CAnimation();

	CAnimation& CAnimation::operator = (const CAnimation &Anim);

	void Play();
	void Stop();
	void Resume();
	void Update(float fDeltaTime);
	bool IsPlaying() const;

	void SetMode(DWORD dwMode);
	void SetSpeed(float FPS);
	void SetFrame(int n);
	void SetFrames(int n);

	DWORD GetMode() const;
	float GetSpeed() const;
	int GetFrame() const;
	int GetFrames() const;

protected:
	bool m_bPlaying;
	float m_fSpeed, m_fSinceLastFrame;
	DWORD m_dwMode;
	int m_nDelta, m_nFrames, m_nCurFrame;
};

#endif  // _ANIMATION_H_
