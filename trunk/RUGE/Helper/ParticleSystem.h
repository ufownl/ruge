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

#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "Sprite.h"
#include "Vector.h"
#include "Color.h"

#define MAX_PARTICLES	500

#ifndef M_PI
#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f
#define M_PI_4	0.785398163397448309616f
#define M_1_PI	0.318309886183790671538f
#define M_2_PI	0.636619772367581343076f
#endif

typedef struct PARTICLE
{
	CVector vecLocation, vecVelocity;
	float fGravity, fRadialAccel, fTangentialAccel;
	float fSpin, fSpinDelta;
	float fSize, fSizeDelta;
	CColor colColor, colColorDelta;
	float fAge, fTerminalAge;
} *PPARTICLE;

typedef struct PARTICLESYSTEMINFO
{
	CSprite *pSprite;  // texture + blend mode
	int nEmission;  // particles per sec
	float fLifetime;
	float fParticleLifeMin, fParticleLifeMax;
	float fDirection, fSpread;
	bool bRelative;
	float fSpeedMin, fSpeedMax;
	float fGravityMin, fGravityMax;
	float fRadialAccelMin, fRadialAccelMax;
	float fTangentialAccelMin, fTangentialAccelMax;
	float fSizeStart, fSizeEnd, fSizeVar;
	float fSpinStart, fSpinEnd, fSpinVar;
	CColor colColorStart, colColorEnd;
	float fColorVar, fAlphaVar;
} *PPARTICLESYSTEMINFO;

class CParticleSystem
{
public:
	CParticleSystem(const char *pcszPath, CSprite *pSpr);
	CParticleSystem(PPARTICLESYSTEMINFO pPsi);
	CParticleSystem(const CParticleSystem &ps);
	virtual ~CParticleSystem();

	CParticleSystem& operator = (const CParticleSystem &ps);

	void Render();
	void Fire();
	void FireAt(float x, float y);
	void Stop(bool bKillParticles=false);
	void Update(float fDeltaTime);
	void MoveTo(float x, float y, bool bMoveParticles=false);
	void Transpose(float x, float y);
	void SetScale(float fScale);
	void TrackBoundingBox(bool bTrack);

	int GetParticlesAlive() const;
	float GetAge() const;
	void GetPosition(float *x, float *y) const;
	void GetTransposition(float &x, float &y) const;
	float GetScale() const;
	CRect* GetBoundingBox(CRect *pRect) const;

public:
	PARTICLESYSTEMINFO m_Info;

protected:
	IRandomPtr m_pRandom;
	float m_fAge, m_fEmissionResidue;
	CVector m_vecPrevLocation, m_vecLocation;
	float m_fTx, m_fTy, m_fScale;
	int m_nParticlesAlive;
	CRect m_rectBoundingBox;
	bool m_bUpdateBoundingBox;
	PARTICLE m_Particles[MAX_PARTICLES];
};

#endif  // _PARTICLESYSTEM_H_
