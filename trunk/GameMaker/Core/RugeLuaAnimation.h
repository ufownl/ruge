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

#include "RugeLuaSprite.h"

#define ANIM_FWD		0L
#define ANIM_REV		1L
#define ANIM_PINGPONG	2L
#define ANIM_NOPINGPONG	0L
#define ANIM_LOOP		4L
#define ANIM_NOLOOP		0L
#define ANIM_DEFAULT	(ANIM_FWD|ANIM_LOOP)

typedef HANDLE HANIMATION;

HANIMATION Animation_Create(RUGE::HTEXTURE hTex, int nFrames, float FPS, float x, float y, float w, float h);
void Animation_Free(HANIMATION hAnim);

HANIMATION Animation_Assign(HANIMATION hDst, HANIMATION hSrc);

void Animation_Play(HANIMATION hAnim);
void Animation_Stop(HANIMATION hAnim);
void Animation_Resume(HANIMATION hAnim);
void Animation_Update(HANIMATION hAnim, float fDelta);
bool Animation_IsPlaying(HANIMATION hAnim);

void Animation_SetMode(HANIMATION hAnim, int nMode);
void Animation_SetSpeed(HANIMATION hAnim, float FPS);
void Animation_SetFrame(HANIMATION hAnim, int n);
void Animation_SetFrames(HANIMATION hAnim, int n);

int Animation_GetMode(HANIMATION hAnim);
float Animation_GetSpeed(HANIMATION hAnim);
int Animation_GetFrame(HANIMATION hAnim);
int Animation_GetFrames(HANIMATION hAnim);