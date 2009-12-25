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

#include "StdAfx.h"
#include "RugeLuaAnimation.h"
#include <Animation.h>

HANIMATION Animation_Create(RUGE::HTEXTURE hTex, int nFrames, float FPS, float x, float y, float w, float h)
{
	return new RUGE::CAnimation(hTex, nFrames, FPS, x, y, w, h);
}

void Animation_Free(HANIMATION hAnim)
{
	delete (RUGE::CAnimation*)hAnim;
}

HANIMATION Animation_Assign(HANIMATION hDst, HANIMATION hSrc)
{
	*(RUGE::CAnimation*)hDst=*(RUGE::CAnimation*)hSrc;
	return hDst;
}

void Animation_Play(HANIMATION hAnim)
{
	((RUGE::CAnimation*)hAnim)->Play();
}

void Animation_Stop(HANIMATION hAnim)
{
	((RUGE::CAnimation*)hAnim)->Stop();
}

void Animation_Resume(HANIMATION hAnim)
{
	((RUGE::CAnimation*)hAnim)->Resume();
}

void Animation_Update(HANIMATION hAnim, float fDelta)
{
	((RUGE::CAnimation*)hAnim)->Update(fDelta);
}

bool Animation_IsPlaying(HANIMATION hAnim)
{
	return ((RUGE::CAnimation*)hAnim)->IsPlaying() ? true : false;
}

void Animation_SetMode(HANIMATION hAnim, int nMode)
{
	((RUGE::CAnimation*)hAnim)->SetMode(nMode);
}

void Animation_SetSpeed(HANIMATION hAnim, float FPS)
{
	((RUGE::CAnimation*)hAnim)->SetSpeed(FPS);
}

void Animation_SetFrame(HANIMATION hAnim, int n)
{
	((RUGE::CAnimation*)hAnim)->SetFrame(n);
}

void Animation_SetFrames(HANIMATION hAnim, int n)
{
	((RUGE::CAnimation*)hAnim)->SetFrames(n);
}

int Animation_GetMode(HANIMATION hAnim)
{
	return ((RUGE::CAnimation*)hAnim)->GetMode();
}

float Animation_GetSpeed(HANIMATION hAnim)
{
	return ((RUGE::CAnimation*)hAnim)->GetSpeed();
}

int Animation_GetFrame(HANIMATION hAnim)
{
	return ((RUGE::CAnimation*)hAnim)->GetFrame();
}

int Animation_GetFrames(HANIMATION hAnim)
{
	return ((RUGE::CAnimation*)hAnim)->GetFrames();
}