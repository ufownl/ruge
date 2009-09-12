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
