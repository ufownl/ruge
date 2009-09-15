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
#include "Animation.h"

CAnimation::CAnimation(HTEXTURE hTex, int nFrames, float FPS, float x, float y, float w, float h)
	: CSprite(hTex, x, y, w, h)
{
	m_fSinceLastFrame=-1.0f;
	SetSpeed(FPS);
	Stop();
	SetFrames(nFrames);
	SetMode(ANIM_DEFAULT);
	SetFrame(0);
}

CAnimation::CAnimation(const CAnimation &Anim)
	: CSprite(Anim)
	, m_bPlaying(Anim.m_bPlaying)
	, m_fSpeed(Anim.m_fSpeed)
	, m_fSinceLastFrame(Anim.m_fSinceLastFrame)
	, m_dwMode(Anim.m_dwMode)
	, m_nDelta(Anim.m_nDelta)
	, m_nFrames(Anim.m_nFrames)
	, m_nCurFrame(Anim.m_nCurFrame)
{
}

CAnimation::~CAnimation()
{
}

CAnimation& CAnimation::operator = (const CAnimation &Anim)
{
	if (this!=&Anim)
	{
		*(CSprite*)this=Anim;
		m_bPlaying=Anim.m_bPlaying;
		m_fSpeed=Anim.m_fSpeed;
		m_fSinceLastFrame=Anim.m_fSinceLastFrame;
		m_dwMode=Anim.m_dwMode;
		m_nDelta=Anim.m_nDelta;
		m_nFrames=Anim.m_nFrames;
		m_nCurFrame=Anim.m_nCurFrame;
	}
	return *this;
}

void CAnimation::Play()
{
	m_bPlaying=true;
	m_fSinceLastFrame=-1.0f;
	if (m_dwMode & ANIM_REV)
	{
		m_nDelta=-1;
		SetFrame(m_nFrames-1);
	}
	else
	{
		m_nDelta=1;
		SetFrame(0);
	}
}

void CAnimation::Stop()
{
	m_bPlaying=false;
}

void CAnimation::Resume()
{
	m_bPlaying=true;
}

void CAnimation::Update(float fDeltaTime)
{
	if (!m_bPlaying) return;
	if (m_fSinceLastFrame==-1.0f) m_fSinceLastFrame=0.0f;
	else m_fSinceLastFrame+=fDeltaTime;
	while (m_fSinceLastFrame>=m_fSpeed)
	{
		m_fSinceLastFrame-=m_fSpeed;
		if (m_nCurFrame+m_nDelta==m_nFrames)
		{
			switch (m_dwMode)
			{
			case ANIM_FWD:
			case ANIM_REV | ANIM_PINGPONG:
				m_bPlaying = false;
				break;

			case ANIM_FWD | ANIM_PINGPONG:
			case ANIM_FWD | ANIM_PINGPONG | ANIM_LOOP:
			case ANIM_REV | ANIM_PINGPONG | ANIM_LOOP:
				m_nDelta=-m_nDelta;
				break;
			}
		}
		else if (m_nCurFrame+m_nDelta<0)
		{
			switch (m_dwMode)
			{
			case ANIM_REV:
			case ANIM_FWD | ANIM_PINGPONG:
				m_bPlaying = false;
				break;

			case ANIM_REV | ANIM_PINGPONG:
			case ANIM_REV | ANIM_PINGPONG | ANIM_LOOP:
			case ANIM_FWD | ANIM_PINGPONG | ANIM_LOOP:
				m_nDelta=-m_nDelta;
				break;
			}
		}
		if (m_bPlaying) SetFrame(m_nCurFrame+m_nDelta);
	}
}

bool CAnimation::IsPlaying() const
{
	return m_bPlaying;
}

void CAnimation::SetMode(DWORD dwMode)
{
	m_dwMode=dwMode;
	if(dwMode & ANIM_REV)
	{
		m_nDelta=-1;
		SetFrame(m_nFrames-1);
	}
	else
	{
		m_nDelta=1;
		SetFrame(0);
	}
}

void CAnimation::SetSpeed(float FPS)
{
	if (FPS<=0.0f) FPS=1.0f;
	m_fSpeed=1.0f/FPS;
}

void CAnimation::SetFrame(int n)
{
	int nTexWidth=m_pApp->Texture_GetWidth(m_quadTex.hTex),
		nTexHeight=m_pApp->Texture_GetHeight(m_quadTex.hTex);
	int nCols=nTexWidth/(int)m_fWidth;

	n%=m_nFrames;
	if (n<0) n+=m_nFrames;
	m_nCurFrame=n;

	float tx1=m_fLeft+n*m_fWidth, ty1=m_fTop;

	if (tx1>nTexWidth-m_fWidth)
	{
		n-=(nTexWidth-(int)m_fLeft)/(int)m_fWidth;
		tx1=m_fWidth*(n%nCols);
		ty1+=m_fHeight*(1+n/nCols);
	}

	float tx2=tx1+m_fWidth, ty2=ty1+m_fHeight;

	tx1/=nTexWidth;
	ty1/=nTexHeight;
	tx2/=nTexWidth;
	ty2/=nTexHeight;
	m_quadTex.v[0].tu=tx1;
	m_quadTex.v[0].tv=ty1;
	m_quadTex.v[1].tu=tx2;
	m_quadTex.v[1].tv=ty1;
	m_quadTex.v[2].tu=tx2;
	m_quadTex.v[2].tv=ty2;
	m_quadTex.v[3].tu=tx1;
	m_quadTex.v[3].tv=ty2;
}

void CAnimation::SetFrames(int n)
{
	if (n<1) n=1;
	m_nFrames=n;
}

DWORD CAnimation::GetMode() const
{
	return m_dwMode;
}

float CAnimation::GetSpeed() const
{
	return 1.0f/m_fSpeed;
}

int CAnimation::GetFrame() const
{
	return m_nCurFrame;
}

int CAnimation::GetFrames() const
{
	return m_nFrames;
}
