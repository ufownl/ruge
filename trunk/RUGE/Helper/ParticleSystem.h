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

#ifndef _RUGE_PARTICLESYSTEM_H_
#define _RUGE_PARTICLESYSTEM_H_

#include "Sprite.h"
#include "Vector.h"
#include "Color.h"

#define MAX_PARTICLES	500

namespace RUGE
{

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
		CSprite *pSprite;
		int nEmission;
		float fLifetime;
		float fParticleLifeMin, fParticleLifeMax;
		float fDirection, fSpread;
		BOOL bRelative;
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
		void Stop(BOOL bKillParticles=FALSE);
		void Update(float fDelta);
		void MoveTo(float x, float y, BOOL bMoveParticles=FALSE);
		void Transpose(float x, float y);
		void SetScale(float fScale);
		void TrackBoundingBox(BOOL bTrack);

		int GetParticlesAlive() const;
		float GetAge() const;
		void GetPosition(float *x, float *y) const;
		void GetTransposition(float *x, float *y) const;
		float GetScale() const;
		CRect* GetBoundingBox(CRect *pRect) const;

	public:
		PARTICLESYSTEMINFO m_Info;

	protected:
		PAPPLICATION m_pApp;
		float m_fAge, m_fEmissionResidue;
		CVector m_vecPrevLocation, m_vecLocation;
		float m_fTx, m_fTy, m_fScale;
		int m_nParticlesAlive;
		CRect m_rectBoundingBox;
		BOOL m_bUpdateBoundingBox;
		PARTICLE m_Particles[MAX_PARTICLES];
	};

}

#endif  // _RUGE_PARTICLESYSTEM_H_
